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

package org.glassfish.test.jms.jmsxdeliverycount.ejb;

import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.ejb.*;
import javax.inject.Inject;
import javax.jms.*;

/**
 *
 * @author LILIZHAO
 */
@Stateless(mappedName="MySessionBean/remote")
public class MySessionBean implements MySessionBeanRemote {
    @Resource(mappedName = "jms/jms_unit_test_Queue")
    private Queue queue;

    @Resource(mappedName = "jms/jms_unit_test_QCF")
    private ConnectionFactory myQueueFactory;

    @Inject
    @JMSConnectionFactory("jms/jms_unit_test_QCF")
    @JMSSessionMode(JMSContext.AUTO_ACKNOWLEDGE)
    private JMSContext jmsContext;

    @Resource
    EJBContext ctx;

    @Override
    public void sendMessage(String text) {
        try {
            JMSProducer producer = jmsContext.createProducer();
            TextMessage msg = jmsContext.createTextMessage(text);
            producer.send(queue, msg);
        } catch (Exception e) {
            throw new EJBException(e);
        }
    }

    @Override
    public boolean checkMessage1(String text) {
        Connection conn = null;
        Session session = null;
        try {
            conn = myQueueFactory.createConnection();
            conn.start();
            session = conn.createSession();

            MessageConsumer consumer = session.createConsumer(queue);
            TextMessage msg = (TextMessage) consumer.receive(1000);
            if (msg == null) {
                Logger.getLogger("MySessionBean").severe("No message received 1.");
                return false;
            }
            int deliveryCount = msg.getIntProperty("JMSXDeliveryCount");
            if (deliveryCount != 1) {
                Logger.getLogger("MySessionBean").severe("Invalid JMSXDeliveryCount - Got <" + deliveryCount + ">, but expected <1>.");
                return false;
            }
            ctx.setRollbackOnly();
        } catch (Exception e) {
            throw new EJBException(e);
        } finally {
            try {
                session.close();
                conn.close();
            }catch(Exception e) {
                throw new EJBException(e);
            }
        }
        return true;
    }

    @Override
    public boolean checkMessage2(String text) {
        Connection conn = null;
        Session session = null;
        try {
            conn = myQueueFactory.createConnection();
            conn.start();
            session = conn.createSession();

            MessageConsumer consumer = session.createConsumer(queue);
            TextMessage msg = (TextMessage) consumer.receive(1000);
            if (msg == null) {
                Logger.getLogger("MySessionBean").severe("No message received 2.");
                return false;
            }
            int deliveryCount = msg.getIntProperty("JMSXDeliveryCount");
            if (deliveryCount != 2) {
                Logger.getLogger("MySessionBean").severe("Invalid JMSXDeliveryCount - Got <" + deliveryCount + ">, but expected <2>.");
                return false;
            }
        } catch (Exception e) {
            throw new EJBException(e);
        } finally {
            try {
                session.close();
                conn.close();
            }catch(Exception e) {
                throw new EJBException(e);
            }
        }
        return true;
    }
}
