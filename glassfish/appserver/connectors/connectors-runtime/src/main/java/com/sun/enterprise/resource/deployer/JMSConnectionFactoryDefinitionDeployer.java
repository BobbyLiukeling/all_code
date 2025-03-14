/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2012-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.resource.deployer;

import com.sun.appserv.connectors.internal.api.ConnectorConstants;
import com.sun.appserv.connectors.internal.api.ConnectorsUtil;
import com.sun.enterprise.config.serverbeans.Resource;
import com.sun.enterprise.config.serverbeans.Resources;
import com.sun.enterprise.deployment.JMSConnectionFactoryDefinitionDescriptor;
import com.sun.logging.LogDomains;
import org.glassfish.connectors.config.ConnectorConnectionPool;
import org.glassfish.connectors.config.ConnectorResource;
import org.glassfish.connectors.config.SecurityMap;
import org.glassfish.resourcebase.resources.api.ResourceConflictException;
import org.glassfish.resourcebase.resources.api.ResourceDeployer;
import org.glassfish.resourcebase.resources.api.ResourceDeployerInfo;
import org.glassfish.resourcebase.resources.util.ResourceManagerFactory;
import org.jvnet.hk2.annotations.Service;
import org.jvnet.hk2.config.ConfigBeanProxy;
import org.jvnet.hk2.config.TransactionFailure;
import org.jvnet.hk2.config.types.Property;

import javax.inject.Inject;
import javax.inject.Provider;
import java.beans.PropertyVetoException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map.Entry;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

import static org.glassfish.deployment.common.JavaEEResourceType.*;

@Service
@ResourceDeployerInfo(JMSConnectionFactoryDefinitionDescriptor.class)
public class JMSConnectionFactoryDefinitionDeployer implements ResourceDeployer {

    @Inject
    private Provider<ResourceManagerFactory> resourceManagerFactoryProvider;

    private static Logger _logger = LogDomains.getLogger(JMSConnectionFactoryDefinitionDeployer.class, LogDomains.RSR_LOGGER);
    final static String PROPERTY_PREFIX = "org.glassfish.connector-connection-pool.";

    public void deployResource(Object resource, String applicationName, String moduleName) throws Exception {
        //TODO ASR
    }

    public void deployResource(Object resource) throws Exception {

        final JMSConnectionFactoryDefinitionDescriptor desc = (JMSConnectionFactoryDefinitionDescriptor)resource;
        String poolName = ConnectorsUtil.deriveResourceName(desc.getResourceId(), desc.getName(), JMSCFDDPOOL);
        String resourceName = ConnectorsUtil.deriveResourceName(desc.getResourceId(), desc.getName(), desc.getResourceType());

        if(_logger.isLoggable(Level.FINE)) {
            _logger.log(Level.FINE, "JMSConnectionFactoryDefinitionDeployer.deployResource() : pool-name [" + poolName + "], " +
                    " resource-name ["+resourceName+"]");
        }

        ConnectorConnectionPool connectorCp = new MyJMSConnectionFactoryConnectionPool(desc, poolName);

        //deploy pool
        getDeployer(connectorCp).deployResource(connectorCp);

        //deploy resource
        ConnectorResource connectorResource = new MyJMSConnectionFactoryResource(poolName, resourceName);
        getDeployer(connectorResource).deployResource(connectorResource);

    }

    /**
     * {@inheritDoc}
     */
    public boolean canDeploy(boolean postApplicationDeployment, Collection<Resource> allResources, Resource resource) {
        if (handles(resource)) {
            if (!postApplicationDeployment) {
                return true;
            }
        }
        return false;
    }

    /**
     * {@inheritDoc}
     */
    public void validatePreservedResource(com.sun.enterprise.config.serverbeans.Application oldApp,
                                          com.sun.enterprise.config.serverbeans.Application newApp,
                                          Resource resource,
                                          Resources allResources)
    throws ResourceConflictException {
        //do nothing.
    }


