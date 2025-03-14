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

package com.sun.s1asdev.ejb.ee.ejb;

import javax.ejb.SessionBean;
import javax.ejb.SessionContext;
import javax.ejb.*;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.*;
import javax.rmi.PortableRemoteObject;

import javax.transaction.UserTransaction;

import java.rmi.RemoteException;

public class BMTSessionBean
    implements SessionBean 
{

    private static final String LOCAL_CHILD_SUFFIX = "_childLocal";

    private transient String message;

    private int activateCount;
    private int passivateCount;
    private int	count;

    private SessionContext              sessionCtx;
    private String                      sfsbName;
    private UserTransaction		userTx;

    public void ejbCreate(String sfsbName) {
        System.out.println ("In SFSB.ejbCreate() for name -> " + sfsbName);
        this.sfsbName = sfsbName;
    }

    public String getName() {
        System.out.println("In getName() for " + sfsbName);
        return this.sfsbName;
    }

    public String getTxName() {
        return this.sfsbName;
    }

    public void checkpoint() {
    }

    public void checkpoint2() {
    }

    public void setSessionContext(SessionContext sc) {
        this.sessionCtx = sc;
    }

    public void startTx() {
	try {
	    userTx = sessionCtx.getUserTransaction();
	    userTx.begin();
	} catch (Exception ex) {
	    throw new EJBException(ex.toString());
	}
    }

    public void commitTx() {
	try {
	    userTx.commit();
	} catch (Exception ex) {
	    throw new EJBException(ex.toString());
	}
    }

    public void rollbackTx() {
	try {
	    userTx.rollback();
	} catch (Exception ex) {
	    throw new EJBException(ex.toString());
	}
    }

    public void incrementCount() {
	count++;
    }

    public int getActivateCount() {
	return activateCount;
    }

    public int getPassivateCount() {
	return passivateCount;
    }

    public void ejbRemove() {}

    public void ejbActivate() {
	activateCount++;
    }

    public void ejbPassivate() {
	passivateCount++;
    }

}
