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

package org.glassfish.test.jms.injection.ejb;

import javax.annotation.Resource;
import javax.ejb.*;
import javax.inject.Inject;
import javax.jms.*;
import javax.transaction.UserTransaction;
import javax.transaction.NotSupportedException;
import javax.transaction.SystemException;
import javax.transaction.RollbackException;
import javax.transaction.HeuristicMixedException;
import javax.transaction.HeuristicRollbackException;
import java.lang.SecurityException;
import java.lang.IllegalStateException;


/**
 *
 * @author JIGWANG
 */
@Stateless(mappedName="SessionBeanInjection/remote")
@TransactionManagement(TransactionManagementType.BEAN)
public class SessionBeanInjection implements SessionBeanInjectionRemote {
    @Resource(mappedName = "jms/jms_unit_test_Queue")
    private Queue queue;

    @Inject
    @JMSConnectionFactory("jms/jms_unit_test_QCF")
    @JMSSessionMode(JMSContext.AUTO_ACKNOWLEDGE)
    private JMSContext jmsContext;

    @Inject 
    UserTransaction ut;
    
    private static String transactionScope = "around TransactionScoped";
    private static String preIdentical = "fingerPrint";

    public Boolean sendMessage(String text) {

        String context1 = "";
        String context2 = "";
        String context3 = "";
        String context4 = "";
        try {
            ut.begin();
            TextMessage msg = jmsContext.createTextMessage(text);
            
            jmsContext.createProducer().send(queue, msg);
            context1 = jmsContext.toString();
            System.out.println("JMSContext1:"+jmsContext.toString());
            
            jmsContext.createProducer().send(queue, msg);
            context2 = jmsContext.toString();
            System.out.println("JMSContext2:"+jmsContext.toString());

            ut.commit();
            ut.begin();

            jmsContext.createProducer().send(queue, msg);
            context3 = jmsContext.toString();
            System.out.println("JMSContext3:"+jmsContext.toString());
            
            jmsContext.createProducer().send(queue, msg);
            context4 = jmsContext.toString();
            System.out.println("JMSContext4:"+jmsContext.toString());
            ut.commit();

            return checkScope(context1, context2, context3, context4);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public Boolean checkScope(String context1, String context2, String context3, String context4){
				
        if (context1.indexOf(transactionScope) != -1){
            System.out.println("The context variables used in the first call are in transaction scope.");
        }else{
            System.out.println("The context variables used in the first call are NOT in transaction scope.");
            return false;
        }
            
        if (context2.indexOf(transactionScope) != -1){
            System.out.println("The context variables used in the second call are in transaction scope.");
        }else{
            System.out.println("The context variables used in the second call are NOT in transaction scope.");
            return false;
        }
        
        if (context3.indexOf(transactionScope) != -1){
            System.out.println("The context variables used in the third call are in transaction scope.");
        }else{
            System.out.println("The context variables used in the third call are NOT in transaction scope.");
            return false;
        }
        
        if (context4.indexOf(transactionScope) != -1){
            System.out.println("The context variables used in the fourth call are in transaction scope.");
        }else{
            System.out.println("The context variables used in the fourth call are NOT in transaction scope.");
            return false;
        }
        
        String context1Annotation = context1.substring(context1.indexOf(preIdentical),context1.indexOf(transactionScope));
        String context2Annotation = context2.substring(context2.indexOf(preIdentical),context2.indexOf(transactionScope));
        String context3Annotation = context3.substring(context3.indexOf(preIdentical),context3.indexOf(transactionScope));
        String context4Annotation = context4.substring(context4.indexOf(preIdentical),context3.indexOf(transactionScope));
        
        if(context1Annotation.equals(context2Annotation)){
            System.out.println("The context variables in the first and second calls to context.send() injected are using identical annotations.");
                if(context1Annotation.equals(context3Annotation)){
                    System.out.println("The context variables in the first and second and third calls to context.send() injected are using identical annotations.");
                        if(context1Annotation.equals(context4Annotation)){
                            System.out.println("The context variables in thest four calls to context.send() injected are using identical annotations.");
                        }else{
                            System.out.println("The context variables in the first and fourth calls to context.send() injected are not using identical annotations.");
                            return false;
                        }
                }else{
                    System.out.println("The context variables in the first and third calls to context.send() injected are not using identical annotations.");
                    return false;
                }
        }else{
            System.out.println("The context variables in the first and second calls to context.send() injected are not using identical annotations.");
            return false;
        }
       	
        if (context1.substring(context1.indexOf(transactionScope)).equals(context2.substring(context2.indexOf(transactionScope)))){
            System.out.println("The context variables used in the first and second calls to context.send() take place in the same transaction.");
        }else{
            System.out.println("The context variables used in the first and second calls to context.send() take place in the different transaction.");
            return false;
        }
        
        if (context3.substring(context3.indexOf(transactionScope)).equals(context4.substring(context4.indexOf(transactionScope)))){
            System.out.println("The context variables used in the third and fourth calls to context.send() take place in the same transaction.");
        }else{
            System.out.println("The context variables used in the third and fourth calls to context.send() take place in the different transaction.");
            return false;
        }
        
        if (context1.substring(context1.indexOf(transactionScope)).equals(context3.substring(context3.indexOf(transactionScope)))){
            System.out.println("The context variables used in the first and third calls to context.send() take place in the same transaction.");
            return false;
        }else{
            System.out.println("The context variables used in the first and third calls to context.send() take place in the different transaction.");
        }
        return true;
    }
}