    private ResourceDeployer getDeployer(Object resource) {
        return resourceManagerFactoryProvider.get().getResourceDeployer(resource);
    }

    private JMSConnectionFactoryProperty convertProperty(String name, String value) {
        return new JMSConnectionFactoryProperty(name, value);
    }

    public void undeployResource(Object resource, String applicationName, String moduleName) throws Exception {
        //TODO ASR
    }

    public void undeployResource(Object resource) throws Exception {

        final JMSConnectionFactoryDefinitionDescriptor desc = (JMSConnectionFactoryDefinitionDescriptor) resource;

        String poolName = ConnectorsUtil.deriveResourceName(desc.getResourceId(), desc.getName(), JMSCFDDPOOL);
        String resourceName = ConnectorsUtil.deriveResourceName(desc.getResourceId(), desc.getName(), desc.getResourceType());

        if(_logger.isLoggable(Level.FINE)) {
            _logger.log(Level.FINE, "JMSConnectionFactoryDefinitionDeployer.undeployResource() : pool-name [" + poolName + "], " +
                    " resource-name ["+resourceName+"]");
        }

        //undeploy resource
        ConnectorResource connectorResource = new MyJMSConnectionFactoryResource(poolName, resourceName);
        getDeployer(connectorResource).undeployResource(connectorResource);

        //undeploy pool
        ConnectorConnectionPool connectorCp = new MyJMSConnectionFactoryConnectionPool(desc, poolName);
        getDeployer(connectorCp).undeployResource(connectorCp);

    }

    public void redeployResource(Object resource) throws Exception {
        throw new UnsupportedOperationException("redeploy() not supported for jms-connection-factory-definition type");
    }

    public void enableResource(Object resource) throws Exception {
        throw new UnsupportedOperationException("enable() not supported for jms-connection-factory-definition type");
    }

    public void disableResource(Object resource) throws Exception {
        throw new UnsupportedOperationException("disable() not supported for jms-connection-factory-definition type");
    }

    public boolean handles(Object resource) {
        return resource instanceof JMSConnectionFactoryDefinitionDescriptor;
    }

    /**
     * @inheritDoc
     */
    public boolean supportsDynamicReconfiguration() {
        return false;
    }

    /**
     * @inheritDoc
     */
    @SuppressWarnings("rawtypes")
    public Class[] getProxyClassesForDynamicReconfiguration() {
        return new Class[0];
    }

    private boolean isValidProperty(String s) {
        return (s != null) && !s.equals("");
    }

    abstract class FakeConfigBean implements ConfigBeanProxy {

        public ConfigBeanProxy deepCopy(ConfigBeanProxy parent) {
            throw new UnsupportedOperationException();
        }

        public ConfigBeanProxy getParent() {
            return null;
        }

        public <T extends ConfigBeanProxy> T getParent(Class<T> tClass) {
            return null;
        }

        public <T extends ConfigBeanProxy> T createChild(Class<T> tClass) throws TransactionFailure {
            return null;
        }
    }

    class JMSConnectionFactoryProperty extends FakeConfigBean implements Property {

        private String name;
        private String value;
        private String description;

        JMSConnectionFactoryProperty(String name, String value) {
            this.name = name;
            this.value = value;
        }

        public String getName() {
            return name;
        }

        public void setName(String value) throws PropertyVetoException {
            this.name = value;
        }

        public String getValue() {
            return value;
        }

        public void setValue(String value) throws PropertyVetoException {
            this.value = value;
        }

        public String getDescription() {
            return description;
        }

        public void setDescription(String value) throws PropertyVetoException {
            this.description = value;
        }

        public void injectedInto(Object o) {
            //do nothing
        }
    }

    class MyJMSConnectionFactoryResource extends FakeConfigBean implements ConnectorResource {

        private String poolName;
        private String jndiName;

        MyJMSConnectionFactoryResource(String poolName, String jndiName) {
            this.poolName = poolName;
            this.jndiName = jndiName;
        }

        public String getPoolName() {
            return poolName;
        }

