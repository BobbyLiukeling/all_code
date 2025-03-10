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

package org.glassfish.appclient.server.core.jws.servedcontent;

import java.util.Properties;
import org.glassfish.appclient.server.core.jws.Util;

/**
 *
 * @author Tim
 */
public class SimpleDynamicContentImpl extends Content.Adapter implements DynamicContent {

    private final String template;
    private final String mimeType;
    private final boolean isMain;
    
    private Instance instance = null;

    public SimpleDynamicContentImpl(final String template, final String mimeType) {
        this(template, mimeType, false);
    }
    
    public SimpleDynamicContentImpl(final String template, final String mimeType, final boolean isMain) {
        this.template = template;
        this.mimeType = mimeType;
        this.isMain = isMain;
    }

    public Instance getExistingInstance(Properties tokenValues) {
        return getOrCreateInstance(tokenValues, false);
    }

    public Instance getOrCreateInstance(Properties tokenValues) {
        return getOrCreateInstance(tokenValues, true);
    }

    private Instance getOrCreateInstance(final Properties tokenValues,
            final boolean createIfAbsent) {
//        if (instance == null && createIfAbsent) {
            instance = new DynamicContent.InstanceAdapter(
                    Util.replaceTokens(template, tokenValues));
//        }
        return instance;
    }

    public String getMimeType() {
        return mimeType;
    }
    
    @Override
    public boolean isMain() {
        return isMain;
    }

    @Override
    public String toString() {
        return (instance == null ? "null" : instance.getText());
    }



}
