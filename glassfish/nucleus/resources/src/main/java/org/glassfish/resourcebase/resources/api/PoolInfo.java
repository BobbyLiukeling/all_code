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

package org.glassfish.resourcebase.resources.api;


/**
 * Represents pool information.
 * @author Jagadish Ramu
 */
public class PoolInfo implements org.glassfish.resourcebase.resources.api.GenericResourceInfo {

    private String name;
    private String applicationName = null;
    private String moduleName = null;

    public PoolInfo(String name){
        this.name = name;
    }
    public PoolInfo(String name, String applicationName){
        this.name = name;
        this.applicationName = applicationName;
    }

    public PoolInfo(String name, String applicationName, String moduleName){
        this.name = name;
        this.applicationName = applicationName;
        this.moduleName = moduleName;
    }

    /**
     * @inheritDoc
     */
    public String getName() {
        return name;
    }

    /**
     * @inheritDoc
     */
    public String getApplicationName() {
        return applicationName;
    }

    /**
     * @inheritDoc
     */
    public String getModuleName() {
        return moduleName;
    }

        public String toString(){
            if(applicationName != null && moduleName != null){
                return "{ PoolInfo : (name="+name+"), (applicationName="+applicationName+"), (moduleName="+moduleName+")}";
            }else if(applicationName != null){
                return "{ PoolInfo : (name="+name+"), (applicationName="+applicationName+") }";
            }else{
                return name;
            }
    }

    public boolean equals(Object o){
        boolean result = false;
        if(o == this){
            result = true;
        }else if(o instanceof PoolInfo){
            PoolInfo poolInfo = (PoolInfo)o;
            boolean poolNameEqual = poolInfo.getName().equals(name);
            boolean appNameEqual = false;
            if(applicationName == null && poolInfo.getApplicationName() == null){
                appNameEqual = true;
            }else if(applicationName !=null && poolInfo.getApplicationName() != null
                    && applicationName.equals(poolInfo.getApplicationName())){
                appNameEqual = true;
            }
            boolean moduleNameEqual = false;
            if(moduleName == null && poolInfo.getModuleName() == null){
                moduleNameEqual = true;
            }else if(moduleName !=null && poolInfo.getModuleName() != null
                    && moduleName.equals(poolInfo.getModuleName())){
                moduleNameEqual = true;
            }
            result = poolNameEqual && appNameEqual && moduleNameEqual;
        }
        return result;
    }

    public int hashCode(){
        int result = 67;
        if (name != null)
            result = 67 * result + name.hashCode();
        if (applicationName != null)
            result = 67 * result + applicationName.hashCode();
        if (moduleName != null)
            result = 67 * result + moduleName.hashCode();

        return result;
    }
}
