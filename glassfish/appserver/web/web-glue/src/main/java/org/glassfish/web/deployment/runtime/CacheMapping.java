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

package org.glassfish.web.deployment.runtime;

import com.sun.enterprise.deployment.runtime.RuntimeDescriptor;

/**
* this class contains runtime information for the web bundle 
* it was kept to be backward compatible with the schema2beans descriptors
* generated by iAS 7.0 engineering team.
*
* @author Jerome Dochez
*/
public class CacheMapping extends RuntimeDescriptor
{
    
    static public final String SERVLET_NAME = "ServletName";	// NOI18N
    static public final String URL_PATTERN = "UrlPattern";	// NOI18N
    static public final String CACHE_HELPER_REF = "CacheHelperRef";	// NOI18N
    static public final String TIMEOUT = "Timeout";	// NOI18N
    static public final String NAME = "Name";
    static public final String SCOPE = "Scope";
    static public final String REFRESH_FIELD = "RefreshField";	// NOI18N
    static public final String HTTP_METHOD = "HttpMethod";	// NOI18N
    static public final String DISPATCHER = "Dispatcher";	// NOI18N
    static public final String KEY_FIELD = "KeyField";	// NOI18N
    static public final String CONSTRAINT_FIELD = "ConstraintField";	// NOI18N
        
    public CacheMapping(CacheMapping other) {
	super(other);
    }

    public CacheMapping() {
	setAttributeValue(KEY_FIELD, SCOPE, "request.parameter");
	setAttributeValue(REFRESH_FIELD, SCOPE, "request.parameter");	
    }
    
    // This attribute is mandatory
    public void setServletName(String value)
    {
	this.setValue(SERVLET_NAME, value);
    }
    
    //
    public String getServletName()
    {
	return (String)this.getValue(SERVLET_NAME);
    }
    
    // This attribute is mandatory
    public void setURLPattern(String value)
    {
	this.setValue(URL_PATTERN, value);
    }
    
    //
    public String getURLPattern()
    {
	return (String)this.getValue(URL_PATTERN);
    }
    
    // This attribute is mandatory
    public void setCacheHelperRef(String value)
    {
	this.setValue(CACHE_HELPER_REF, value);
    }
    
    //
    public String getCacheHelperRef()
    {
	return (String)this.getValue(CACHE_HELPER_REF);
    }
    
    // This attribute is optional
    public void setTimeout(String value)
    {
	this.setValue(TIMEOUT, value);
    }
    
    //
    public String getTimeout()
    {
	return (String)this.getValue(TIMEOUT);
    }
    
    // This attribute is optional
    public void setRefreshField(boolean value)
    {
	this.setValue(REFRESH_FIELD, Boolean.valueOf(value));
    }
    
    //
    public boolean isRefreshField()
    {
	Boolean ret = (Boolean)this.getValue(REFRESH_FIELD);
	if (ret == null)
	    return false;
	return ret.booleanValue();
    }

    
    // This attribute is an array, possibly empty
    public void setDispatcher(int index, String value)
    {
	this.setValue(DISPATCHER, index, value);
    }
    
    //
    public String getDispatcher(int index)
    {
	return (String)this.getValue(DISPATCHER, index);
    }
    
    // This attribute is an array, possibly empty
    public void setDispatcher(String[] value)
    {
	this.setValue(DISPATCHER, value);
    }
    
    //
    public String[] getDispatcher()
    {
	return (String[])this.getValues(DISPATCHER);
    }
    
    // Return the number of properties
    public int sizeDispatcher()
    {
	return this.size(DISPATCHER);
    }
    
    // Add a new element returning its index in the list
    public int addDispatcher(String value)
    {
	return this.addValue(DISPATCHER, value);
    }

    // Add a new element returning its index in the list
    public void addNewDispatcher(String value)
    {
	addValue(DISPATCHER, value);
    }    
    
    //
    // Remove an element using its reference
    // Returns the index the element had in the list
    //
    public int removeDispatcher(String value)
    {
	return this.removeValue(DISPATCHER, value);
    }
    
    
    // This attribute is an array, possibly empty
    public void setHttpMethod(int index, String value)
    {
	this.setValue(HTTP_METHOD, index, value);
    }
    
