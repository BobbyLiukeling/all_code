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

package org.glassfish.admin.amxtest.config;

import com.sun.appserv.management.config.ConfigConfig;
import com.sun.appserv.management.config.DiagnosticServiceConfig;
import org.glassfish.admin.amxtest.AMXTestBase;

import java.util.logging.Level;

/**
 */
public final class DiagnosticServiceConfigTest
        extends AMXTestBase {
    public DiagnosticServiceConfigTest() {
    }

    public void
    testCreateRemove() {
        final ConfigConfig config = getConfigConfig();

        // set defaults
        String computeChecksum = "" + true;
        String captureInstallLog = "" + true;
        String captureSystemInfo = "" + true;
        String captureHADBInfo = "" + true;
        String captureAppDD = "" + true;
        String verifyConfig = "" + true;
        String minLogLevel = Level.INFO.toString();
        String maxLongEntries = "10000";

        DiagnosticServiceConfig ds = config.getDiagnosticServiceConfig();
        if (ds != null) {
            // remember current settings
            computeChecksum = ds.getComputeChecksum();
            captureInstallLog = ds.getCaptureInstallLog();
            captureSystemInfo = ds.getCaptureSystemInfo();
            captureHADBInfo = ds.getCaptureHADBInfo();
            captureAppDD = ds.getCaptureAppDD();
            verifyConfig = ds.getVerifyConfig();
            minLogLevel = ds.getMinLogLevel();
            maxLongEntries = ds.getMaxLogEntries();

            config.removeDiagnosticServiceConfig();
            ds = null;
        }

        ds = config.createDiagnosticServiceConfig();
        config.removeDiagnosticServiceConfig();
        ds = null;

        // re-create it so one stays around
        ds = config.createDiagnosticServiceConfig();
        ds.setComputeChecksum(computeChecksum);
        ds.setCaptureInstallLog(captureInstallLog);
        ds.setCaptureSystemInfo(captureSystemInfo);
        ds.setCaptureHADBInfo(captureHADBInfo);
        ds.setCaptureAppDD(captureAppDD);
        ds.setVerifyConfig(verifyConfig);
        ds.setMinLogLevel(minLogLevel);
        ds.setMaxLogEntries(maxLongEntries);
    }

}


