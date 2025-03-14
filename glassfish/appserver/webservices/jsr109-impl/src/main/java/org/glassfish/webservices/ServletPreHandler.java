/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.webservices;

import javax.xml.namespace.QName;

import javax.xml.rpc.handler.GenericHandler;
import javax.xml.rpc.handler.MessageContext;

import java.util.logging.Logger;
import java.util.logging.Level;
import org.glassfish.api.invocation.InvocationManager;

import com.sun.enterprise.web.WebComponentInvocation;

import com.sun.xml.rpc.server.http.Implementor;
import com.sun.xml.rpc.server.http.MessageContextProperties;

/**
 * This handler is inserted first in the handler chain for an
 * servlet web service endpoint.  
 *
 * @author Kenneth Saks
 */
public class ServletPreHandler extends GenericHandler {

    private static Logger logger = LogUtils.getLogger();
    private final WsUtil wsUtil = new WsUtil();

    public ServletPreHandler() {}

    @Override
    public QName[] getHeaders() {
        return new QName[0];
    }

    @Override
    public boolean handleRequest(MessageContext context) {
        WebComponentInvocation inv = null;

        try {
            WebServiceContractImpl wscImpl = WebServiceContractImpl.getInstance();
            InvocationManager invManager = wscImpl.getInvocationManager();
            Object obj = invManager.getCurrentInvocation();
            if (obj instanceof WebComponentInvocation) {
                inv = WebComponentInvocation.class.cast(obj);
                com.sun.xml.rpc.spi.runtime.Tie tie
                        = (com.sun.xml.rpc.spi.runtime.Tie) inv.getWebServiceTie();
                if (tie == null) {
                    Implementor implementor = (Implementor) context.getProperty(MessageContextProperties.IMPLEMENTOR);
                    tie = implementor.getTie();
                    inv.setWebServiceTie(tie);
                }
                inv.setWebServiceMethod(wsUtil.getInvMethod(tie, context));
            }

        } catch(Exception e) {
            logger.log(Level.WARNING, LogUtils.PRE_WEBHANDLER_ERROR, e.toString());
            wsUtil.throwSOAPFaultException(e.getMessage(), context);
        }
        return true;
    }
}
