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

import org.glassfish.deployment.common.Descriptor;

import java.lang.reflect.Method;

/**
 * Deployment object representing the lifecycle-callback.
 *
 * @author Shing Wai Chan
 */
public class LifecycleCallbackDescriptor extends Descriptor {

    private String lifecycleCallbackClass;
    private String lifecycleCallbackMethod;
    private String defaultLifecycleCallbackClass;
    private MetadataSource metadataSource = MetadataSource.XML;

    public enum CallbackType {

        AROUND_CONSTRUCT,
        POST_CONSTRUCT,
        PRE_DESTROY,
        PRE_PASSIVATE,
        POST_ACTIVATE 

    }

    public void setLifecycleCallbackClass(String clazz) {
        lifecycleCallbackClass = clazz;
    }

    public String getLifecycleCallbackClass() {
        if (lifecycleCallbackClass == null || 
            lifecycleCallbackClass.trim().equals("")) {
            return defaultLifecycleCallbackClass;
        } else {
            return lifecycleCallbackClass;
        }
    }

    public void setDefaultLifecycleCallbackClass(String clazz) {
        defaultLifecycleCallbackClass = clazz;
    }

    public String getDefaultLifecycleCallbackClass() {
        return defaultLifecycleCallbackClass;
    }

    public void setLifecycleCallbackMethod(String method) {
        lifecycleCallbackMethod = method;
    }

    public String getLifecycleCallbackMethod() {
        return lifecycleCallbackMethod;
    }

    /**
     * Given a classloader, find the Method object corresponding to this
     * lifecycle callback.  
     *
     * @throw Exception if no method found
     */
    public Method getLifecycleCallbackMethodObject(ClassLoader loader) 
        throws Exception {

        Method method = null;

        if( getLifecycleCallbackClass() == null ) {
            throw new IllegalArgumentException("no lifecycle class defined");
        }

        // according to the ejb interceptors spec the around invoke and life cycle methods can be on the super class.
        Class clazz = loader.loadClass(getLifecycleCallbackClass());
        
        while ( method == null && ! clazz.equals( Object.class ) ) {
            for(Method next : clazz.getDeclaredMethods()) {
                if( next.getName().equals(lifecycleCallbackMethod) ) {
                    method = next;
                    break;
                }
            }
            if ( method == null ) {
                clazz = clazz.getSuperclass();
            }
        }

        if( method == null ) {
            throw new NoSuchMethodException("no method matching " + lifecycleCallbackMethod);
        }

        return method;
    }

    public MetadataSource getMetadataSource() {
        return metadataSource;
    }

    public void setMetadataSource(MetadataSource metadataSource) {
        this.metadataSource = metadataSource;
    }
}
