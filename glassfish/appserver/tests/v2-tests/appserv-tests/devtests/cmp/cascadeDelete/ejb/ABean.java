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

package cascadeDelete;

import javax.ejb.*;
import javax.naming.*;
import java.util.*;

/**
 * Created Dec 23, 2002 12:43:09 PM
 * Code generated by the Forte For Java EJB Builder
 * @author mvatkina
 */


public abstract class ABean implements javax.ejb.EntityBean {
    
    private javax.ejb.EntityContext context;
    LocalBHome bhome;
    LocalCHome chome;
    LocalDHome dhome;

    
    
    /**
     * @see javax.ejb.EntityBean#setEntityContext(javax.ejb.EntityContext)
     */
    public void setEntityContext(javax.ejb.EntityContext aContext) {
        context=aContext;
        try {
            bhome = lookupB();
            chome = lookupC();
            dhome = lookupD();
        } catch (NamingException e) {
            throw new EJBException(e.getMessage());
        }
    }
    
    
    /**
     * @see javax.ejb.EntityBean#ejbActivate()
     */
    public void ejbActivate() {
        
    }
    
    
    /**
     * @see javax.ejb.EntityBean#ejbPassivate()
     */
    public void ejbPassivate() {
        
    }
    
    
    /**
     * @see javax.ejb.EntityBean#ejbRemove()
     */
    public void ejbRemove() {
        System.out.println("Debug: A ejbRemove");
        Collection bs = getBs();
        System.out.println("Bs: " + bs.size());
        System.out.println("Cs: " + getCs().size());
        System.out.println("Ds: " + getDs().size());
        for (java.util.Iterator it = bs.iterator(); it.hasNext();) {
            ((LocalB)it.next()).cascadeDeleteFromA();
        }
        
    }
    
    
    /**
     * @see javax.ejb.EntityBean#unsetEntityContext()
     */
    public void unsetEntityContext() {
        context=null;
    }
    
    
    /**
     * @see javax.ejb.EntityBean#ejbLoad()
     */
    public void ejbLoad() {
        
    }

    
    /**
     * @see javax.ejb.EntityBean#ejbStore()
     */
    public void ejbStore() {
        
    }
    
    public abstract java.lang.Integer getId();
    public abstract void setId(java.lang.Integer id);
    
    public abstract java.lang.String getName();
    public abstract void setName(java.lang.String name);
    
    public abstract java.util.Collection getDs();
    
    public abstract void setDs(java.util.Collection ds);
    
    public abstract java.util.Collection getCs();
    
    public abstract void setCs(java.util.Collection cs);
    
    public abstract java.util.Collection getBs();
    
    public abstract void setBs(java.util.Collection bs);
    
    public java.lang.Integer ejbCreate(java.lang.Integer id, java.lang.String name) throws javax.ejb.CreateException {
        setId(id);
        setName(name);
        return null;
    }
    
    public void ejbPostCreate(java.lang.Integer id, java.lang.String name) throws javax.ejb.CreateException {
    }
    
    public void addAll() {
        try {
            System.out.println("Debug: A addB");
            Collection bs = bhome.findAll();
            getBs().addAll(bs);
            
            System.out.println("Debug: A addC");
            Collection cs = chome.findAll();
            getCs().addAll(cs);
            
            System.out.println("Debug: A addD");
            Collection ds = dhome.findAll();
            getDs().addAll(ds);
            
            System.out.println("Debug: A addOthers");
            for (Iterator it = bs.iterator(); it.hasNext();) {
                LocalB b = (LocalB)it.next();
                Integer pk = b.getId();
                
                System.out.println("Debug: A add to B " + pk);
                LocalC c = chome.findByPrimaryKey(pk);
                b.setC(c);
                int i = pk.intValue() - 1;
                System.out.println("Debug: A find Ds between " + (i*10) + " and " + (i*20));
                ds = dhome.findInRange(new Integer(i*10), new Integer(i*20));

                b.getDs().addAll(ds);
                c.getDs().addAll(ds);
            }
        } catch (Exception e) {
            throw new EJBException(e.getMessage());
        }
    }
    
    private LocalBHome lookupB() throws NamingException {
        System.out.println("Debug: A lookupB");
        Context initial = new InitialContext();
        Object objref = initial.lookup("java:comp/env/ejb/SimpleB");
        return (LocalBHome) objref;
    }
    
    private LocalCHome lookupC() throws NamingException {
        System.out.println("Debug: A lookupC");
        Context initial = new InitialContext();
        Object objref = initial.lookup("java:comp/env/ejb/SimpleC");
        return (LocalCHome) objref;
    }
    
    private LocalDHome lookupD() throws NamingException {
        System.out.println("Debug: A lookupD");
        Context initial = new InitialContext();
        Object objref = initial.lookup("java:comp/env/ejb/SimpleD");
        return (LocalDHome) objref;
    }

}