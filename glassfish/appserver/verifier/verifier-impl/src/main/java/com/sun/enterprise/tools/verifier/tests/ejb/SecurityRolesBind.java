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

import com.sun.enterprise.deployment.RoleReference;
import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import org.glassfish.ejb.deployment.descriptor.EjbBundleDescriptorImpl;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;
import org.glassfish.security.common.Role;

import java.util.Iterator;
import java.util.Set;

/**
 * If the Application assembler defines security roles in the deployment 
 * descriptor, the Application Assembler must bind security role references 
 * declared by the Bean Provider to the security roles. 
 */
public class SecurityRolesBind extends EjbTest implements EjbCheck { 



    /** 
     * If the Application assembler defines security roles in the deployment
     * descriptor, the Application Assembler must bind security role references
     * declared by the Bean Provider to the security roles.
     *
     * @param descriptor the Enterprise Java Bean deployment descriptor
     *
     * @return <code>Result</code> the results for this assertion
     */
    public Result check(EjbDescriptor descriptor) {

	Result result = getInitializedResult();
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();

	EjbBundleDescriptorImpl bundleDescriptor = descriptor.getEjbBundleDescriptor();
	Set ejbs = bundleDescriptor.getEjbs();
	Iterator ejbIterator = ejbs.iterator();
	EjbDescriptor ejb = null;
	Set roleReferences = null;
	Iterator roleRefsIterator = null;
	Set roles = bundleDescriptor.getRoles();
	Iterator rolesIterator = roles.iterator();
	RoleReference roleReference = null;
	Role role = null;
	boolean oneFailed = false;
        
	// check to see if there are any undefined roles being referenced
	while (ejbIterator.hasNext()) {
	    ejb = (EjbDescriptor)ejbIterator.next();
	    roleReferences = ejb.getRoleReferences();
	    roleRefsIterator = roleReferences.iterator();
	    if (roleRefsIterator.hasNext()) {
		while (roleRefsIterator.hasNext()) {
		    roleReference = (RoleReference)roleRefsIterator.next();
		    role = roleReference.getRole();
		    if (!role.getName().equals("")
			&& !bundleDescriptor.getRoles().contains(role) ) {
			// print the undefine role
			result.addErrorDetails(smh.getLocalString
					       ("tests.componentNameConstructor",
						"For [ {0} ]",
						new Object[] {compName.toString()}));
			result.addErrorDetails(smh.getLocalString
					       (getClass().getName() + ".failed",
						"Error: The role [ {0} ] for bean [ {1} ] is undefined.",
						new Object[] {role.getName(),ejb.getName()}));
			if (!oneFailed) {
			    oneFailed = true;
			}
		    } else {
			result.addGoodDetails(smh.getLocalString
					      ("tests.componentNameConstructor",
					       "For [ {0} ]",
					       new Object[] {compName.toString()}));
			result.passed(smh.getLocalString
				      (getClass().getName() + ".passed",
				       "The role [ {0} ] for bean [ {1} ] is defined.",
				       new Object[] {role.getName(),ejb.getName()}));
		    }
		}
	    } else {
		result.addNaDetails(smh.getLocalString
				    ("tests.componentNameConstructor",
				     "For [ {0} ]",
				     new Object[] {compName.toString()}));
		result.notApplicable(smh.getLocalString
				     (getClass().getName() + ".notApplicable",
				      "There are no role references which need to be bound to other security roles within this bean [ {0} ]",
				      new Object[] {ejb.getName()}));
	    }
	}

	if (oneFailed) {
	    result.setStatus(Result.FAILED);   
	}
        
	return result;
    }    
}
