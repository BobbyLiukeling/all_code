/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2008-2017 Oracle and/or its affiliates. All rights reserved.
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

//  
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.1.3-04/12/2007 12:08 AM(kohsuke)-fcs
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a>
// Any modifications to this file will be lost upon recompilation of the source schema.
// Generated on: 2007.08.24 at 01:25:15 PM PDT
//


package org.glassfish.connectors.config;

import com.sun.enterprise.config.serverbeans.Resource;
import com.sun.enterprise.config.serverbeans.ResourcePool;
import org.glassfish.connectors.config.validators.ConnectionPoolConstraint;
import org.glassfish.connectors.config.validators.ConnectionPoolConstraints;
import org.glassfish.connectors.config.validators.ConnectionPoolErrorMessages;
import org.glassfish.admin.cli.resources.UniqueResourceNameConstraint;
import org.glassfish.resourcebase.resources.ResourceTypeOrder;
import org.glassfish.resourcebase.resources.ResourceDeploymentOrder;
import org.jvnet.hk2.config.*;
import org.jvnet.hk2.config.types.Property;
import org.jvnet.hk2.config.types.PropertyBag;

import java.beans.PropertyVetoException;
import java.util.List;

import org.glassfish.api.admin.config.PropertiesDesc;
import org.glassfish.api.admin.RestRedirects;
import org.glassfish.api.admin.RestRedirect;

import org.glassfish.quality.ToDo;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;

/**
 * Defines configuration used to create and manage
 * a pool of connections to a EIS. Pool definition is named, and can be referred
 * to by multiple connector-resource elements (See connector-resource)
 *
 * Each named pool definition results in a pool instantiated at server start-up.
 * Pool is populated when accessed for the first time. If two or more
 * connector-resource elements point to the same connector-connection-pool
 * element, they are using the same pool of connections, at run time
 *
 * There can be more than one pool for one connection-definition in one
 * resource-adapter
 * 
 */

/* @XmlType(name = "", propOrder = {
    "description",
    "securityMap",
    "property"
}) */

