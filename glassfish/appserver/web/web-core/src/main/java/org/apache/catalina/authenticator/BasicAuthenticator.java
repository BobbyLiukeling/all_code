/*
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.catalina.authenticator;

import org.apache.catalina.HttpRequest;
import org.apache.catalina.HttpResponse;
import org.apache.catalina.deploy.LoginConfig;
import org.apache.catalina.util.Base64;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.charset.Charset;
import java.security.Principal;
import java.util.Locale;
import java.util.logging.Level;

/**
 * An <b>Authenticator</b> and <b>Valve</b> implementation of HTTP BASIC
 * Authentication, as outlined in RFC 2617:  "HTTP Authentication: Basic
 * and Digest Access Authentication."
 *
 * @author Craig R. McClanahan
 * @version $Revision: 1.7 $ $Date: 2007/05/05 05:31:52 $
 */

public class BasicAuthenticator
    extends AuthenticatorBase {

    // --------------------------------------------------- Instance Variables


    /**
     * Descriptive information about this implementation.
     */
    protected static final String info =
        "org.apache.catalina.authenticator.BasicAuthenticator/1.0";


    // ----------------------------------------------------------- Properties


    /**
     * Return descriptive information about this Valve implementation.
     */
    @Override
    public String getInfo() {
        return (this.info);
    }


    // ------------------------------------------------------- Public Methods


    /**
     * Authenticate the user making this request, based on the specified
     * login configuration.  Return <code>true</code> if any specified
     * constraint has been satisfied, or <code>false</code> if we have
     * created a response challenge already.
     *
     * @param request Request we are processing
     * @param response Response we are creating
     * @param config Login configuration describing how authentication
     * should be performed
     *
     * @exception IOException if an input/output error occurs
     */
    @Override
    public boolean authenticate(HttpRequest request,
                                HttpResponse response,
                                LoginConfig config)
        throws IOException {

        // Have we already authenticated someone?
        Principal principal =
            ((HttpServletRequest) request.getRequest()).getUserPrincipal();
        if (principal != null) {
            if (log.isLoggable(Level.FINE))
                log.log(Level.FINE, "Already authenticated '" + principal.getName() + "'");
            return (true);
        }

        // Validate any credentials already included with this request
        HttpServletResponse hres =
            (HttpServletResponse) response.getResponse();
        String authorization = request.getAuthorization();

        /* IASRI 4868073 
        String username = parseUsername(authorization);
        String password = parsePassword(authorization);
        principal = context.getRealm().authenticate(username, password);
        if (principal != null) {
            register(request, response, principal, Constants.BASIC_METHOD,
                     username, password);
            return (true);
        }
        */
        // BEGIN IASRI 4868073
        // Only attempt to parse and validate the authorization if one was
        // sent by the client. No reason to attempt to login with null
        // authorization which must fail anyway. With basic auth this
        // scenario always occurs first so this is a common case. This
        // will also prevent logging the audit message for failure to
        // authenticate null user (since login failures are always logged
        // per psarc req).

        if (authorization != null) {
            String username = parseUsername(authorization);
            char[] password = parsePassword(authorization);
            principal = context.getRealm().authenticate(username, password);
            if (principal != null) {
                register(request, response, principal, Constants.BASIC_METHOD,
                         username, password);
                String ssoId = (String) request.getNote(
                    Constants.REQ_SSOID_NOTE);
                if (ssoId != null) {
                    getSession(request, true);
                }
                return (true);
            }
        }
        // END IASRI 4868073

        // Send an "unauthorized" response and an appropriate challenge
        String realmName = config.getRealmName();
        if (realmName == null)
            realmName = REALM_NAME;
    //        if (debug >= 1)
    //            log("Challenging for realm '" + realmName + "'");
        hres.setHeader(AUTH_HEADER_NAME,
                       "Basic realm=\"" + realmName + "\"");
        hres.sendError(HttpServletResponse.SC_UNAUTHORIZED);
        //      hres.flushBuffer();
        return (false);

    }


    // ------------------------------------------------------ Protected Methods


    /**
     * Parse the username from the specified authorization credentials.
     * If none can be found, return <code>null</code>.
     *
     * @param authorization Authorization credentials from this request
     */
    protected String parseUsername(String authorization) {

        if (authorization == null)
            return (null);
        if (!authorization.toLowerCase(Locale.ENGLISH).startsWith("basic "))
            return (null);
        authorization = authorization.substring(6).trim();

        // Decode and parse the authorization credentials
        String unencoded =
          new String(Base64.decode(authorization.getBytes(Charset.defaultCharset())));
        int colon = unencoded.indexOf(':');
        if (colon < 0)
            return (null);
        String username = unencoded.substring(0, colon);
        //        String password = unencoded.substring(colon + 1).trim();
        return (username);

    }


    /**
     * Parse the password from the specified authorization credentials.
     * If none can be found, return <code>null</code>.
     *
     * @param authorization Authorization credentials from this request
     */
    protected char[] parsePassword(String authorization) {

        if (authorization == null)
            return (null);
        if (!authorization.toLowerCase(Locale.ENGLISH).startsWith("basic "))
            return (null);
        authorization = authorization.substring(6).trim();

        // Decode and parse the authorization credentials
        String unencoded =
          new String(Base64.decode(authorization.getBytes(Charset.defaultCharset())));
        int colon = unencoded.indexOf(':');
        if (colon < 0)
            return (null);
        //        String username = unencoded.substring(0, colon).trim();
        char[] password = unencoded.substring(colon + 1).toCharArray();
        return (password);

    }

    @Override
    protected String getAuthMethod() {
        return HttpServletRequest.BASIC_AUTH;
    }
}
