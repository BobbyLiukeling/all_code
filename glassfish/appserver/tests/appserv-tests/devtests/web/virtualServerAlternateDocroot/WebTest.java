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
 * Unit test for alternate docroot support.
 *
 * This test configures the virtual server "server" with the following
 * alternate docroot properties:
 *
 * Exact match:
 *
 *   <property
 *     name="alternatedocroot_1"
 *     value="from=/domain.xml dir=${env.S1AS_HOME}/domains/${admin.domain}/config"/>
 *
 * Extension match:
 *
 *   <property
 *     name="alternatedocroot_2"
 *     value="from=*.policy dir=${env.S1AS_HOME}/domains/${admin.domain}/config"/>
 *
 * Path prefix match:
 *
 *   <property
 *     name="alternatedocroot_3"
 *     value="from=/config/* dir=${env.S1AS_HOME}/domains/${admin.domain}"/>
 *
 * and then ensures that a request with a URI of the form
 *   "/domain.xml"
 * is mapped to:
 *   ${env.S1AS_HOME}/domains/${admin.domain}/config/domain.xml
 * (exact match),
 *
 * a second request with a URI of the form
 *   "/server.policy"
 * is mapped to:
 *   ${env.S1AS_HOME}/domains/${admin.domain}/config/server.policy
 * (extension match),
 *
 * and a third request with a URI of the form
 *  "/config/login.conf"
 * is mapped to:
 *   ${env.S1AS_HOME}/domains/${admin.domain}/config/login.conf
 * (path prefix match).
 *
 * If it were not for the alternate docroots, the above requests would
 * result in a 404, since the requested resources are not available in the
 * regular docroot of virtual server "server".
 */
public class WebTest {

    private static SimpleReporterAdapter stat
        = new SimpleReporterAdapter("appserv-tests");

    private static final String TEST_NAME = "virtual-server-alternate-docroot";

    private String host;
    private String port;

    public WebTest(String[] args) {
        host = args[0];
        port = args[1];
    }
    
    public static void main(String[] args) {
        stat.addDescription("Unit test for alternate docroot support");
        WebTest webTest = new WebTest(args);
        webTest.doTest();
        stat.printSummary(TEST_NAME);
    }

    public void doTest() {     
        try { 
            invoke("/domain.xml", "<domain ");
            invoke("/server.policy", "grant codeBase");
            invoke("/config/login.conf", "fileRealm");
            stat.addStatus(TEST_NAME, stat.PASS);
        } catch (Exception ex) {
            stat.addStatus(TEST_NAME, stat.FAIL);
            ex.printStackTrace();
        }
    }

    /*
     * @param uri The URI to connect to
     * @param expected The string that must be present in the returned contents
     * in order for the test to pass
     */
    private void invoke(String uri, String expected) throws Exception {
        
        URL url = new URL("http://" + host  + ":" + port + uri);
        System.out.println("Connecting to: " + url.toString());
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.connect();

        int responseCode = conn.getResponseCode();
        if (responseCode != 200) {
            throw new Exception("Wrong response code. Expected: 200"
                                + ", received: " + responseCode);
        }

        InputStream is = conn.getInputStream();
        BufferedReader input = new BufferedReader(new InputStreamReader(is));
        String line = null;
        while ((line = input.readLine()) != null) {
            // Search resource contents for expected string
            if (line.contains(expected)) {
                break;
            }
        }

        if (line == null) {
            throw new Exception("Missing content for " + uri);
        }
    }
}
