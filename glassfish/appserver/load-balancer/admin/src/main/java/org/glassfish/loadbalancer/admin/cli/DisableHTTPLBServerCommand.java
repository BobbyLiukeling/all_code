/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2010-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.loadbalancer.admin.cli;

import com.sun.enterprise.config.serverbeans.Cluster;
import com.sun.enterprise.config.serverbeans.Server;
import java.util.logging.Logger;
import java.util.List;

import org.glassfish.hk2.api.PerLookup;
import org.glassfish.internal.api.Target;

import org.jvnet.hk2.annotations.Service;
import org.jvnet.hk2.component.*;
import org.jvnet.hk2.config.*;
import org.glassfish.api.Param;
import org.glassfish.api.ActionReport;
import com.sun.enterprise.util.LocalStringManagerImpl;
import com.sun.enterprise.config.serverbeans.ServerRef;
import org.glassfish.loadbalancer.config.LbConfigs;
import org.glassfish.loadbalancer.config.LbConfig;

import org.glassfish.api.admin.*;
import org.glassfish.config.support.TargetType;
import org.glassfish.config.support.CommandTarget;

import javax.inject.Inject;

/**
 * This is a remote command that enables lb-enabled attribute of
 * server-ref
 * @author Yamini K B
 */
@Service(name = "disable-http-lb-server")
@PerLookup
@TargetType(value={CommandTarget.STANDALONE_INSTANCE, CommandTarget.CLUSTER, CommandTarget.CLUSTERED_INSTANCE})
@org.glassfish.api.admin.ExecuteOn(RuntimeType.DAS)
@RestEndpoints({
    @RestEndpoint(configBean=Cluster.class,
        opType=RestEndpoint.OpType.POST, 
        path="disable-http-lb-server", 
        description="disable-http-lb-server",
        params={
            @RestParam(name="id", value="$parent")
        }),
    @RestEndpoint(configBean=Server.class,
        opType=RestEndpoint.OpType.POST, 
        path="disable-http-lb-server", 
        description="disable-http-lb-server",
        params={
            @RestParam(name="id", value="$parent")
        })
})
public final class DisableHTTPLBServerCommand extends LBCommandsBase
                                              implements AdminCommand {

    @Param(primary=true)
    String target;

    @Param(optional=true, defaultValue="30")
    String timeout;

    @Inject
    Target tgt;

    final private static LocalStringManagerImpl localStrings =
        new LocalStringManagerImpl(DisableHTTPLBServerCommand.class);

    @Override
    public void execute(AdminCommandContext context) {
        ActionReport report = context.getActionReport();
        
        Logger logger = context.getLogger();

        report.setActionExitCode(ActionReport.ExitCode.SUCCESS);

        LbConfigs lbconfigs = domain.getExtensionByType(LbConfigs.class);
        if (lbconfigs == null) {
            String msg = localStrings.getLocalString("NoLbConfigsElement",
                    "Empty lb-configs");
            report.setActionExitCode(ActionReport.ExitCode.FAILURE);
            report.setMessage(msg);
            return;
        }

        int t = Integer.parseInt(timeout);
        if (t < 0) {
            String msg = localStrings.getLocalString("InvalidTimeout", "Invalid timeout {0}",
                    timeout);
            report.setActionExitCode(ActionReport.ExitCode.FAILURE);
            report.setMessage(msg);
            return;
        }

        if (tgt.isCluster(target)) {
            //disable all servers in cluster
            updateLBForCluster(report, target, "false", timeout);
        }  else {
            boolean foundTarget = false;
            List<LbConfig> lbConfigs = lbconfigs.getLbConfig();
            for (LbConfig lc:lbConfigs) {
                ServerRef  sRef = lc.getRefByRef(ServerRef.class, target);
                if (sRef == null) {
                    //log a warning and continue search
                    logger.warning(localStrings.getLocalString("InvalidInstance",
                            "Server {0} does not exist in {1}", target, lc.getName()));
                } else {
                    int curTout = Integer.parseInt(sRef.getDisableTimeoutInMinutes());

                    boolean enabled = sRef.getLbEnabled().equals("true");
                    if ((enabled == false) && (curTout == t)) {
                        String msg = localStrings.getLocalString("ServerDisabled",
                                "Server [{0}] is already disabled.", sRef.getRef());
                        report.setMessage(msg);
                        return;
                    }
                    try {
                        updateLbEnabled(sRef, "false", timeout);
                    } catch (TransactionFailure ex) {
                        String msg = localStrings.getLocalString("FailedToUpdateAttr",
                            "Failed to update lb-enabled attribute for {0}", target);
                        report.setMessage(msg);
                        report.setActionExitCode(ActionReport.ExitCode.FAILURE);
                        report.setFailureCause(ex);
                        return;
                    }
                    foundTarget = true;
                }
            }
            // did not find server target
            if (!foundTarget) {
                ServerRef sRef = getServerRefFromCluster(report, target);

                if (sRef == null) {
                    String msg = localStrings.getLocalString("InvalidServer",
                            "Server {0} does not exist", target);
                    report.setActionExitCode(ActionReport.ExitCode.FAILURE);
                    report.setMessage(msg);
                    return;
                } else {
                    int curTout = Integer.parseInt(sRef.getDisableTimeoutInMinutes());

                    boolean enabled = sRef.getLbEnabled().equals("true");
                    if ((enabled == false) && (curTout == t)) {
                        String msg = localStrings.getLocalString("ServerDisabled",
                                "Server [{0}] is already disabled.", sRef.getRef());
                        report.setActionExitCode(ActionReport.ExitCode.FAILURE);
                        report.setMessage(msg);
                        return;
                    }
                    try {
                        updateLbEnabled(sRef, "false", timeout);
                    } catch (TransactionFailure ex) {
                        String msg = localStrings.getLocalString("FailedToUpdateAttr",
                            "Failed to update lb-enabled attribute for {0}", target);
                        report.setMessage(msg);
                        report.setActionExitCode(ActionReport.ExitCode.FAILURE);
                        report.setFailureCause(ex);
                        return;
                    }
                }
            }
        }
    }
}
