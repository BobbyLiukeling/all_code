/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2008-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.container.common.spi.util;

import com.sun.enterprise.deployment.JndiNameEnvironment;
import com.sun.enterprise.deployment.EnvironmentProperty;
import com.sun.enterprise.deployment.ResourceReferenceDescriptor;

import org.glassfish.api.invocation.ApplicationEnvironment;
import org.glassfish.api.naming.JNDIBinding;
import org.jvnet.hk2.annotations.Contract;

import javax.naming.NamingException;
import java.util.Collection;

@Contract
public interface ComponentEnvManager {

    //Remove once WebContainer sets JndiNameEnvironment on every "new ComponentInvocation()"
    public JndiNameEnvironment getJndiNameEnvironment(String componentId);

    //Remove once WebContainer sets JndiNameEnvironment on every "new ComponentInvocation()"
    public JndiNameEnvironment getCurrentJndiNameEnvironment();

    public String getComponentEnvId(JndiNameEnvironment env);

    public String bindToComponentNamespace(JndiNameEnvironment env)
        throws NamingException;

    public void addToComponentNamespace(JndiNameEnvironment origEnv,
                                        Collection<EnvironmentProperty> envProps,
                                        Collection<ResourceReferenceDescriptor> resRefs)
        throws NamingException;

    public void unbindFromComponentNamespace(JndiNameEnvironment env)
        throws NamingException;
    
    /**
     * Returns the current application environment if not running in a specified
     * container
     * 
     * @return The current application environment or null if we are not currently
     * running as a specific application
     */
    public ApplicationEnvironment getCurrentApplicationEnvironment();
    
}
