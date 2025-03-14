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

package com.sun.enterprise.tools.verifier.tests.ejb.businessmethod;

import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.Verifier;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbCheck;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbTest;
import com.sun.enterprise.tools.verifier.tests.ejb.RmiIIOPUtils;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;
import org.glassfish.ejb.deployment.descriptor.EjbEntityDescriptor;
import org.glassfish.ejb.deployment.descriptor.EjbSessionDescriptor;

import java.lang.reflect.Method;
import java.util.Set;


/**  
 * Enterprise Bean's business(...) methods argument RMI IIOP test.
 * Each enterprise Bean class must define zero or more business(...) methods. 
 * The method signatures must follow these rules: 
 * 
 * The methods return value must be legal types for RMI-IIOP. 
 */
public class BusinessMethodRmiIIOPReturn extends EjbTest implements EjbCheck { 
    
    Result result = null;
    ComponentNameConstructor compName = null;
    /** 
     * Enterprise Bean's business(...) methods argument RMI IIOP test.
     * Each enterprise Bean class must define zero or more business(...)  
     * methods.  The method signatures must follow these rules: 
     * 
     * The methods return value must be legal types for RMI-IIOP. 
     * 
     * @param descriptor the Enterprise Java Bean deployment descriptor
     *   
     * @return <code>Result</code> the results for this assertion
     */
    public Result check(EjbDescriptor descriptor) {
        
        result = getInitializedResult();
        compName = getVerifierContext().getComponentNameConstructor();
        
        if ((descriptor instanceof EjbSessionDescriptor)  ||
                (descriptor instanceof EjbEntityDescriptor)) {
            if(descriptor.getRemoteClassName() != null && !"".equals(descriptor.getRemoteClassName())) 
                commonToBothInterfaces(descriptor.getRemoteClassName(),descriptor);
            
            Set<String> remoteInterfaces = descriptor.getRemoteBusinessClassNames();
            for (String remoteIntf : remoteInterfaces) 
                commonToBothInterfaces(remoteIntf, descriptor);
        } 
        if(result.getStatus() != Result.FAILED) {
            addGoodDetails(result, compName);
            result.passed(smh.getLocalString
                    (getClass().getName() + ".passed",
                    "Proper declaration of business method(s) found."));
        }
        return result;
    }
    
    private void commonToBothInterfaces(String intf, EjbDescriptor descriptor) {
        try {
            Class intfClass = Class.forName(intf, false, getVerifierContext().getClassLoader());
            
            for (Method remoteMethod : intfClass.getMethods()) {
                
                // we don't test the EJB methods
                if (remoteMethod.getDeclaringClass().getName().equals("javax.ejb.EJBObject")) 
                    continue;
                Class beanClass = Class.forName(descriptor.getEjbClassName(), 
                                                false, 
                                                getVerifierContext().getClassLoader());
                for (Method method : beanClass.getMethods()) {
                    
                    if (method.getName().equals(remoteMethod.getName()) &&
                            !RmiIIOPUtils.isValidRmiIIOPReturnType(method.getReturnType())) {
                        // The methods arguments types must be legal types for
                        // RMI-IIOP.  This means that their return values must
                        // be of valid types for RMI-IIOP,
                        addErrorDetails(result, compName);
                        result.failed(smh.getLocalString
                                (getClass().getName() + ".failed",
                                "Error: business method [ {0} ] was found, but " +
                                "business method has invalid return type [ {1} ]. Business " +
                                "method return type must be a valid type for RMI-IIOP.",
                                new Object[] {method.getName(), method.getReturnType()}));
                    }
                }
            }
            
        } catch (ClassNotFoundException e) {
            Verifier.debug(e);
            addErrorDetails(result, compName);
            result.failed(smh.getLocalString
                    (getClass().getName() + ".failedException",
                    "Error: Remote interface [ {0} ] or bean class [ {1} ] does " +
                    "not exist or is not loadable within bean [ {2} ].",
                    new Object[] {descriptor.getRemoteClassName(),
                                  descriptor.getEjbClassName(),
                                  descriptor.getName()}));
        }  
        
    }
}
