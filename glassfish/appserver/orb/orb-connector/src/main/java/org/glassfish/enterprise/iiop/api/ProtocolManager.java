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

package org.glassfish.enterprise.iiop.api;

import java.rmi.*;

import org.glassfish.enterprise.iiop.spi.EjbContainerFacade;
import org.glassfish.enterprise.iiop.spi.EjbService;

import com.sun.enterprise.deployment.EjbDescriptor;

import org.jvnet.hk2.annotations.Contract;
import org.omg.CORBA.ORB;
import java.rmi.Remote;


/**
 * The ProtocolManager interface specifies the functionality of the
 * remote communication layer, which provides the support for
 * distribution described in Chapter 13 of the EJB spec.
 * Possible implementations of the ProtocolManager include RMI/IIOP,
 * RMI/JRMP, RMI/DCOM, RMI/HTTP ....
 * @author Vivek Nagar
 */

@Contract
public interface ProtocolManager {

    void initialize(ORB o);


    public void initializePOAs() throws Exception;


    public void initializeNaming() throws Exception;

    public void initializeRemoteNaming(Remote remoteNamingProvider) throws Exception;

    /**
     * Return a factory that can be used to create/destroy remote
     * references for a particular EJB type.
     */
    RemoteReferenceFactory getRemoteReferenceFactory(EjbContainerFacade container,
                                                     boolean remoteHomeView,
                                                     String id);


    /**
     * Return true if the two object references refer to the same
     * remote object.
     */
    boolean isIdentical(Remote obj1, Remote obj2);

    /**
     * Check that all Remote interfaces implemented by target object
     * conform to the rules for valid RMI-IIOP interfaces.  Throws
     * runtime exception if validation fails.  
     */
    void validateTargetObjectInterfaces(Remote targetObj);

    /**
     * Map the RMI exception to a protocol-specific (e.g. CORBA) exception
     */
    Throwable mapException(Throwable exception);

    /**
     * True if object is a corba stub
     */
    boolean isStub(Object obj);

    boolean isLocal(Object obj);

    byte[] getObjectID(org.omg.CORBA.Object obj);

    /**
     * Connect the RMI object to the protocol.
     */
    void connectObject(Remote remoteObj) throws RemoteException;


    EjbDescriptor getEjbDescriptor(byte[] ejbKey);

}
    

