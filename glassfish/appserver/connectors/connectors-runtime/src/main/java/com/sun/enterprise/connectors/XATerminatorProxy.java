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

package com.sun.enterprise.connectors;

import javax.resource.spi.XATerminator;
import javax.transaction.xa.Xid;
import javax.transaction.xa.XAException;
import java.io.Externalizable;
import java.io.ObjectOutput;
import java.io.IOException;
import java.io.ObjectInput;

/**
 * Proxy for XATerminator.<br>
 * This implementation is Serializable(Externalizable) such that RAR implementation
 * can use it safely in Serialization mandated scenarios<br>
 *
 * @author Jagadish Ramu
 */
public class XATerminatorProxy implements XATerminator, Externalizable {

    private transient XATerminator xat;

    /**
     * Provides a proxy for XATerminator
     * @param xat Actual XATerminator
     */
    public XATerminatorProxy(XATerminator xat){
        this.xat = xat;
    }

    /**
     * Provides a proxy for XATerminator<br>
     * no-args constructor for de-serialization
     */
    public XATerminatorProxy(){
    }

    /**
     * @see javax.resource.spi.XATerminator
     */
    public void commit(Xid xid, boolean onePhase) throws XAException {
        xat.commit(xid, onePhase);
    }

    /**
     * @see javax.resource.spi.XATerminator
     */
    public void forget(Xid xid) throws XAException {
        xat.forget(xid);
    }

    /**
     * @see javax.resource.spi.XATerminator
     */
    public int prepare(Xid xid) throws XAException {
        return xat.prepare(xid);
    }

    /**
     * @see javax.resource.spi.XATerminator
     */
    public Xid[] recover(int flag) throws XAException {
        return xat.recover(flag);
    }

    /**
     * @see javax.resource.spi.XATerminator
     */
    public void rollback(Xid xid) throws XAException {
        xat.rollback(xid);
    }

    /**
     * @see java.io.Externalizable
     */
    public void writeExternal(ObjectOutput out) throws IOException {
        //do nothing
    }

    /**
     * @see java.io.Externalizable
     */
    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        xat = ConnectorRuntime.getRuntime().getTransactionManager().getXATerminator();
    }
}
