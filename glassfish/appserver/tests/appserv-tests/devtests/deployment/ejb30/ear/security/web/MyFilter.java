/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2005-2017 Oracle and/or its affiliates. All rights reserved.
 *
 * The contents of this file are subject to the terms of either the GNU
 * General Public License Version 2 only ("GPL") or the Common Development
 * and Distribution License("CDDL") (collectively, the "License").  You
 * may not use this file except in compliance with the License.  You can
 * obtain a copy of the License at
 * https://oss.oracle.com/licenses/CDDL+GPL-1.1
 * or LICENSE.txt.  See the License for the specific
 * language governing permissions and limitations under the License.
 *
 * When distributing the software, include this License Header Notice in each
 * file and include the License file at LICENSE.txt.
 *
 * GPL Classpath Exception:
 * Oracle designates this particular file as subject to the "Classpath"
 * exception as provided by Oracle in the GPL Version 2 section of the License
 * file that accompanied this code.
 *
 * Modifications:
 * If applicable, add the following below the License Header, with the fields
 * enclosed by brackets [] replaced by your own identifying information:
 * "Portions Copyright [year] [name of copyright owner]"
 *
 * Contributor(s):
 * If you wish your version of this file to be governed by only the CDDL or
 * only the GPL Version 2, indicate your decision by adding "[Contributor]
 * elects to include this software in this distribution under the [CDDL or GPL
 * Version 2] license."  If you don't indicate a single choice of license, a
 * recipient has the option to distribute your version of this file under
 * either the CDDL, the GPL Version 2 or to extend the choice of license to
 * its licensees as provided above.  However, if you add GPL Version 2 code
 * and therefore, elected the GPL Version 2 license, then the option applies
 * only if the new code is made subject to such option by the copyright
 * holder.
 */

package com.sun.s1asdev.deployment.ejb30.ear.security;

import java.io.IOException;

import javax.annotation.Resource;
import javax.annotation.security.DeclareRoles;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpServletRequest;
import javax.sql.DataSource;

@DeclareRoles({ "j2ee", "nobody", "sunuser" })
public class MyFilter implements Filter {

    private @Resource(mappedName="jdbc/__default") DataSource ds1;

    public void init(FilterConfig filterConfig) throws ServletException {

        ServletContext sc = filterConfig.getServletContext();
    
        try {

            int loginTimeout = ds1.getLoginTimeout();
            sc.log("ds1-login-timeout=" + loginTimeout);

        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    public void doFilter (ServletRequest request,
                          ServletResponse response,
                          FilterChain chain)
            throws IOException, ServletException {
        int loginTimeout = 0;
        try {
            loginTimeout = ds1.getLoginTimeout();
        } catch(Exception ex) {
            ex.printStackTrace();
            throw new IOException(ex.toString());
        }
        HttpServletRequest httpRequest = (HttpServletRequest)request;
        HttpSession httpSession = httpRequest.getSession(true);
        if (httpRequest.isUserInRole("j2ee")) {
            httpSession.putValue("deployment.ejb30.ear.security",
                "filterMessage=hello world: " + loginTimeout);

        }
        chain.doFilter(request, response);
    }

    public void destroy() {
        // do nothing
    }
}
