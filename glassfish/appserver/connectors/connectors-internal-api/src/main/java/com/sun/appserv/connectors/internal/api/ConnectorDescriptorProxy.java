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

package com.sun.appserv.connectors.internal.api;

import org.glassfish.api.naming.NamingObjectProxy;
import org.jvnet.hk2.annotations.Service;

import org.glassfish.hk2.api.PerLookup;

import javax.inject.Inject;
import javax.inject.Provider;
import javax.naming.Context;
import javax.naming.NamingException;

import com.sun.enterprise.deployment.ConnectorDescriptor;
import com.sun.appserv.connectors.internal.api.ConnectorRuntime;
import com.sun.appserv.connectors.internal.api.ConnectorRuntimeException;

@Service
@PerLookup

public class ConnectorDescriptorProxy implements NamingObjectProxy.InitializationNamingObjectProxy{
    @Inject
    private Provider<ConnectorRuntime> connectorRuntimeProvider;

    private ConnectorDescriptor desc;
    private String rarName;
    private String jndiName;

    public void setRarName(String rarName){
        this.rarName = rarName;
    }

    public String getRarName(){
        return rarName;
    }

    public void setJndiName(String jndiName){
        this.jndiName = jndiName;
    }

    public String getJndiName(){
        return jndiName;
    }

    protected ConnectorRuntime getConnectorRuntime() {
        return connectorRuntimeProvider.get();
    }

    public synchronized Object create(Context ic) throws NamingException {
        //this is a per-lookup object and once we have the descriptor,
        //we remove the proxy and bind the descriptor with same jndi-name
        //hence block synchronization is fine as it blocks only callers
        //of this particular connector descriptor and also only for first time (initialization)
        if(desc == null) {
            try {
                desc = getConnectorRuntime().getConnectorDescriptor(rarName);
                ic.rebind(jndiName, desc);
            } catch (ConnectorRuntimeException e) {
                NamingException ne = new NamingException(e.getMessage());
                ne.initCause(e);
                throw ne;
            }
        }
        return desc;
    }
}
