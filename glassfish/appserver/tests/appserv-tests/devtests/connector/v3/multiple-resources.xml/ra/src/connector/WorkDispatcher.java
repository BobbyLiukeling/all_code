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

package connector;

import com.sun.enterprise.connectors.work.context.CustomWorkContext_D;
import org.glassfish.security.common.PrincipalImpl;

import java.lang.reflect.Method;
import javax.resource.spi.ActivationSpec;
import javax.resource.spi.BootstrapContext;
import javax.resource.spi.XATerminator;
import javax.resource.spi.endpoint.MessageEndpoint;
import javax.resource.spi.endpoint.MessageEndpointFactory;
import javax.resource.spi.work.*;
import javax.transaction.xa.Xid;

/**
 * @author Qingqing Ouyang
 */
public class WorkDispatcher implements Work {

    private boolean stop = false;
    private String id;
    private MessageEndpointFactory factory;
    private BootstrapContext ctx;
    private ActivationSpec spec;
    private WorkManager wm;
    private XATerminator xa;

    private int numOfMessages = 1;

    public WorkDispatcher(
            String id,
            BootstrapContext ctx,
            MessageEndpointFactory factory,
            ActivationSpec spec) {
        this.id = id;
        this.ctx = ctx;
        this.factory = factory;
        this.spec = spec;
        this.wm = ctx.getWorkManager();
        this.xa = ctx.getXATerminator();
    }

    public void run() {

        debug("ENTER...");

        try {
            synchronized (Controls.readyLock) {
                debug("WAIT...");
                Controls.readyLock.wait();

                if (stop) {
                    return;
                }
            }
        } catch (Throwable ex) {
            ex.printStackTrace();
        }

        debug("Running...");

        //try 3 times to create endpoint (in case of failure)
        for (int i = 0; i < 1; i++) {

            try {

                Method onMessage = getOnMessageMethod();
                System.out.println("isDeliveryTransacted = " +
                        factory.isDeliveryTransacted(onMessage));

                if (!factory.isDeliveryTransacted(onMessage)) {
                    //MessageEndpoint ep = factory.createEndpoint(null);
                    //DeliveryWork d = new DeliveryWork("NO_TX", ep); 
                    //wm.doWork(d, 0, null, null);
                } else {

                    String jagadish = "jagadish";
                    String prasath = "prasath";
                    String groupName = "iec";

                    boolean translationRequired = determineIdentityType();
                    if (translationRequired) {
                        jagadish = "eis-jagadish";
                        prasath = "eis-prasath";
                        groupName = "eis-group";
                    }
                    newLine(1);


                    int count = 0;
                    count = testExecutionContext(count);


                    count = testTransactionContext(count, translationRequired, "abc", "xyz", "abc", true, false);

                    count = testTICWithSIC(count, translationRequired, "jagadish", "prasath", jagadish, true, true);

                    //testTICWithSIC(translationRequired, "", "", "ADM");
                    //testTICWithSIC(translationRequired, "", "", "j2ee");


                    count = testRollbackTICWithSIC(count, translationRequired, "jagadish", "prasath", jagadish, true, true);

                    count = testDuplicateTICWithSIC(count, translationRequired, "jagadish", "prasath", jagadish);

                    count = testTICWithSICAndSICListener(count, translationRequired, "jagadish", "prasath", prasath, true, true);

                    count = testTICWithSICAndSICListenerForGroupCallback(count, groupName);

                    if (translationRequired) {
                        count = testTICWithSICAndSICListenerForDomainXMLFlag(count, "jagadish", "prasath", jagadish);

                        count = testTICSICWithoutMappingValue(count, "jagadish", "prasath", "eis-user", true, true);

                        count = testTICWithRogueSIC(count, "jagadish", "prasath", jagadish);
                    }

                    count = testTICWithECWithSIC(count, translationRequired, "abc", "xyz", "abc", false, false);

                    count = testECWithoutAnyWorkContext(count);

                    count = testRollbackTICWithSC(count, translationRequired, "abc", "xyz", "abc", true, false);

                    count = testSICAbstractClassSupport(count);

                    count = testCIC_C_Support(count);

                    count = testCIC_D_Support(count);

                    count = testIdempotentCIC_D(count);

                    count = testTICWithCIC_C(count);

                    count = testTICWithCIC_E(count);

                    count = testTICWithCIC_D(count);

                    count = testTICWithUnsupportedIC(count);

                    //testTICWithUnauthenticatedIC();

                    //testTICWithUnauthenticatedICWithEmptyEC();

                    //testTICWithUnauthenticatedICWithSinglePrincipal();

                    count = testSinglePrincipalSIC(count, jagadish);

                    count = testUnauthenticatedSIC_NullName(count);

                    count = testUnauthenticatedSIC_NullPrincipal(count);

                    count = testNestedWorkSupport(count, false, false, "jagadish", "prasath", "jagadish", true, true, true, translationRequired);


                    count = testNestedWorkSupport(count, true, false, "jagadish", "prasath", "jagadish", true, true, true, translationRequired);

                    count = testNestedWorkSupport(count, true, false, "jagadish", "xyz", "jagadish", true, false, true, translationRequired);

                    count = testNestedWorkSupport(count, true, false, "jagadish", "prasath", "jagadish", true, true, false, translationRequired);


                    count = testNestedWorkSupport(count, false, true, "jagadish", "prasath", "jagadish", true, true, true, translationRequired);


/*
                    testTICWIthNestedWorkWithSICWithoutEC();

*/

                    count = deleteAll(count);

                    done();
                }

                break;
            } /*catch (UnavailableThrowable ex) {
                //ex.printStackTrace();
                System.out.println("WorkDispatcher[" + id + "] Endpoint Unavailable");
                try {
                    Thread.currentThread().sleep(3 * 1000); //3 seconds
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            } catch (XAException ex) {
                ex.printStackTrace();
                System.out.println("ERROR CODE = " + ex.errorCode);
                done();
                break;
            }*/ catch (Throwable ex) {
                ex.printStackTrace();
                done();
                break;
            }
        }

        debug("LEAVE...");
    }

