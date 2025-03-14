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

package com.sun.enterprise.tools.verifier.tests.ejb.runtime.beanpool;

import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.Verifier;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;

/** ejb [0,n]
 *    bean-pool ?
 *        steady-pool-size ? [String]
 *        pool-resize-quantity ? [String]
 *        max-pool-size ? [String]
 *        pool-idle-timeout-in-seconds ? [String]
 *        max-wait-time-in-millis ? [String]
 *
 * The steady-pool-size element specifies the initial and minimum number of beans
 * that must be maintained in the bean pool.
 *
 * Valid values are from 0 to MAX_INT
 *
 *
 * @author Irfan Ahmed
 */
public class ASEjbBPSteadyPoolSize extends ASEjbBeanPool
{
    
    public Result check(EjbDescriptor descriptor)
    {
        Result result = getInitializedResult();
        ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();
        String pool = null;
        String steadyPoolSize=null;
        String maxPoolSize = null;

        try{
            pool = getXPathValue("/sun-ejb-jar/enterprise-beans/ejb[ejb-name=\""+descriptor.getName()+"\"]/bean-pool");
            if (pool!=null)
            {
                steadyPoolSize = getXPathValue("/sun-ejb-jar/enterprise-beans/ejb[ejb-name=\""+descriptor.getName()+"\"]/bean-pool/steady-pool-size");
                if (steadyPoolSize!=null){
                    steadyPoolSize = steadyPoolSize.trim();
                    if (steadyPoolSize.length()==0)
                    {
                        addErrorDetails(result, compName);
                        result.failed(smh.getLocalString(getClass().getName()+".failed",
                            "FAILED [AS-EJB bean-pool] : steady-pool-size cannot be empty"));
                    }else
                    {
                        try
                        {
                            int value = Integer.parseInt(steadyPoolSize);
                            if(value < 0  || value > Integer.MAX_VALUE)
                            {
                                addErrorDetails(result, compName);
                                result.failed(smh.getLocalString(getClass().getName()+".failed1",
                                    "FAILED [AS-EJB bean-pool] : steady-pool-size cannot be {0}. It should be between 0 and {1}",
                                     new Object[]{new Integer(value),new Integer(Integer.MAX_VALUE)}));
                            }else
                            {
                                maxPoolSize = getXPathValue("/sun-ejb-jar/enterprise-beans/ejb[ejb-name=\""+descriptor.getName()+"\"]/bean-pool/max-pool-size");
                                int maxPool = 0;
                                if(maxPoolSize != null)
                                {
                                    try{
                                        maxPool = Integer.parseInt(maxPoolSize);
                                    }catch(NumberFormatException nfe){
                                        addErrorDetails(result, compName);
                                        result.failed(smh.getLocalString(getClass().getName()+".failed2",
                                            "FAILED [AS-EJB bean-pool] : The value {0} for max-pool-size is not a valid Integer number",new Object[]{maxPoolSize}));
                                            return result;
                                    }
                                    if(value <= maxPool)
                                    {
                                        addGoodDetails(result, compName);
                                        result.passed(smh.getLocalString(getClass().getName()+".passed",
                                            "PASSED [AS-EJB bean-pool] : steady-pool-size is {0} and is less-than/equal-to max-pool-size [{1}]",
                                             new Object[]{new Integer(value), new Integer(maxPool)}));
                                    }else
                                    {
                                        addWarningDetails(result, compName);
                                        result.warning(smh.getLocalString(getClass().getName()+".warning","WARNING [AS-EJB bean-pool] : steady-pool-size [{0}]  is greater than max-pool-size[{1}]", new Object[]{new Integer(value), new Integer(maxPool)}));
                                    }
                                }else
                                {
                                    addGoodDetails(result, compName);
                                    result.passed(smh.getLocalString(getClass().getName()+".passed1",
                                        "PASSED [AS-EJB bean-pool] : steady-pool-size is {0}",new Object[] { new Integer(value)}));
                                }
                            }
                        }catch(NumberFormatException nfex)
                        {
                            Verifier.debug(nfex);
                            addErrorDetails(result, compName);
                            result.failed(smh.getLocalString(getClass().getName()+".failed3",
                                    "FAILED [AS-EJB bean-pool] : The value {0} for steady-pool-size is not a valid Integer number",
                                    new Object[]{steadyPoolSize}));
                        }
                    }
                }else  // steady-pool-size not defined
                {
                    addNaDetails(result, compName);
                    result.notApplicable(smh.getLocalString(getClass().getName()+".notApplicable",
                        "NOT APPLICABLE [AS-EJB bean-pool] : steady-pool-size element not defined"));
                }
            }else   // bean-pool not defined
            {
                addNaDetails(result, compName);
                result.notApplicable(smh.getLocalString(getClass().getName()+".notApplicable1",
                        "NOT APPLICABLE [AS-EJB] : bean-pool element not defined"));
            }
        }catch(Exception ex){
            addErrorDetails(result, compName);
            result.addErrorDetails(smh.getLocalString
                 (getClass().getName() + ".notRun",
                  "NOT RUN [AS-EJB] : Could not create an descriptor object"));
        }
        return result;
    }
}
