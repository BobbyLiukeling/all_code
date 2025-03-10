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

package com.sun.enterprise.deployment;

import org.glassfish.api.deployment.archive.ArchiveType;
import org.glassfish.deployment.common.RootDeploymentDescriptor;

import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;

/**
 * Information about the web services defined in a single module.
 *
 * @author Kenneth Saks
 * @author Jerome Dochez
 */

public class WebServicesDescriptor extends RootDeploymentDescriptor {

    // Module in which these web services are defined.
    private BundleDescriptor bundleDesc;

    private Collection<WebService> webServices;
    /** 
     * Default constructor. 
     */
    public WebServicesDescriptor() {
        webServices = new HashSet<WebService>();
    }

    /**
     * @return the default version of the deployment descriptor
     * loaded by this descriptor
     */
    public String getDefaultSpecVersion() {
        return "1.3";//TODO fix this WebServicesDescriptorNode.SPEC_VERSION;
    }

    public void setBundleDescriptor(BundleDescriptor module) {
        bundleDesc = module;
    }

    public BundleDescriptor getBundleDescriptor() {
        return bundleDesc;
    }

    public boolean hasWebServices() {
        return !(webServices.isEmpty());
    }

    public boolean isEmpty() {
        return webServices.isEmpty();
    }

    public WebService getWebServiceByName(String webServiceName) {
        for (WebService webService : webServices) {
            if( webService.getName().equals(webServiceName) ) {
                return webService;
            }
        }
        return null;
    }

    public void addWebService(WebService descriptor) {
        descriptor.setWebServicesDescriptor(this);
        webServices.add(descriptor);

    }

    public void removeWebService(WebService descriptor) {
        descriptor.setWebServicesDescriptor(null);
        webServices.remove(descriptor);

    }

    public Collection<WebService> getWebServices() {
        return new HashSet<WebService>(webServices);
    }

    /**
     * Endpoint has a unique name within all the endpoints in the module.
     * @return WebServiceEndpoint or null if not found
     */
    public WebServiceEndpoint getEndpointByName(String endpointName) {
        for(Iterator iter = getEndpoints().iterator(); iter.hasNext();) {
            WebServiceEndpoint next = (WebServiceEndpoint) iter.next();
            if( next.getEndpointName().equals(endpointName) ) {
                return next;
            }
        }
        return null;
    }

    public boolean hasEndpointsImplementedBy(EjbDescriptor ejb) {
        return !(getEndpointsImplementedBy(ejb).isEmpty());
    }

    public Collection<WebServiceEndpoint> getEndpointsImplementedBy(EjbDescriptor ejb) {
        Collection<WebServiceEndpoint> endpoints = new HashSet();
        if( ejb instanceof EjbSessionDescriptor ) {
            for(WebServiceEndpoint next : getEndpoints()) {
                if( next.implementedByEjbComponent(ejb) ) {
                    endpoints.add(next);
                }
            }
        }
        return endpoints;
    }

    public boolean hasEndpointsImplementedBy(WebComponentDescriptor desc) {
        return !(getEndpointsImplementedBy(desc).isEmpty());
    }

    public Collection<WebServiceEndpoint> getEndpointsImplementedBy(WebComponentDescriptor desc) {
        Collection<WebServiceEndpoint> endpoints = new HashSet();
        for(WebServiceEndpoint next : getEndpoints()) {
            if( next.implementedByWebComponent(desc) ) {
                endpoints.add(next);
            }
        }
        return endpoints;
    }

    public Collection<WebServiceEndpoint> getEndpoints() {
        Collection allEndpoints = new HashSet();
        for(WebService webService : webServices) {
            allEndpoints.addAll( webService.getEndpoints() );
        }
        return allEndpoints;
    }
    
    public ArchiveType getModuleType() {
        if (bundleDesc!=null) {
          return bundleDesc.getModuleType();  
        } 
        return null; 
    }

    
    //
    // Dummy RootDeploymentDescriptor implementations for methods that
    // do not apply to WebServicesDescriptor.
    //
    public String getModuleID() { return ""; } 
    public ClassLoader getClassLoader() { return null; }
    public boolean isApplication() {return false; }

    /**
     * Returns a formatted String of the attributes of this object.
     */
    public void print(StringBuffer toStringBuffer) {
	super.print(toStringBuffer);
        if (hasWebServices()) {
            for (Iterator itr = getWebServices().iterator();itr.hasNext();) {
                WebService aWebService = (WebService) itr.next();
                toStringBuffer.append("\n Web Service : ");
                aWebService.print(toStringBuffer);
            }
        }
    }
    
}    
