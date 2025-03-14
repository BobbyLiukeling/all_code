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

package com.sun.enterprise.security.ee.authorize;

import java.lang.reflect.Method;

import com.sun.enterprise.security.authorize.PolicyContextDelegate;
import org.glassfish.api.invocation.ComponentInvocation;
import org.glassfish.ejb.api.EJBInvocation;
import org.jvnet.hk2.annotations.Service;

/**
 * This class is primarily a delegate for PolicyContextHandler related queries
 * But also handles Authorization of WebServiceInvocations
 * @author Kumar
 */
@Service(name="EJB")
public class EJBPolicyContextDelegate implements PolicyContextDelegate {

    public Object getEnterpriseBean(ComponentInvocation inv) {
        if (inv instanceof EJBInvocation) {
            return ((EJBInvocation)inv).getJaccEjb();
        }
        return null;
    }
    
    public Object getEJbArguments(ComponentInvocation inv) {
        if (inv instanceof EJBInvocation) {
            EJBInvocation eInv = (EJBInvocation) inv;
            if (eInv.isAWebService()) {
                return null;
            } else {
                return (eInv.getMethodParams() != null) ? eInv.getMethodParams() : new Object[0];
            }
        }
        return null;
    }
    
    public Object getSOAPMessage(ComponentInvocation inv) {
        if (inv instanceof EJBInvocation) {
            EJBInvocation eInv = (EJBInvocation) inv;
            if (eInv.isAWebService()) {
               //TODO:V3 does this violate JACC spec?, we may have to convert to SOAPMessage on demand
               //return eInv.getSOAPMessage();
                return eInv.getMessage();
            }
        }
        return null;
    }

    public void setSOAPMessage(Object message, ComponentInvocation inv) {
         if (inv instanceof EJBInvocation) {
            EJBInvocation eInv = (EJBInvocation) inv;
            if (eInv.isAWebService()) {
               eInv.setMessage(message);
            }
        }
    }

    public boolean authorize(ComponentInvocation inv, Method m) throws Exception {
         Exception ie = null;
         if (inv instanceof EJBInvocation) {
             return ((EJBInvocation)inv).authorizeWebService(m);
             
         }
         return true;
    }
    
}
