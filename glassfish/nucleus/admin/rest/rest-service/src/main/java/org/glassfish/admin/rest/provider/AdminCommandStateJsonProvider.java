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

package org.glassfish.admin.rest.provider;

import com.sun.enterprise.v3.common.ActionReporter;
import java.lang.reflect.Type;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.ext.Provider;
import org.codehaus.jettison.json.JSONException;
import org.codehaus.jettison.json.JSONObject;
import org.glassfish.api.admin.AdminCommandState;

/**
 *
 * @author mmares
 */
@Provider
@Produces({MediaType.APPLICATION_JSON, "application/x-javascript"})
public class AdminCommandStateJsonProvider extends BaseProvider<AdminCommandState> {
    
    private static final ActionReportJson2Provider actionReportJsonProvider = new ActionReportJson2Provider();

    public AdminCommandStateJsonProvider() {
        super(AdminCommandState.class, MediaType.APPLICATION_JSON_TYPE, new MediaType("application", "x-javascript"));
    }
    
    @Override
    protected boolean isGivenTypeWritable(Class<?> type, Type genericType) {
        return desiredType.isAssignableFrom(type);
    }
    
    @Override
    public String getContent(AdminCommandState proxy) {
        try {
            return processState(proxy).toString();
        } catch (JSONException ex) {
            throw new RuntimeException(ex);
        }
    }
    
    public JSONObject processState(AdminCommandState state) throws JSONException {
        JSONObject result = new JSONObject();
        result.put("state", state.getState().name());
        result.put("id", state.getId());
        result.put("empty-payload", state.isOutboundPayloadEmpty());
        ActionReporter ar = (ActionReporter) state.getActionReport();
        addActionReporter(ar, result);
        return result;
    }
    
    protected void addActionReporter(ActionReporter ar, JSONObject json) throws JSONException {
        if (ar != null) {
            json.put("action-report", actionReportJsonProvider.processReport(ar));
        }
    }
    
}
