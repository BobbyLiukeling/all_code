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

package org.glassfish.test.jms.annotation.ejb;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.ejb.ActivationConfigProperty;
import javax.ejb.EJBException;
import javax.ejb.MessageDriven;
import javax.inject.Inject;
import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConnectionFactory;
import javax.jms.JMSConnectionFactoryDefinition;
import javax.jms.JMSContext;
import javax.jms.JMSDestinationDefinition;
import javax.jms.JMSException;
import javax.jms.JMSProducer;
import javax.jms.JMSSessionMode;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.MessageProducer;
import javax.jms.Queue;
import javax.jms.Session;
import javax.jms.TextMessage;

@JMSConnectionFactoryDefinition(
    description = "global-scope CF defined by @JMSConnectionFactoryDefinition",
    name = "java:global/env/annotation_CF",
    interfaceName = "javax.jms.ConnectionFactory",
    resourceAdapter = "jmsra",
    user = "admin",
    password = "admin",
    properties = {"org.glassfish.connector-connection-pool.transaction-support=XATransaction"},
    minPoolSize = 0
)

@JMSDestinationDefinition(
    description = "global-scope test queue defined by @JMSDestinationDefinition",
    name = "java:global/env/annotation_testQueue",
    interfaceName = "javax.jms.Queue",
    resourceAdapter = "jmsra",
    destinationName = "myPhysicalTestQueue"
)

@MessageDriven(mappedName = "java:global/env/annotation_testQueue", activationConfig = {
    @ActivationConfigProperty(propertyName = "acknowledgeMode", propertyValue = "Auto-acknowledge"),
    @ActivationConfigProperty(propertyName = "destinationType", propertyValue = "javax.jms.Queue"),
    @ActivationConfigProperty(propertyName = "endpointExceptionRedeliveryAttempts", propertyValue = "1")
})
public class MyMessageBean implements MessageListener {
    private static final Logger logger = Logger.getLogger(MyMessageBean.class.getName());

    @Resource(mappedName = "java:global/env/annotation_resultQueue")
    private Queue resultQueue;

    @Resource(mappedName = "java:global/env/annotation_CF")
    private ConnectionFactory myConnectionFactory;

    @Inject
    @JMSConnectionFactory("java:global/env/annotation_CF")
    @JMSSessionMode(JMSContext.AUTO_ACKNOWLEDGE)
    private JMSContext jmsContext;

    public MyMessageBean() {
    }

    @Override
    public void onMessage(Message message) {
        try {
            if (message instanceof TextMessage) {
                sendMessage(true, ((TextMessage) message).getText());
            } else {
                sendMessage(false, "The received message is not a expected TextMessage.");
            }
        } catch (JMSException ex) {
            Logger.getLogger(MyMessageBean.class.getName()).log(Level.SEVERE, null, ex);
            throw new EJBException(ex);
        }
    }

    private void sendMessage(boolean success, String text) {
        JMSProducer producer = jmsContext.createProducer();
        TextMessage message = jmsContext.createTextMessage(success + ":" + text);
        producer.send(resultQueue, message);
    }
}
