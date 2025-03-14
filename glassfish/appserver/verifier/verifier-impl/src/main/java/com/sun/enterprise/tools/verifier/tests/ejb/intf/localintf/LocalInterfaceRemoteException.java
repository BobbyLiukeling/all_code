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

package com.sun.enterprise.tools.verifier.tests.ejb.intf.localintf;

import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.Verifier;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbTest;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;

import java.lang.reflect.Method;

/**
 * The throws clause of a home method on the local home interface may include 
 * additional application-level exceptions. It must not include the 
 * java.rmi.RemoteException.
 * 
 * @author Vikas Awasthi
 */
public class LocalInterfaceRemoteException extends EjbTest {

    public Result check(EjbDescriptor descriptor) {
        Result result = getInitializedResult();
        ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();
        ClassLoader cl = getVerifierContext().getClassLoader();
        String localClassName = descriptor.getLocalHomeClassName();
        if (localClassName!=null) {
            try {
                Class localHome = Class.forName(localClassName, false, cl);
                Method[] methods = localHome.getMethods();
                for (int i = 0; i < methods.length; i++) {
                    if(containsRemote(methods[i].getExceptionTypes())) {
                        addErrorDetails(result, compName);
                        result.failed(smh.getLocalString
                                (getClass().getName()+".failed",
                                "Method [ {0} ] throws a RemoteException.", 
                                new Object[]{methods[i]}));
                    }
                
                }
            } catch (ClassNotFoundException e) {
                Verifier.debug(e);
                addErrorDetails(result, compName);
                result.failed(smh.getLocalString
                                (getClass().getName()+".failed1",
                                "LocalHome class [ {0} ] not found.", 
                                new Object[]{localClassName}));
            }
        }

        if(result.getStatus() != Result.FAILED) {
            addGoodDetails(result, compName);
            result.passed(smh.getLocalString
                    (getClass().getName() + ".passed",
                            "Valid LocalInterface."));
        }
        return result;
    }
    
    /** returns true if one of the exceptions is RemoteException*/
    private boolean containsRemote(Class[] exceptions) {
        for (int i = 0; i < exceptions.length; i++) 
            if(exceptions[i].getName().equals("java.rmi.RemoteException"))
                return true;
        
        return false;
    }
}