        public void setPoolName(String value) throws PropertyVetoException {
            this.poolName = value;
        }

        public String getObjectType() {
            return null;
        }

        public void setObjectType(String value) throws PropertyVetoException {
        }

        public String getIdentity() {
            return jndiName;
        }

        public String getEnabled() {
            return String.valueOf(true);
        }

        public void setEnabled(String value) throws PropertyVetoException {
        }

        public String getDescription() {
            return null;
        }

        public void setDescription(String value) throws PropertyVetoException {
        }

        public List<Property> getProperty() {
            return null;
        }

        public Property getProperty(String name) {
            return null;
        }

        public String getPropertyValue(String name) {
            return null;
        }

        public String getPropertyValue(String name, String defaultValue) {
            return null;
        }

        public void injectedInto(Object o) {
        }

        public String getJndiName() {
            return jndiName;
        }

        public void setJndiName(String value) throws PropertyVetoException {
            this.jndiName = value;
        }

        public String getDeploymentOrder() {
            return null;
        }

        public void setDeploymentOrder(String value) {
            //do nothing
        }

        @Override
        public Property addProperty(Property prprt) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property lookupProperty(String string) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property removeProperty(String string) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property removeProperty(Property prprt) {
            throw new UnsupportedOperationException("Not supported yet.");
        }
    }

    class MyJMSConnectionFactoryConnectionPool extends FakeConfigBean implements ConnectorConnectionPool {

        private JMSConnectionFactoryDefinitionDescriptor desc;
        private String name;

        public MyJMSConnectionFactoryConnectionPool(JMSConnectionFactoryDefinitionDescriptor desc, String name) {
            this.desc = desc;
            this.name = name;
        }

        @Override
        public String getObjectType() {
            return "user";  //To change body of implemented methods use File | Settings | File Templates.
        }

        @Override
        public void setObjectType(String value) throws PropertyVetoException {
            //To change body of implemented methods use File | Settings | File Templates.
        }

        public String getIdentity() {
            return name;
        }

        public String getSteadyPoolSize() {
            int minPoolSize = desc.getMinPoolSize();
            if (minPoolSize >= 0) {
                return String.valueOf(minPoolSize);
            } else {
                return "8";
            }
        }

