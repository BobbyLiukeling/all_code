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

package org.apache.catalina.valves;


import org.apache.catalina.*;
import org.apache.catalina.session.PersistentManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

/**
 * Valve that implements the default basic behavior for the
 * <code>StandardHost</code> container implementation.
 * <p>
 * <b>USAGE CONSTRAINT</b>: To work correctly it requires a  PersistentManager.
 *
 * @author Jean-Frederic Clere
 * @version $Revision: 1.2 $ $Date: 2005/12/08 01:28:24 $
 */

public class PersistentValve
    extends ValveBase {

    // ----------------------------------------------------- Instance Variables


    /**
     * The descriptive information related to this implementation.
     */
    private static final String info =
        "org.apache.catalina.valves.PersistentValve/1.0";


    // ------------------------------------------------------------- Properties


    /**
     * Return descriptive information about this Valve implementation.
     */
    public String getInfo() {

        return (info);

    }


    // --------------------------------------------------------- Public Methods


    /**
     * Select the appropriate child Context to process this request,
     * based on the specified request URI.  If no matching Context can
     * be found, return an appropriate HTTP error.
     *
     * @param request Request to be processed
     * @param response Response to be produced
     *
     * @exception IOException if an input/output error occurred
     * @exception ServletException if a servlet error occurred
     */
     public int invoke(Request request, Response response)
         throws IOException, ServletException {

        // Select the Context to be used for this Request
        Context context = request.getContext();
        if (context == null) {
            ((HttpServletResponse) response.getResponse()).sendError
                (HttpServletResponse.SC_INTERNAL_SERVER_ERROR,
                 rb.getString(LogFacade.NO_CONTEXT_CONFIGURED));
            return END_PIPELINE;
        }

        // Bind the context CL to the current thread
        Thread.currentThread().setContextClassLoader
            (context.getLoader().getClassLoader());

        // Update the session last access time for our session (if any)
        HttpServletRequest hreq = (HttpServletRequest) request.getRequest();
        String sessionId = hreq.getRequestedSessionId();
        Manager manager = context.getManager();
        if (sessionId != null && manager != null) {
            if (manager instanceof PersistentManager) {
                Store store = ((PersistentManager) manager).getStore();
                if (store != null) {
                    Session session = null;
                    try {
                        session = store.load(sessionId);
                    } catch (Exception e) {
                        log("deserializeError");
                    }
                    if (session != null) {
                        if (!session.isValid() ||
                            isSessionStale(session, System.currentTimeMillis())) {
                            log("session swapped in is invalid or expired");
                            session.expire();
                            store.remove(sessionId);
                        } else {
                            session.setManager(manager);
                            // session.setId(sessionId); Only if new ???
                            manager.add(session);
                            // ((StandardSession)session).activate();
                            session.access();
                        }
                    }
                }
            }
        }
        log("sessionId: " + sessionId);

        // Ask the next valve to process the request.
        return INVOKE_NEXT;
    }


    public void postInvoke(Request request, Response response)
                                    throws IOException, ServletException{
        Context context = request.getContext();
        if (context == null) {
            ((HttpServletResponse) response.getResponse()).sendError
                (HttpServletResponse.SC_INTERNAL_SERVER_ERROR,
                 rb.getString(LogFacade.NO_CONTEXT_CONFIGURED));
            return;
        }

        // Bind the context CL to the current thread
        Thread.currentThread().setContextClassLoader
            (context.getLoader().getClassLoader());

        // Update the session last access time for our session (if any)
        HttpServletRequest hreq = (HttpServletRequest) request.getRequest();
        Manager manager = context.getManager();

        // Read the sessionid after the response.
        // HttpSession hsess = hreq.getSession(false);
        String newsessionId = null;
        if (request instanceof org.apache.catalina.connector.Request) {
            Session sess;
            try {
                sess = ((org.apache.catalina.connector.Request) request).getSessionInternal();
            } catch (Exception ex) {
                sess = null;
            }
            if (sess!=null) {
                newsessionId = sess.getIdInternal();
            }
        } else {
            HttpSession hsess;
            try {
                hsess = hreq.getSession();
            } catch (Exception ex) {
                hsess = null;
            }
            if (hsess!=null) {
                newsessionId = hsess.getId();
            }
        }

        log("newsessionId: " + newsessionId);
        if (newsessionId!=null) {
            /* store the session in the store and remove it from the manager */
            if (manager instanceof PersistentManager) {
                Session session = manager.findSession(newsessionId);
                Store store = ((PersistentManager) manager).getStore();
                if (store != null && session!=null &&
                    session.isValid() &&
                    !isSessionStale(session, System.currentTimeMillis())) {
                    // ((StandardSession)session).passivate();
                    store.save(session);
                    ((PersistentManager) manager).removeSuper(session);
                    session.recycle();
                } else if (session!=null) {
                    log("newsessionId store: " + store + " session: " +
                        session + " valid: " + session.isValid() +
                        " Staled: " +
                        isSessionStale(session, System.currentTimeMillis()));

                }
            } else {
                log("newsessionId Manager: " + manager);
            }
        }

    }

    /**
     * Log a message on the Logger associated with our Container (if any).
     *
     * @param message Message to be logged
     */
    protected void log(String message) {
 
        Logger logger = container.getLogger();
        if (logger != null)
            logger.log(this.toString() + ": " + message);
        else
            System.out.println(this.toString() + ": " + message);
 
    }

    /**
     * Indicate whether the session has been idle for longer
     * than its expiration date as of the supplied time.
     *
     * FIXME: Probably belongs in the Session class.
     */
    protected boolean isSessionStale(Session session, long timeNow) {
 
        int maxInactiveInterval = session.getMaxInactiveInterval();
        if (maxInactiveInterval >= 0) {
            int timeIdle = // Truncate, do not round up
                (int) ((timeNow - session.getLastAccessedTime()) / 1000L);
            if (timeIdle >= maxInactiveInterval)
                return true;
        }
 
        return false;
 
    }

}
