/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2012-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.tests.progress;

import javax.inject.Inject;
import org.glassfish.api.I18n;
import org.glassfish.api.admin.AdminCommand;
import org.glassfish.api.admin.AdminCommandContext;
import org.glassfish.api.admin.CommandLock;
import org.glassfish.api.admin.CommandRunner;
import org.glassfish.api.admin.Progress;
import org.glassfish.api.admin.ProgressStatus;
import org.glassfish.hk2.api.PerLookup;
import org.jvnet.hk2.annotations.Service;

/** Example of other command execution with progress status support.
 *
 * @author mmares
 */
@Service(name = "progress-exec-other")
@PerLookup
@CommandLock(CommandLock.LockType.NONE)
@I18n("progress")
@Progress(totalStepCount=40)
public class ProgressExecOtherCommand implements AdminCommand {
    
    @Inject
    CommandRunner commandRunner;
    
    @Override
    public void execute(AdminCommandContext context) {
        ProgressStatus ps = context.getProgressStatus();
        //Do some before logic
        ps.progress("Preparing");
        for (int i = 0; i < 10; i++) {
            doSomeLogic();
            ps.progress(1);
        }
        
        //Execute other command
        final CommandRunner.CommandInvocation commandInvocation = 
                commandRunner.getCommandInvocation("progress-simple", 
                    context.getActionReport().addSubActionsReport(), context.getSubject());
        commandInvocation
                //.subject(context.getSubject())
                .progressStatusChild(ps.createChild("subcommand", 20)) //Number 20 is little bit tricky. Please see javadoc of ProgressStatus
                .execute();
        
        //Do some after logic
        ps.progress("Finishing outer command");
        for (int i = 0; i < 10; i++) {
            doSomeLogic();
            ps.progress(1);
        }
        ps.complete("Finished outer command");
    }
    
    private void doSomeLogic() {
        try {
            Thread.sleep(250L);
        } catch (Exception ex) {
        }
    }
    
}
