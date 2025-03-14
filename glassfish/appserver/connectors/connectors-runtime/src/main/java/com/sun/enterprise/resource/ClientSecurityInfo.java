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

package com.sun.enterprise.resource;

import com.sun.enterprise.deployment.ResourcePrincipal;

import javax.resource.spi.ConnectionRequestInfo;

/**
 * This class represents the client-specific information associated
 * with a resource. Used for pool partitioning
 *
 * @author Tony Ng
 */
public class ClientSecurityInfo {

    // union: either store Principal or ConnectionRequestInfo
    private ResourcePrincipal prin;
    private ConnectionRequestInfo info;

    static private final int NULL_HASH_CODE = Integer.valueOf(1).hashCode();

    public ClientSecurityInfo(ResourcePrincipal prin) {
        if (prin == null) {
            throw new NullPointerException("Principal is null");
        }
        this.prin = prin;
        this.info = null;
    }

    public ClientSecurityInfo(ConnectionRequestInfo info) {
        // info can be null
        this.prin = null;
        this.info = info;
    }


    public ResourcePrincipal getPrincipal() {
        return prin;
    }

    public ConnectionRequestInfo getConnectionRequestInfo() {
        return info;
    }

    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (obj instanceof ClientSecurityInfo) {
            ClientSecurityInfo other = (ClientSecurityInfo) obj;
            return ((isEqual(prin, other.prin)) &&
                    (isEqual(info, other.info)));
        }
        return false;
    }

    public int hashCode() {
        int result = NULL_HASH_CODE;
        if (prin != null) {
            result = prin.hashCode();
        }
        if (info != null) {
            result += info.hashCode();
        }
        return result;
    }

    private boolean isEqual(Object a, Object b) {
        if (a == null) {
            return (b == null);
        } else {
            return (a.equals(b));
        }
    }

    public String toString() {
        return "ClientSecurityInfo: prin=" + prin + " info=" + info;
    }
}
