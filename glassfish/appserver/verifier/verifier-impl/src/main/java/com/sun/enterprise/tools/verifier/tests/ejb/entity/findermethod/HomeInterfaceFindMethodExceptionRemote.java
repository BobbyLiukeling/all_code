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

package com.sun.enterprise.tools.verifier.tests.ejb.entity.findermethod;

import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.Verifier;
import com.sun.enterprise.tools.verifier.VerifierTestContext;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbCheck;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbTest;
import com.sun.enterprise.tools.verifier.tests.ejb.EjbUtils;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;
import org.glassfish.ejb.deployment.descriptor.EjbEntityDescriptor;

import java.lang.reflect.Method;

/** 
 * Entity beans home interface find<METHOD> method throws 
 * java.rmi.RemoteException test.
 * 
 * The following are the requirements for the enterprise Bean's home interface 
 * find<METHOD> signature: 
 * 
 * An Entity Bean's home interface defines one or more find<METHOD>(...) 
 * methods. 
 * 
 * The throws clause must include java.rmi.RemoteException. 
 */
public class HomeInterfaceFindMethodExceptionRemote extends EjbTest implements EjbCheck { 


    /** 
     * Entity beans home interface find<METHOD> method throws 
     * java.rmi.RemoteException test.
     * 
     * The following are the requirements for the enterprise Bean's home interface 
     * find<METHOD> signature: 
     * 
     * An Entity Bean's home interface defines one or more find<METHOD>(...) 
     * methods. 
     * 
     * The throws clause must include java.rmi.RemoteException. 
     *    
     * @param descriptor the Enterprise Java Bean deployment descriptor
     *   
     * @return <code>Result</code> the results for this assertion
     */
    public Result check(EjbDescriptor descriptor) {

	Result result = getInitializedResult();
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();

	if (descriptor instanceof EjbEntityDescriptor) {
	    String persistence =
		((EjbEntityDescriptor)descriptor).getPersistenceType();
	    if (EjbEntityDescriptor.BEAN_PERSISTENCE.equals(persistence)) {
		boolean oneFailed = false;
		// RULE: Entity home interface are only allowed to have find<METHOD> 
		//       methods which must throw java.rmi.RemoteException
		if(descriptor.getHomeClassName() == null || "".equals(descriptor.getHomeClassName())) {
		    result.addNaDetails(smh.getLocalString
				   ("tests.componentNameConstructor",
				    "For [ {0} ]",
				    new Object[] {compName.toString()}));
		    result.addNaDetails(smh.getLocalString
						      (getClass().getName() + ".notApplicable1",
						       "No Remote Interface for this Ejb",
						       new Object[] {}));
		    return result;
		}

		try {
		    VerifierTestContext context = getVerifierContext();
		ClassLoader jcl = context.getClassLoader();
		    Class c = Class.forName(descriptor.getHomeClassName(), false, getVerifierContext().getClassLoader());
		    Method methods[] = c.getDeclaredMethods();
		    Class [] methodExceptionTypes;
		    boolean throwsRemoteException = false;
  
		    for (int i=0; i< methods.length; i++) {
			// clear these from last time thru loop
			throwsRemoteException = false;
			if (methods[i].getName().startsWith("find")) {
			    methodExceptionTypes = methods[i].getExceptionTypes();
                 
			    // methods must throw java.rmi.RemoteException
			    if (EjbUtils.isValidRemoteException(methodExceptionTypes)) {
				throwsRemoteException = true;
				break;
			    }
  
			    // report for this particular find<METHOD> method found in home 
			    // interface , now display the appropriate results for this 
			    // particular find<METHOD> method
			    if (throwsRemoteException ) {
				result.addGoodDetails(smh.getLocalString
				   ("tests.componentNameConstructor",
				    "For [ {0} ]",
				    new Object[] {compName.toString()}));
				result.addGoodDetails(smh.getLocalString
						      (getClass().getName() + ".debug1",
						       "For Home Interface [ {0} ] Method [ {1} ]",
						       new Object[] {c.getName(),methods[i].getName()}));
				result.addGoodDetails(smh.getLocalString
						      (getClass().getName() + ".passed",
						       "The find<METHOD> method which must throw java.rmi.RemoteException was found."));
			    } else if (!throwsRemoteException) {
				oneFailed = true;
				result.addErrorDetails(smh.getLocalString
				   ("tests.componentNameConstructor",
				    "For [ {0} ]",
				    new Object[] {compName.toString()}));
				result.addErrorDetails(smh.getLocalString
						       (getClass().getName() + ".debug1",
							"For Home Interface [ {0} ] Method [ {1} ]",
							new Object[] {c.getName(),methods[i].getName()}));
				result.addErrorDetails(smh.getLocalString
						       (getClass().getName() + ".failed",
							"Error: A find<METHOD> method was found, but did not throw java.rmi.RemoteException." ));
			    }  // end of reporting for this particular 'find' method
			} // if the home interface found a "find" method
		    } // for all the methods within the home interface class, loop
               
  
		} catch (ClassNotFoundException e) {
		    Verifier.debug(e);
		    result.addErrorDetails(smh.getLocalString
					   ("tests.componentNameConstructor",
					    "For [ {0} ]",
					    new Object[] {compName.toString()}));
		    result.failed(smh.getLocalString
				  (getClass().getName() + ".failedException",
				   "Error: Home interface [ {0} ] does not exist or is not loadable within bean [ {1} ]",
				   new Object[] {descriptor.getHomeClassName(), descriptor.getName()}));
		}
  
		if (oneFailed) {
		    result.setStatus(result.FAILED);
		} else {
		    result.setStatus(result.PASSED);
		}
		return result;
	    } else { //if (CONTAINER_PERSISTENCE.equals(persistence))
		result.addNaDetails(smh.getLocalString
				   ("tests.componentNameConstructor",
				    "For [ {0} ]",
				    new Object[] {compName.toString()}));
		result.notApplicable(smh.getLocalString
				     (getClass().getName() + ".notApplicable2",
				      "Expected [ {0} ] managed persistence, but [ {1} ] bean has [ {2} ] managed persistence.",
				      new Object[] {EjbEntityDescriptor.BEAN_PERSISTENCE,descriptor.getName(),persistence}));
		return result;
	    }
        
	} else {
	    result.addNaDetails(smh.getLocalString
				   ("tests.componentNameConstructor",
				    "For [ {0} ]",
				    new Object[] {compName.toString()}));
	    result.notApplicable(smh.getLocalString
				 (getClass().getName() + ".notApplicable",
				  "{0} expected {1} bean, but called with {2} bean",
				  new Object[] {getClass(),"Entity","Session"}));
	    return result;
	} 
    }
}
