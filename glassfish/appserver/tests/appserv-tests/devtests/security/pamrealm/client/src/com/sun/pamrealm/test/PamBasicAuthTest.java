/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.pamrealm.test;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.UsernamePasswordCredentials;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.commons.httpclient.auth.AuthScope;
import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

public class PamBasicAuthTest {

    public static final int DEFAULT_HTTP_PORT = 8080;
    public static final String DEFAULT_HOST = "localhost";
    public static final String CONTEXT_ROOT = "pamrealmsimpleweb";
    public static final String testId = "SEC: PamRealm";
    public static final String EXPECTED_RESPONSE = "This is a protected page";

    public static void main(String args[]) {
        SimpleReporterAdapter stat =
                new SimpleReporterAdapter("appserv-tests");

        // The stat reporter writes out the test info and results
        // into the top-level quicklook directory during a run.

        stat.addDescription("PamRealm Web Authentication Test");

        HttpClient client = new HttpClient();

        String host = args[0];

        if (host == null) {
            host = DEFAULT_HOST;
        }

        String strPort = args[1];

        Integer port;
        try {
            port = Integer.valueOf(strPort);
        } catch (Exception e) {
            port = DEFAULT_HTTP_PORT;
        }

        String userName = args[2];//username
        String password = args[3];//password

        client.getState().setCredentials(new AuthScope(host, port, "pam"), new UsernamePasswordCredentials(userName, password));

        String url = "http://" + host + ":" + port + "/" + CONTEXT_ROOT;

        GetMethod get = new GetMethod(url);
        get.setDoAuthentication(true);
        String response = "";
        try {
            int status = client.executeMethod(get);
            response = get.getResponseBodyAsString();
            System.out.println("Obtained response.." + response);
        } catch (Exception ex) {
            ex.printStackTrace();
            stat.addStatus(testId, stat.FAIL);
        }
        if (response.trim().equals(EXPECTED_RESPONSE.trim())) {
            stat.addStatus(testId, stat.PASS);
            System.out.println("PASS");
        } else {
            stat.addStatus(testId, stat.FAIL);
            System.out.println("FAIL");

        }
        stat.printSummary();
    }
}