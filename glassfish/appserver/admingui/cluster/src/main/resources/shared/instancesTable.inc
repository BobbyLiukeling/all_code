<!--

    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

    Copyright (c) 2010-2017 Oracle and/or its affiliates. All rights reserved.

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

<!-- appserver/instancesTable.inc -->

<sun:table id="instancesTable" title="#{tableTitle}"
    deselectMultipleButton="$boolean{true}"
    deselectMultipleButtonOnClick="setTimeout('admingui.table.changeThreeTableButtons(\\\\\'#{pageSession.topActionGroup}\\\\\', \\\\\'#{pageSession.tableId}\\\\\');', 0)"
    selectMultipleButton="$boolean{true}"
    selectMultipleButtonOnClick="setTimeout('admingui.table.changeThreeTableButtons(\\\\\'#{pageSession.topActionGroup}\\\\\', \\\\\'#{pageSession.tableId}\\\\\');', 0)" >
     <!afterCreate
        getClientId(component="$this{component}" clientId=>$page{tableId});
    />

#include "/common/shared/listTableButtons.inc"

<sun:tableRowGroup id="rowGroup1" selected="#{td.value.selected}" data={"$attribute{listOfRows}"} sourceVar="td">
    <!afterCreate
        getClientId(component="$this{component}" clientId=>$page{tableRowGroupId});
    />

    <sun:tableColumn headerText="$resource{i18n.common.SelectHeader}" selectId="select" rowHeader="$boolean{false}" id="col0">
        <sun:checkbox id="select"
            toolTip="$resource{i18n.common.select}"
            selected="#{td.value.selected}"
            selectedValue="$boolean{true}"
            onClick="setTimeout('admingui.table.changeThreeTableButtons(\\\\\'#{pageSession.topActionGroup}\\\\\', \\\\\'#{pageSession.tableId}\\\\\'); admingui.table.initAllRows(\\\\\'#{pageSession.tableId}\\\\\');', 0);"
        />
    </sun:tableColumn>
    <sun:tableColumn headerText="$resource{i18n.common.name.header}" sort="name" rowHeader="$boolean{true}" id="col1">
        <sun:hyperlink id="link" text="#{td.value.name}" url="#{pageSession.editLink}&instanceName=#{td.value.name}" />
    </sun:tableColumn>
    <sun:tableColumn headerText="$resource{i18ncs.standalone.ColWeight}" sort="lbWeight" rowHeader="$boolean{false}" id="col2">
        <sun:textField id="weight" columns="$int{10}" maxLength="#{sessionScope.fieldLengths['maxLength.standalone.lbWeight']}" text="#{td.value.lbWeight}" />
    </sun:tableColumn>
    <sun:tableColumn headerText="$resource{i18ncs.common.ConfigurationCol}" sort="configRef" rowHeader="$boolean{false}" id="col3">
        <sun:hyperlink id="configlink" text="#{td.value.configRef}" url="/configuration/configuration.jsf?configName=#{td.value.configRef}" />
    </sun:tableColumn>
    <sun:tableColumn headerText="$resource{i18ncs.common.NodeCol}" sort="node" rowHeader="$boolean{false}" id="col5">
        <sun:hyperlink id="nodeAgentlink" text="#{td.value.nodeRef}"  url="#{request.contextPath}/cluster/node/nodeEdit.jsf?nodeName=#{td.value.nodeRef}" />
    </sun:tableColumn>
    <sun:tableColumn headerText="$resource{i18n.common.Status}"  rowHeader="$boolean{false}" id="col6">
        <staticText id="statusCol" value="#{requestScope.statusString}" >
            <!beforeEncode
                mapGet(Map="#{pageSession.instanceStatusMap}" Key="#{td.value.name}" Value="#{requestScope.status}")
                setAttribute(key="statusString" value="$resource{i18nc.status.image.$attribute{status}}  &nbsp; $resource{i18nc.status.$attribute{status}}");
            />
        </staticText>
    </sun:tableColumn>
</sun:tableRowGroup>

</sun:table>
