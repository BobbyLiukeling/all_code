/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2002-2017 Oracle and/or its affiliates. All rights reserved.
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

package beans;

import javax.rmi.PortableRemoteObject;
import javax.ejb.SessionBean;
import javax.ejb.SessionContext;
import javax.ejb.EJBException;
import javax.ejb.CreateException;
import java.util.Properties;
import java.util.Vector;
import java.sql.*;
import java.rmi.RemoteException;

import javax.transaction.UserTransaction;
import javax.naming.*;
import javax.sql.*;
//import com.sun.jdbcra.spi.JdbcSetupAdmin;

public class VersionCheckerEJB implements SessionBean {
    private InitialContext initContext = null;
    private SessionContext sessionContext = null;


    public VersionCheckerEJB() {
        debug("Constructor");
    }

    public void ejbCreate()
            throws CreateException {
        debug("ejbCreate()");
    }

    public boolean lookupResource() {
        boolean foundResource = false;
        try {
            InitialContext ic = new InitialContext();
            foundResource = ic.lookup("jdbc/ejb-subclassing") != null;
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            debug("lookupResource() : " + foundResource);
        }
        return foundResource;
    }

    public int getVersion() {
        debug("Checking the version!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        try {
            initContext = new javax.naming.InitialContext();
        } catch (Exception e) {
            System.out.println("Exception occured when creating InitialContext: " + e.toString());
            e.printStackTrace();
            return -1;
        }

        try {
            com.sun.jdbcra.spi.JdbcSetupAdmin ja = (com.sun.jdbcra.spi.JdbcSetupAdmin) initContext.lookup("eis/testAdmin");
            int versionno = ja.getVersion();
            debug("Version number is " + versionno);
            return versionno;
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException(e.getMessage());
        }

        // return -1;
    }


    public void setSessionContext(SessionContext context) {
        debug(" bean removed");
        sessionContext = context;
    }

    public void ejbRemove() {
        debug(" bean removed");
    }

    public void ejbActivate() {
        debug(" bean activated");
    }

    public void ejbPassivate() {
        debug(" bean passivated");
    }


    private void debug(String msg) {
        System.out.println("[VersionCheckerEJB]:: -> " + msg);
    }
}