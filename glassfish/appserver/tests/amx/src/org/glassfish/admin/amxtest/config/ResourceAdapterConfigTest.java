/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
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

/*
* $Header: /cvs/glassfish/admin/mbeanapi-impl/tests/org.glassfish.admin.amxtest/config/ResourceAdapterConfigTest.java,v 1.5 2007/05/05 05:23:55 tcfujii Exp $
* $Revision: 1.5 $
* $Date: 2007/05/05 05:23:55 $
*/
package org.glassfish.admin.amxtest.config;


import com.sun.appserv.management.config.DomainConfig;
import com.sun.appserv.management.config.ResourceAdapterConfig;
import org.glassfish.admin.amxtest.AMXTestBase;


/**
 */
public final class ResourceAdapterConfigTest
        extends AMXTestBase {
    public ResourceAdapterConfigTest() {
        if (checkNotOffline("ensureDefaultInstance")) {
            ensureDefaultInstance(getDomainConfig());
        }
    }

    public static String
    getDefaultInstanceName() {
        return getDefaultInstanceName("ResourceAdapterConfig");
    }

    public static ResourceAdapterConfig
    ensureDefaultInstance(final DomainConfig domainConfig) {
        ResourceAdapterConfig result =
                domainConfig.getResourcesConfig().getResourceAdapterConfigMap().get(getDefaultInstanceName());

        if (result == null) {
            result = createInstance(domainConfig, getDefaultInstanceName());
        }

        return result;
    }

    public static ResourceAdapterConfig
    createInstance(
            final DomainConfig domainConfig,
            final String name) {
        final ResourceAdapterConfig rac =
                domainConfig.getResourcesConfig().createResourceAdapterConfig(name, null);

        return rac;
    }

    private void
    testGetters(final ResourceAdapterConfig resAdapterConfig) {
        resAdapterConfig.getResourceAdapterName();
        resAdapterConfig.getThreadPoolIDs();
    }

    public void
    testCreateRemove() {
        if (checkNotOffline("testCreateSSL")) {
            final ResourceAdapterConfig resAdapterConfig =
                    createInstance(getDomainConfig(),
                                   "ResourceAdapterConfigTest.testCreateRemove");

            try {
                testGetters(resAdapterConfig);
            }
            finally {
                getDomainConfig().getResourcesConfig().removeResourceAdapterConfig(resAdapterConfig.getName());
            }
        }
    }

}



























