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

package com.sun.enterprise.config.serverbeans;

import org.glassfish.api.I18n;
import org.glassfish.config.support.*;
import org.jvnet.hk2.config.Configured;
import org.jvnet.hk2.config.DuckTyped;
import org.jvnet.hk2.config.Element;
import org.jvnet.hk2.config.ConfigBeanProxy;

import java.util.List;


/**
 * Clusters configuration. Maintain a list of {@link Cluster}
 * active configurations.
 */
@Configured
public interface Clusters extends ConfigBeanProxy {

     /**
      * Return the list of clusters currently configured
      *
      * @return list of {@link Cluster }
      */
    @Element
    @Create(value="create-cluster", decorator=Cluster.Decorator.class, i18n=@I18n("create.cluster.command"))
    @Delete(value="delete-cluster", resolver= TypeAndNameResolver.class, decorator=Cluster.DeleteDecorator.class
        , i18n=@I18n("delete.cluster.command"))


    public List<Cluster> getCluster();

    /**
     * Return the cluster with the given name, or null if no such cluster exists.
     *
     * @param   name    the name of the cluster
     * @return          the Cluster object, or null if no such server
     */
    @DuckTyped
    public Cluster getCluster(String name);

    class Duck {
        public static Cluster getCluster(Clusters clusters, String name) {
            for (Cluster cluster : clusters.getCluster()) {
                if (cluster.getName().equals(name)) {
                    return cluster;
                }
            }
            return null;
        }
    }
}
