<!--

    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

    Copyright (c) 1997-2017 Oracle and/or its affiliates. All rights reserved.

    The contents of this file are subject to the terms of either the GNU
    General Public License Version 2 only ("GPL") or the Common Development
    and Distribution License("CDDL") (collectively, the "License").  You
    may not use this file except in compliance with the License.  You can
    obtain a copy of the License at
    https://oss.oracle.com/licenses/CDDL+GPL-1.1
    or LICENSE.txt.  See the License for the specific
    language governing permissions and limitations under the License.

    When distributing the software, include this License Header Notice in each
    file and include the License file at LICENSE.txt.

    GPL Classpath Exception:
    Oracle designates this particular file as subject to the "Classpath"
    exception as provided by Oracle in the GPL Version 2 section of the License
    file that accompanied this code.

    Modifications:
    If applicable, add the following below the License Header, with the fields
    enclosed by brackets [] replaced by your own identifying information:
    "Portions Copyright [year] [name of copyright owner]"

    Contributor(s):
    If you wish your version of this file to be governed by only the CDDL or
    only the GPL Version 2, indicate your decision by adding "[Contributor]
    elects to include this software in this distribution under the [CDDL or GPL
    Version 2] license."  If you don't indicate a single choice of license, a
    recipient has the option to distribute your version of this file under
    either the CDDL, the GPL Version 2 or to extend the choice of license to
    its licensees as provided above.  However, if you add GPL Version 2 code
    and therefore, elected the GPL Version 2 license, then the option applies
    only if the new code is made subject to such option by the copyright
    holder.

-->

<!-- applications/descriptorsTable.inc -->

<!-- Descriptos Table .... -->
               
<sun:table id="basicTable" style="padding: 10pt" deselectMultipleButton="$boolean{false}" selectMultipleButton="$boolean{false}" title="$resource{i18n.deploy.descriptors}">

    <sun:tableRowGroup id="rowGroup1" data={"$attribute{descriptors}"} sourceVar="td">      
        <sun:tableColumn headerText="$resource{i18n.deploy.ApplicationName}" rowHeader="$boolean{false}" id="col1">
            <staticText id="name" value="#{pageSession.appName}" />
        </sun:tableColumn>
        <sun:tableColumn  headerText="$resource{i18n.deploy.subCompName}" rowHeader="$boolean{false}" id="col2">
            <staticText id="name" value="#{td.value.moduleName}" />
        </sun:tableColumn>
        <sun:tableColumn headerText="$resource{i18n.deploy.descriptorFileName}" rowHeader="$boolean{false}" id="col3">
            <sun:hyperlink id="link" text="#{td.value.ddPath}" >
                <!command
                    //setSessionAttribute(key="descriptorForDisplay" value="#{td.value.ddContent}")
                    urlencode(value="#{td.value.moduleName}" encoding="UTF-8" result="#{pageSession.encodedModName}");
                    urlencode(value="#{td.value.ddPath}" encoding="UTF-8" result="#{pageSession.encodedDdPath}");
                    gf.redirect(page="#{request.contextPath}/common/applications/viewDD.jsf?appName=#{pageSession.encodedAppName}&moduleName=#{pageSession.encodedModName}&ddPath=#{pageSession.encodedDdPath}");
                />
            </sun:hyperlink>
        </sun:tableColumn>
    </sun:tableRowGroup>
</sun:table>    