        public void setSteadyPoolSize(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getMaxPoolSize() {
            int maxPoolSize = desc.getMaxPoolSize();
            if (maxPoolSize >= 0) {
                return String.valueOf(maxPoolSize);
            } else {
                return "32";
            }
        }

        public void setMaxPoolSize(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getMaxWaitTimeInMillis() {
            String maxWaitTimeInMillis = desc.getProperty(PROPERTY_PREFIX + "max-wait-time-in-millis");
            if (isValidProperty(maxWaitTimeInMillis)) {
                return maxWaitTimeInMillis;
            } else {
                return "60000";
            }
        }

        public void setMaxWaitTimeInMillis(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getPoolResizeQuantity() {
            String poolResizeQuantity = desc.getProperty(PROPERTY_PREFIX + "pool-resize-quantity");
            if (isValidProperty(poolResizeQuantity)) {
                return poolResizeQuantity;
            } else {
                return "2";
            }
        }

        public void setPoolResizeQuantity(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getIdleTimeoutInSeconds() {
            String idleTimeoutInSeconds = desc.getProperty(PROPERTY_PREFIX + "idle-timeout-in-seconds");
            if (isValidProperty(idleTimeoutInSeconds)) {
                return idleTimeoutInSeconds;
            } else {
                return "300";
            }
        }

        public void setIdleTimeoutInSeconds(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getIsConnectionValidationRequired() {
            String isConnectionValidationRequired = desc.getProperty(PROPERTY_PREFIX + "is-connection-validation-required");
            if (isValidProperty(isConnectionValidationRequired)) {
                return isConnectionValidationRequired;
            } else {
                return "false";
            }
        }

        public void setIsConnectionValidationRequired(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getResourceAdapterName() {
            String resourceAdapter = desc.getResourceAdapter();
            if (isValidProperty(resourceAdapter)) {
                return resourceAdapter;
            } else {
                return ConnectorConstants.DEFAULT_JMS_ADAPTER;
            }
        }

        public void setResourceAdapterName(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getConnectionDefinitionName() {
            String interfaceName = desc.getInterfaceName();
            if (isValidProperty(interfaceName)) {
                return interfaceName;
            } else {
                return "javax.jms.ConnectionFactory";
            }
        }

        public void setConnectionDefinitionName(String value)  throws PropertyVetoException {
            //do nothing
        }

        public String getFailAllConnections() {
            String failAllConnections = desc.getProperty(PROPERTY_PREFIX + "fail-all-connections");
            if (isValidProperty(failAllConnections)) {
                return failAllConnections;
            } else {
                return "false";
            }
        }

        public void setFailAllConnections(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getTransactionSupport() {
            String transactionSupport = desc.getProperty(PROPERTY_PREFIX + "transaction-support");
            if (isValidProperty(transactionSupport)) {
                return transactionSupport;
            } else {
                return "NoTransaction";
            }
        }

        public void setTransactionSupport(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getValidateAtmostOncePeriodInSeconds() {
            String validateAtmostOncePeriodInSeconds = desc.getProperty(PROPERTY_PREFIX + "validate-at-most-once-period-in-seconds");
            if (isValidProperty(validateAtmostOncePeriodInSeconds)) {
                return validateAtmostOncePeriodInSeconds;
            } else {
                return "0";
            }
        }

        public void setValidateAtmostOncePeriodInSeconds(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getConnectionLeakTimeoutInSeconds() {
            String connectionLeakTimeoutInSeconds = desc.getProperty(PROPERTY_PREFIX + "connection-leak-timeout-in-seconds");
            if (isValidProperty(connectionLeakTimeoutInSeconds)) {
                return connectionLeakTimeoutInSeconds;
            } else {
                return "0";
            }
        }

        public void setConnectionLeakTimeoutInSeconds(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getConnectionLeakReclaim() {
            String connectionLeakReclaim = desc.getProperty(PROPERTY_PREFIX + "connection-leak-reclaim");
            if (isValidProperty(connectionLeakReclaim)) {
                return connectionLeakReclaim;
            } else {
                return "0";
            }
        }

        public void setConnectionLeakReclaim(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getConnectionCreationRetryAttempts() {
            String connectionCreationRetryAttempts = desc.getProperty(PROPERTY_PREFIX + "connection-creation-retry-attempts");
            if (isValidProperty(connectionCreationRetryAttempts)) {
                return connectionCreationRetryAttempts;
            } else {
                return "0";
            }
        }

        public void setConnectionCreationRetryAttempts(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getConnectionCreationRetryIntervalInSeconds() {
            String connectionCreationRetryIntervalInSeconds = desc.getProperty(PROPERTY_PREFIX + "connection-creation-retry-interval-in-seconds");
            if (isValidProperty(connectionCreationRetryIntervalInSeconds)) {
                return connectionCreationRetryIntervalInSeconds;
            } else {
                return "0";
            }
        }

        public void setConnectionCreationRetryIntervalInSeconds(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getLazyConnectionEnlistment() {
            String lazyConnectionEnlistment = desc.getProperty(PROPERTY_PREFIX + "lazy-connection-enlistment");
            if (isValidProperty(lazyConnectionEnlistment)) {
                return lazyConnectionEnlistment;
            } else {
                return "false";
            }
        }

        public void setLazyConnectionEnlistment(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getLazyConnectionAssociation() {
            String lazyConnectionAssociation = desc.getProperty(PROPERTY_PREFIX + "lazy-connection-association");
            if (isValidProperty(lazyConnectionAssociation)) {
                return lazyConnectionAssociation;
            } else {
                return "false";
            }
        }

        public void setLazyConnectionAssociation(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getAssociateWithThread() {
            String associateWithThread = desc.getProperty(PROPERTY_PREFIX + "associate-with-thread");
            if (isValidProperty(associateWithThread)) {
                return associateWithThread;
            } else {
                return "false";
            }
        }

        public void setAssociateWithThread(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getPooling() {
            String pooling = desc.getProperty(PROPERTY_PREFIX + "pooling");
            if (isValidProperty(pooling)) {
                return pooling;
            } else {
                return "true";
            }
        }

        public void setPooling(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getMatchConnections() {
            String matchConnections = desc.getProperty(PROPERTY_PREFIX + "match-connections");
            if (isValidProperty(matchConnections)) {
                return matchConnections;
            } else {
                return "true";
            }
        }

        public void setMatchConnections(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getMaxConnectionUsageCount() {
            String maxConnectionUsageCount = desc.getProperty(PROPERTY_PREFIX + "max-connection-usage-count");
            if (isValidProperty(maxConnectionUsageCount)) {
                return maxConnectionUsageCount;
            } else {
                return "0";
            }
        }

        public void setMaxConnectionUsageCount(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getDescription() {
            return desc.getDescription();
        }

        public void setDescription(String value) throws PropertyVetoException {
            //do nothing
        }

        public List<Property> getProperty() {
            Properties p = desc.getProperties();
            List<Property> jmsConnectionFactoryProperties = new ArrayList<Property>();

            if (isValidProperty(desc.getUser())) {
                JMSConnectionFactoryProperty property = convertProperty("UserName", desc.getUser());
                jmsConnectionFactoryProperties.add(property);
            }

            if (isValidProperty(desc.getPassword())) {
                JMSConnectionFactoryProperty property = convertProperty("Password", desc.getPassword());
                jmsConnectionFactoryProperties.add(property);
            }

            if (isValidProperty(desc.getClientId())) {
                JMSConnectionFactoryProperty property = convertProperty("clientId", desc.getClientId());
                jmsConnectionFactoryProperties.add(property);
            }

            for (Entry<Object, Object> entry : p.entrySet()) {
                String key = (String)entry.getKey();
                if (key.startsWith(PROPERTY_PREFIX)
                    || (key.equalsIgnoreCase("UserName") && isValidProperty(desc.getUser()))
                    || (key.equalsIgnoreCase("Password") && isValidProperty(desc.getPassword()))
                    || (key.equalsIgnoreCase("clientId") && isValidProperty(desc.getClientId()))) {
                    continue;
                }
                String value = (String)entry.getValue();
                JMSConnectionFactoryProperty property = convertProperty(key, value);
                jmsConnectionFactoryProperties.add(property);
            }

            return jmsConnectionFactoryProperties;
        }

        public Property getProperty(String name) {
            String value = desc.getProperty(name);
            return new JMSConnectionFactoryProperty(name, value);
        }

        public String getPropertyValue(String name) {
            return desc.getProperty(name);
        }

        public String getPropertyValue(String name, String defaultValue) {
            String value = null;
            value = desc.getProperty(name);
            if (value != null) {
                return value;
            } else {
                return defaultValue;
            }
        }

        public void injectedInto(Object o) {
            //do nothing
        }

        public String getName() {
            return name;
        }

        public void setName(String value) throws PropertyVetoException {
            //do nothing
        }

        public String getPing() {
            String ping = desc.getProperty(PROPERTY_PREFIX + "ping");
            if (isValidProperty(ping)) {
                return ping;
            } else {
                return "false";
            }
        }

        public void setPing(String value) throws PropertyVetoException {
            //do nothing
        }

        public List<SecurityMap> getSecurityMap() {
            return new ArrayList<SecurityMap>(0);
        }

        public String getDeploymentOrder() {
            return null;
        }

        public void setDeploymentOrder(String value) {
            //do nothing
        }

        @Override
        public Property addProperty(Property prprt) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property lookupProperty(String string) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property removeProperty(String string) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        @Override
        public Property removeProperty(Property prprt) {
            throw new UnsupportedOperationException("Not supported yet.");
        }
    }
}

