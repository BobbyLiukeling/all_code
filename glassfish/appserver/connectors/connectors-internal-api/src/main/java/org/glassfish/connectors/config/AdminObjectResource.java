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

package org.glassfish.connectors.config;

import com.sun.enterprise.config.serverbeans.BindableResource;
import com.sun.enterprise.config.serverbeans.Resource;
import org.glassfish.admin.cli.resources.ResourceConfigCreator;
import org.glassfish.api.admin.RestRedirect;
import org.glassfish.api.admin.RestRedirects;
import org.glassfish.api.admin.config.PropertiesDesc;
import org.glassfish.quality.ToDo;
import org.glassfish.admin.cli.resources.UniqueResourceNameConstraint;
import org.glassfish.resourcebase.resources.ResourceTypeOrder;
import org.glassfish.resourcebase.resources.ResourceDeploymentOrder;
import org.jvnet.hk2.config.*;
import org.jvnet.hk2.config.types.Property;
import org.jvnet.hk2.config.types.PropertyBag;

import javax.validation.constraints.NotNull;
import java.beans.PropertyVetoException;
import java.util.List;

/**
 *
 */
@Configured
@ResourceConfigCreator(commandName="create-admin-object")
@RestRedirects({
 @RestRedirect(opType = RestRedirect.OpType.POST, commandName = "create-admin-object"),
 @RestRedirect(opType = RestRedirect.OpType.DELETE, commandName = "delete-admin-object")
})
@ResourceTypeOrder(deploymentOrder=ResourceDeploymentOrder.ADMIN_OBJECT_RESOURCE)
@UniqueResourceNameConstraint(message="{resourcename.isnot.unique}", payload=AdminObjectResource.class)
/**
 * The admin-object-resource element describes a administered object
 * for a inbound resource adapter.
 */
public interface AdminObjectResource extends ConfigBeanProxy, BindableResource, Resource,
    PropertyBag {

    /**
     * Interface definition for the administered object
     * @return the interface definition
     */
    @Attribute
    @NotNull
    String getResType();

    /**
     * Sets the Interface definition for the administered object
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setResType(String value) throws PropertyVetoException;

    /**
     * Gets the value of the resAdapter property.
     * Name of the inbound resource adapter
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute
    @NotNull
    String getResAdapter();


    /**
     * Gets the value of the (admin object) classname property.
     * Name of the admin object class
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute
    String getClassName();

    /**
     * Sets the value of the (admin object) classname property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setClassName(String value) throws PropertyVetoException;

    /**
     * Sets the value of the resAdapter property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setResAdapter(String value) throws PropertyVetoException;

    /**
     * Gets the value of the enabled property.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="true",dataType=Boolean.class)
    String getEnabled();

    /**
     * Sets the value of the enabled property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setEnabled(String value) throws PropertyVetoException;

    /**
     * Gets the value of the description property.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute
    String getDescription();

    /**
     * Sets the value of the description property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setDescription(String value) throws PropertyVetoException;
    
    /**
    	Properties as per {@link PropertyBag}
     */
    @ToDo(priority=ToDo.Priority.IMPORTANT, details="Provide PropertyDesc for legal props" )
    @PropertiesDesc(props={})
    @Element
    List<Property> getProperty();

    @DuckTyped
    String getIdentity();

    class Duck {
        public static String getIdentity(AdminObjectResource resource){
            return resource.getJndiName();
        }
    }

}