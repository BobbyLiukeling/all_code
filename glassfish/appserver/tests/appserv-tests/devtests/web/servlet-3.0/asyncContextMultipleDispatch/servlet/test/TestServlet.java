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

package test;

import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class TestServlet extends HttpServlet implements AsyncListener {
    private static StringBuffer sb = new StringBuffer();

    public void doGet(HttpServletRequest req, HttpServletResponse res)
            throws IOException, ServletException {

        if ("1".equals(req.getParameter("result"))) {
            res.getWriter().println(sb.toString());
            sb.delete(0, sb.length());
            return;
        }

        if (!req.isAsyncSupported()) {
            throw new ServletException("Async not supported when it should");
        }
   
        if (req.getDispatcherType() == DispatcherType.REQUEST) {
            // Container-initiated dispatch
            req.setAttribute("ABC", "DEF");
            final AsyncContext ac = req.startAsync();
            ac.addListener(this);
            Timer asyncTimer = new Timer("AsyncTimer", true);
            asyncTimer.schedule(
                new TimerTask() {
                    @Override
                    public void run() {
                        ac.dispatch();
                    }
                },
                5000);
        } else if (req.getDispatcherType() == DispatcherType.ASYNC) {
            if ("DEF".equals(req.getAttribute("ABC"))) {
                // First async dispatch
                req.removeAttribute("ABC");
                req.startAsync().dispatch();
            } else {
                // Second async dispatch
                req.startAsync().complete();
            }
        }
    }

    public void onComplete(AsyncEvent event) throws IOException {
        sb.append("onComplete");
    }

    public void onTimeout(AsyncEvent event) throws IOException {
        // do nothing
    }

    public void onError(AsyncEvent event) throws IOException {
        // do nothing
    }

    public void onStartAsync(AsyncEvent event) throws IOException {
        sb.append("onStartAsync,");
        /*
         * ServletRequest#startAsync clears the list of AsyncListener
         * instances registered with the AsyncContext - after calling
         * each AsyncListener at its onStartAsync method, which is the 
         * method we're in.
         * Register ourselves again, so we continue to get notified
         */
        event.getAsyncContext().addListener(this);
    }

}
