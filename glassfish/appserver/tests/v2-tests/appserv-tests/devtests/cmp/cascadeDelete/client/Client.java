/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2018 Oracle and/or its affiliates. All rights reserved.
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

/*
 * Client.java
 *
 * Created on February 21, 2003, 3:20 PM
 */

import javax.servlet.*;
import javax.servlet.http.*;
import javax.naming.*;
import javax.rmi.PortableRemoteObject;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

/**
 *
 * @author  mvatkina
 * @version
 */
public class Client {
    
    private static SimpleReporterAdapter stat =
        new SimpleReporterAdapter("appserv-tests");

    public static void main(String[] args) {
       
        try {
            System.out.println("START");
            stat.addDescription("copySemantics");

            Context initial = new InitialContext();
                        Object objref = initial.lookup("java:comp/env/ejb/RemoteA");
            cascadeDelete.AHome ahome =
            (cascadeDelete.AHome)PortableRemoteObject.narrow(objref,
            cascadeDelete.AHome.class);

            objref = initial.lookup("java:comp/env/ejb/RemoteB");
            cascadeDelete.BHome bhome =
            (cascadeDelete.BHome)PortableRemoteObject.narrow(objref,
            cascadeDelete.BHome.class);

            objref = initial.lookup("java:comp/env/ejb/RemoteC");
            cascadeDelete.CHome chome =
            (cascadeDelete.CHome)PortableRemoteObject.narrow(objref,
            cascadeDelete.CHome.class);

            objref = initial.lookup("java:comp/env/ejb/RemoteD");
            cascadeDelete.DHome dhome =
            (cascadeDelete.DHome)PortableRemoteObject.narrow(objref,
            cascadeDelete.DHome.class);


            cascadeDelete.A abean = ahome.create(new Integer(1), "A1");

            cascadeDelete.B bbean = bhome.create(new Integer(100), "B100");
            bbean = bhome.create(new Integer(200), "B200");

            cascadeDelete.C cbean = chome.create(new Integer(100), "C100");
            cbean = chome.create(new Integer(200), "C200");

            cascadeDelete.D dbean = dhome.create(new Integer(1000), "D1000");
            dbean = dhome.create(new Integer(1100), "D1100");
            dbean = dhome.create(new Integer(2000), "D2000");
            dbean = dhome.create(new Integer(2200), "D2200");

            abean.addAll();

            System.out.println("Created " + ahome.findAll().size() + " As.");
            System.out.println("Created " + bhome.findAll().size() + " Bs.");
            System.out.println("Created " + chome.findAll().size() + " Cs.");
            System.out.println("Created " + dhome.findAll().size() + " Ds.");

            System.out.println("Removing last C...");
            cbean.remove();

            System.out.println("Left " + ahome.findAll().size() + " As.");
            System.out.println("Left " + bhome.findAll().size() + " Bs.");
            System.out.println("Left " + chome.findAll().size() + " Cs.");
            System.out.println("Left " + dhome.findAll().size() + " Ds.");


            System.out.println("Removing A...");
            abean.remove();

            System.out.println("Left " + ahome.findAll().size() + " As.");
            System.out.println("Left " + bhome.findAll().size() + " Bs.");
            System.out.println("Left " + chome.findAll().size() + " Cs.");
            System.out.println("Left " + dhome.findAll().size() + " Ds.");

            stat.addStatus("ejbclient cascadeDelete", stat.PASS);
            System.out.println("FINISH");

        } catch (Exception ex) {
            System.err.println("Caught an exception:");
            ex.printStackTrace();
	    stat.addStatus("ejbclient cascadeDelete", stat.FAIL);
        }
	  stat.printSummary("cascadeDelete");

    }
    
}
