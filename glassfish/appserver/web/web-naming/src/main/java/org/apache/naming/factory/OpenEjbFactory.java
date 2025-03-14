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

package org.apache.naming.factory;

import org.apache.naming.EjbRef;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.Name;
import javax.naming.Reference;
import javax.naming.RefAddr;
import javax.naming.spi.ObjectFactory;
import java.util.Hashtable;
import java.util.Properties;

/**
 * Object factory for EJBs.
 * 
 * @author Jacek Laskowski
 * @author Remy Maucherat
 * @version $Revision: 1.2 $ $Date: 2005/12/08 01:29:07 $
 */
public class OpenEjbFactory implements ObjectFactory {


    // -------------------------------------------------------------- Constants


    protected static final String DEFAULT_OPENEJB_FACTORY = 
        "org.openejb.client.LocalInitialContextFactory";


    // -------------------------------------------------- ObjectFactory Methods


    /**
     * Crete a new EJB instance using OpenEJB.
     * 
     * @param obj The reference object describing the DataSource
     */
    public Object getObjectInstance(Object obj, Name name, Context nameCtx,
                                    Hashtable<?,?> environment)
        throws Exception {

        Object beanObj = null;

        if (obj instanceof EjbRef) {

            Reference ref = (Reference) obj;

            String factory = DEFAULT_OPENEJB_FACTORY;
            RefAddr factoryRefAddr = ref.get("openejb.factory");
            if (factoryRefAddr != null) {
                // Retrieving the OpenEJB factory
                factory = factoryRefAddr.getContent().toString();
            }

            Properties env = new Properties();
            env.put(Context.INITIAL_CONTEXT_FACTORY, factory);

            RefAddr linkRefAddr = ref.get("openejb.link");
            if (linkRefAddr != null) {
                String ejbLink = linkRefAddr.getContent().toString();
                beanObj = (new InitialContext(env)).lookup(ejbLink);
            }

        }

        return beanObj;

    }


}
