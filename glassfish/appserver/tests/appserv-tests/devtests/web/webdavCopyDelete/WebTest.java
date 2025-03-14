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

import java.io.*;
import java.net.*;
import com.sun.ejte.ccl.reporter.*;

/**
 * Unit test for WebDAV.
 *
 */
public class WebTest {

    private static SimpleReporterAdapter stat
        = new SimpleReporterAdapter("appserv-tests");

    private static final String TEST_NAME
        = "webdav-copy-delete";

    private static String EXPECTED = "Hello WebDAV";
    private static String EXPECTED2 = "HTTP/1.1 404";

    private String host;
    private String port;
    private String contextRoot;

    public WebTest(String[] args) {
        host = args[0];
        port = args[1];
        contextRoot = args[2];
    }
    
    public static void main(String[] args) {
        stat.addDescription("Unit test for WebDAV copy and delete");
        WebTest webTest = new WebTest(args);
        webTest.doTest();
        stat.printSummary(TEST_NAME);
    }

    public void doTest() {
        try {
            String tmplate = "/data.html";
            String page = "/index.html";
            invoke(new String[] { "COPY " + contextRoot + tmplate + " HTTP/1.1", 
                    "Destination: http://" + host + ":" + port + contextRoot + page }, null, false);

            boolean status = invoke(new String[] { "GET " + contextRoot + page  + " HTTP/1.1"}, EXPECTED, false);

            if (!status) {
                System.err.println("Missing expected response: " + EXPECTED);
            }

            invoke(new String[] { "DELETE " + contextRoot + page + " HTTP/1.1" }, null, false);

            boolean status2 = invoke(new String[] { "GET " + contextRoot + page  + " HTTP/1.1"}, EXPECTED2, true);

            if (!status2) {
                System.err.println("Missing expected response: " + EXPECTED);
            }

            if (status && status2) {
                stat.addStatus(TEST_NAME, stat.PASS);
            } else {
                stat.addStatus(TEST_NAME, stat.FAIL);
            }
        } catch (Exception ex) {
            stat.addStatus(TEST_NAME, stat.FAIL);
            ex.printStackTrace();
        }
    }

    private boolean invoke(String[] reqLines, String expected,
            boolean startsWith) throws Exception {

        boolean ok = (expected == null);
        System.out.println("Host=" + host + ", port=" + port);
        Socket sock = new Socket(host, new Integer(port).intValue());
        OutputStream os = sock.getOutputStream();
        for (String reqLine : reqLines) {
            System.out.println(reqLine);
            os.write((reqLine + "\n").getBytes());
        }   

        os.write("Host: localhost\n".getBytes());
        os.write("Connection: close\n".getBytes());
        os.write("\r\n".getBytes());

        System.out.println();

        InputStream is = sock.getInputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(is));

        String line = null;
        while ((line = br.readLine()) != null) {
            if (startsWith) {
                if (expected != null && line.startsWith(expected)) {
                    ok = true;
                }
            } else {
                if (line.equals(expected)) {
                    ok = true;
                }
            }

            System.out.println(line);
        }
        br.close();
        is.close();
        os.close();
        sock.close();

        return ok;
    }
}
