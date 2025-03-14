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
 * https://glassfish.dev.java.net/public/CDDL+GPL_1_1.html
 * or packager/legal/LICENSE.txt.  See the License for the specific
 * language governing permissions and limitations under the License.
 *
 * When distributing the software, include this License Header Notice in each
 * file and include the License file at packager/legal/LICENSE.txt.
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

package org.glassfish.admingui.devtests;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class HttpServiceTest extends BaseSeleniumTestClass {
    private static final String TRIGGER_HTTP_SERVICE = "i18n_web.httpService.pageTitleHelp";
    
    @Test
    public void testHttpService() {
        final String interval = Integer.toString(generateRandomNumber(2880));
        final String maxFiles = Integer.toString(generateRandomNumber(50));
        final String bufferSize = Integer.toString(generateRandomNumber(65536));
        final String logWriteInterval = Integer.toString(generateRandomNumber(600));

        clickAndWait("treeForm:tree:configurations:server-config:httpService:httpService_link", TRIGGER_HTTP_SERVICE);
        markCheckbox("form1:propertySheet:http:acLog:ssoEnabled");
        markCheckbox("form1:propertySheet:accessLog:acLog:accessLoggingEnabled");
        setFieldValue("form1:propertySheet:accessLog:intervalProp:Interval", interval);
        setFieldValue("form1:propertySheet:accessLog:MaxHistoryFiles:MaxHistoryFiles", maxFiles);
        setFieldValue("form1:propertySheet:accessLog:accessLogBufferSize:accessLogBufferSize", bufferSize);
        setFieldValue("form1:propertySheet:accessLog:accessLogWriteInterval:accessLogWriteInterval", logWriteInterval);
        int count = addTableRow("form1:basicTable", "form1:basicTable:topActionsGroup1:addSharedTableButton");
        setFieldValue("form1:basicTable:rowGroup1:0:col2:col1St", "property"+generateRandomString());
        setFieldValue("form1:basicTable:rowGroup1:0:col3:col1St", "value");
        setFieldValue("form1:basicTable:rowGroup1:0:col4:col1St", "description");
        clickAndWait("form1:propertyContentPage:topButtons:saveButton", TRIGGER_NEW_VALUES_SAVED);
        reset(); 
        clickAndWait("treeForm:tree:configurations:server-config:httpService:httpService_link", TRIGGER_HTTP_SERVICE);
        assertEquals(true, isChecked("form1:propertySheet:http:acLog:ssoEnabled"));
        assertEquals(interval, getFieldValue("form1:propertySheet:accessLog:intervalProp:Interval"));
        assertEquals(maxFiles, getFieldValue("form1:propertySheet:accessLog:MaxHistoryFiles:MaxHistoryFiles"));
        assertEquals(bufferSize, getFieldValue("form1:propertySheet:accessLog:accessLogBufferSize:accessLogBufferSize"));
        assertEquals(logWriteInterval, getFieldValue("form1:propertySheet:accessLog:accessLogWriteInterval:accessLogWriteInterval"));
        assertTableRowCount("form1:basicTable", count);
    }
}
