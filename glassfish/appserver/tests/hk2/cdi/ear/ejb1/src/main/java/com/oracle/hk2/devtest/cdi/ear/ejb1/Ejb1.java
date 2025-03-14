/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2013-2018 Oracle and/or its affiliates. All rights reserved.
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

package com.oracle.hk2.devtest.cdi.ear.ejb1;

import javax.ejb.Remote;
import javax.ejb.Stateless;
import javax.inject.Inject;

import com.oracle.hk2.devtest.cdi.ear.lib1.HK2Service;
import com.oracle.hk2.devtest.cdi.ear.lib1.Lib1HK2Service;

/**
 * 
 * @author jwells
 *
 */
@Stateless
@Remote(Ejb1Remote.class)
public class Ejb1 implements Ejb1Remote {
    @Inject
    private Ejb1HK2Service ejb1Service;
    
    @Inject
    private Lib1HK2Service lib1Service;

    @Override
    public boolean isEjb1HK2ServiceAvailable() {
        return (ejb1Service != null) && HK2Service.EJB1.equals(ejb1Service.getComponentName()) ;
    }

    @Override
    public boolean isLib1HK2ServiceAvailable() {
        return (lib1Service != null) && HK2Service.LIB1.equals(lib1Service.getComponentName()) ;
    }
}
