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

/*
 * ConnectionMetaDataExistence.java
 *
 * Created on October 5, 2000, 10:44 AM
 */

package com.sun.enterprise.tools.verifier.tests.connector.cci;

import java.io.File;
import com.sun.enterprise.tools.verifier.tests.connector.ConnectorTest;
import com.sun.enterprise.tools.verifier.tests.connector.ConnectorCheck;
import com.sun.enterprise.tools.verifier.*;
import com.sun.enterprise.tools.verifier.tests.*;
import com.sun.enterprise.deployment.ConnectorDescriptor;

/**
 * Test if a javax.resource.cci.ConnectionMetaData implementation has been provided in
 * the rar file
 *
 * @author  Jerome Dochez
 * @version 
 */
public class ConnectionMetaDataExistence 
    extends ConnectionFactoryTest 
    implements ConnectorCheck 
{

    /** <p>
     * Test if a javax.resource.cci.ConnectionMetaData implementation has been 
     * provided in the rar file
     * </p>
     *
     * @paramm descriptor deployment descriptor for the rar file
     * @return result object containing the result of the individual test
     * performed
     */
    public Result check(ConnectorDescriptor descriptor) {
                
        Result result = getInitializedResult();
	ComponentNameConstructor compName = getVerifierContext().getComponentNameConstructor();
        
        if (isCCIImplemented(descriptor, result)) {
            //File jarFile = Verifier.getJarFile(descriptor.getModuleDescriptor().getArchiveUri());
//            File f=Verifier.getArchiveFile(descriptor.getModuleDescriptor().getArchiveUri());
            findImplementorOf(descriptor, "javax.resource.cci.ConnectionMetaData", result);
        } else {
	    result.addNaDetails(smh.getLocalString
				  ("tests.componentNameConstructor",
				   "For [ {0} ]",
				   new Object[] {compName.toString()}));
	    result.notApplicable(smh.getLocalString
    	        ("com.sun.enterprise.tools.verifier.tests.connector.cci.InteractionExistence.notapp",
                 "NotApplicable : The CCI interfaces do not seem to be implemented by this resource adapter"));
        }       
        return result;
    }
}
