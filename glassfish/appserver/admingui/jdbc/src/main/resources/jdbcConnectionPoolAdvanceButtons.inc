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

<!-- jdbc/jdbcConnectionPoolAdvanceButtons.jsf -->

<!facet pageButtonsTop>
    <sun:panelGroup id="topButtons">
        <sun:button id="saveButton"  text="$resource{i18n.button.Save}"
                onClick="if (checkPoolAttr('#{timeoutId}', '#{reqInt}') && guiValidate('#{reqMsg}','#{reqInt}','#{reqPort}')) {submitAndDisable(this, '$resource{i18n.button.Processing}');}; return false;" >
            <!command
                if ("#{pageSession.valueMap.isConnectionValidationRequired}=true") {
                    if ("#{pageSession.valueMap.connectionValidationMethod}=table") {
                        if ("#{pageSession.myTableOption}=dropdown") {
                            setValueExpression(expression="#{pageSession.valueMap['validationTableName']}", value="#{pageSession.tableDropDownValue}");
                        }
                        if ("#{pageSession.myTableOption}=text") {
                            setValueExpression(expression="#{pageSession.valueMap['validationTableName']}", value="#{pageSession.tableTextValue}");
                        }
                    }
                    if ("#{pageSession.valueMap.connectionValidationMethod}=custom-validation") {
                        if ("#{pageSession.myValidCNOption}=dropdown") {
                            setValueExpression(expression="#{pageSession.valueMap['validationClassname']}", value="#{pageSession.validCNDropDownValue}");
                        }
                        if ("#{pageSession.myValidCNOption}=text") {
                            setValueExpression(expression="#{pageSession.valueMap['validationClassname']}", value="#{pageSession.validCNTextValue}");
                        }
                        gf.filterMap(map="#{pageSession.valueMap}" attrNames={'validationClassname'} keep="#{true}" resultMap="#{validationClassNameMap}");
                        gf.createEntity(endpoint="#{pageSession.resourceUrl}"
                                attrs="#{validationClassNameMap}"
                         );
                    }
                }

                if ("!(#{pageSession.valueMap.isConnectionValidationRequired}=true)") {
                    //While saving the connection validation settings, first save the connection validation to false.
                    gf.filterMap(map="#{pageSession.valueMap}" attrNames={'isConnectionValidationRequired'} keep="#{true}" resultMap="#{validationMap}");
                    gf.createEntity(endpoint="#{pageSession.resourceUrl}"
                            attrs="#{validationMap}"
                            convertToFalse="#{pageSession.convertToFalseList}"
                     );
                }
                
                if ("#{pageSession.valueMap['lazyConnectionAssociation']}") {
                        setValueExpression(expression="#{pageSession.valueMap['lazyConnectionEnlistment']}", value="true");
                }

                gf.createEntity(endpoint="#{pageSession.resourceUrl}"
                            attrs="#{pageSession.valueMap}"
                            skipAttrs="#{pageSession.skipAttrsList}"
                            convertToFalse="#{pageSession.convertToFalseList}"
                        );
                if ("#{valueMap['ping']}") {
                    urlencode(value="#{valueMap['name']}" encoding="UTF-8" result="#{pageSession.encodeName}");
                    gf.createAttributeMap(keys={"id"} values={"$pageSession{encodeName}"} map="#{requestScope.attrMap}");
                    if(#{pageSession.isAppScopedRes}){
                        mapPut(map="#{requestScope.attrMap}" key="appname" value="#{pageSession.encodedAppName}");
                        if(#{pageSession.moduleName}){
                            mapPut(map="#{requestScope.attrMap}" key="modulename" value="#{pageSession.encodedModuleName}");
                        }
                    }
                    gf.restRequest(endpoint="#{sessionScope.REST_URL}/resources/ping-connection-pool.json"
                                   attrs="#{requestScope.attrMap}"
                                   method="get"
                                   result="#{requestScope.result}");
                }
                prepareSuccessfulMsg();
                gf.redirect(page="#{pageSession.selfPage}&alertType=${alertType}&alertSummary=${alertSummary}&alertDetail=${alertDetail}");
            />
        </sun:button>
        <sun:button id="cancelButton" immediate="#{true}" primary="#{false}"text="$resource{i18n.button.Cancel}" >
            <!command
                gf.redirect(page="#{parentPage}");
            />
        </sun:button>
    </sun:panelGroup>
</facet>
