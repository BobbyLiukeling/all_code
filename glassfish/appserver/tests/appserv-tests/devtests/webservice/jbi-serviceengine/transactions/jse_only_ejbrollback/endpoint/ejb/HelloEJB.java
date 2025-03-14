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

package endpoint.ejb;

import javax.jws.WebService;
import javax.xml.ws.WebServiceRef;
import javax.ejb.Stateless;
import javax.ejb.SessionContext;
import javax.ejb.TransactionAttribute;
import javax.ejb.TransactionAttributeType;
import javax.annotation.Resource;
import java.sql.*;
import javax.sql.DataSource;

@WebService(endpointInterface="endpoint.ejb.Hello", targetNamespace="http://endpoint/ejb")
@Stateless
public class HelloEJB implements Hello {

    @Resource private SessionContext ctx;
    @Resource(mappedName="jdbc/__default") private DataSource ds;

    @TransactionAttribute(TransactionAttributeType.REQUIRED)
    public String sayHello(String who) {
	System.out.println("**** EJB Called");
	Connection con=null;
	String tableName = "CUSTOMER_rb";
	try {
	con = ds.getConnection();
	System.out.println("**** auto commit = " + con.getAutoCommit());

	updateTable(con, tableName, "Vikas", "vikas@sun.com");
	readData(con, tableName);
        } catch(Exception ex) {
            throw new RuntimeException(ex);
        } finally {
	    try {
	    if(con != null) con.close();
	    } catch (SQLException se) {}
	}
	ctx.setRollbackOnly();
        return "WebSvcTest-Hello " + who;
    }

    private void updateTable(Connection con, String tableName, String name, String email) throws Exception {
        PreparedStatement pStmt = 
             con.prepareStatement("INSERT INTO "+ tableName +" (NAME, EMAIL) VALUES(?,?)");
	pStmt.setString(1, name);
	pStmt.setString(2, email);
        pStmt.executeUpdate();
    }

    private void readData(Connection con, String tableName) throws Exception {
        PreparedStatement pStmt = 
             con.prepareStatement("SELECT NAME, EMAIL FROM "+tableName);
        ResultSet rs = pStmt.executeQuery();
        while(rs.next()){
            System.out.println("NAME="+rs.getString(1)+", EMAIL="+rs.getString(2));
        }
    }
}
