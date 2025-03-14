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

package com.sun.jts.pi;

import org.omg.CORBA.Policy;
import org.omg.CORBA.LocalObject;

import org.omg.CosTransactions.ADAPTS;
import org.omg.CosTransactions.FORBIDS;
import org.omg.CosTransactions.REQUIRES;
import org.omg.CosTransactions.OTSPolicy;
import org.omg.CosTransactions.OTS_POLICY_TYPE;

/**
 * This is the OTSPolicy object which holds an appropriate policy value.
 *
 * @author Ram Jeyaraman 11/11/2000
 * @version 1.0
 */
public class OTSPolicyImpl extends LocalObject implements OTSPolicy {

    // class constants

    public static final OTSPolicy _ADAPTS = new OTSPolicyImpl(ADAPTS.value);
    public static final OTSPolicy _FORBIDS = new OTSPolicyImpl(FORBIDS.value);
    public static final OTSPolicy _REQUIRES = new OTSPolicyImpl(REQUIRES.value);

    // instance variables

    private short value = FORBIDS.value;

    // constructor

    public OTSPolicyImpl() {
        this.value = FORBIDS.value;
    }

    public OTSPolicyImpl(short value) {
        this.value = value;
    }

    // org.omg.CosTransactions.OTSPolicyOperations implementation

    public short value() {
        return this.value;
    }

    // org.omg.CORBA.PolicyOperations implementation

    public int policy_type() {
	return OTS_POLICY_TYPE.value;
    }

    public Policy copy() {
	return new OTSPolicyImpl(this.value);
    }

    public void destroy() {
	value = FORBIDS.value;
    }

    public String toString() {
	return "OTSPolicy[" + this.value + "]";
    }
}
