/*
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.naming;

import java.util.Hashtable;
import javax.naming.Reference;
import javax.naming.Context;
import javax.naming.StringRefAddr;

/**
 * Represents a reference address to a resource.
 *
 * @author Remy Maucherat
 * @version $Revision: 1.2 $ $Date: 2005/12/08 01:29:05 $
 */

public class ResourceLinkRef
    extends Reference {


    // -------------------------------------------------------------- Constants


    /**
     * Default factory for this reference.
     */
    public static final String DEFAULT_FACTORY = 
        org.apache.naming.factory.Constants.DEFAULT_RESOURCE_LINK_FACTORY;


    /**
     * Description address type.
     */
    public static final String GLOBALNAME = "globalName";


    // ----------------------------------------------------------- Constructors


    /**
     * ResourceLink Reference.
     * 
     * @param resourceClass Resource class
     * @param globalName Global name
     */
    public ResourceLinkRef(String resourceClass, String globalName) {
        this(resourceClass, globalName, null, null);
    }


    /**
     * ResourceLink Reference.
     * 
     * @param resourceClass Resource class
     * @param globalName Global name
     */
    public ResourceLinkRef(String resourceClass, String globalName, 
                           String factory, String factoryLocation) {
        super(resourceClass, factory, factoryLocation);
        StringRefAddr refAddr = null;
        if (globalName != null) {
            refAddr = new StringRefAddr(GLOBALNAME, globalName);
            add(refAddr);
        }
    }


    // ----------------------------------------------------- Instance Variables


    // ------------------------------------------------------ Reference Methods


    /**
     * Retrieves the class name of the factory of the object to which this 
     * reference refers.
     */
    public String getFactoryClassName() {
        String factory = super.getFactoryClassName();
        if (factory != null) {
            return factory;
        } else {
            factory = System.getProperty(Context.OBJECT_FACTORIES);
            if (factory != null) {
                return null;
            } else {
                return DEFAULT_FACTORY;
            }
        }
    }


    // ------------------------------------------------------------- Properties


}
