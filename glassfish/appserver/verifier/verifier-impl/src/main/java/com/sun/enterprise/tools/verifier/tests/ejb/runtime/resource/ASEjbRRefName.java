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

package com.sun.enterprise.tools.verifier.tests.ejb.runtime.resource;

import java.util.Iterator;
import java.util.Set;

import com.sun.enterprise.deployment.ResourceReferenceDescriptor;
import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;

/** ejb [0,n]
 *   resource-ref [0,n]
 *       res-ref-name [String]
 *       jndi-name [String]
 *       default-resource-principal ?
 *           name [String]
 *           password [String]
 *
 * The res-ref-name specfies the name of the resource in the ejb-jar.xml for which
 * this element shows the jndi binding properties
 *
 * The res-ref-name should exist in the ejb-jar.xml file
 *
 * @author Irfan Ahmed
 */
public class ASEjbRRefName extends ASEjbResRef { 

    public Result check(EjbDescriptor descriptor)
    {
        Result result = getInitializedResult();
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();
        boolean oneFailed = false;
        try
        {
        Set resRef = descriptor.getResourceReferenceDescriptors();
        if(!(resRef.isEmpty()))
        {
            Iterator it = resRef.iterator();
            while (it.hasNext())
            {
                ResourceReferenceDescriptor resDesc = ((ResourceReferenceDescriptor)it.next());
                String refName = resDesc.getName();
                if(refName == null || refName.length()==0)
                    {
                        addErrorDetails(result, compName);
                        result.failed(smh.getLocalString(getClass().getName()+".failed",
                            "FAILED [AS-EJB resource-ref] : resource-ref has empty res-ref-name"));
                    }
                    else
                    {
                        addGoodDetails(result, compName);
                        result.passed(smh.getLocalString(getClass().getName()+".passed",
                            "PASSED [AS-EJB resource-ref] : res-ref-name is {0}",new Object[]{refName}));
                    }
            }
        }
        else
        {
            addNaDetails(result, compName);
            result.notApplicable(smh.getLocalString
                (getClass().getName() + ".notApplicable",
                    "{0} Does not define any resource-ref Elements",
                    new Object[] {descriptor.getName()}));
        }
        }catch(Exception ex)
        {
            addErrorDetails(result, compName);
            result.addErrorDetails(smh.getLocalString
                 (getClass().getName() + ".notRun",
                  "NOT RUN [AS-EJB] : Could not create the descriptor object"));
        }
        return result;
    }
}
