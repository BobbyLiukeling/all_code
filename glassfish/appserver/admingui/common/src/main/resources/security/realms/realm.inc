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

<!--  security/realms/realm.inc -->

<event>
    <!beforeEncode
        # need to put back the required image if there is any error in processing and the page is refreshed.
        # we had turned off the requirement in initPage before.
        setComponentRequired(id="form1:fileSection:jaax:jaax" required="$boolean{true}" );
        setComponentRequired(id="form1:fileSection:keyFile:keyFile" required="$boolean{true}" );
        setComponentRequired(id="form1:ldapSection:jaax:jaax" required="$boolean{true}" );
        setComponentRequired(id="form1:ldapSection:directory:directory" required="$boolean{true}" );
        setComponentRequired(id="form1:ldapSection:baseDn:baseDn" required="$boolean{true}" );
        setComponentRequired(id="form1:solarisSection:jaax:jaax" required="$boolean{true}" );
        setComponentRequired(id="form1:pamSection:jaax:jaax" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:jaax:jaax" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:jndi:jndi" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:userTable:userTable" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:userName:userName" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:pswd:pswd" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:groupTable:groupTable" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:groupName:groupName" required="$boolean{true}" );
        setComponentRequired(id="form1:jdbcSection:pswdEnc:pswdEnc" required="$boolean{true}" );
    />
</event>

        <sun:form id="form1">
#include "/common/shared/alertMsg.inc"
        <!-- there seems to be a bug with the radio button component where if we switch from 'input' to 'predefine',
             the selected value will not get updated.  It will always stay as 'input'.
             So i work around the problem by using a hidden field
          -->
        <sun:hidden id="option"  value="#{myOption}" />

        <sun:title id="propertyContentPage" title="#{pageTitle}" helpText="#{pageTitleHelp}">
            <sun:button id="manageUsersButton" rendered="#{showUserButton}" immediate="#{true}" style="margin-left: 8pt"  text="$resource{i18n.button.ManageUsers}" >
                <!command
                    gf.redirect(page="#{request.contextPath}/common/security/realms/manageUsers.jsf?name=#{pageSession.encodedName}&configName=#{pageSession.encodedConfigName}");
                />
            </sun:button>

            <!facet pageButtonsTop>
#include "/security/realms/realmButtons.inc"            
            </facet>   
            </sun:title>

#include "/security/realms/realmAttrs.inc" 
#include "/common/shared/propertyDescTable.inc"

        <sun:title id="title2">
            <!facet pageButtonsBottom>
#include "/security/realms/realmButtons.inc" 
            </facet> 
        </sun:title>    

        <sun:hidden id="helpKey" value="#{helpKey}" />
    </sun:form>
    "<br/><br/>
#include "/common/security/realms/realmjs.inc"
#include "/common/shared/changeButtonsJS.inc"
