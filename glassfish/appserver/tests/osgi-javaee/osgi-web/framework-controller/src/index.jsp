<%--

    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

    Copyright (c) 2010-2017 Oracle and/or its affiliates. All rights reserved.

    The contents of this file are subject to the terms of either the GNU
    General Public License Version 2 only ("GPL") or the Common Development
    and Distribution License("CDDL") (collectively, the "License").  You
    may not use this file except in compliance with the License.  You can
    obtain a copy of the License at
    https://oss.oracle.com/licenses/CDDL+GPL-1.1
    or LICENSE.txt.  See the License for the specific
    language governing permissions and limitations under the License.

    When distributing the software, include this License Header Notice in each
    file and include the License file at LICENSE.txt.

    GPL Classpath Exception:
    Oracle designates this particular file as subject to the "Classpath"
    exception as provided by Oracle in the GPL Version 2 section of the License
    file that accompanied this code.

    Modifications:
    If applicable, add the following below the License Header, with the fields
    enclosed by brackets [] replaced by your own identifying information:
    "Portions Copyright [year] [name of copyright owner]"

    Contributor(s):
    If you wish your version of this file to be governed by only the CDDL or
    only the GPL Version 2, indicate your decision by adding "[Contributor]
    elects to include this software in this distribution under the [CDDL or GPL
    Version 2] license."  If you don't indicate a single choice of license, a
    recipient has the option to distribute your version of this file under
    either the CDDL, the GPL Version 2 or to extend the choice of license to
    its licensees as provided above.  However, if you add GPL Version 2 code
    and therefore, elected the GPL Version 2 license, then the option applies
    only if the new code is made subject to such option by the copyright
    holder.

--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>

<%--
    Document   : index
    Created on : 10 Nov, 2009, 12:13:01 PM
    Author     : mohit
--%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Index Page</title>
    </head>
    <body>
        <table border="1" width="100%">
            <tr>
                <td colspan="2" align="center" height="50" bgcolor="black">
                    <font color="white" style="font-weight:bold">OSGI Framework Controller</font>
                </td>
            </tr>
            <tr>
                <td width="20%" align="center">
                    <a href="install.jsp" target="mainFrame">Install Bundle</a> <br><br>
                    <a href="uninstall.jsp" target="mainFrame">Uninstall Bundle</a> <br><br>
                    <a href="web/bundleviewer" target="mainFrame">View Bundles </a>
                </td>
                <td height="100%">
                    <iframe name="mainFrame" width="100%" height="500">
                        <p>Nothing HERE..</p>
                    </iframe>
                </td>
            </tr>
        </table>
    </body>
</html>
