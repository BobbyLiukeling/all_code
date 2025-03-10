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

package ejb32.methodintf;

import javax.ejb.*;
import javax.interceptor.*;
import javax.annotation.*;

@Stateless
public class StlesEJB implements St {

    private static boolean tm = false;
    private static boolean intf = false;

    private String caller = null;

    @EJB SingletonBean singleton;

    @Schedule(second="*/2",minute="*",hour="*")
    public void test() {
        if (caller != null) {
            if (caller.equals("timeout")) {
                System.out.println("In StlesEJB: test timeout");
                tm = Verifier.verify_tx(false);
            } else {
                System.out.println("In StlesEJB: test remote");
                intf = Verifier.verify_tx(true);
                singleton.test();
            }
        }
        caller = null;
    }

    @AroundInvoke
    private Object around_invoke(InvocationContext ctx) throws Exception {
        caller = "intf";
        return ctx.proceed();
    }

    @AroundTimeout
    private Object around_timeout(InvocationContext ctx) throws Exception {
        caller = "timeout";
        return ctx.proceed();
    }

    public boolean verify() {
        boolean rc = singleton.verifyResult();
        return tm && intf && rc;
    }

}
