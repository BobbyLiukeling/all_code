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

package com.sun.s1peqe.connector.mq.simplestress.ejb;

import java.io.Serializable;
import java.rmi.RemoteException;
import javax.ejb.EJBException;
import javax.ejb.MessageDrivenBean;
import javax.ejb.MessageDrivenContext;
import javax.ejb.CreateException;
import javax.naming.*;
import javax.jms.*;

public class SimpleMessageBean implements MessageDrivenBean,
    MessageListener {

    Context                 jndiContext = null;
    QueueConnectionFactory  queueConnectionFactory = null;
    QueueConnection         queueConnection = null;
    QueueSession            queueSession = null;
    Queue                   queue = null;
    QueueSender             queueSender = null;
    final int               NUM_MSGS = 100;

    private transient MessageDrivenContext mdc = null;
    private Context context;

    public SimpleMessageBean() {
        System.out.println("In SimpleMessageBean.SimpleMessageBean()");
    }

    public void setMessageDrivenContext(MessageDrivenContext mdc) {
        System.out.println("In "
            + "SimpleMessageBean.setMessageDrivenContext()");
	this.mdc = mdc;
    }

    public void ejbCreate() {
	System.out.println("In SimpleMessageBean.ejbCreate()");
        try {
            jndiContext = new InitialContext();
            queueConnectionFactory = (QueueConnectionFactory)
                jndiContext.lookup
                ("java:comp/env/jms/QCFactory");
            queue = (Queue) jndiContext.lookup("java:comp/env/jms/clientQueue");
        } catch (NamingException e) {
            System.out.println("JNDI lookup failed: " +
                e.toString());
        }
    }

    public void onMessage(Message inMessage) {
        TextMessage msg = null;

        try {
            if (inMessage instanceof TextMessage) {
                msg = (TextMessage) inMessage;
                System.out.println("MESSAGE BEAN: Message received: "
                    + msg.getText());
		long sleepTime = msg.getLongProperty("sleeptime");
		System.out.println("Sleeping for : " + sleepTime + " milli seconds ");
		Thread.sleep(sleepTime);
		queueConnection =
	            queueConnectionFactory.createQueueConnection();
		queueSession =
	            queueConnection.createQueueSession(false,
		    Session.AUTO_ACKNOWLEDGE);
		queueSender = queueSession.createSender(queue);
		TextMessage message = queueSession.createTextMessage();

		message.setText("REPLIED:" + msg.getText());
		message.setIntProperty("replyid", msg.getIntProperty("id") );
		System.out.println("Sending message: " +
		message.getText());
		queueSender.send(message);
            } else {
                System.out.println("Message of wrong type: "
                    + inMessage.getClass().getName());
            }
        } catch (JMSException e) {
            e.printStackTrace();
        } catch (Throwable te) {
            te.printStackTrace();
        } finally {
	    try {
	        queueSession.close();
		queueConnection.close();
	    } catch (Exception e) {
	    }
	}
    }  // onMessage

    public void ejbRemove() {
        System.out.println("In SimpleMessageBean.remove()");
    }
} // class

