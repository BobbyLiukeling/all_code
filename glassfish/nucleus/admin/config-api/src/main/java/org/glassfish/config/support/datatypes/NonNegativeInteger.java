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

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.glassfish.config.support.datatypes;

import org.jvnet.hk2.annotations.Service;
import org.jvnet.hk2.config.DataType;
import org.jvnet.hk2.config.ValidationException;

/** Represents an integer from 0 to Integer.MAX_VALUE. 
 *  It's modeled as a functional class.
 * @author &#2325;&#2375;&#2342;&#2366;&#2352 (km@dev.java.net)
 */
@Service
public class NonNegativeInteger implements DataType {

    /** Validates the value as a non-negative integer.
     * @param value
     * @throws org.jvnet.hk2.config.ValidationException
     */
    public void validate(String value) throws ValidationException {
        if (value == null)
            throw new ValidationException("null value is not of type NonNegativeInteger");
        if (isTokenized(value))
            return; //a token is always valid
        try {
            long number = Long.parseLong(value);
            if (number < 0 || number > Integer.MAX_VALUE) {
                String msg = "value: " + number + " not applicable for NonNegativeInteger [0, " + Integer.MAX_VALUE + "] data type";
                throw new ValidationException(msg);
            }
        } catch(NumberFormatException e) {
            throw new ValidationException(e);
        }
    }
    /*package*/
    static boolean isTokenized(String value) {
        if (value != null && value.startsWith("${") && value.endsWith("}"))
            return true;
        return false;
    }
}
