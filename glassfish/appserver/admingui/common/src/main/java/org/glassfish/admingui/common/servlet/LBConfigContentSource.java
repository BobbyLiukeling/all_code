/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2009-2017 Oracle and/or its affiliates. All rights reserved.
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
 * LBConfigContentSource.java
 *
 * Created on December 26, 2006, 11:08 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.glassfish.admingui.common.servlet;

import java.io.File;
import java.io.InputStream;

import java.io.FileInputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import org.glassfish.admingui.common.util.RestUtil;
import javax.servlet.http.HttpServletRequest;

/**
 *
 * @author anilam
 */
public class LBConfigContentSource  implements DownloadServlet.ContentSource {
    
     /**
     *	<p> This method returns a unique string used to identify this
     *	    {@link DownloadServlet#ContentSource}.  This string must be
     *	    specified in order to select the appropriate
     *	    {@link DownloadServlet#ContentSource} when using the
     *	    {@link DownloadServlet}.</p>
     */
    public String getId() {
	return "LBConfig";					// NOI18N
    }

    /**
     *  <p> This method is responsible for generating the content and
     *	    returning an InputStream to that content.  It is also
     *	    responsible for setting any attribute values in the
     *	    {@link DownloadServlet#Context}, such as {@link DownloadServlet#EXTENSION} or
     *	    {@link DownloadServlet#CONTENT_TYPE}.</p>
     */
    public InputStream getInputStream(DownloadServlet.Context ctx) {
	// Set the extension so it can be mapped to a MIME type
	ctx.setAttribute(DownloadServlet.EXTENSION, "xml");

	// Get appName
	HttpServletRequest request = (HttpServletRequest) ctx.getServletRequest();
	String lbName = request.getParameter("lbName");
        String restUrl = request.getParameter("restUrl");
        
	// Create the tmpFile
	InputStream tmpFile = null;
	try {
            String endpoint = restUrl + "/load-balancers/load-balancer/" + lbName + "/export-http-lb-config";
            DateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");
            Date date = new Date();
            Map attrsMap = new HashMap();
            String tempDir = System.getProperty("java.io.tmpdir");
            String lbFileName = "loadbalancer.xml." + lbName + "_LB_CONFIG." + dateFormat.format(date);
            String slbFile = tempDir + System.getProperty("file.separator") + lbFileName;
            File lbFile = new File(slbFile);
            attrsMap.put("id", slbFile);
            RestUtil.postRestRequestFromServlet(request, endpoint, attrsMap, true, true);
	    tmpFile = new FileInputStream(lbFile);
            boolean success = lbFile.delete();
            if (!success) {
                throw new Exception("Load Balancer config file delete failed");
            }
	} catch (Exception ex) {
	    throw new RuntimeException(ex);
	}

	// Save some important stuff for cleanUp
	ctx.setAttribute("tmpFile", tmpFile);			// NOI18N

	// Return an InputStream to the tmpFile
	return tmpFile;
    }

    /**
     *	<p> This method may be used to clean up any temporary resources.  It
     *	    will be invoked after the <code>InputStream</code> has been
     *	    completely read.</p>
     */
    public void cleanUp(DownloadServlet.Context ctx) {
	// Get the File information
	InputStream tmpFile =
	    (InputStream) ctx.getAttribute("tmpFile");		// NOI18N

	// Close the InputStream
	if (tmpFile != null) {
	    try {
		tmpFile.close();
	    } catch (Exception ex) {
		// Ignore...
	    }
	}

	ctx.removeAttribute("tmpFile");			// NOI18N
    }

    /**
     *	<p> This method is responsible for returning the last modified date of
     *	    the content, or -1 if not applicable.  This information will be
     *	    used for caching.  This implementation always returns -1.</p>
     *
     *	@return	-1
     */
    public long getLastModified(DownloadServlet.Context context) {
	return -1;
    }
}
