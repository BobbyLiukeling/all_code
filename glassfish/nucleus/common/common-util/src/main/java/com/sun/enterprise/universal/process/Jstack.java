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

package com.sun.enterprise.universal.process;

import java.io.OutputStream;

import java.util.Map;
import java.util.Set;
import static com.sun.enterprise.universal.process.ProcessUtils.jstackExe;

/**
 * Provide a Jstack getDump of a given PID -- or a concatenated getDump of ALL
 * running JVMs.
 *
 * @author Byron Nevins
 */
public class Jstack {

    private static final Set<Map.Entry<Integer, String>> set;

    public static void main(String[] args) {

        System.out.println("** Got " + set.size() + " process entries");
        if (args.length > 0) {
            int pid = Integer.parseInt(args[0]);
            boolean legal = Jps.isPid(Integer.parseInt(args[0]));
            System.out.printf("Jps.isPid(%s) ==> %b%n", args[0], legal);
            getDump(pid);
        }
        else {
            for (Map.Entry<Integer, String> e : set) {
                System.out.printf("%d %s%n", e.getKey(), e.getValue());
            }
            System.out.println(getDump());
            System.out.println("XXXXX");
        }
    }

    public static String getDump() {
        StringBuilder sb = new StringBuilder();

        for (Map.Entry<Integer, String> e : set) {
            int pid = e.getKey();
            sb.append(prepend(pid, e.getValue()));
            sb.append(getDump(pid));
        }
        return sb.toString();
    }

    public static String getDump(int pid) {
        try {
            if (jstackExe == null) {
                return "";
            }
            ProcessManager pm = new ProcessManager(jstackExe.getPath(), "-l", "" + pid);
            pm.setEcho(false);
            pm.execute();
            return pm.getStdout();
        }
        catch (Exception e) {
            return "";
        }
    }

    private static String prepend(int pid, String name) {
        return "-------    DUMPING JSTACK FOR PID= " + pid + ", name = " + name + " -------\n";
    }

    static {
        set = Jps.getProcessTable().entrySet();
    }
}
