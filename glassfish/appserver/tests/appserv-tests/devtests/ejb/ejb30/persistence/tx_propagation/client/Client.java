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

package com.sun.s1asdev.ejb.ejb30.persistence.tx_propagation.client;

import java.io.*;
import java.util.*;
import java.sql.*;
import javax.ejb.EJB;
import javax.transaction.UserTransaction;
import javax.annotation.Resource;
import javax.sql.DataSource;
import com.sun.s1asdev.ejb.ejb30.persistence.tx_propagation.*;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

public class Client {

    private static SimpleReporterAdapter stat =
        new SimpleReporterAdapter("appserv-tests");

    private String personName;

    private /** static @Resource(mappedName="jdbc/xa") **/ DataSource ds;

    public static void main (String[] args) {

        stat.addDescription("ejb-ejb30-persistence-tx_propagation");
        Client client = new Client(args);
        client.doTest(false);
        client.doTest(true);
        stat.printSummary("ejb-ejb30-persistence-tx_propagationID");
    }

    public Client (String[] args) {

        personName = "duke";

        if( args.length > 0 ) {
            personName = args[0];
        }

    }

    private static @EJB Sful sful;

    public void doTest(boolean commit) {

        ResultSet rs = null;
        Connection connection = null;
        PreparedStatement s = null;
        try {
            System.err.println("I am in client");
            
            UserTransaction utx = (UserTransaction)(new javax.naming.InitialContext()).lookup("java:comp/UserTransaction");
            ds = (DataSource)(new javax.naming.InitialContext()).lookup("jdbc/xa");

            System.err.println("calling createPerson(" + personName + ")");
            if (sful == null) {
                // Java SE client
                sful = (Sful)(new javax.naming.InitialContext()).lookup("com.sun.s1asdev.ejb.ejb30.persistence.tx_propagation.Sful");
            }
            sful.setName(personName);
            System.err.println("created ");

            utx.begin();
            System.err.println("utx.begin called ");
            
            connection = ds.getConnection();
            s = connection.prepareStatement("insert into EJB30_PERSISTENCE_EEM_INJECTION_PERSON values('1', '1')");
            s.execute();
            System.err.println("inserted 1,1 into table ");

            Map<String, Boolean> map = sful.doTests();
            if (commit) {
                System.err.println("calling utx.commit ");
                utx.commit();
                System.err.println("utx.commit called ");
            } else {
                System.err.println("calling utx.rollback ");
                utx.rollback();
                System.err.println("utx.rollback called ");
            }
            
            Iterator<String> iter = map.keySet().iterator();
            while (iter.hasNext()) {
                String testName = iter.next();
                boolean result = map.get(testName);
                stat.addStatus("local " + testName,
                        (result) ? stat.PASS : stat.FAIL);
            }

        } catch(Exception e) {
            e.printStackTrace();
            stat.addStatus("local main" , stat.FAIL);
        } finally {

            try {
                if (rs != null)
                    rs.close();
            } catch (Exception e) { }

            try {
                if (s != null)
                    s.close();
            } catch (Exception e) { }

            try {
                if (connection != null)
                    connection.close();
            } catch (Exception e) { }

        }

    	return;
    }


}

