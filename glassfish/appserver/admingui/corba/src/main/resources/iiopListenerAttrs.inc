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

<!-- iiopListener.inc  -->

<sun:propertySheet id="propertySheet">
#include "/common/shared/configNameSection.inc"
    <!-- General Settings section -->
    <sun:propertySheetSection id="generalSettingsSetion">
        <sun:property id="IiopNameProp"  rendered="#{pageSession.edit}" labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n.common.Name}" >
            <sun:staticText id="IiopName" text="#{pageSession.valueMap['id']}" />
        </sun:property>
        <sun:property id="IiopNameTextProp"  rendered="#{!pageSession.edit}" labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n.common.Name}">
            <sun:textField id="IiopNameText" styleClass="required" text="#{pageSession.valueMap['id']}" columns="$int{55}" maxLength="#{sessionScope.fieldLengths['maxLength.common.Name']}" required="#{true}" />
        </sun:property>
        <sun:property id="NetwkAddrProp"  labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n_corba.iiopListener.netwkAddrLabel}" helpText="$resource{i18n_corba.iiopListener.netwkAddrHelp}" >
            <sun:textField id="NetwkAddr" styleClass="required"  columns="$int{20}" maxLength="#{sessionScope.fieldLengths['maxLength.iiopListener.netwkAddr']}" text="#{pageSession.valueMap['address']}" required="#{true}" />
        </sun:property>
        <sun:property id="ListenerPortProp"  labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n_corba.iiopListener.listPortLabel}" helpText="$resource{i18n_corba.iiopListener.listPortHelp}" >
            <sun:textField id="ListenerPort" styleClass="required port" columns="$int{20}" maxLength="#{sessionScope.fieldLengths['maxLength.iiopListener.listPort']}" text="#{pageSession.valueMap['port']}" required="#{true}" />
        </sun:property>
        <sun:property id="ListenerProp"  labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n_corba.iiopListener.listenerLabel}" helpText="$resource{i18n_corba.iiopListener.listenerHelp}" >
            <sun:checkbox  selected="#{pageSession.valueMap['enabled']}" selectedValue="true" />
        </sun:property>
        <sun:property id="SecurityProp"  labelAlign="left" noWrap="#{true}" overlapLabel="#{false}" label="$resource{i18n_corba.iiopListener.securityEnable}" >
            <sun:checkbox id="Security"  selected="#{pageSession.valueMap['securityEnabled']}" selectedValue="true" />
        </sun:property>
    </sun:propertySheetSection>
</sun:propertySheet>    

