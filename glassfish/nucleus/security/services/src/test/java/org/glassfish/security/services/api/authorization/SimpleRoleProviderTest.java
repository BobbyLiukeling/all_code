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

package org.glassfish.security.services.api.authorization;

import java.net.URI;
import javax.security.auth.Subject;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import org.jvnet.hk2.testing.junit.HK2Runner;

import org.glassfish.security.common.Group;
import org.glassfish.security.common.PrincipalImpl;
import org.glassfish.security.services.impl.authorization.AuthorizationServiceImpl;
import org.glassfish.security.services.spi.authorization.RoleMappingProvider;


public class SimpleRoleProviderTest extends HK2Runner {

	private AuthorizationService authorizationService = new AuthorizationServiceImpl();
	private RoleMappingProvider simpleRoleProvider = null;

	@Before
	public void before() {
		super.before();

		simpleRoleProvider = testLocator.getService(RoleMappingProvider.class, "simpleRoleMapping");
	}

	@Test
	public void testProviderAdmin() throws Exception {
		Assert.assertNotNull(simpleRoleProvider);
		boolean result = simpleRoleProvider.isUserInRole(null,
				authorizationService.makeAzSubject(adminSubject()),
				authorizationService.makeAzResource(URI.create("admin://my/respath")),
				"Admin", null, null);
		Assert.assertEquals(true, result);
	}

	private Subject adminSubject() {
		Subject result = new Subject();
		result.getPrincipals().add(new PrincipalImpl("admin"));
		result.getPrincipals().add(new Group("asadmin"));
		return result;
	}

	@Test
	public void testProviderNonAdmin() throws Exception {
		Assert.assertNotNull(simpleRoleProvider);
		boolean result = simpleRoleProvider.isUserInRole(null,
				authorizationService.makeAzSubject(nonAdminSubject()),
				authorizationService.makeAzResource(URI.create("admin://negative")),
				"Admin", null, null);
		Assert.assertEquals(false, result);
	}

	private Subject nonAdminSubject() {
		Subject result = new Subject();
		result.getPrincipals().add(new PrincipalImpl("joe"));
		result.getPrincipals().add(new Group("myGroup"));
		return result;
	}

	@Test
	public void testProviderNonAdminRole() throws Exception {
		Assert.assertNotNull(simpleRoleProvider);
		boolean result = simpleRoleProvider.isUserInRole(null,
				authorizationService.makeAzSubject(adminSubject()),
				authorizationService.makeAzResource(URI.create("foo://other")), // Warning Message
				"otherRole", null, null);
		Assert.assertEquals(false, result);
	}
}
