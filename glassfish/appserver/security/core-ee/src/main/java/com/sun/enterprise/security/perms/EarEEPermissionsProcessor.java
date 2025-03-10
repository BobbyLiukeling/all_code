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

package com.sun.enterprise.security.perms;

import java.security.PermissionCollection;
import java.security.Permissions;
import java.security.Permission;

import java.util.HashMap;
import java.util.Map;
import java.util.Enumeration;
import java.util.logging.Level;
import java.net.MalformedURLException;

import org.glassfish.api.deployment.DeploymentContext;

import com.sun.enterprise.security.perms.SMGlobalPolicyUtil.CommponentType;



public class EarEEPermissionsProcessor extends PermissionsProcessor {

    
    //map recording the 'Java EE component type' to its EE adjusted granted permissions
    private static final Map<CommponentType, PermissionCollection> compTypeToEEGarntsMap 
            = new HashMap<CommponentType, PermissionCollection>();

    
    public EarEEPermissionsProcessor( 
            DeploymentContext dc)  throws SecurityException {
        
        super(SMGlobalPolicyUtil.CommponentType.ear, dc);
        
        try {
            convertEEPermissionPaths(CommponentType.ejb);
            convertEEPermissionPaths(CommponentType.war);
            convertEEPermissionPaths(CommponentType.rar);
            convertEEPermissionPaths(CommponentType.car);
            
            //combine all ee permissions then assign to ear 
            combineAllEEPermisssonsForEar();
            
        } catch (MalformedURLException e) {            
            throw new SecurityException(e);
        }

    }
    
    
    /**
     * get the EE permissions which have the file path adjusted for the right module
     * @return  adjusted EE permissions
     */
    public PermissionCollection getAdjustedEEPermission(CommponentType type) {
        return compTypeToEEGarntsMap.get(type);
    }
    

    public Map<CommponentType, PermissionCollection> getAllAdjustedEEPermission() {
        return compTypeToEEGarntsMap;
    }

    
    //conver the path for permissions
    private void convertEEPermissionPaths(CommponentType cmpType) throws MalformedURLException {        
        //get server suppled default policy
        PermissionCollection defWarPc = 
            SMGlobalPolicyUtil.getEECompGrantededPerms(cmpType);

        //revise the filepermission's path
        PermissionCollection eePc = processPermisssonsForPath(defWarPc, context);
        
        if (logger.isLoggable(Level.FINE)){
            logger.fine("Revised permissions = " + eePc);
        }

        compTypeToEEGarntsMap.put(cmpType, eePc);        
    }
    
    
    private PermissionCollection combineAllEEPermisssonsForEar() {
        
        if (compTypeToEEGarntsMap == null) 
            return null;
        
        Permissions allEEPerms = new Permissions();
        
        addPermissions(allEEPerms, getAdjustedEEPermission(CommponentType.war));
        addPermissions(allEEPerms, getAdjustedEEPermission(CommponentType.ejb));
        addPermissions(allEEPerms, getAdjustedEEPermission(CommponentType.rar));
        //addPermissions(allEEPerms, getAdjustedEEPermission(CommponentType.car));

        compTypeToEEGarntsMap.put(CommponentType.ear, allEEPerms);
        
        return allEEPerms;
    }
    
    private void addPermissions(Permissions combined, PermissionCollection toAdd) {
        
        if (toAdd == null)
            return;

        Enumeration<Permission> enumAdd = toAdd.elements();
        while (enumAdd.hasMoreElements()) {
            Permission p = enumAdd.nextElement();
            combined.add(p);
        }
        
    }

}