@Configured
@ConnectionPoolConstraints({
    @ConnectionPoolConstraint(value = ConnectionPoolErrorMessages.MAX_STEADY_INVALID)
})
@RestRedirects({
 @RestRedirect(opType = RestRedirect.OpType.POST, commandName = "create-connector-connection-pool"),
 @RestRedirect(opType = RestRedirect.OpType.DELETE, commandName = "delete-connector-connection-pool")
})
@ResourceTypeOrder(deploymentOrder=ResourceDeploymentOrder.CONNECTOR_POOL)
@UniqueResourceNameConstraint(message="{resourcename.isnot.unique}", payload=ConnectorConnectionPool.class)
public interface ConnectorConnectionPool extends ConfigBeanProxy, Resource, ResourcePool,
        PropertyBag {

    /**
     * Gets the value of the resourceAdapterName property.
     * 
     * This is the name of resource adapter. Name of .rar file is taken as the
     * unique name for the resource adapter.
     *
     * @param value allowed object is
     *              {@link String }
     */
    @Attribute
    @NotNull
    String getResourceAdapterName();

    /**
     * Sets the value of the resourceAdapterName property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setResourceAdapterName(String value) throws PropertyVetoException;

    /**
     * Gets the value of the connectionDefinitionName property.
     * Unique name, identifying one connection-definition in a Resource Adapter.
     * Currently this is ConnectionFactory type.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute
    @NotNull
    String getConnectionDefinitionName();

    /**
     * Sets the value of the connectionDefinitionName property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setConnectionDefinitionName(String value) throws PropertyVetoException;

    /**
     * Gets the value of the steadyPoolSize property.
     *
     * Minimum and initial number of connections maintained in the pool
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="8")
    @Min(value=0)
    String getSteadyPoolSize();

    /**
     * Sets the value of the steadyPoolSize property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setSteadyPoolSize(String value) throws PropertyVetoException;

    /**
     * Gets the value of the maxPoolSize property.
     *
     * Maximum number of conections that can be created
     * 
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="32")
    @Min(value=1)
    String getMaxPoolSize();

    /**
     * Sets the value of the maxPoolSize property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setMaxPoolSize(String value) throws PropertyVetoException;

    /**
     * Gets the value of the maxWaitTimeInMillis property.
     *
     * Amount of time the caller will wait before getting a connection timeout.
     * The default is 60 seconds. A value of 0 will force caller to wait
     * indefinitely.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="60000")
    @Min(value=0)
    String getMaxWaitTimeInMillis();

    /**
     * Sets the value of the maxWaitTimeInMillis property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setMaxWaitTimeInMillis(String value) throws PropertyVetoException;

    /**
     * Gets the value of the poolResizeQuantity property.
     *
     * Number of connections to be removed when idle-timeout-in-seconds timer
     * expires. Connections that have idled for longer than the timeout are
     * candidates for removal. When the pool size reaches steady-pool-size,
     * the connection removal stops.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="2")
    @Min(value=1)
    String getPoolResizeQuantity();

    /**
     * Sets the value of the poolResizeQuantity property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setPoolResizeQuantity(String value) throws PropertyVetoException;

    /**
     * Gets the value of the idleTimeoutInSeconds property.
     *
     * Maximum time in seconds, that a connection can remain idle in the pool.
     * After this time, the pool implementation can close this connection.
     *
     * Note that this does not control connection timeouts enforced at the
     * database server side. Adminsitrators are advised to keep this timeout
     * shorter than the EIS connection timeout (if such timeouts are configured
     * on the specific EIS), to prevent accumulation of unusable connection in
     * Application Server.                                        
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="300")
    @Min(value=1)
    @Max(value=Integer.MAX_VALUE)
    String getIdleTimeoutInSeconds();

    /**
     * Sets the value of the idleTimeoutInSeconds property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setIdleTimeoutInSeconds(String value) throws PropertyVetoException;

    /**
     * Gets the value of the failAllConnections property.
     *
     * Indicates if all connections in the pool must be closed should a single
     * connection fail validation. The default is false. One attempt will be
     * made to re-establish failed connections.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getFailAllConnections();

    /**
     * Sets the value of the failAllConnections property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setFailAllConnections(String value) throws PropertyVetoException;

    /**
     * Gets the value of the transactionSupport property.
     *
     * Indicates the level of transaction support that this pool will have.
     * Possible values are "XATransaction", "LocalTransaction" & "NoTransaction"
     * This attribute will override that transaction support attribute in the
     * Resource Adapter in a downward compatible way, i.e it can support a lower
     * or equal transaction level than specified in the RA, but not higher level
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute
    String getTransactionSupport();

    /**
     * Sets the value of the transactionSupport property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setTransactionSupport(String value) throws PropertyVetoException;

    /**
     * Gets the value of the isConnectionValidationRequired property.
     *
     * This attribute specifies if the connection that is about to be returned
     * is to be validated by the container,
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getIsConnectionValidationRequired();

    /**
     * Sets the value of the isConnectionValidationRequired property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setIsConnectionValidationRequired(String value) throws PropertyVetoException;

    /**
     * Gets the value of the validateAtmostOncePeriodInSeconds property.
     *
     * Used to set the time-interval within which a connection is validated
     * atmost once. Default is 0 which implies that it is not enabled.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="0")
    @Min(value=0)
    String getValidateAtmostOncePeriodInSeconds();

    /**
     * Sets the value of the validateAtmostOncePeriodInSeconds property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setValidateAtmostOncePeriodInSeconds(String value) throws PropertyVetoException;

    /**
     * Gets the value of the connectionLeakTimeoutInSeconds property.
     *
     * To aid user in detecting potential connection leaks by the application.
     * When a connection is not returned back to the pool by the application
     * within the specified period, it is assumed to be a potential leak and
     * stack trace of the caller will be logged.
     *
     * Default is 0, which implies there is no leak detection, by default.
     * A positive non-zero value turns on leak detection. Note however that,
     * this attribute only detects if there is a connection leak. The connection
     * can be reclaimed only if connection-leak-reclaim is set to true.
     * 
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="0")
    @Min(value=0)
    String getConnectionLeakTimeoutInSeconds();

    /**
     * Sets the value of the connectionLeakTimeoutInSeconds property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setConnectionLeakTimeoutInSeconds(String value) throws PropertyVetoException;

    /**
     * Gets the value of the connectionLeakReclaim property.
     * If enabled, connection will be reusable (put back into pool) after
     * connection-leak-timeout-in-seconds occurs.
     * 
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getConnectionLeakReclaim();

    /**
     * Sets the value of the connectionLeakReclaim property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setConnectionLeakReclaim(String value) throws PropertyVetoException;

    /**
     * Gets the value of the connectionCreationRetryAttempts property.
     *
     * The number of attempts to create a new connection. Default is 0,
     * which implies no retries.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="0")
    String getConnectionCreationRetryAttempts();

    /**
     * Sets the value of the connectionCreationRetryAttempts property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setConnectionCreationRetryAttempts(String value) throws PropertyVetoException;

    /**
     * Gets the value of the connectionCreationRetryIntervalInSeconds property.
     *
     * The time interval between retries while attempting to create a connection
     * Default is 10 seconds. Effective when connection-creation-retry-attempts
     * is greater than 0.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="10")
    String getConnectionCreationRetryIntervalInSeconds();

    /**
     * Sets the value of the connectionCreationRetryIntervalInSeconds property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setConnectionCreationRetryIntervalInSeconds(String value) throws PropertyVetoException;

    /**
     * Gets the value of the lazyConnectionEnlistment property.
     *
     * Enlist a resource to the transaction only when it is actually used in a
     * method, which avoids enlistment of connections that are not used in a
     * transaction. This also prevents unnecessary enlistment of connections
     * cached in the calling components. Default value is false.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getLazyConnectionEnlistment();

    /**
     * Sets the value of the lazyConnectionEnlistment property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setLazyConnectionEnlistment(String value) throws PropertyVetoException;

    /**
     * Gets the value of the lazyConnectionAssociation property.
     *
     * Connections are lazily associated when an operation is performed on them.
     * Also, they are disassociated when the transaction is completed and a
     * component method ends, which helps reuse of the physical connections.
     * Default value is false.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getLazyConnectionAssociation();

    /**
     * Sets the value of the lazyConnectionAssociation property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setLazyConnectionAssociation(String value) throws PropertyVetoException;

    /**
     * Gets the value of the associateWithThread property.
     *
     * Associate a connection with the thread such that when the same thread is
     * in need of a connection, it can reuse the connection already associated
     * with that thread, thereby not incurring the overhead of getting a
     * connection from the pool.
     * 
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="false",dataType=Boolean.class)
    String getAssociateWithThread();

    /**
     * Sets the value of the associateWithThread property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setAssociateWithThread(String value) throws PropertyVetoException;

    /**
     * Gets the value of the pooling property.
     *
     * Property to disable pooling for the pool.
     * 
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="true",dataType=Boolean.class)
    String getPooling();

    /**
     * Sets the value of the pooling property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setPooling(String value) throws PropertyVetoException;
    
    /**
     * Gets the value of the matchConnections property.
     *
     * To switch on/off connection matching for the pool. It can be set to false
     * if the administrator knows that the connections in the pool will always
     * be homogeneous and hence a connection picked from the pool need not be
     * matched by the resource adapter. Default value is true.                               
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="true",dataType=Boolean.class)
    String getMatchConnections();

    /**
     * Sets the value of the matchConnections property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setMatchConnections(String value) throws PropertyVetoException;

    /**
     * Gets the value of the maxConnectionUsageCount property.
     * When specified, connections will be re-used by the pool for the specified
     * number of times after which it will be closed. This is useful for
     * instance, to avoid statement-leaks. Default value is 0, which implies the
     * feature is not enabled.
     *
     * @return possible object is
     *         {@link String }
     */
    @Attribute (defaultValue="0")
    @Min(value=0)
    @Max(value=Integer.MAX_VALUE)
    String getMaxConnectionUsageCount();

    /**
     * Sets the value of the maxConnectionUsageCount property.
     *
     * @param value allowed object is
     *              {@link String }
     */
    void setMaxConnectionUsageCount(String value) throws PropertyVetoException;

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
     * Gets the value of the securityMap property.
     * <p/>
     * <p/>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the securityMap property.
     * <p/>
     * <p/>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getSecurityMap().add(newItem);
     * </pre>
     * <p/>
     * <p/>
     * <p/>
     * Objects of the following type(s) are allowed in the list
     * {@link SecurityMap }
     */
    @Element
    @NotNull
    List<SecurityMap> getSecurityMap();
    
    /**
     *	Properties as per {@link org.jvnet.hk2.config.types.PropertyBag}
     *
     *  Properties are used to override the ManagedConnectionFactory  javabean
     * configuration settings. When one or more of these properties are
     * specified, they are passed as is using set<Name>(<Value>) methods to the
     * Resource Adapter's ManagedConnectionfactory class (specified in ra.xml).
     *
     */
    @ToDo(priority=ToDo.Priority.IMPORTANT, details="Provide PropertyDesc for legal props" )
    @PropertiesDesc(props={})
    @Element
    List<Property> getProperty();

    @DuckTyped
    String getIdentity();

    class Duck {
        public static String getIdentity(ConnectorConnectionPool resource){
            return resource.getName();
        }
    }

}
