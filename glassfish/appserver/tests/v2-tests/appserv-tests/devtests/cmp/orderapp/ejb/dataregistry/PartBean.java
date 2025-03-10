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

package dataregistry;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;

import javax.ejb.*;


public abstract class PartBean implements EntityBean {

    private EntityContext context;


    /**
     * @see EntityBean#setEntityContext(EntityContext)
     */
    public void setEntityContext(EntityContext aContext) {
        context=aContext;
    }


    /**
     * @see EntityBean#ejbActivate()
     */
    public void ejbActivate() {

    }


    /**
     * @see EntityBean#ejbPassivate()
     */
    public void ejbPassivate() {

    }


    /**
     * @see EntityBean#ejbRemove()
     */
    public void ejbRemove() {

    }


    /**
     * @see EntityBean#unsetEntityContext()
     */
    public void unsetEntityContext() {
        context=null;
    }


    /**
     * @see EntityBean#ejbLoad()
     */
    public void ejbLoad() {

    }


    /**
     * @see EntityBean#ejbStore()
     */
    public void ejbStore() {

    }

    public abstract String getPartNumber();
    public abstract void setPartNumber(String partNumber);

    public abstract int getRevision();
    public abstract void setRevision(int revision);

    public abstract String getDescription();
    public abstract void setDescription(String description);

    public abstract Date getRevisionDate();
    public abstract void setRevisionDate(Date revisionDate);

    public abstract Serializable getDrawing();
    public abstract void setDrawing(Serializable drawing);

    public abstract String getSpecification();
    public abstract void setSpecification(String specification);

    public abstract LocalPart getBomPart();
    public abstract void setBomPart(LocalPart bomPart);

    public abstract Collection getParts();
    public abstract void setParts(Collection parts);

    public abstract LocalVendorPart getVendorPart();
    public abstract void setVendorPart(LocalVendorPart vendorPart);

    public PartKey ejbCreate(String partNumber, int revision, String description,
            Date revisionDate, String specification, Serializable drawing)
            throws CreateException {

        setPartNumber(partNumber);
        setRevision(revision);
        setDescription(description);
        setRevisionDate(revisionDate);
        setSpecification(specification);
        setDrawing(drawing);

        return null;
    }

    public void ejbPostCreate(String partNumber, int revision, String description,
            Date revisionDate, String specification, Serializable drawing)
            throws CreateException {
    }

}