    private int testNestedWorkSupport(int count, boolean transacted, boolean transactedChild, String user, String password,
                                      String principal, boolean expectSuccess, boolean expectPVSuccess, boolean successfulPVForChild, boolean translationRequired) {
        ExecutionContext ec = null;
        try {
            int numOfMessages = 1;

            debug("writing to DB - nested work");
            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            if (transacted)
                count++;

            if (transactedChild)
                count++;

            //importing transaction

            NestedWork_Parent w =
                    new NestedWork_Parent(ep, numOfMessages, "WRITE", false, 1, wm, xa, transacted, transactedChild, successfulPVForChild,  translationRequired);

            if (transacted) {
                //write/commit
                ec = startTx();
                TransactionContext tc = new TransactionContext();
                tc.setXid(ec.getXid());
                w.addWorkContext(tc);
                debug("Start TX - " + ec.getXid());
            }

            MySecurityContext sic =
                    new MySecurityContextWithListener(user, password, principal, translationRequired, expectSuccess, expectPVSuccess);
            w.addWorkContext(sic);

            wm.doWork(w, 0, null, null);
            if (transacted) {
                xa.commit(ec.getXid(), true);
                debug("commited write to DB - with ExecutionContext");
            }


            debug("completed - nested work");
        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private boolean determineIdentityType() {
        String raName = "generic-ra";
        if (System.getProperty(raName + "-principals-map") != null) {
            return true;
        } else if (System.getProperty(raName + "-groups-map") != null) {
            return true;
        }
        return false;
    }

    private int deleteAll(int count) {
        try {
            MessageEndpoint ep3 = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec3 = startTx();
            debug("Start TX - " + ec3.getXid());

            DeliveryWork w3 =
                    new DeliveryWork(ep3, 1, "DELETE_ALL");
            wm.doWork(w3, 0, ec3, null);
            xa.commit(ec3.getXid(), true);
            count = 0;

            debug("DELETED ALL FROM DB");
            //Controls.expectedResults = 0;
        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = 0;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testIdempotentCIC_D(int count) {
        debug("Idompotent test on a supported context " + CustomWorkContext_D.class.getName());
        checkContainerSupportForWorkContext(CustomWorkContext_D.class);
        newLine(2);
        return count;
    }

    private int testCIC_D_Support(int count) {
        //check for specific class support
        debug("check for specific class support from container  " + CustomWorkContext_D.class.getName());
        checkContainerSupportForWorkContext(CustomWorkContext_D.class);
        newLine(2);
        return count;
    }

    private int testCIC_C_Support(int count) {
        //check for class that has no support, but its parent has support from container
        debug("check for a class support from container  " + CustomWorkContext_C.class.getName());
        checkContainerSupportForWorkContext(CustomWorkContext_C.class);
        newLine(2);
        return count;
    }

    private int testSICAbstractClassSupport(int count) {
        //check for abstract class
        debug("check for a abstract class support from container  " + SecurityContext.class.getName());
        checkContainerSupportForWorkContext(SecurityContext.class);
        newLine(2);
        return count;

    }

    //"jagadish", "prasath", "eis-user", true
    private int testTICSICWithoutMappingValue(int count, String user, String password, String principal,
                                              boolean expectSuccess, boolean expectPVSuccess) {
        try {
            count++;
            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec = startTx();
            debug("Write to DB - with TransactionContext, SecurityContext With LISTENER, " +
                    "Translation Required (no mapping available)");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, true,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);


            wm.doWork(w1, 0, null, null);
            //wm.doWork(w1, 0, ec, null);
            xa.commit(ec.getXid(), true);


            debug("commited write to DB - with TransactionContext, SecurityContext With LISTENER, " +
                    "Translation Required (no mapping available)");
            //   newLine(2);
            //Controls.expectedResults = 5;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private void testTICWithUnauthenticatedICWithSinglePrincipal() {
        try {
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext -" +
                    " single principal exec. subject");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            UnauthenticatedIdentityOptWorkContext uic = new UnauthenticatedIdentityOptWorkContext(true, true,
                    "eis-jagadish", "jagadish", "prasath");
            w1.addWorkContext(uic);


            wm.doWork(w1, 0, null, null);
            xa.rollback(ec1.getXid());


            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext - " +
                    "single principal exec. subject");
            //   newLine(2);

            Controls.expectedResults = 6;


        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            notifyAndWait();
            newLine(2);
        }
    }

    //"abc", "xyz", "abc", true
    private void testTICWIthNestedWorkWithSICWithoutEC(boolean translationRequired, String user, String password,
                                                       String principal, boolean expectSuccess,
                                                       boolean expectPVSuccess) {
        try {
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - NestedWork with TransactionContext, with SIC, without ExecutionContext");
            debug("Start TX - " + ec1.getXid());

            NestedWork_Parent w1 =
                    new NestedWork_Parent(ep2, numOfMessages, "WRITE", 1, wm, xa, true, false, true, translationRequired);


            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal,
                    translationRequired, expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);


            debug("commited write to DB - NestedWork with TransactionContext, with SIC, without ExecutionContext");
            //   newLine(2);

            Controls.expectedResults = 7;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            notifyAndWait();
            newLine(2);
        }
    }

    private void testTICWithUnauthenticatedICWithEmptyEC() {
        try {
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext - " +
                    "empty exec. subject");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            UnauthenticatedIdentityOptWorkContext uic = new UnauthenticatedIdentityOptWorkContext(
                    true, false, null, null, null);
            w1.addWorkContext(uic);

            wm.doWork(w1, 0, null, null);
            xa.rollback(ec1.getXid());


            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext -" +
                    " empty exec. subject");
            //   newLine(2);

            Controls.expectedResults = 6;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            notifyAndWait();
            newLine(2);
        }
    }

    private void testTICWithUnauthenticatedIC() {
        try {
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext -" +
                    " null principal");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            UnauthenticatedIdentityOptWorkContext uic = new UnauthenticatedIdentityOptWorkContext(
                    true, true, null, null, null);
            w1.addWorkContext(uic);

            wm.doWork(w1, 0, null, null);
            xa.rollback(ec1.getXid());


            debug("writing to DB - with TransactionContext, with UnauthenticatedIdentityOptWorkContext " +
                    "- null principal");
            //   newLine(2);

            Controls.expectedResults = 6;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            notifyAndWait();
            newLine(2);
        }
    }

    private int testTICWithUnsupportedIC(int count) {
        try {
            //expect failure
            //count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with UnSupportedWorkContext");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            UnsupportedWorkContext uic = new UnsupportedWorkContext();
            w1.addWorkContext(uic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);



            debug("writing to DB - with TransactionContext, with UnsupportedWorkContext");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testTICWithCIC_D(int count) {
        try {
            count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with CustomWorkContext_D");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            CustomWorkContext_D cic = new CustomWorkContext_D();
            w1.addWorkContext(cic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);



            debug("writing to DB - with TransactionContext, with CustomWorkContext_D");
            //   newLine(2);

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testTICWithCIC_E(int count) {
        try {
            count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with CustomWorkContext_E");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            CustomWorkContext_E cic = new CustomWorkContext_E();
            w1.addWorkContext(cic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);



            debug("writing to DB - with TransactionContext, with CustomWorkContext_E");
            //   newLine(2);

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testTICWithCIC_C(int count) {
        try {
            count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with CustomWorkContext_C");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            CustomWorkContext_C cic = new CustomWorkContext_C();
            w1.addWorkContext(cic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);


            debug("writing to DB - with TransactionContext, with CustomWorkContext_C");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //"abc", "xyz", "abc", false
    private int testRollbackTICWithSC(int count, boolean translationRequired, String user, String password,
                                      String principal, boolean expectSuccess, boolean expectPVSuccess) {
        try {
            //expect failure
            //count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext, with ExecutionContext, with SIC");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);


            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, translationRequired,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);

            wm.doWork(w1, 0, ec1, null);
            xa.commit(ec1.getXid(), true);



            debug("commited write to DB - with TransactionContext, with ExecutionContext, with SIC");


        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testECWithoutAnyWorkContext(int count) {
        try {
            //expect failure
            //count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - without any WorkContext, with ExecutionContext");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            wm.doWork(w1, 0, ec1, null);
            xa.commit(ec1.getXid(), true);



            debug("commited write to DB - without any WorkContext, with ExecutionContext");
            //   newLine(2);

            Controls.expectedResults = 6;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //"abc", "xyz", "abc", false
    private int testTICWithECWithSIC(int count, boolean translationRequired, String user, String password,
                                     String principal, boolean expectSuccess, boolean expectPVSuccess) {
        try {
            //expect failure
            //count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - without TransactionContext, with SIC, with ExecutionContext");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");


            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, translationRequired,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);

            wm.doWork(w1, 0, ec1, null);
            xa.commit(ec1.getXid(), true);



            debug("rolled back write to DB - without TransactionContext, with SIC,  with ExecutionContext");
            //   newLine(2);


        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //"jagadish", "prasath", "eis-jagadish" [ONLY FOR TRANSLATION REQUIRED]
    private int testTICWithRogueSIC(int count, String user, String password, String principal) {
        try {
            //expect failure
            //count++;
            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec = startTx();
            debug("Write to DB - with TransactionContext, ROGUE SecurityContext having PasswordValidationCallback for " +
                    "Translation Required Case");

            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new RogueSecurityContextWithListener(user, password, principal);
            w1.addWorkContext(sic);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec.getXid(), true);


            debug("commited write to DB - with TransactionContext, ROGUE SecurityContext " +
                    "having PasswordValidationCallback for " +
                    "Translation Required Case");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //"jagadish", "prasath", "eis-jagadish"
    private int testTICWithSICAndSICListenerForDomainXMLFlag(int count, String user, String password, String principal) {
        try {
            count++;
            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec = startTx();
            debug("write to DB - with TransactionContext, SecurityContext");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MyPlainSecurityContext sic = new MyPlainSecurityContext(user, password, principal, true);
            w1.addWorkContext(sic);


            wm.doWork(w1, 0, null, null);
            //wm.doWork(w1, 0, ec, null);
            xa.commit(ec.getXid(), true);



            debug("commited write to DB - with TransactionContext, " +
                    "SecurityContext");
            //   newLine(2);
            //Controls.expectedResults = 1;
        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //eis-group
    private int testTICWithSICAndSICListenerForGroupCallback(int count, String groupName) {
        try {
            count++;
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec = startTx();
            debug("write to DB - with TransactionContext, SecurityContext");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MyPlainSICWithGPC sic = new MyPlainSICWithGPC(new String[]{groupName});
            w1.addWorkContext(sic);


            wm.doWork(w1, 0, null, null);
            //wm.doWork(w1, 0, ec, null);
            xa.commit(ec.getXid(), true);



            debug("commited write to DB - with TransactionContext, " +
                    "SecurityContext");
            //   newLine(2);
            Controls.expectedResults = 1;
        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //"jagadish", "prasath", "eis-prasath", true
    private int testTICWithSICAndSICListener(int count, boolean translationRequired, String user, String password,
                                             String principal, boolean expectSuccess, boolean expectPVSuccess) {
        try {
            count++;

            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //importing transaction

            //write/commit
            ExecutionContext ec = startTx();
            debug("write to DB - with TransactionContext, SecurityContext With LISTENER");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, translationRequired,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);


            wm.doWork(w1, 0, null, null);
            //wm.doWork(w1, 0, ec, null);
            xa.commit(ec.getXid(), true);



            debug("commited write to DB - with TransactionContext, " +
                    "SecurityContext With LISTENER");
            //   newLine(2);

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //jagadish prasath eis-jagadish true
    private int testDuplicateTICWithSIC(int count, boolean translationRequired, String user, String password,
                                        String principal) {
        try {
            //expect failure
            //count++;
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //write/commit
            ExecutionContext ec = startTx();
            debug("Write to DB - with DUPLICATE TransactionContext, SecurityContext");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal,
                    translationRequired, false, false);
            w1.addWorkContext(sic);

            //duplicate tx inflow context
            TransactionContext tic1 = new TransactionContext();
            tic1.setXid(ec.getXid());
            w1.addWorkContext(tic1);


            wm.doWork(w1, 0, null, null);
            xa.commit(ec.getXid(), true);



            debug("commited write to DB - with DUPLICATE TransactionContext, SecurityContext");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //jagadish, prasath, eis-jagadish, true
    private int testRollbackTICWithSIC(int count, boolean translationRequired, String user, String password,
                                       String principal, boolean expectSuccess, boolean expectPVSuccess) {
        try {
            count++;
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //write/commit
            ExecutionContext ec = startTx();
            debug("writing to DB - with TransactionContext, SecurityContext");
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContext(user, password, principal, translationRequired,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);
            wm.doWork(w1, 0, null, null);
            xa.commit(ec.getXid(), true);


            debug("committed write to DB - with TransactionContext, SecurityContext");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //jagadish, prasath, eis-jagadish, true
    private int testTICWithSIC(int count, boolean translationRequired, String user, String password, String principal,
                               boolean expectSuccess, boolean expectPVSuccess) {
        try {
            count++;
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //write/commit
            debug("writing to DB - with TransactionContext, SecurityContext");
            ExecutionContext ec = startTx();
            debug("Start TX - " + ec.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, translationRequired, expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);
            wm.doWork(w1, 0, null, null);
            xa.commit(ec.getXid(), true);


            debug("Committed write to DB - with TransactionContext, SecurityContext");

        } catch (Throwable e) {
            Controls.expectedResults = numOfMessages;
            e.printStackTrace();
            debug(e.toString());
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //abc, xyz, abc, true
    private int testTransactionContext(int count, boolean translationRequired, String user, String password,
                                       String principal, boolean expectSuccess, boolean expectPVSuccess) {
        try {
            count++;
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("writing to DB - with TransactionContext");
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);

            MySecurityContext sic = new MySecurityContextWithListener(user, password, principal, translationRequired,
                    expectSuccess, expectPVSuccess);
            w1.addWorkContext(sic);

            wm.doWork(w1, 0, null, null);
            xa.commit(tic.getXid(), true);


            debug("committed write to DB - with TransactionContext");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }


    private void testUnauthenticatedSIC_EmptyExecutionSubject() {
        try {

            debug("writing to DB - Unauthenticated SIC With Empty Execution Subject");

            //importing transaction

            //write/commit
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            UnauthenticatedSecurityContext_EmptyExecutionSubject uscees =
                    new UnauthenticatedSecurityContext_EmptyExecutionSubject();
            w1.addWorkContext(uscees);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);

            debug("commited write to DB - Unauthenticated SIC With Empty Execution Subject");

            Controls.expectedResults = numOfMessages;

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            notifyAndWait();
            newLine(2);
        }
    }


    private int testUnauthenticatedSIC_NullPrincipal(int count) {
        try {
            count++;
            debug("writing to DB - Unauthenticated SIC With Null Principal");

            //importing transaction

            //write/commit
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            UnauthenticatedSecurityContext_NullPrincipalOrName uscees =
                    new UnauthenticatedSecurityContext_NullPrincipalOrName(true, "", true);
            w1.addWorkContext(uscees);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);


            debug("commited write to DB - Unauthenticated SIC With Null Principal");


        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testUnauthenticatedSIC_NullName(int count) {
        try {
            count++;
            debug("writing to DB - Unauthenticated SIC With Null name");

            //importing transaction

            //write/commit
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            UnauthenticatedSecurityContext_NullPrincipalOrName uscees =
                    new UnauthenticatedSecurityContext_NullPrincipalOrName(true, null, false);
            w1.addWorkContext(uscees);

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);


            debug("commited write to DB - Unauthenticated SIC With Null name");


        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    //principal = eis-jagadish/jagadish
    private int testSinglePrincipalSIC(int count, String principal) {
        try {
            count++;
            debug("writing to DB - Single Principal SIC with TIC");

            //importing transaction

            //write/commit
            MessageEndpoint ep2 = factory.createEndpoint(new FakeXAResource());
            ExecutionContext ec1 = startTx();
            debug("Start TX - " + ec1.getXid());

            JSR322Work w1 =
                    new JSR322Work(ep2, numOfMessages, "WRITE");

            SinglePrincipalSIC spsic = new SinglePrincipalSIC(new PrincipalImpl(principal));
            w1.addWorkContext(spsic);

            TransactionContext tic = new TransactionContext();
            tic.setXid(ec1.getXid());
            w1.addWorkContext(tic);

          /*  HintsContext hc = new HintsContext();
            hc.setName("Hints-Context-Work");
            hc.setHint(HintsContext.NAME_HINT,"Hints-Context-Work");
            w1.addWorkContext(hc);*/

            wm.doWork(w1, 0, null, null);
            xa.commit(ec1.getXid(), true);

            debug("commited write to DB - Single Principal SIC with TIC");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();

        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;
        }
    }

    private int testExecutionContext(int count) {

        ExecutionContext ec = null;
        try {
            count++;
            debug("writing to DB - with ExecutionContext");
            //MessageEndpoint ep = factory.createEndpoint(null);
            MessageEndpoint ep = factory.createEndpoint(new FakeXAResource());

            //write/commit
            ec = startTx();
            debug("Start TX - " + ec.getXid());

            DeliveryWork w =
                    new DeliveryWork(ep, numOfMessages, "WRITE");
            wm.doWork(w, 0, ec, null);
            xa.commit(ec.getXid(), true);


            debug("commited write to DB - with ExecutionContext");

        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
            xa.rollback(ec.getXid());

        } finally {
            Controls.expectedResults = count;
            notifyAndWait();
            newLine(2);
            return Controls.expectedResults;

        }
    }

    private void checkContainerSupportForWorkContext(Class clz) {
        try {
            boolean supported = ctx.isContextSupported(clz);
            if (supported) {
                debug(clz.getName() + " is supported by container [bootstrapContext.isContextSupported()]");
            } else {
                debug(clz.getName() + " is NOT supported by container [bootstrapContext.isContextSupported()]");
            }
        } catch (Throwable e) {
            debug(e.toString());
            e.printStackTrace();
        } finally {
            //notifyAndWait();
        }
    }

    private void newLine(int count) {
        //for(int i=0; i<count; i++){
        System.out.println("JSR-322 -------------------------------------------------------------------------------");
        //}
    }

    public void release() {
    }

    public void stop() {
        this.stop = true;
    }

    public String toString() {
        return id;
    }

    public Method getOnMessageMethod() {

        Method onMessageMethod = null;
        try {
            Class msgListenerClass = connector.MyMessageListener.class;
            Class[] paramTypes = {java.lang.String.class};
            onMessageMethod =
                    msgListenerClass.getMethod("onMessage", paramTypes);

        } catch (NoSuchMethodException ex) {
            ex.printStackTrace();
        }
        return onMessageMethod;
    }

    private ExecutionContext startTx() {
        ExecutionContext ec = new ExecutionContext();
        try {
            Xid xid = new XID();
            ec.setXid(xid);
            ec.setTransactionTimeout(5 * 1000); //5 seconds
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
        return ec;
    }

    private void notifyAndWait() {
        try {
            //Sleep for 5 seconds
            //Thread.currentThread().sleep(5*1000);

            synchronized (Controls.readyLock) {
                //Notify the client to check the results
                Controls.readyLock.notify();

                //Wait until results are verified by the client
                Controls.readyLock.wait();

                if (stop) {
                    return;
                }
            }
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }

    private void done() {
        try {
            Controls.done = true;
            synchronized (Controls.readyLock) {
                //Notify the client to check the results
                Controls.readyLock.notify();
            }
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }

    public void debug(String message) {
        System.out.println("JSR-322 [RA] [WorkDispatcher(" + id + ")]: " + message);
    }

}
