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

package com.sun.s1peqe.transaction.txnegative.client;

/*
 * Client.java
 *
 */

import javax.naming.*;
import javax.rmi.PortableRemoteObject;
import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;
import javax.transaction.*;

public class Client {
    public SimpleReporterAdapter status;
    private UserTransaction             userTransaction;


    public Client() {
    status = new SimpleReporterAdapter("appserv-tests");
    try{
    userTransaction = (UserTransaction) new InitialContext().lookup("java:comp/UserTransaction");
    }catch(Exception ex) {
    	ex.printStackTrace();
    }
    }

    
    public static void main(String[] args) {
	System.out.println("\nStarting Txglobal Test Suite");
        Client client = new Client();

        // run the tests
        client.runTestClient();

    }
    public void runTestClient() {
	status.addDescription("This is to test the valid transaction exception!");
        try {
            System.out.println("START");

            /*Context initial = new InitialContext();

            Object objref = initial.lookup("java:comp/env/ejb/TestHung");
            com.sun.s1peqe.transaction.txnegative.ejb.test.TestHome thome = (com.sun.s1peqe.transaction.txhung.ejb.test.TestHome)PortableRemoteObject.narrow(objref, TestHome.class);

            com.sun.s1peqe.transaction.txnegative.ejb.test.TestRemote t = thome.create();
            boolean result=false;
            boolean xa = true;
            boolean nonxa = false;

            try {
                result = t.testA1(xa);
		System.out.println("TEST FAILED");
            } catch (javax.ejb.CreateException e) {
                System.out.println("CreateException");
		System.out.println("TEST FAILED");
            } catch (Exception e) {
		System.out.println("TEST PASSED");
            }
            if (!result) {
                status.addStatus("txnegative testA1 ", status.PASS);
            } else {
                status.addStatus("txnegative testA1 ", status.FAIL);
            }
	    result = false;

            try {
                result = t.testA1(nonxa);
		System.out.println("TEST FAILED");
            } catch (javax.ejb.CreateException e) {
                System.out.println("CreateException");
		System.out.println("TEST FAILED");
            } catch (Exception e) {
		System.out.println("TEST PASSED");
            }
            if (!result) {
                status.addStatus("txnegative testA2 ", status.PASS);
            } else {
                status.addStatus("txnegative testA2 ", status.FAIL);
            }*/
            boolean result=false;

            try {
		userTransaction.begin();
		userTransaction.begin();
		System.out.println("TEST FAILED");
            } catch (NotSupportedException ne) {
                System.out.println("NotSupportedException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (SystemException ne) {
                System.out.println("SystemException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (Exception e) {
		e.printStackTrace();
		System.out.println("TEST FAILED");
            }
            if (result) {
                status.addStatus("txnegative t1 ", status.PASS);
            } else {
                status.addStatus("txnegative t1 ", status.FAIL);
            }
	    result = false;
            try {
		userTransaction.commit();
		System.out.println("TEST FAILED");
            } catch (IllegalStateException ne) {
                System.out.println("IllegalStateException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (SystemException ne) {
                System.out.println("SystemException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (Exception e) {
		e.printStackTrace();
		System.out.println("TEST FAILED");
            }
            if (result) {
                status.addStatus("txnegative t2 ", status.PASS);
            } else {
                status.addStatus("txnegative t2 ", status.FAIL);
            }
	    result = false;
            try {
		userTransaction.rollback();
		System.out.println("TEST FAILED");
            } catch (IllegalStateException ne) {
                System.out.println("IllegalStateException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (SystemException ne) {
                System.out.println("SystemException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (Exception e) {
		e.printStackTrace();
		System.out.println("TEST FAILED");
            }
            if (result) {
                status.addStatus("txnegative t3 ", status.PASS);
            } else {
                status.addStatus("txnegative t3 ", status.FAIL);
            }
	    result = false;
            try {
		userTransaction.setRollbackOnly();
		System.out.println("TEST FAILED");
            } catch (IllegalStateException ne) {
                System.out.println("IllegalStateException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (SystemException ne) {
                System.out.println("SystemException");
		System.out.println("TEST PASSED");
		result = true;
            } catch (Exception e) {
		e.printStackTrace();
		System.out.println("TEST FAILED");
            }
            if (result) {
                status.addStatus("txnegative t4 ", status.PASS);
            } else {
                status.addStatus("txnegative t4 ", status.FAIL);
            }



            System.out.println("FINISH");
            status.printSummary("txglobalID");

        } catch (Exception ex) {
            System.err.println("Caught an exception:");
            ex.printStackTrace();
            status.addStatus("txnegative testA1 ", status.FAIL);
        }
	}
    
}