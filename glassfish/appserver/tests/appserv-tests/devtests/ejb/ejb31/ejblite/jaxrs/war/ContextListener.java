/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
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

package com.acme;

import javax.servlet.annotation.WebListener;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.annotation.PostConstruct;
import javax.naming.InitialContext;

import java.lang.reflect.Method;


@WebListener
public class ContextListener implements ServletContextListener {

    public void contextInitialized(ServletContextEvent sce) {

	System.out.println("In ContextListener::contextInitialized");

	try {

	    FooManagedBean f = (FooManagedBean)
		new InitialContext().lookup("java:module/FooManagedBean");
	    f.hello();

	    Object jaxrsEjbGlue = new InitialContext().lookup("java:org.glassfish.ejb.container.interceptor_binding_spi");
	    System.out.println("jaxrsEjbGlue = " + jaxrsEjbGlue);
	    Method m = jaxrsEjbGlue.getClass().getMethod("registerInterceptor", java.lang.Object.class);
	    System.out.println("register interceptor method = " + m);

	    m.invoke(jaxrsEjbGlue, new com.sun.jersey.JerseyInterceptor());


	    // Test InjectionManager managed bean functionality
	    Object injectionMgr = new InitialContext().lookup("com.sun.enterprise.container.common.spi.util.InjectionManager");
	    Method createManagedMethod = injectionMgr.getClass().getMethod("createManagedObject", java.lang.Class.class);
	    System.out.println("create managed object method = " + createManagedMethod);
	    FooManagedBean f2 = (FooManagedBean) createManagedMethod.invoke(injectionMgr, FooManagedBean.class);
	    f2.hello();
	    f2.assertInterceptorBinding();

	    Method destroyManagedMethod = injectionMgr.getClass().getMethod("destroyManagedObject", java.lang.Object.class);
	    System.out.println("destroy managed object method = " + destroyManagedMethod);
	    destroyManagedMethod.invoke(injectionMgr, f2);

	     FooNonManagedBean nonF = (FooNonManagedBean) createManagedMethod.invoke(injectionMgr, FooNonManagedBean.class);
	     System.out.println("FooNonManagedBean = " + nonF);
	     nonF.hello();
	     destroyManagedMethod.invoke(injectionMgr, nonF);
	    
	} catch(Exception e) {
	    e.printStackTrace();
	}

    }

    @PostConstruct
    public void pc() {
	System.out.println("In ContextListener::postConstruct");
    }

    public void contextDestroyed(ServletContextEvent sce) {

	System.out.println("In ContextListener::contextDestroyed");

    }

}
