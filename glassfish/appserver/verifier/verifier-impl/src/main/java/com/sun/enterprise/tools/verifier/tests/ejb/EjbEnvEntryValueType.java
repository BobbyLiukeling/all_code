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

package com.sun.enterprise.tools.verifier.tests.ejb;

import com.sun.enterprise.deployment.EnvironmentProperty;
import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;

import java.util.Iterator;

/** 
 * The environment entry value type must be one of the following Java types:
 * String, Integer, Boolean, Double, Byte, Short, Long, and Float.
 */
public class EjbEnvEntryValueType extends EjbTest implements EjbCheck { 



    /** 
     * The environment entry value type must be one of the following Java types:
     * String, Integer, Boolean, Double, Byte, Short, Long, and Float.
     *
     * @param descriptor the Enterprise Java Bean deployment descriptor
     *
     * @return <code>Result</code> the results for this assertion
     */
    public Result check(EjbDescriptor descriptor) {

        Result result = getInitializedResult();
        ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();

        if (!descriptor.getEnvironmentProperties().isEmpty()) {
            // environment entry value type must be one of the following Java types:
            // String, Integer, Boolean, Double, Byte, Short, Long, and Float.
            for (Iterator itr = descriptor.getEnvironmentProperties().iterator();
                 itr.hasNext();) {
                EnvironmentProperty nextEnvironmentProperty =
                        (EnvironmentProperty) itr.next();
                String envType = nextEnvironmentProperty.getType();
                if (!((envType.equals("java.lang.String")) ||
                        (envType.equals("java.lang.Integer")) ||
                        (envType.equals("java.lang.Boolean")) ||
                        (envType.equals("java.lang.Double")) ||
                        (envType.equals("java.lang.Byte")) ||
                        (envType.equals("java.lang.Short")) ||
                        (envType.equals("java.lang.Long")) ||
                        (envType.equals("java.lang.Character")) ||
                        (envType.equals("java.lang.Float")))) {
                    addErrorDetails(result, compName);
                    result.failed(smh.getLocalString
                            (getClass().getName() + ".failed",
                            "Error: Environment entry value [ {0} ] does not have" +
                            " valid value type [ {1} ] within bean [ {2} ]",
                            new Object[] {nextEnvironmentProperty.getName(),envType, descriptor.getName()}));
                }
            }
        }
        if(result.getStatus() != Result.FAILED) {
            addGoodDetails(result, compName);
            result.passed(smh.getLocalString
                    (getClass().getName() + ".passed",
                    "Environment entry value has valid value type"));
        }
        return result;
    }
}
