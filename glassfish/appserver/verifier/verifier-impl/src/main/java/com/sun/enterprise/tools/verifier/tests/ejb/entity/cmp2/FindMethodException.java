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

package com.sun.enterprise.tools.verifier.tests.ejb.entity.cmp2;

import com.sun.enterprise.tools.verifier.Result;
import com.sun.enterprise.tools.verifier.tests.ComponentNameConstructor;
import org.glassfish.ejb.deployment.descriptor.EjbCMPEntityDescriptor;

import java.lang.reflect.Method;

/**
 * All finder methods should throw the javax.ejb.FinderException
 * 
 * @author  Jerome Dochez
 * @version 
 */
public class FindMethodException extends QueryMethodTest {

 
    /**
     * <p>
     * Run an individual test against a finder method (single or multi)
     * </p>
     * 
     * @param method is the finder method reference
     * @param descriptor is the entity bean descriptor
     * @param targetClass is the class to apply to tests to
     * @param result is where to place the result
     * 
     * @return true if the test passes
     */
    protected boolean runIndividualQueryTest(Method method, EjbCMPEntityDescriptor descriptor, Class targetClass, Result result) {
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();    
        if (methodThrowException(method, "javax.ejb.FinderException")) {
	    result.addGoodDetails(smh.getLocalString
				       ("tests.componentNameConstructor",
					"For [ {0} ]",
					new Object[] {compName.toString()}));
            result.addGoodDetails(smh.getLocalString
		("com.sun.enterprise.tools.verifier.tests.ejb.entity.cmp2.FindMethodException.passed",
                "[ {0} ] throws the javax.ejb.FinderException",
		new Object[] {method.getName()}));                   
            return true;
        } else {
	    result.addErrorDetails(smh.getLocalString
				       ("tests.componentNameConstructor",
					"For [ {0} ]",
					new Object[] {compName.toString()}));
            result.addErrorDetails(smh.getLocalString
		("com.sun.enterprise.tools.verifier.tests.ejb.entity.cmp2.FindMethodException.failed",
                "Error : [ {0} ] does not throw the javax.ejb.FinderException",
		new Object[] {method.getName()}));                   
            return false;
        }
    }
}
