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

import java.io.IOException;
import java.io.PrintWriter;

import javax.inject.Inject;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebInitParam;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import test.artifacts.Asynchronous;
import test.artifacts.AsynchronousPaymentProcessor;
import test.artifacts.PaymentProcessor;
import test.artifacts.Synchronous;
import test.artifacts.SynchronousPaymentProcessor;
import test.beans.BeanToTestAny;
import test.beans.BeanToTestConstructorInjection;
import test.beans.BeanToTestInitializerMethodInjection;
import test.beans.BeanToTestMultipleQualifiers;

@WebServlet(name = "mytest", urlPatterns = { "/myurl" }, initParams = {
        @WebInitParam(name = "n1", value = "v1"),
        @WebInitParam(name = "n2", value = "v2") })
public class QualifierServlet extends HttpServlet {
    
    @Inject
    BeanToTestInitializerMethodInjection tb;

    @Inject
    BeanToTestConstructorInjection tb2;

    @Inject
    BeanToTestAny tb3;
    
    @Inject
    BeanToTestMultipleQualifiers tb4;

    @Inject
    @Synchronous
    PaymentProcessor synchronousPaymentProcessor;
    @Inject
    @Asynchronous
    PaymentProcessor asynchronousPaymentProcessor;

    public void service(HttpServletRequest req, HttpServletResponse res)
            throws IOException, ServletException {
        PrintWriter writer = res.getWriter();
        writer.write("Hello from Servlet 3.0. ");
        String msg = "n1=" + getInitParameter("n1") + ", n2="
                + getInitParameter("n2");
        if (tb == null)
            msg += "Bean injection into Servlet failed";

        boolean qualifierTestSuccess = synchronousPaymentProcessor instanceof SynchronousPaymentProcessor
                && asynchronousPaymentProcessor instanceof AsynchronousPaymentProcessor;
        if (!qualifierTestSuccess)
            msg += "Qualifier based injection into Servlet Failed";
        if (!tb.testInjection())
            msg += "Qualifier based injection into BeanToTestInitializerMethodInjection (initializer method injection) Failed";
        if (!tb2.testInjection())
            msg += "Qualifier based injection into BeanToTestConstructorMethodInjection (constructor method injection) Failed";
        if (!tb3.testInjection())
            msg += "Qualifier based @Any injection into BeanToTestAny Failed";
        if (!tb4.testInjection()) 
            msg += "Multiple qualifiers test failed";

        writer.write("initParams: " + msg + "\n");
    }
}