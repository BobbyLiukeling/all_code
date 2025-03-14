/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2012-2018 Oracle and/or its affiliates. All rights reserved.
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

package com.oracle.hk2.devtest.cdi.ejb1.scoped;

import javax.enterprise.context.RequestScoped;
import javax.inject.Inject;
import javax.inject.Named;

/**
 * @author jwells
 *
 */
@RequestScoped
public class CustomScopedEjb {
    @Inject
    private HK2Service hk2Service;
    
    @Inject @Named
    private HK2NamedService rumplestiltskin;
    
    @Inject @Named(HK2NamedServiceFactory2.NAME)
    private HK2NamedService carol;
    
    public void checkMe() {
        int jobValue = hk2Service.doAJob();
        
        if (jobValue != HK2Service.RETURN_VALUE) {
            throw new AssertionError("The doAJob method should have returned " + HK2Service.RETURN_VALUE +
                    " but returned " + jobValue);
        }
        
        if (!rumplestiltskin.getName().equals(HK2NamedServiceFactory.NAMED_SERVICE_NAME)) {
            throw new AssertionError("The naked @Named HK2NamedService was not set or had the wrong name: " + rumplestiltskin.getName());
        }
        
        if (!carol.getName().equals(HK2NamedServiceFactory2.NAME)) {
            throw new AssertionError("The specific @Named HK2NamedService was not set or had the wrong name: " + carol.getName());
        }
    }

}
