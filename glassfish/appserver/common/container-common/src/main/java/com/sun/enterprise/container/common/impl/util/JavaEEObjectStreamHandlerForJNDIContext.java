/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2009-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.container.common.impl.util;

import com.sun.enterprise.container.common.spi.util.JavaEEObjectStreamHandler;
import org.glassfish.api.naming.GlassfishNamingManager;
import javax.inject.Inject;
import org.jvnet.hk2.annotations.Service;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import java.io.IOException;
import java.io.Serializable;

/**
 * @author Mahesh Kannan
 *         Date: Sep 3, 2008
 */
@Service
public class JavaEEObjectStreamHandlerForJNDIContext
        implements JavaEEObjectStreamHandler {

    @Inject
    GlassfishNamingManager gfNM;

    public Object replaceObject(Object obj)
            throws IOException {
        Object result = obj;
        if (obj instanceof Context) {
            Context ctx = (Context) obj;
            try {
                // Serialize state for a jndi context.  The spec only requires
                // support for serializing contexts pointing to java:comp/env
                // or one of its subcontexts.  We also support serializing the
                // references to the the default no-arg InitialContext, as well
                // as references to the the contexts java: and java:comp. All
                // other contexts will either not serialize correctly or will
                // throw an exception during deserialization.
                result = new SerializableJNDIContext(ctx.getNameInNamespace());
            } catch (NamingException ex) {
                IOException ioe = new IOException();
                ioe.initCause(ex);
                throw ioe;
            }
        }

        return result;
    }

    public Object resolveObject(Object obj)
        throws IOException {
        Object result = obj;
        if (obj instanceof SerializableJNDIContext) {
            SerializableJNDIContext sctx = (SerializableJNDIContext) obj;
            try {
                String name = sctx.getName();
                if ((name == null) || (name.length() == 0)) {
                    result = new InitialContext();
                } else {
                    result = gfNM.restoreJavaCompEnvContext(name);
                }
            } catch (NamingException namEx) {
                IOException ioe = new IOException();
                ioe.initCause(namEx);
                throw ioe;
            }
        }

        return result;
    }

    private static final class SerializableJNDIContext
        implements Serializable {

        private String name;

        SerializableJNDIContext(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }
    }

}
