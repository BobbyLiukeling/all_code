/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2006-2018 Oracle and/or its affiliates. All rights reserved.
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

package test.admin;

import org.testng.Assert;
import org.testng.annotations.Test;

/** Supposed to have JDBC connection pool and resource tests.
 *
 * @author &#2325;&#2375;&#2342;&#2366;&#2352 (km@dev.java.net)
 * @since GlassFish v3 Prelude
 */
@Test(groups = {"adminconsole"}, description = "Admin Console tests")
public class AdminConsoleTests extends BaseAdminConsoleTest {

    /**
     * Request /commonTask.jsf and verify that the common task page was rendered.
     * @throws java.lang.Exception
     */
    @Test
    public void testCommonTasks() throws Exception {
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "commonTask.jsf?bare=true",
                "id=\"form:commonTasksSection\""),
                "The Common Task page does not appear to have been rendered.");
    }

    /**
     * Request /applications/applications.jsf and verify that the applications page was rendered.
     * @throws java.lang.Exception
     */
    @Test
    public void testDeployedAppPage() throws Exception {
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "applications/applications.jsf?bare=true",
                "id=\"propertyForm:deployTable\""),
                "The Deployed Applications table does not appear to have been rendered.");
    }

    /**
     * Request /common/security/realms/realms.jsf to test that pages from plugin module can be rendered.
     * @throws java.lang.Exception
     */
    @Test
    public void testRealmsList() throws Exception {
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "common/security/realms/realms.jsf?bare=true",
                "id=\"propertyForm:realmsTable\""),
                "The Security realms table does not appear to have been rendered.");
    }

    /*
     * Disabling for now, we have a new help system in place -- the old help system has been removed.
    @Test
    public void testHelpPage() throws Exception {
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "com_sun_webui_jsf/help/helpwindow.jsf?&windowTitle=Help+Window&helpFile=CONTEXT_HELP.html",
                "id=\"navFrame\"", "id=\"buttonNavFrame\"", "id=\"contentFrame\""));
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "com_sun_webui_jsf/help/navigator.jsf",
                "id=\"helpNavigatorForm:javaHelpTabSet\""));
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "com_sun_webui_jsf/help/buttonnav.jsf",
                "input id=\"helpButtonNavForm_hidden\""));
        Assert.assertTrue(getUrlAndTestForStrings(this.adminUrl + "html/en/help/CONTEXT_HELP.html",
                "body class=\"HlpBdy\""));
    }
    */
}
