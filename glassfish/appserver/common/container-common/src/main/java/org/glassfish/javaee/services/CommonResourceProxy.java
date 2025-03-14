/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2012-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.javaee.services;

import com.sun.appserv.connectors.internal.api.ConnectorsUtil;
import org.glassfish.api.naming.NamingObjectProxy;
import com.sun.enterprise.deployment.ResourceDescriptor;
import org.glassfish.hk2.api.PerLookup;
import org.glassfish.hk2.api.ServiceLocator;
import org.glassfish.internal.api.Globals;
import org.glassfish.resourcebase.resources.api.ResourceDeployer;
import org.glassfish.resourcebase.resources.util.ResourceManagerFactory;
import org.jvnet.hk2.annotations.Service;

import javax.inject.Inject;
import javax.naming.Context;
import javax.naming.NamingException;
import java.io.Serializable;

/**
 * Created with IntelliJ IDEA.
 * User: naman
 * Date: 27/8/12
 * Time: 2:51 PM
 * To change this template use File | Settings | File Templates.
 */
@Service
@PerLookup
public class CommonResourceProxy implements NamingObjectProxy.InitializationNamingObjectProxy, Serializable {

    @Inject
    protected transient ServiceLocator serviceLocator;
    protected ResourceDescriptor desc;
    protected String actualResourceName;

    public synchronized Object create(Context ic) throws NamingException {
        if (actualResourceName == null) {

            actualResourceName = ConnectorsUtil.deriveResourceName
                    (desc.getResourceId(), desc.getName(), desc.getResourceType());

            try {
                if (serviceLocator == null) {
                    serviceLocator = Globals.getDefaultHabitat();
                    if (serviceLocator == null) {
                        throw new NamingException("Unable to create resource " +
                                "[" + desc.getName() + " ] as habitat is null");
                    }
                }
                getResourceDeployer(desc).deployResource(desc);
            } catch (Exception e) {
                NamingException ne = new NamingException("Unable to create resource [" + desc.getName() + " ]");
                ne.initCause(e);
                throw ne;
            }
        }
        return ic.lookup(actualResourceName);
    }

    protected ResourceDeployer getResourceDeployer(Object resource) {
        return serviceLocator.<ResourceManagerFactory>getService(ResourceManagerFactory.class).getResourceDeployer(resource);
    }

    public synchronized void setDescriptor(ResourceDescriptor desc) {
        this.desc = desc;
    }
}
