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

/*
 * MappingContext.java
 *
 * Created on January 28, 2002, 6:30 PM
 */

package com.sun.jdo.spi.persistence.utility;

import java.util.*;

/** Special resource bundle which delegates to two others.
 * Ideally could just set the parent on the first, but this is protected, 
 * so it might not work.  It's still unclear whether that approach would work 
 * in this subclass because it may break the localization fall through 
 * mechanism if used.
 * Note: This code is copied from NbBundle in the openide sources with 
 * the following modifications:
 * - reformatting
 * - making variables final
 * - renaming variables and some params
 * - removing locale code
 * - creating the merged set of keys using jdk classes and not nb utils
 *
 * @author Rochelle Raccah
 * @version %I%
 */
public class MergedBundle extends ResourceBundle
{
	private final ResourceBundle _mainBundle, _parentBundle;

	public MergedBundle (ResourceBundle mainBundle, 
		ResourceBundle parentBundle)
	{
		_mainBundle = mainBundle;
		_parentBundle = parentBundle;
	}

	public Enumeration getKeys () { return mergeKeys(); }

	private Enumeration mergeKeys ()
	{
		Set noDuplicatesMerge = 
			new HashSet(getCollection(_mainBundle.getKeys()));

		noDuplicatesMerge.addAll(getCollection(_parentBundle.getKeys()));

		return Collections.enumeration(noDuplicatesMerge);
	}

	private Collection getCollection (Enumeration enumeration)
	{
		List returnList = new ArrayList();

		if (enumeration != null)
		{
			while (enumeration.hasMoreElements())
				returnList.add(enumeration.nextElement());
		}

		return returnList;
	}

	protected Object handleGetObject (String key)
		throws MissingResourceException
	{
		try
		{
			return _mainBundle.getObject(key);
		}
		catch (MissingResourceException mre)	// try the other bundle
		{
			return _parentBundle.getObject(key);
		}
	}
}
