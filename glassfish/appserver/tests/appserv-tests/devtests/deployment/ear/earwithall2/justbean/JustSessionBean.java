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

package justbean;

import java.rmi.RemoteException;
import javax.ejb.SessionBean;
import javax.ejb.SessionContext;

public class JustSessionBean implements SessionBean {
 
    private SessionContext ctx;
    
    public void 
    ejbCreate() 
        throws RemoteException 
    {
        log("JustSessionBean.ejbCreate()...");
    }

    public void 
    ejbRemove() 
        throws RemoteException 
    {
        log("JustSessionBean.ejbRemove()...");
    }
    
    public void
    log(String message) 
    {
        Log.log(message);
    }

    public String[]
    findAllMarbles()
    {
        System.out.println("JustSessionBean.findAllMarbles()...");
        String[] strArray = new String[2];
        strArray[0] = "This is a test.";
        strArray[1] = "You have lost all your marbles.";
        return strArray;
    }
    
    
    /** 
     * ejbDestroy - called by the Container before this bean is destroyed.
     */ 
    public void 
    ejbDestroy() 
    {
        log("JustSessionBean.ejbDestroy()...");
    }
    
    /** 
     * ejbActivate - called by the Container after this bean instance 
     * is activated from its passive state.
     */
    public void 
    ejbActivate() 
    {
        log("JustSessionBean.ejbActivate()...");
    }
    
    /**
     * ejbPassivate - called by the Container before this bean instance 
     * is put in passive state. 
     */ 
    public void 
    ejbPassivate() 
    {
        log("JustSessionBean.ejbPassivate()...");
    }
    
    /**
     * setSessionContext - called by the Container after creation of this
     * bean instance.
     */
    public void 
    setSessionContext(SessionContext context) 
    {
        log("JustSessionBean.setSessionContext(ctx)... ctx = " + ctx);
        ctx = context;
    }
}
