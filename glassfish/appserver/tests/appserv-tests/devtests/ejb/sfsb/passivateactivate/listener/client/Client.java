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

package com.sun.s1asdev.ejb.ejb30.sfsb.lifecycle.client;

import java.util.ArrayList;

import java.io.Serializable;
import javax.naming.*;
import javax.jms.*;
import javax.ejb.*;
import javax.rmi.PortableRemoteObject;
import java.rmi.NoSuchObjectException;

import com.sun.s1asdev.ejb.ejb30.sfsb.lifecycle.ejb.SFSBHome;
import com.sun.s1asdev.ejb.ejb30.sfsb.lifecycle.ejb.SFSB;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

public class Client {

    // consts
    public static String kTestNotRun    = "TEST NOT RUN";
    public static String kTestPassed    = "TEST PASSED";
    public static String kTestFailed    = "TEST FAILED";
    
    private static SimpleReporterAdapter stat = 
        new SimpleReporterAdapter("appserv-tests");

    private static final int    MAX_SFSBS = 24;

    private SFSBHome home;
    private ArrayList sfsbList = new ArrayList();

    private String _sfsbPrefix = "SFSB_" + System.currentTimeMillis() + "_";

    public static void main (String[] args) {

        stat.addDescription("passivateactivate");
        Client client = new Client(args);
        System.out.println("[lfTraditional] doTest()...");
        client.doTest();
        System.out.println("[lfTraditional] DONE doTest()...");
        stat.printSummary("passivateactivate");
    }  
    
    public Client (String[] args) {
    }
    
    public void doTest() {
        initSFSBList();     //create SFSBs 
        accessSFSB();       //access the SFBS
	removeTest();
    }

    private void initSFSBList() {
        System.out.println("[lfTraditional] Inside init....");
        try {
            Context ic = new InitialContext();
            Object objref = ic.lookup("java:comp/env/ejb/SFSB");
            home = (SFSBHome)PortableRemoteObject.narrow
                (objref, SFSBHome.class);
            for (int i=0; i < MAX_SFSBS; i++) {

                //Creating these many SFSBs will cause passivation
                SFSB sfsb = (SFSB) home.create(_sfsbPrefix + i);
                sfsb.getName();
                sfsbList.add(sfsb);
            }
            System.out.println("[lfTraditional] Initalization done");
            stat.addStatus("ejbclient initSFSBList", stat.PASS);
        } catch(Exception e) {
            e.printStackTrace();
            //stat.addStatus("ejbclient localEntityGetEJBObject(-)" , stat.PASS);
            System.out.println("[lfTraditional] Exception in init....");
            e.printStackTrace();
            stat.addStatus("ejbclient initSFSBList", stat.FAIL);
        }
    }

    public void accessSFSB() {
        try {
	    System.out.println("Waiting for 10 seconds before accessing...");
	    for (int i=0; i<10; i++) {
		System.out.println("" + (10 - i) + " seconds left...");
		try {
		    Thread.currentThread().sleep(1*1000);
		} catch (Exception ex) {
		}
	    }

            boolean passed = true;
            for (int i=0; i < MAX_SFSBS; i++) {
                try {
		SFSB sfsb = (SFSB) sfsbList.get(i);
                String sfsbName = _sfsbPrefix+i;
		String retrievedName = sfsb.getName();
                
                boolean ok = sfsb.isOK(sfsbName);
		int actCount = sfsb.getActivationCount();
		int pasCount = sfsb.getPassivationCount();

		boolean activationTest = (actCount != 0);
		boolean passivationTest = (pasCount != 0);

                System.out.println("Bean[" + i + "/" + MAX_SFSBS + "] name: " + sfsbName
		    + "; retrievedName: " + retrievedName
		    + "; ok: " + ok
		    + "; " + activationTest + " (" + actCount + ")"
		    + "; " + passivationTest + " (" + pasCount + ")"
		);

                passed = passed & sfsbName.equals(retrievedName)
                    && ok
		    && activationTest && passivationTest;

                if (! passed) {
                    //break;
                }
		sfsb.sleepForSeconds(1);
		} catch (Exception ex) {
		    System.out.println("Bean[" + i + "] Got exception: " + ex);
		}
            }

            if (passed) {
                stat.addStatus("ejbclient accessSFSB", stat.PASS);
            } else {
                stat.addStatus("ejbclient accessSFSB", stat.FAIL);
            }

            for (int i=0; i < MAX_SFSBS; i++) {
                SFSB sfsb = (SFSB) sfsbList.get(i);
                String sfsbName = _sfsbPrefix+i;

                sfsb.makeStateNonSerializable();
	    }

	    //Creating these many SFSBs should force passivation of the above
	    //	non-serializable beans
            for (int i=0; i < MAX_SFSBS; i++) {
		home.create(_sfsbPrefix + (i+1)*1000);
	    }

	    System.out.println("Waiting for 10 seconds for passivation to complete...");

	    for (int i=0; i<10; i++) {
		System.out.println("" + (10 - i) + " seconds left...");
		try {
		    Thread.currentThread().sleep(1*1000);
		} catch (Exception ex) {
		}
	    }

            for (int i=0; i < MAX_SFSBS; i++) {
                SFSB sfsb = (SFSB) sfsbList.get(i);
                String sfsbName = _sfsbPrefix+i;

                try {
		    System.out.print("Expecting exception for: " + sfsbName);
		    String nm = sfsb.getName();
		    System.out.println("ERROR. Didn't get expected exception. "
			    + "Got: " + nm);
		    passed = false;
		    break;
		} catch (Exception ex) {
		    System.out.println("[**Got Exception**]");
		}
	    }
	    if (passed) {
		stat.addStatus("ejbclient non-serializable-state", stat.PASS);
	    } else {
		stat.addStatus("ejbclient non-serializable-state", stat.FAIL);
	    }
        } catch (Exception ex) {
            stat.addStatus("ejbclient accessSFSB", stat.FAIL);

        }
    }


    public void removeTest() {
	SFSB sfsb = null;
	try {
	    String myName = "_2_" + _sfsbPrefix + "_2_";
	    sfsb = (SFSB) home.create(myName);
	    String retrievedName = sfsb.getName();
	    boolean nameOK = myName.equalsIgnoreCase(retrievedName);
	    boolean gotException = false;
	    sfsb.remove();
	    Exception excep = null;
	    try {
		sfsb.getName();
		gotException = false;	    //Expecting an exception
	    } catch (Exception ex) {
		gotException = true;
		excep = ex;
	    }

	    String resultStr = "(" + nameOK + " @@@ " + gotException + ")";
            if (nameOK && gotException) {
                stat.addStatus("ejbclient removeTest " + resultStr, stat.PASS);
            } else {
                System.err.println("======> FAIL 2 because: nameOK: " + nameOK + " gotException: " + gotException);
		stat.addStatus("ejbclient removeTest " + resultStr, stat.FAIL);
            }

        } catch (Exception ex) {
            ex.printStackTrace();
            stat.addStatus("ejbclient removeTest_2", stat.FAIL);
        }
    }

} //Client{}
