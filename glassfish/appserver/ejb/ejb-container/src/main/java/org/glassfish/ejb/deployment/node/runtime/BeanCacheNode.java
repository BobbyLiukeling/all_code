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

package org.glassfish.ejb.deployment.node.runtime;

import java.util.Map;

import com.sun.enterprise.deployment.node.DeploymentDescriptorNode;
import com.sun.enterprise.deployment.node.XMLElement;
import com.sun.enterprise.deployment.xml.RuntimeTagNames;
import org.glassfish.ejb.deployment.descriptor.runtime.BeanCacheDescriptor;
import org.w3c.dom.Node;

/**
 * This node handles the bean-cache untime deployment descriptors 
 *
 * @author  Jerome Dochez
 * @version 
 */
public class BeanCacheNode extends DeploymentDescriptorNode<BeanCacheDescriptor> {

    private BeanCacheDescriptor descriptor;

    @Override
    public BeanCacheDescriptor getDescriptor() {
        if (descriptor==null) descriptor = new BeanCacheDescriptor();
        return descriptor;
    }

    @Override
    public void setElementValue(XMLElement element, String value) {
	if (RuntimeTagNames.IS_CACHE_OVERFLOW_ALLOWED.equals(element.getQName())) {
	    descriptor.setIsCacheOverflowAllowed(Boolean.valueOf(value));
	} else 
        super.setElementValue(element, value);
    }

    @Override
    protected Map getDispatchTable() {
	Map dispatchTable = super.getDispatchTable();
	dispatchTable.put(RuntimeTagNames.MAX_CACHE_SIZE, "setMaxCacheSize");
	dispatchTable.put(RuntimeTagNames.RESIZE_QUANTITY, "setResizeQuantity");
	dispatchTable.put(RuntimeTagNames.CACHE_IDLE_TIMEOUT_IN_SECONDS, "setCacheIdleTimeoutInSeconds");
	dispatchTable.put(RuntimeTagNames.REMOVAL_TIMEOUT_IN_SECONDS, "setRemovalTimeoutInSeconds");
	dispatchTable.put(RuntimeTagNames.VICTIM_SELECTION_POLICY, "setVictimSelectionPolicy");
	return dispatchTable;
    }

    @Override
    public Node writeDescriptor(Node parent, String nodeName, BeanCacheDescriptor descriptor) {
	Node beanCacheNode = super.writeDescriptor(parent, nodeName, descriptor);
	appendTextChild(beanCacheNode, RuntimeTagNames.MAX_CACHE_SIZE, descriptor.getMaxCacheSize());	
	appendTextChild(beanCacheNode, RuntimeTagNames.RESIZE_QUANTITY, descriptor.getResizeQuantity());	
	appendTextChild(beanCacheNode, RuntimeTagNames.IS_CACHE_OVERFLOW_ALLOWED, String.valueOf(descriptor.isIsCacheOverflowAllowed()));
	appendTextChild(beanCacheNode, RuntimeTagNames.CACHE_IDLE_TIMEOUT_IN_SECONDS, descriptor.getCacheIdleTimeoutInSeconds());	
	appendTextChild(beanCacheNode, RuntimeTagNames.REMOVAL_TIMEOUT_IN_SECONDS, descriptor.getRemovalTimeoutInSeconds());	
	appendTextChild(beanCacheNode, RuntimeTagNames.VICTIM_SELECTION_POLICY, descriptor.getVictimSelectionPolicy());	
	return beanCacheNode;
    }
}
