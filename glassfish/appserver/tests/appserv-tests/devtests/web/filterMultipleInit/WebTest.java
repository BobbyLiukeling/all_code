/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2010-2017 Oracle and/or its affiliates. All rights reserved.
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

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import com.sun.ejte.ccl.reporter.*;

/*
 * Unit test for
 *
 *  https://glassfish.dev.java.net/issues/show_bug.cgi?id=11979
 *  ("Filter.init() called twice")
 */
public class WebTest {

    private static final String TEST_NAME =
        "filter-multiple-init";

    private static SimpleReporterAdapter stat =
        new SimpleReporterAdapter("appserv-tests");

    private String host;
    private String port;
    private String contextRoot;

    public WebTest(String[] args) {
        host = args[0];
        port = args[1];
        contextRoot = args[2];
    }
    
    public static void main(String[] args) {

        stat.addDescription("Unit test for IT 11979");
        final WebTest webTest = new WebTest(args);

        try {
            ExecutorService exService = Executors.newFixedThreadPool(3);
            List<Callable<Boolean>> tasks = new ArrayList<Callable<Boolean>>();
            tasks.add(new Callable<Boolean>() {
                public Boolean call() throws Exception {
                    return webTest.doTest("index.jsp");
                }
            });
            tasks.add(new Callable<Boolean>() {
                public Boolean call() throws Exception {
                    return webTest.doTest("index2.jsp");
                }
            });

            List<Future<Boolean>> futures = exService.invokeAll(tasks, 6, TimeUnit.SECONDS);
            boolean status = futures.get(0).get() && futures.get(1).get();

            stat.addStatus(TEST_NAME, ((status) ? stat.PASS : stat.FAIL));
        } catch (Exception ex) {
            ex.printStackTrace();
            stat.addStatus(TEST_NAME, stat.FAIL);
        }

        stat.printSummary();
    }

    public boolean doTest(String page) throws Exception {
        URL url = new URL("http://" + host  + ":" + port
                          + contextRoot + "/" + page);
     
        System.out.println("Connecting to: " + url.toString());

        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.connect();
        int responseCode = conn.getResponseCode();

        System.out.println(page + ": " + responseCode);
        return (responseCode == 200);
    }
}
