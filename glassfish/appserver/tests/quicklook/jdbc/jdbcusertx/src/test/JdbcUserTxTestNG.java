/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
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

package test.jdbc.jdbcusertx;
import org.testng.annotations.Configuration;
import org.testng.annotations.ExpectedExceptions;
import org.testng.annotations.Test;
import org.testng.annotations.*;
import org.testng.Assert;

import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Simple TestNG client for basic WAR containing one JSP,one Servlet and one static
 *HTML resource.Each resources (HTML,JSP,Servlet) is invoked as a separate test.
 *
 */
public class JdbcUserTxTestNG {

    private static final String TEST_NAME =
        "jdbc-jdbcusertx";
   
    private String strContextRoot="jdbcusertx";

    static String result = "";
    String host=System.getProperty("http.host");
    String port=System.getProperty("http.port");
           
    /*
     *If two asserts are mentioned in one method, then last assert is taken in
     *to account.
     *Each method can act as one test within one test suite
     */


    @Test(groups ={ "pulse"} ) // test method
    public void testUserTx() throws Exception{
        
        try{

          String testurl = "http://" + host  + ":" + port + "/"+ 
	    strContextRoot + "/MyServlet?testcase=usertx";
	  URL url = new URL(testurl);
	  //echo("Connecting to: " + url.toString());
	  HttpURLConnection conn = (HttpURLConnection) url.openConnection();
	  conn.connect();
	  int responseCode = conn.getResponseCode();

	  InputStream is = conn.getInputStream();
	  BufferedReader input = new BufferedReader(new InputStreamReader(is));

	  String line = null;
	  boolean result=false;
	  String testLine = null;        
	  String EXPECTED_RESPONSE ="user-tx-commit:true";
	  String EXPECTED_RESPONSE2 ="user-tx-rollback:true";
	  while ((line = input.readLine()) != null) {
	    // echo(line);
            if(line.indexOf(EXPECTED_RESPONSE)!=-1 &&
               line.indexOf(EXPECTED_RESPONSE2)!=-1){
	      testLine = line;
	      //echo(testLine);
	      result=true;
	      break;
            }
	  }        
                
	  Assert.assertEquals(result, true,"Unexpected Results");
        
        }catch(Exception e){
	  e.printStackTrace();
	  throw new Exception(e);
        }

    }

    @Test(groups ={ "pulse"} ) // test method
    public void testNoLeak() throws Exception{
        
        try{

          String testurl = "http://" + host  + ":" + port + "/"+ 
	    strContextRoot + "/MyServlet?testcase=noleak";
	  URL url = new URL(testurl);
	  //echo("Connecting to: " + url.toString());
	  HttpURLConnection conn = (HttpURLConnection) url.openConnection();
	  conn.connect();
	  int responseCode = conn.getResponseCode();

	  InputStream is = conn.getInputStream();
	  BufferedReader input = new BufferedReader(new InputStreamReader(is));

	  String line = null;
	  boolean result=false;
	  String testLine = null;        
	  String EXPECTED_RESPONSE ="no-leak-test:true";
	  while ((line = input.readLine()) != null) {
	    // echo(line);
   	    if(line.indexOf(EXPECTED_RESPONSE)!=-1){
	      testLine = line;
	      //echo(testLine);
	      result=true;
	      break;
            }
	  }        
                
	  Assert.assertEquals(result, true,"Unexpected Results");
               
        }catch(Exception e){
            e.printStackTrace();
            throw new Exception(e);
        }

    }

    public static void echo(String msg) {
        System.out.println(msg);
    }

}
