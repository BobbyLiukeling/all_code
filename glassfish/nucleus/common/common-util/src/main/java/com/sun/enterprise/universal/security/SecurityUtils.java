/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2010-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.universal.security;

import java.security.SecureRandom;

/**
 * Created October 28, 2010
 * @author Byron Nevins
 */
public final class SecurityUtils {

    public static String getSecureRandomHexString(int numBytes) {
        SecureRandom random = new SecureRandom();
        byte[] bb = new byte[numBytes];
        random.nextBytes(bb);
        return toHexString(bb);
    }

    /**
     * No instances allowed.
     */
    private SecurityUtils() {
    }

    static private String toHexString(byte b) {
        String s = Integer.toHexString((int) b + 128);

        if (s.length() == 1)
            s = "0" + s;

        return s;
    }

    static private String toHexString(byte[] bb) {
        StringBuilder sb = new StringBuilder();

        for (byte b : bb)
            sb.append(toHexString(b));

        return sb.toString();
    }
}
