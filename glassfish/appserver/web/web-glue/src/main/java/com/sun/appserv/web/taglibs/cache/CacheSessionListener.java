/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.appserv.web.taglibs.cache;

import com.sun.appserv.util.cache.Cache;
import com.sun.appserv.web.cache.CacheManager;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

/** 
 * HttpSessionListener which creates a cache for JSP tag body invocations
 * and adds it as a session attribute in response to sessionCreated events,
 * and clears the cache in response to sessionDestroyed events.
 */
public class CacheSessionListener implements HttpSessionListener {

    /**
     * No-arg constructor
     */
    public CacheSessionListener() {}


    /** 
     * Receives notification that a session was created, and adds newly
     * created cache for JSP tag body invocations as a session attribute.
     *
     * @param hse the notification event
     */
    public void sessionCreated(HttpSessionEvent hse) {
      
        HttpSession session = hse.getSession();  
        ServletContext context = session.getServletContext();

        // Check if a cache manager has already been created and set in the
        // context
        CacheManager cm = (CacheManager)
            context.getAttribute(CacheManager.CACHE_MANAGER_ATTR_NAME);

        // Create a new cache manager if one is not present and use it
        // to create a new cache
        if (cm == null) {
            cm = new CacheManager();
        }

        Cache cache = null;
        try {
            cache = cm.createCache();
        } catch (Exception ex) {}

        // Set the cache as a session attribute
        if (cache != null) {
            session.setAttribute(Constants.JSPTAG_CACHE_KEY, cache);
        }
    }


    /** 
     * Receives notification that a session is about to be invalidated, and
     * clears the session's cache of JSP tag body invocations (if present).
     *
     * @param hse the notification event
     */
    public void sessionDestroyed(HttpSessionEvent hse) {

        // Clear the cache
        HttpSession session = hse.getSession();  
        Cache cache = (Cache)session.getAttribute(Constants.JSPTAG_CACHE_KEY);
        if (cache != null) {
            cache.clear();
        }
    }
}
