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

package Data;

import javax.ejb.*;
import javax.naming.*; 


/**
 * Created Dec 16, 2002 2:08:21 PM
 * Code generated by the Forte For Java EJB Builder
 * @author mvatkina
 */


public class SPSessionBean implements javax.ejb.SessionBean {
    private javax.ejb.SessionContext context;
    private LocalSuppliersHome suppliersHome = null;
    private LocalPartsHome partsHome = null;
    
    
    /**
     * @see javax.ejb.SessionBean#setSessionContext(javax.ejb.SessionContext)
     */
    public void setSessionContext(javax.ejb.SessionContext aContext) {
        context=aContext;
    }
    
    
    /**
     * @see javax.ejb.SessionBean#ejbActivate()
     */
    public void ejbActivate() {
        
    }
    
    
    /**
     * @see javax.ejb.SessionBean#ejbPassivate()
     */
    public void ejbPassivate() {
        
    }
    
    
    /**
     * @see javax.ejb.SessionBean#ejbRemove()
     */
    public void ejbRemove() {
        
    }
    
    
    /**
     * See section 7.10.3 of the EJB 2.0 specification
     */
    public void ejbCreate() throws CreateException {
        System.out.println("Debug: SPSession ejbCreate");
        try {
            suppliersHome = lookupSuppliers();
            partsHome = lookupParts();
        } catch (NamingException ex) {System.out.println("lookupSuppliers");
            throw new CreateException(ex.getMessage());
        }
    }
    
    private LocalSuppliersHome lookupSuppliers() throws NamingException {
        System.out.println("Debug: SPSession lookupSuppliers");
        Context initial = new InitialContext();
        Object objref = initial.lookup("java:comp/env/ejb/SimpleSuppliers");
        return (LocalSuppliersHome) objref;
    }
    
    private LocalPartsHome lookupParts() throws NamingException {
        System.out.println("Debug: SPSession lookupParts");
        Context initial = new InitialContext();
        Object objref = initial.lookup("java:comp/env/ejb/SimpleParts");
        return (LocalPartsHome) objref;
    }
    
    public int checkAllParts() {
        System.out.println("Debug: SPSessionBean getAllParts");
        java.util.Collection parts = null;
        try {
            parts = partsHome.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
            throw new EJBException(ex.getMessage());
        }
        return parts.size();
    }
    
    public int checkAllSuppliers() {
        System.out.println("Debug: SPSessionBean getAllSuppliers");
        java.util.Collection suppliers = null;
        try {
            suppliers = suppliersHome.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
            throw new EJBException(ex.getMessage());
        }
        return suppliers.size();
    }
    
    public void createPartsAndSuppliers() {
       try {
            System.out.println("InsertData");
            java.lang.Integer partid1 = new java.lang.Integer(807);
            java.lang.Integer partid2 = new java.lang.Integer(200);
            java.lang.Integer partid3 = new java.lang.Integer(145);
            java.lang.Integer supplierid1= new java.lang.Integer(103);
            java.lang.Integer supplierid2= new java.lang.Integer(145);
            java.lang.Integer supplierid3= new java.lang.Integer(122);
            
            partsHome.create(partid1,"partname1","red", new java.math.BigDecimal(45), new java.lang.Double(99));
            partsHome.create(partid2,"partname2","blue", new java.math.BigDecimal(37), new java.lang.Double(50));
            partsHome.create(partid3,"partname3","green", new java.math.BigDecimal(222), new java.lang.Double(65));
            suppliersHome.create(partid1,supplierid1,"suppliername1",1,"San Jose");
            suppliersHome.create(partid1,supplierid2,"suppliername2",1,"Oakland");
            suppliersHome.create(partid1,supplierid3,"suppliername3",1,"Menlo Park");
            suppliersHome.create(partid2,supplierid2,"suppliername2",1,"Oakland");
            suppliersHome.create(partid2,supplierid3,"suppliername3",1,"Menlo Park");
            suppliersHome.create(partid3,supplierid2,"suppliername2",1,"Oakland");
        } catch (Exception ex) {
            System.err.println("Caught an exception during createPartsAndSuppliers:");
            ex.printStackTrace();
        }
    }
    
    public void removePart(java.lang.Integer partid) {
        System.out.println("Debug: SPSession removePart");
        try {
            LocalParts parts = partsHome.findByPrimaryKey(partid);
            parts.remove();
        } catch (Exception ex) {
            System.out.println("inside removePart exception");
            ex.printStackTrace();
            throw new EJBException(ex.getMessage());
        }
    }
    
    public void removeSupplier(java.lang.Integer partid, java.lang.Integer supplierid) {
        System.out.println("Debug: SPSession removeSupplier");
        try {
            SuppliersKey key = new SuppliersKey();
            key.partid = partid;
            key.supplierid = supplierid;
            LocalSuppliers supplier = suppliersHome.findByPrimaryKey(key);
            supplier.remove();
        } catch (Exception ex) {
            System.out.println("inside removeSupplier exception");
            ex.printStackTrace();
            throw new EJBException(ex.getMessage());
        }
    }
    
}
