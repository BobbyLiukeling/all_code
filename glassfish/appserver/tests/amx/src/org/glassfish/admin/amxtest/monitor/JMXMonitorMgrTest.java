/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
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
* $Header: /cvs/glassfish/admin/mbeanapi-impl/tests/org.glassfish.admin.amxtest/monitor/JMXMonitorMgrTest.java,v 1.5 2007/05/05 05:24:05 tcfujii Exp $
* $Revision: 1.5 $
* $Date: 2007/05/05 05:24:05 $
*/
package org.glassfish.admin.amxtest.monitor;

import com.sun.appserv.management.base.Util;
import com.sun.appserv.management.monitor.AMXStringMonitor;
import com.sun.appserv.management.monitor.JMXMonitorMgr;
import org.glassfish.admin.amxtest.AMXTestBase;

import javax.management.ObjectName;
import java.io.IOException;

/**
 */
public final class JMXMonitorMgrTest
        extends AMXTestBase {
    public JMXMonitorMgrTest() {
    }

    public JMXMonitorMgr
    getMgr() {
        return (getDomainRoot().getJMXMonitorMgr());
    }

    public void
    testGetMgr() {
        final JMXMonitorMgr mgr = getMgr();
        assert (mgr != null);
    }

    public void
    testCreateRemoveStringMonitor()
            throws IOException {
        final JMXMonitorMgr mgr = getMgr();

        final AMXStringMonitor mon = mgr.createStringMonitor(getClass().getName() + "Test");
        final ObjectName objectName = Util.getObjectName(mon);

        mon.setObservedAttribute("Group");
        final ObjectName observee = Util.getObjectName(mgr);
        assert (observee != null);
        mon.addObservedObject(observee);
        assert mon.containsObservedObject(observee);
        mon.removeObservedObject(observee);

        assert (getConnection().isRegistered(objectName));
        mgr.remove(mon.getName());
        assert (!getConnection().isRegistered(objectName));
    }
}


