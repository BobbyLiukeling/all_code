/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.resources.beans;

import org.glassfish.resources.api.JavaEEResource;
import org.glassfish.resources.api.JavaEEResourceBase;
import org.glassfish.resourcebase.resources.api.ResourceConstants;
import org.glassfish.resourcebase.resources.api.ResourceInfo;

/**
 * Resource info for ExternalJndiResource.
 * IASRI #4626188
 * <p><b>NOT THREAD SAFE: mutable instance variables</b>
 *
 * @author Sridatta Viswanath
 */
public class ExternalJndiResource extends JavaEEResourceBase {

    private String jndiLookupName_;
    private String resType_;
    private String factoryClass_;

    public ExternalJndiResource(ResourceInfo resourceInfo) {
        super(resourceInfo);
    }

    protected JavaEEResource doClone(ResourceInfo resourceInfo) {
        ExternalJndiResource clone = new ExternalJndiResource(resourceInfo);
        clone.setJndiLookupName(getJndiLookupName());
        clone.setResType(getResType());
        clone.setFactoryClass(getFactoryClass());
        return clone;
    }

    public int getType() {
        return JavaEEResource.EXTERNAL_JNDI_RESOURCE;
    }

    public String getJndiLookupName() {
        return jndiLookupName_;
    }

    public void setJndiLookupName(String jndiLookupName) {
        jndiLookupName_ = jndiLookupName;
    }

    public String getResType() {
        return resType_;
    }

    public void setResType(String resType) {
        resType_ = resType;
    }

    public String getFactoryClass() {
        return factoryClass_;
    }

    public void setFactoryClass(String factoryClass) {
        factoryClass_ = factoryClass;
    }

    //START OF IASRI 4660565
    public boolean isJMSConnectionFactory() {
        if (resType_ == null) return false;

        return (ResourceConstants.JMS_QUEUE_CONNECTION_FACTORY.equals(resType_) ||
                ResourceConstants.JMS_TOPIC_CONNECTION_FACTORY.equals(resType_));
    }
    //END OF IASRI 4660565

    public String toString() {
        return "< External Jndi Resource : " + getResourceInfo() + " , " + getJndiLookupName() + "... >";
    }
}
