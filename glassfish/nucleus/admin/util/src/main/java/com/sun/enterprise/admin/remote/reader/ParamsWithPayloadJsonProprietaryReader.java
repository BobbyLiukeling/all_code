/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2013-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.admin.remote.reader;

import com.sun.enterprise.admin.remote.ParamsWithPayload;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;

/**
 *
 * @author martinmares
 */
public class ParamsWithPayloadJsonProprietaryReader implements ProprietaryReader<ParamsWithPayload> {
    
    private final ActionReportJsonProprietaryReader delegate;

    public ParamsWithPayloadJsonProprietaryReader(ActionReportJsonProprietaryReader delegate) {
        this.delegate = delegate;
    }

    public ParamsWithPayloadJsonProprietaryReader() {
        this(new ActionReportJsonProprietaryReader());
    }
    
    
    
    @Override
    public boolean isReadable(final Class<?> type,
                               final String mimetype) {
        return type.isAssignableFrom(ParamsWithPayload.class) 
                && mimetype != null 
                && mimetype.startsWith("application/json");
    }
    
    public ParamsWithPayload readFrom(HttpURLConnection urlConnection) throws IOException {
        return readFrom(urlConnection.getInputStream(), urlConnection.getContentType());
    }

    @Override
    public ParamsWithPayload readFrom(final InputStream is, final String contentType) throws IOException {
        return new ParamsWithPayload(null, delegate.readFrom(is, contentType));
    }
    
}