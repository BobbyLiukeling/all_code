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

package org.glassfish.resources.admin.cli;

import com.sun.enterprise.config.serverbeans.Domain;
import com.sun.enterprise.config.serverbeans.Resources;
import com.sun.enterprise.util.LocalStringManagerImpl;
import com.sun.enterprise.util.SystemPropertyConstants;
import org.glassfish.api.ActionReport;
import org.glassfish.api.I18n;
import org.glassfish.api.Param;
import org.glassfish.api.admin.*;
import org.glassfish.config.support.CommandTarget;
import org.glassfish.config.support.TargetType;
import org.glassfish.hk2.api.PerLookup;
import org.glassfish.resourcebase.resources.api.ResourceStatus;
import org.jvnet.hk2.annotations.Service;

import javax.inject.Inject;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Create add-resources Command
 * 
 */
@TargetType(value={CommandTarget.DAS,CommandTarget.DOMAIN, CommandTarget.CLUSTER, CommandTarget.STANDALONE_INSTANCE })
@ExecuteOn(RuntimeType.ALL)
@Service(name="add-resources")
@PerLookup
@I18n("add.resources")
@RestEndpoints({
    @RestEndpoint(configBean=Resources.class,
        opType=RestEndpoint.OpType.POST, 
        path="add-resources", 
        description="add-resources")
})
public class AddResources implements AdminCommand {
    
    final private static LocalStringManagerImpl localStrings = new LocalStringManagerImpl(AddResources.class);    

    @Param(optional=true)
    private String target = SystemPropertyConstants.DAS_SERVER_NAME;

    @Param(name="xml_file_name", primary=true)
    private File xmlFile;
    
    @Inject
    private Domain domain;

    @Inject
    private ResourceFactory resourceFactory;
    
    /**
     * Executes the command with the command parameters passed as Properties
     * where the keys are the paramter names and the values the parameter values
     *
     * @param context information
     */
    public void execute(AdminCommandContext context) {
        final ActionReport report = context.getActionReport();
        
        // Check if the path xmlFile exists
        if (!xmlFile.exists()) {
            report.setMessage(localStrings.getLocalString("FileNotFound", 
                "The system cannot find the path specified: {0}", xmlFile.getName()));
            report.setActionExitCode(ActionReport.ExitCode.FAILURE);
            return;
        }
        
        try {
            final ArrayList results = ResourcesManager.createResources(
                    domain.getResources(), xmlFile, target, resourceFactory);
            final Iterator resultsIter = results.iterator();
            report.getTopMessagePart().setChildrenType("Command");
            boolean isSuccess = false;
            while (resultsIter.hasNext()) {
                ResourceStatus rs = ((ResourceStatus) resultsIter.next());
                final String msgToAdd = rs.getMessage();
                if ((msgToAdd != null) && (!msgToAdd.equals(""))) {
                    final ActionReport.MessagePart part = report.getTopMessagePart().addChild();
                    part.setMessage(msgToAdd);
                }
                if (rs.getStatus() == ResourceStatus.SUCCESS || rs.isAlreadyExists())
                    isSuccess = true;
            }
            report.setActionExitCode(
                    (isSuccess)?ActionReport.ExitCode.SUCCESS:ActionReport.ExitCode.FAILURE);
            if (!isSuccess)
                report.setMessage(localStrings.getLocalString("add.resources.failed", 
                                                "add-resources <{0}> failed", xmlFile.getName()));
                
        } catch (Exception ex) {
            Logger.getLogger(AddResources.class.getName()).log(Level.SEVERE, "Something went wrong in add-resources", ex);
            report.setMessage(localStrings.getLocalString("add.resources.failed", 
                                                "add-resources <{0}> failed", xmlFile.getName()));
            report.setActionExitCode(ActionReport.ExitCode.FAILURE);
            //Need to fix, doesn't show the error from exception, though it writes in the log
            report.setFailureCause(ex);
        }
    }
}
