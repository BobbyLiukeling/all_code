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

package org.glassfish.admin.rest.composite.resource;

import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.UriInfo;
import org.glassfish.admin.rest.composite.LegacyCompositeResource;
import org.glassfish.admin.rest.composite.RestCollection;
import org.glassfish.admin.rest.composite.metadata.HelpText;
import org.glassfish.admin.rest.model.BaseModel;

/**
 *
 * @author jdlee
 */
@Path("dummies")
public class DummiesResource extends LegacyCompositeResource {

    @Override
    public UriInfo getUriInfo() {
        return new DummyUriInfo();
    }

    @GET
    public RestCollection<BaseModel> getDummyDataCollection(
            @QueryParam("type") @HelpText(bundle="org.glassfish.admin.rest.composite.HelpText", key="dummy.type") String type
            ) {
        RestCollection<BaseModel> rc = new RestCollection<BaseModel>();

        return rc;
    }

    @Path("id/{name}")
    public DummyResource getDummyData(@QueryParam("foo") String foo) {
        return getSubResource(DummyResource.class);
    }

    @POST
    public Response createDummy(BaseModel model) {
        return Response.ok().build();
    }
}
