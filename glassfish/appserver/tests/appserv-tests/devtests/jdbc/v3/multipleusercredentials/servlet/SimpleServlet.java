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

package servlet;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.ejb.CreateException;
import java.io.IOException;
import java.io.PrintWriter;

import com.sun.s1asdev.jdbc.multipleusercredentials.ejb.SimpleSessionHome;
import com.sun.s1asdev.jdbc.multipleusercredentials.ejb.SimpleSession;

public class SimpleServlet extends HttpServlet {


    public void doGet (HttpServletRequest request, HttpServletResponse response)
          throws ServletException, IOException {
      doPost(request, response);
    }

    /** handles the HTTP POST operation **/
    public void doPost (HttpServletRequest request,HttpServletResponse response)
          throws ServletException, IOException {
        doTest(request, response);
    }

    public void doTest(HttpServletRequest request, HttpServletResponse response) throws IOException{
        PrintWriter out = response.getWriter();

        try{
        System.out.println("JDBC Multiple User Credentials test");

        InitialContext ic = new InitialContext();
        SimpleSessionHome simpleSessionHome = (SimpleSessionHome) ic.lookup("java:comp/env/ejb/SimpleSessionEJB");
        out.println("Running multiple user credentials test ");

        //stat.addDescription("Running serializable connector test ");
        SimpleSession simpleSession = simpleSessionHome.create();

        boolean passed = true;
        for (int i = 0; i < 50; i++) {
            try {
                if (simpleSession.test1() == false) {
                    passed = false;
                    break;
                }
            } catch (Exception e) {
                passed = false;
                break;
            }
        }
        if(passed){
	    System.out.println("Multiple User credentials test : test1 : PASS");
            out.println("TEST:PASS");
	} else {
	    System.out.println("Multiple User credentials test : test1 : FAIL");
            out.println("TEST:FAIL");
	}

	} catch(NamingException ne) {
	    ne.printStackTrace();
	} catch(CreateException e) {
	    e.printStackTrace();
        } finally {
	    out.println("END_OF_TEST");
	    out.flush();
	}
    }
}
