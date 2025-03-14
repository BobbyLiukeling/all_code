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

package org.glassfish.web.deployment.node.runtime.gf;

import com.sun.enterprise.deployment.node.XMLElement;
import com.sun.enterprise.deployment.node.runtime.RuntimeDescriptorNode;
import com.sun.enterprise.deployment.runtime.RuntimeDescriptor;
import com.sun.enterprise.deployment.xml.RuntimeTagNames;
import org.glassfish.web.deployment.runtime.ClassLoader;
import org.glassfish.web.deployment.runtime.WebProperty;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

/**
* node for class-loader tag
*/
public class ClassLoaderNode extends RuntimeDescriptorNode<ClassLoader> {
    
    public ClassLoaderNode() {
        registerElementHandler(new XMLElement(RuntimeTagNames.PROPERTY), 
            WebPropertyNode.class, "addWebProperty"); 	
    }

    protected ClassLoader descriptor = null;

    /**
     * @return the descriptor instance to associate with this XMLNode
     */
    @Override
    public ClassLoader getDescriptor() {
        if (descriptor==null) {
            descriptor = new ClassLoader();
        }
        return descriptor;
    }

    /**
     * parsed an attribute of an element
     *
     * @param elementName the element name
     * @param attributeName the attribute name
     * @param value the attribute value
     * @return true if the attribute was processed
     */
    @Override
    protected boolean setAttributeValue(XMLElement elementName, 
        XMLElement attributeName, String value) {
	RuntimeDescriptor descriptor = getDescriptor();
	if (attributeName.getQName().equals(RuntimeTagNames.EXTRA_CLASS_PATH)) {
	    descriptor.setAttributeValue(ClassLoader.EXTRA_CLASS_PATH, value);
	    return true;    
	} else if (attributeName.getQName().equals(RuntimeTagNames.DELEGATE)) {
	    descriptor.setAttributeValue(ClassLoader.DELEGATE, value);
	    return true;    
	} else if (attributeName.getQName().equals(
            RuntimeTagNames.DYNAMIC_RELOAD_INTERVAL)) {
	    descriptor.setAttributeValue(ClassLoader.DYNAMIC_RELOAD_INTERVAL, 
                value);
	    return true;    
	}
	return false;
    }
    
    /**
     * write the descriptor class to a DOM tree and return it
     *
     * @param parent node for the DOM tree
     * @param nodeName node name
     * @param descriptor the descriptor to write
     * @return the DOM tree top node
     */
    @Override
    public Node writeDescriptor(Node parent, String nodeName, 
        ClassLoader descriptor) {       

	Element classLoader = (Element) super.writeDescriptor(parent, 
            nodeName, descriptor);
	
        // property*
        WebProperty[] properties = descriptor.getWebProperty();
        if (properties != null && properties.length > 0) {
            WebPropertyNode wpn = new WebPropertyNode();
            wpn.writeDescriptor(classLoader, RuntimeTagNames.PROPERTY, 
                properties);
        }

	// extra-class-path, delegate, dynamic-reload-interval
	setAttribute(classLoader, RuntimeTagNames.EXTRA_CLASS_PATH, (String) descriptor.getAttributeValue(ClassLoader.EXTRA_CLASS_PATH));
	setAttribute(classLoader, RuntimeTagNames.DELEGATE, (String) descriptor.getAttributeValue(ClassLoader.DELEGATE));
	setAttribute(classLoader, RuntimeTagNames.DYNAMIC_RELOAD_INTERVAL, (String) descriptor.getAttributeValue(ClassLoader.DYNAMIC_RELOAD_INTERVAL));
	
	return classLoader;
    }
}
