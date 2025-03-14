/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2013-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.concurrent.admin;

import com.sun.enterprise.config.serverbeans.*;
import com.sun.enterprise.util.LocalStringManagerImpl;
import com.sun.enterprise.util.SystemPropertyConstants;
import org.glassfish.api.ActionReport;
import org.glassfish.api.I18n;
import org.glassfish.api.Param;
import org.glassfish.api.admin.*;
import org.glassfish.api.naming.DefaultResourceProxy;
import org.glassfish.config.support.CommandTarget;
import org.glassfish.config.support.TargetType;
import org.glassfish.hk2.api.PerLookup;
import org.glassfish.hk2.api.ServiceLocator;
import org.glassfish.concurrent.config.ManagedThreadFactory;
import org.glassfish.resourcebase.resources.util.BindableResourcesHelper;
import org.jvnet.hk2.annotations.Service;

import javax.inject.Inject;
import java.util.*;
import org.glassfish.concurrent.runtime.deployer.DefaultManagedThreadFactory;

/**
 * List Managed Thread Factory Resources command
 * 
 */
@TargetType(value={CommandTarget.DAS,CommandTarget.DOMAIN, CommandTarget.CLUSTER, CommandTarget.STANDALONE_INSTANCE, CommandTarget.CLUSTERED_INSTANCE })
@ExecuteOn(value={RuntimeType.DAS})
@Service(name="list-managed-thread-factories")
@PerLookup
@CommandLock(CommandLock.LockType.NONE)
@I18n("list.managed.thread.factories")
@RestEndpoints({
    @RestEndpoint(configBean=Resources.class,
        opType=RestEndpoint.OpType.GET, 
        path="list-managed-thread-factories", 
        description="List Managed Thread Factories")
})
public class ListManagedThreadFactories implements AdminCommand {
    
    final private static LocalStringManagerImpl localStrings = new LocalStringManagerImpl(ListManagedThreadFactories.class);    

    @Param(primary = true, optional = true, defaultValue = SystemPropertyConstants.DAS_SERVER_NAME)
    private String target ;
    
    @Inject
    private Domain domain;

    @Inject
    private BindableResourcesHelper bindableResourcesHelper;

    @Inject
    private ServiceLocator habitat;

    @Inject
    private DefaultManagedThreadFactory defaultFactory; // make sure default has been created

    /**
     * Executes the command with the command parameters passed as Properties
     * where the keys are the parameter names and the values the parameter values
     *
     * @param context information
     */
    public void execute(AdminCommandContext context) {

        final ActionReport report = context.getActionReport();

        try {
            Collection<ManagedThreadFactory> managedThreadFactories = domain.getResources().getResources(ManagedThreadFactory.class);
            List<Map<String,String>> resourcesList = new ArrayList<Map<String, String>>();
            List<DefaultResourceProxy> drps = habitat.getAllServices(DefaultResourceProxy.class);

            for (ManagedThreadFactory managedThreadFactory : managedThreadFactories) {
                String jndiName = managedThreadFactory.getJndiName();
                if(bindableResourcesHelper.resourceExists(jndiName, target)){
                    ActionReport.MessagePart part = report.getTopMessagePart().addChild();
                    part.setMessage(jndiName);
                    Map<String,String> resourceNameMap = new HashMap<String,String>();
                    String logicalName = DefaultResourceProxy.Util.getLogicalName(drps, jndiName);
                    if (logicalName != null) {
                        resourceNameMap.put("logical-jndi-name", logicalName);
                    }
                    resourceNameMap.put("name", jndiName);
                    resourcesList.add(resourceNameMap);
                }
            }

            Properties extraProperties = new Properties();
            extraProperties.put("managedThreadFactories", resourcesList);
            report.setExtraProperties(extraProperties);
        } catch (Exception e) {
            report.setMessage(localStrings.getLocalString("list.managed.thread.factory.failed", "List managed thread factories failed"));
            report.setActionExitCode(ActionReport.ExitCode.FAILURE);
            report.setFailureCause(e);
            return;
        }
        report.setActionExitCode(ActionReport.ExitCode.SUCCESS);
    }
}
