/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2002-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.s1asdev.ejb.ejb30.hello.mdb2.client;

import java.io.*;
import java.util.*;
import javax.ejb.EJBHome;
import javax.naming.*;
import javax.jms.*;
import javax.annotation.Resource;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;

public class Client {

    // in milli-seconds
    private static long TIMEOUT = 90000;

    private static SimpleReporterAdapter stat =
        new SimpleReporterAdapter("appserv-tests");

    private static @Resource(name="FooCF") 
        QueueConnectionFactory queueConFactory;

    public static void main (String[] args) {
        Client client = new Client(args);

        stat.addDescription("ejb-ejb30-hello-mdb2");
        client.doTest();
        stat.printSummary("ejb-ejb30-hello-mdb2ID");
        System.exit(0);
    }

    private InitialContext context;
    private QueueConnection queueCon;
    private QueueSession queueSession;
    private QueueSender queueSender;
    private QueueReceiver queueReceiver;
    private javax.jms.Queue clientQueue;


    private int numMessages = 2;
    public Client(String[] args) {
        
        if( args.length == 1 ) {
            numMessages = new Integer(args[0]).intValue();
        }
    }

    public void doTest() {
        try {
            setup();
            doTest("java:comp/env/jms/MsgBeanQueue", numMessages);
            stat.addStatus("cmt main", stat.PASS);
        } catch(Throwable t) {
            stat.addStatus("cmt main", stat.FAIL);
            t.printStackTrace();
        } finally {
            cleanup();
        }
    }

    public void setup() throws Exception {
        context = new InitialContext();
        
        queueCon = queueConFactory.createQueueConnection();

        queueSession = queueCon.createQueueSession
            (false, Session.AUTO_ACKNOWLEDGE); 

        // Producer will be specified when actual msg is sent.
        queueSender = queueSession.createSender(null);        

        clientQueue = (javax.jms.Queue)
	    context.lookup("java:comp/env/jms/MsgBeanClientQueue");

        queueReceiver = queueSession.createReceiver(clientQueue);

        queueCon.start();

    }

    public void cleanup() {
        try {
            if( queueCon != null ) {
                queueCon.close();
            }
        } catch(Throwable t) {
            t.printStackTrace();
        }
    }

    public void sendMsgs(javax.jms.Queue queue, Message msg, int num) 
        throws JMSException {
        for(int i = 0; i < num; i++) {
            System.out.println("Sending message " + i + " to " + queue + 
                               " at time " + System.currentTimeMillis());
            queueSender.send(queue, msg);
            System.out.println("Sent message " + i + " to " + queue + 
                               " at time " + System.currentTimeMillis());
        }
    }

    public void doTest(String destName, int num) 
        throws Exception {

        Destination dest = (Destination) context.lookup(destName);

        Message message = queueSession.createTextMessage(destName);

        message.setBooleanProperty("flag", true);
        message.setIntProperty("num", 2);
        sendMsgs((javax.jms.Queue) dest, message, num);

        System.out.println("Waiting for queue message");
        Message recvdmessage = queueReceiver.receive(TIMEOUT);
        if( recvdmessage != null ) {
            System.out.println("Received message : " + 
                                   ((TextMessage)recvdmessage).getText());
        } else {
            System.out.println("timeout after " + TIMEOUT + " seconds");
            throw new JMSException("timeout" + TIMEOUT + " seconds");
        }
    }
}

