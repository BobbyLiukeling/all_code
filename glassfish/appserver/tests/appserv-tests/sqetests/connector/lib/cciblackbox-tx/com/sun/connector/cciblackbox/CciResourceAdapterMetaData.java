/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2018 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.connector.cciblackbox;

import javax.resource.cci.ResourceAdapterMetaData;

/**
 * this implementation class provides info about the capabilities of a 
 * resource adapter implementation.
 * @author Sheetal Vartak
 */
public class CciResourceAdapterMetaData implements ResourceAdapterMetaData {

  private String vendorName = "Oracle";

  private String adapterVersion = "1.0";

  private String specVersion = "1.0";

  private String adapterName = "CCI Resource Adapter";

  private String description = "Resource Adapter for CCI";

  public CciResourceAdapterMetaData() {
  }

  public String getAdapterVersion() {
    return adapterVersion;
  }

  public String getSpecVersion() {
    return specVersion;
  }

  public String getAdapterName() {
    return adapterName;
  }

  public String getAdapterVendorName() {
    return vendorName;
  }

  public String getAdapterShortDescription() {
    return description;
  }

  public void setAdapterVersion(String version) {
    this.adapterVersion = version;
  }

  public void setSpecVersion(String version) {
    this.specVersion = version;
  }

  public void setAdapterName(String name) {
    this.adapterName = name;
  }

  public void setAdapterVendorName(String name) {
    this.vendorName = name;
  }

  public void setAdapterShortDescription(String description) {
    this.description = description;
  }

  public String[] getInteractionSpecsSupported() {
    String[] str = new String[1];
    str[0] = new String("com.sun.connector.cciblackbox.CciInteractionSpec");
    return str;

  }

  public boolean supportsExecuteWithInputAndOutputRecord() {

    /* Method method;
      Class interactionClass = 
    Class.forName("javax.resource.cci.Interaction");
    try {
          method = 
      interactionClass.getDeclaredMethod(InteractionSpec,Record,Record);
    }catch(NoSuchMethodException e) { 
    return false;
    }
    if(method != null) {
    return true;
    }*/

    return true;

  }

  public boolean supportsExecuteWithInputRecordOnly() {
    /*  Method method;
      Class interactionClass = 
    Class.forName("javax.resource.cci.Interaction");
    try {
          method =
      interactionClass.getDeclaredMethod(InteractionSpec,Record);
    }catch(NoSuchMethodException e) { 
    return false;
    }
    if(method != null) {
    return true;
    }*/

    return true;
  }

  public boolean supportsLocalTransactionDemarcation() {

    return true;

  }
}