    //
    public String getHttpMethod(int index)
    {
	return (String)this.getValue(HTTP_METHOD, index);
    }
    
    // This attribute is an array, possibly empty
    public void setHttpMethod(String[] value)
    {
	this.setValue(HTTP_METHOD, value);
    }
    
    //
    public String[] getHttpMethod()
    {
	return (String[])this.getValues(HTTP_METHOD);
    }
    
    // Return the number of properties
    public int sizeHttpMethod()
    {
	return this.size(HTTP_METHOD);
    }
    
    // Add a new element returning its index in the list
    public int addHttpMethod(String value)
    {
	return this.addValue(HTTP_METHOD, value);
    }
    // Add a new element returning its index in the list
    public void addNewHttpMethod(String value)
    {
	addValue(HTTP_METHOD, value);
    }    
    
    //
    // Remove an element using its reference
    // Returns the index the element had in the list
    //
    public int removeHttpMethod(String value)
    {
	return this.removeValue(HTTP_METHOD, value);
    }
    
    // This attribute is an array, possibly empty
    public void setKeyField(int index, boolean value)
    {
	this.setValue(KEY_FIELD, index, Boolean.valueOf(value));
    }
    
    //
    public boolean isKeyField(int index)
    {
	Boolean ret = (Boolean)this.getValue(KEY_FIELD, index);
	if (ret == null)
	    return false;
	return ret.booleanValue();
    }
    
    // This attribute is an array, possibly empty
    public void setKeyField(boolean[] value)
    {
	Boolean[] values = null;
	if (value != null)
	{
	    values = new Boolean[value.length];
	    for (int i = 0; i < value.length; i++)
                 values[i] = Boolean.valueOf(value[i]);
	}
	this.setValue(KEY_FIELD, values);
    }
    
    //
    public boolean[] getKeyField()
    {
	boolean[] ret = null;
	Boolean[] values = (Boolean[])this.getValues(KEY_FIELD);
	if (values != null)
	{
	    ret = new boolean[values.length];
	    for (int i=0; i<values.length; i++)
		ret[i] = values[i].booleanValue();
	}
	return ret;
    }
    
    // Return the number of properties
    public int sizeKeyField()
    {
	return this.size(KEY_FIELD);
    }
    
    // Add a new element returning its index in the list
    public int addKeyField(boolean value)
    {
	return this.addValue(KEY_FIELD, Boolean.valueOf(value));
    }
    
    //
    // Remove an element using its reference
    // Returns the index the element had in the list
    //
    public int removeKeyField(boolean value)
    {
	return this.removeValue(KEY_FIELD, Boolean.valueOf(value));
    }
    
    //
    // Remove an element using its index
    //
    public void removeKeyField(int index)
    {
	this.removeValue(KEY_FIELD, index);
    }
    
    // This attribute is an array, possibly empty
    public void setConstraintField(int index, ConstraintField value)
    {
	this.setValue(CONSTRAINT_FIELD, index, value);
    }
    
    //
    public ConstraintField getConstraintField(int index)
    {
	return (ConstraintField)this.getValue(CONSTRAINT_FIELD, index);
    }
    
    // This attribute is an array, possibly empty
    public void setConstraintField(ConstraintField[] value)
    {
	this.setValue(CONSTRAINT_FIELD, value);
    }
    
    //
    public ConstraintField[] getConstraintField()
    {
	return (ConstraintField[])this.getValues(CONSTRAINT_FIELD);
    }
    
    // Return the number of properties
    public int sizeConstraintField()
    {
	return this.size(CONSTRAINT_FIELD);
    }
    
    // Add a new element returning its index in the list
    public int addConstraintField(ConstraintField value)
    {
	return this.addValue(CONSTRAINT_FIELD, value);
    }
    
    // Add a new element returning its index in the list
    public void addNewConstraintField(ConstraintField value)
    {
	this.addValue(CONSTRAINT_FIELD, value);
    }    
    
    //
    // Remove an element using its reference
    // Returns the index the element had in the list
    //
    public int removeConstraintField(ConstraintField value)
    {
	return this.removeValue(CONSTRAINT_FIELD, value);
    }
    
    // This method verifies that the mandatory properties are set
    public boolean verify()
    {
	return true;
    }
    
}
