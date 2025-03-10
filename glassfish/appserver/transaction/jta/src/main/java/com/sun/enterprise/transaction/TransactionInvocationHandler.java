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

package com.sun.enterprise.transaction;

import java.util.logging.Level;
import java.util.logging.Logger;

import com.sun.logging.LogDomains;
import com.sun.enterprise.transaction.api.JavaEETransactionManager;

import org.glassfish.api.invocation.ComponentInvocation;
import org.glassfish.api.invocation.ComponentInvocation.ComponentInvocationType;
import org.glassfish.api.invocation.ComponentInvocationHandler;
import org.glassfish.api.invocation.InvocationException;

import org.jvnet.hk2.annotations.Service;
import javax.inject.Inject;
import org.glassfish.hk2.api.PostConstruct;
import org.glassfish.hk2.api.ServiceLocator;

@Service
public class TransactionInvocationHandler implements ComponentInvocationHandler {

    private static Logger _logger = LogDomains.getLogger(
            TransactionInvocationHandler.class, LogDomains.JTA_LOGGER);

    @Inject private ServiceLocator habitat;

    private JavaEETransactionManager tm;

    /**
     * Dynamically init the reference. This avoids circular dependencies 
     * on injection: JavaEETransactionManager injects InvocationManager, which in
     * turn injects all ComponentInvocationHandler impls, i.e. instance of this class.
     * PostConstruct has a similar problem.
     */
    private void init() {
        if (tm == null ) {
            tm = habitat.getService(JavaEETransactionManager.class);
        }
    }

    public void beforePreInvoke(ComponentInvocationType invType,
            ComponentInvocation prevInv, ComponentInvocation newInv) throws InvocationException {
    }

    public void afterPreInvoke(ComponentInvocationType invType,
            ComponentInvocation prevInv, ComponentInvocation curInv) throws InvocationException {

        init();
        tm.preInvoke(prevInv);
    }

    public void beforePostInvoke(ComponentInvocationType invType,
            ComponentInvocation prevInv, ComponentInvocation curInv) throws InvocationException {
        init();
        tm.postInvoke(curInv, prevInv);
    }

    public void afterPostInvoke(ComponentInvocationType invType,
            ComponentInvocation prevInv, ComponentInvocation curInv) throws InvocationException {
    }
}
