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

package client;

import javax.xml.ws.WebServiceRef;

import ejb.GatewayImplService;
import ejb.GatewayImpl;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

public class Client {

        private static SimpleReporterAdapter stat =
                new SimpleReporterAdapter("appserv-tests");

	private final static String desc = "ws-ejb-port-field-injection";

	@WebServiceRef(GatewayImplService.class)
        static GatewayImpl port;

        public static void main(String[] args) {
	    stat.addDescription(desc);
            Client client = new Client();
            client.doTest(args);
	    stat.printSummary(desc);
       }

       public void doTest(String[] args) {
            try {
		System.out.println("Method injected reference test...");
                String ret = port.invokeMethod("Appserver Tester !");
		if(ret.indexOf("METHOD WebSvcTest-Hello") == -1) {
                    System.out.println("Unexpected greeting " + ret);
                    stat.addStatus(desc, stat.FAIL);
                    return;
		}
                System.out.println("Server returned " + ret + " : PASSED");
		System.out.println("Field injected reference test...");
                ret = port.invokeField("Appserver Tester !");
		if(ret.indexOf("FIELD WebSvcTest-Hello") == -1) {
                    System.out.println("Unexpected greeting " + ret);
                    stat.addStatus(desc, stat.FAIL);
                    return;
		}
                System.out.println("Server returned " + ret + " : PASSED");
		System.out.println("Dependency jndi looup reference test...");
                ret = port.invokeDependency("Appserver Tester !");
		if(ret.indexOf("JNDI WebSvcTest-Hello") == -1) {
                    System.out.println("Unexpected greeting " + ret);
                    stat.addStatus(desc, stat.FAIL);
                    return;
		}
                System.out.println("Server returned " + ret + " : PASSED");
                stat.addStatus(desc, stat.PASS);
            } catch(Exception e) {
                e.printStackTrace();
                stat.addStatus(desc, stat.FAIL);
            }
       }
}

