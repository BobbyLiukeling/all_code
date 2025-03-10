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

package com.sun.enterprise.tools.verifier.tests.web;

import com.sun.enterprise.tools.verifier.tests.web.WebTest;
import java.util.*;
import java.io.*;
import com.sun.enterprise.deployment.*;
import com.sun.enterprise.tools.verifier.*;
import com.sun.enterprise.tools.verifier.tests.*;


/** The auth-method element is used to configure the authentication mechanism 
 * for the web application. As a prerequisite to gaining access to any web 
 * resources which are protected by an authorization constraint, a user must 
 * have authenticated using the configured mechanism. Legal values for this 
 * element are "BASIC", "DIGEST", "FORM", or "CLIENT-CERT". 
 */
public class AuthMethod extends WebTest implements WebCheck { 

    
    /** The auth-method element is used to configure the authentication mechanism 
     * for the web application. As a prerequisite to gaining access to any web 
     * resources which are protected by an authorization constraint, a user must 
     * have authenticated using the configured mechanism. Legal values for this 
     * element are "BASIC", "DIGEST", "FORM", or "CLIENT-CERT". 
     *
     * @param descriptor the Web deployment descriptor 
     *
     * @return <code>Result</code> the results for this assertion
     */
    public Result check(WebBundleDescriptor descriptor) {

	Result result = getInitializedResult();
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();

	if (descriptor.getLoginConfiguration() != null) {
	    boolean foundIt = false;
	    boolean na = false;
	    String authMethod = descriptor.getLoginConfiguration().getAuthenticationMethod();
	    if (authMethod.length() > 0) {
		// use hard-coded strings until DOL gets updated
		if ((authMethod.equals("BASIC")) || 
		    (authMethod.equals("FORM")) || 
		    (authMethod.equals("CLIENT-CERT")) || 
		    (authMethod.equals("DIGEST"))) {
		    foundIt = true;
		} else {
		    foundIt = false;
		}
	    } else {
		na = true;
	    }
     
	    if (foundIt) {
		result.addGoodDetails(smh.getLocalString
					   ("tests.componentNameConstructor",
					    "For [ {0} ]",
					    new Object[] {compName.toString()}));
					
		result.passed(smh.getLocalString
			      (getClass().getName() + ".passed",
			       "The auth-method [ {0} ] is legal value within web application [ {1} ]",
			       new Object[] {authMethod, descriptor.getName()}));
	    } else if (na) {
		result.addNaDetails(smh.getLocalString
					   ("tests.componentNameConstructor",
					    "For [ {0} ]",
					    new Object[] {compName.toString()}));
	        result.notApplicable(smh.getLocalString
			 (getClass().getName() + ".notApplicable",
			  "There are no auth-method elements within the web archive [ {0} ]",
			  new Object[] {descriptor.getName()}));
	    } else {
		result.addErrorDetails(smh.getLocalString
			("tests.componentNameConstructor",
			"For [ {0} ]",
			new Object[] {compName.toString()}));
		result.failed(smh.getLocalString
			      (getClass().getName() + ".failed",
			       "Error: The auth-method [ {0} ] is not legal value within web application [ {1} ].  It must be either [ {2} ], [ {3} ], [ {4} ] or [ {5} ].",
			       new Object[] {authMethod, descriptor.getName(),"BASIC","FORM","CLIENT-CERT","DIGEST"}));
	    }
	} else {
	    result.addNaDetails(smh.getLocalString
					   ("tests.componentNameConstructor",
					    "For [ {0} ]",
					    new Object[] {compName.toString()}));
	    result.notApplicable(smh.getLocalString
				 (getClass().getName() + ".notApplicable",
				  "There are no auth-method elements within the web archive [ {0} ]",
				  new Object[] {descriptor.getName()}));
	}

	return result;
    }
}
