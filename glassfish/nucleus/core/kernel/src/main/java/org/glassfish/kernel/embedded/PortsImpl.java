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

package org.glassfish.kernel.embedded;

import org.jvnet.hk2.annotations.Service;
import javax.inject.Inject;
import javax.inject.Named;

import org.glassfish.hk2.api.ServiceLocator;
import org.glassfish.internal.embedded.Port;
import org.glassfish.internal.embedded.Ports;

import java.io.IOException;
import java.util.*;
import org.glassfish.api.admin.ServerEnvironment;

import org.glassfish.grizzly.config.dom.NetworkConfig;
import org.glassfish.grizzly.config.dom.NetworkListener;

/**
 * @author Jerome Dochez
 */
@Service
public class PortsImpl implements Ports {


    @Inject @Named(ServerEnvironment.DEFAULT_INSTANCE_NAME)
    NetworkConfig network;

    @Inject
    ServiceLocator habitat;

    final Map<Integer, Port> ports = new HashMap<Integer, Port>();

    public Port createPort(int number) throws IOException {
        return createPort(Integer.valueOf(number));
    }

    private Port createPort(Integer portNumber) throws IOException {

        for (NetworkListener nl : network.getNetworkListeners().getNetworkListener()) {
            if (nl.getPort().equals(portNumber.toString())) {
                throw new IOException("Port " + portNumber + " is already configured");
            }
        }
        for (Integer pn : ports.keySet()) {
            if (pn.equals(portNumber)) {
                throw new IOException("Port " + portNumber + " is alredy open");
            }
        }
        PortImpl port = habitat.getService(PortImpl.class);
        port.setPortNumber(portNumber);
        ports.put(portNumber, port);
        return port;    }

    public Collection<Port> getPorts() {
        return ports.values();
    }

    public void remove(Port port) {
        ports.remove(port.getPortNumber());
    }
}
