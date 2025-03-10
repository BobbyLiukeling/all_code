/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2002-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.s1asdev.jmsdd;

import com.sun.ejte.ccl.reporter.SimpleReporterAdapter;
import com.sun.enterprise.deployment.*;
import com.sun.enterprise.deployment.archivist.AppClientArchivist;
import com.sun.enterprise.deployment.archivist.ApplicationArchivist;
import com.sun.enterprise.loader.ASURLClassLoader;
import junit.framework.TestCase;
import org.glassfish.deployment.common.JavaEEResourceType;
import org.glassfish.ejb.deployment.archivist.EjbArchivist;
import org.glassfish.ejb.deployment.descriptor.EjbBundleDescriptorImpl;
import org.glassfish.ejb.deployment.descriptor.EjbDescriptor;
import org.glassfish.web.deployment.archivist.WebArchivist;
import org.xml.sax.SAXParseException;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class ArchiveTest extends TestCase {

    String archiveDir = null;
    private static SimpleReporterAdapter stat = new SimpleReporterAdapter("appserv-tests");

    protected void setUp() throws Exception {
        super.setUp();
        TestUtil.setupHK2();
        archiveDir = System.getProperty("ArchiveDir");
    }

    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void testApplicationArchive() throws Exception {
        String tcName = "jms-destination-definition-application-archive-test";

        try {
            doTestApplicationArchive();
            stat.addStatus(tcName, stat.PASS);
        } catch(Exception e) {
            stat.addStatus(tcName, stat.FAIL);
            throw e;
        }
    }

    private void doTestApplicationArchive() throws IOException, SAXParseException {
        String appArchiveName = "jms-destination-definition-application";
        File archive = new File(archiveDir, appArchiveName);
        assertTrue("Do not find the archive: " + archive.getAbsolutePath(), archive.exists());

        ApplicationArchivist reader = (ApplicationArchivist) TestUtil.getByType(ApplicationArchivist.class);
        reader.setAnnotationProcessingRequested(true);
        ASURLClassLoader classLoader = new ASURLClassLoader(this.getClass().getClassLoader());
        classLoader.addURL(archive.toURL());
        reader.setClassLoader(classLoader);
        Application applicationDesc = reader.open(archive);

        Map<String, JMSDestinationDefinitionDescriptor> expectedJMSDDDs =
                new HashMap<String, JMSDestinationDefinitionDescriptor>();
        JMSDestinationDefinitionDescriptor desc;

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope jms destination defined in UT Application DD");
        desc.setName("java:global/env/UT_Application_DD_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("application-scope jms destination defined in UT Application DD");
        desc.setName("java:app/env/UT_Application_DD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        TestUtil.compareJMSDDD(expectedJMSDDDs, applicationDesc.getResourceDescriptors(JavaEEResourceType.JMSDD));
    }

    public void testApplicationClientArchive() throws Exception {
        String tcName = "jms-destination-definition-appclient-archive-test";

        try {
            doTestApplicationClientArchive();
            stat.addStatus(tcName, stat.PASS);
        } catch(Exception e) {
            stat.addStatus(tcName, stat.FAIL);
            throw e;
        }
    }

    private void doTestApplicationClientArchive() throws IOException, SAXParseException {
        String appArchiveName = "jms-destination-definition-appclient";
        File archive = new File(archiveDir, appArchiveName);
        assertTrue("Do not find the archive: " + archive.getAbsolutePath(), archive.exists());

        ASURLClassLoader classLoader = new ASURLClassLoader(this.getClass().getClassLoader());
        classLoader.addURL(archive.toURL());

        AppClientArchivist reader = (AppClientArchivist)TestUtil.getByType(AppClientArchivist.class);
        reader.setAnnotationProcessingRequested(true);
        reader.setClassLoader(classLoader);
        assertTrue("Archivist should handle annotations.", reader.isAnnotationProcessingRequested());

        ApplicationClientDescriptor appclientDesc = reader.open(archive);

        Map<String, JMSDestinationDefinitionDescriptor> expectedJMSDDDs =
                new HashMap<String, JMSDestinationDefinitionDescriptor>();
        JMSDestinationDefinitionDescriptor desc;

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource to be modified by Appclient DD");
        desc.setName("java:global/env/Appclient_ModByDD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:global/env/Appclient_Annotation_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("application-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:app/env/Appclient_Annotation_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("module-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:module/env/Appclient_Annotation_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("component-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:comp/env/Appclient_Annotation_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource defined in Appclient DD");
        desc.setName("java:global/env/Appclient_DD_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("application-scope resource defined in Appclient DD");
        desc.setName("java:app/env/Appclient_DD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("module-scope resource defined in Appclient DD");
        desc.setName("java:module/env/Appclient_DD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("component-scope resource defined in Appclient DD");
        desc.setName("java:comp/env/Appclient_DD_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        TestUtil.compareJMSDDD(expectedJMSDDDs, appclientDesc.getResourceDescriptors(JavaEEResourceType.JMSDD));
    }

    public void testWebArchive() throws Exception {
        String tcName = "jms-destination-definition-web-archive-test";

        try {
            doTestWebArchive();
            stat.addStatus(tcName, stat.PASS);
        } catch(Exception e) {
            stat.addStatus(tcName, stat.FAIL);
            throw e;
        }
    }

    private void doTestWebArchive() throws IOException, SAXParseException {
        String appArchiveName = "jms-destination-definition-web";
        File archive = new File(archiveDir, appArchiveName);
        assertTrue("Do not find the archive: " + archive.getAbsolutePath(), archive.exists());

        ASURLClassLoader classLoader = new ASURLClassLoader(this.getClass().getClassLoader());
        classLoader.addURL(archive.toURL());

        WebArchivist reader = (WebArchivist) TestUtil.getByType(WebArchivist.class);
        reader.setAnnotationProcessingRequested(true);
        reader.setClassLoader(classLoader);
        assertTrue("Archivist should handle annotations.", reader.isAnnotationProcessingRequested());

        WebBundleDescriptor webDesc = reader.open(archive);

        Map<String, JMSDestinationDefinitionDescriptor> expectedJMSDDDs =
                new HashMap<String, JMSDestinationDefinitionDescriptor>();
        JMSDestinationDefinitionDescriptor desc;

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource to be modified by Web DD");
        desc.setName("java:global/env/Servlet_ModByDD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:global/env/Servlet_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("application-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:app/env/Servlet_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("module-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:module/env/Servlet_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("component-scope resource defined by @JMSDestinationDefinition");
        desc.setName("java:comp/env/Servlet_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("global-scope resource defined in Web DD");
        desc.setName("java:global/env/Web_DD_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("application-scope resource defined in Web DD");
        desc.setName("java:app/env/Web_DD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("module-scope resource defined in Web DD");
        desc.setName("java:module/env/Web_DD_JMSDestination");
        desc.setClassName("javax.jms.Topic");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalTopic");
        expectedJMSDDDs.put(desc.getName(), desc);

        desc = new JMSDestinationDefinitionDescriptor();
        desc.setDescription("component-scope resource defined in Web DD");
        desc.setName("java:comp/env/Web_DD_JMSDestination");
        desc.setClassName("javax.jms.Queue");
        desc.setResourceAdapter("jmsra");
        desc.setDestinationName("myPhysicalQueue");
        expectedJMSDDDs.put(desc.getName(), desc);

        TestUtil.compareJMSDDD(expectedJMSDDDs, webDesc.getResourceDescriptors(JavaEEResourceType.JMSDD));
    }

    public void testEJBArchive() throws Exception {
        String tcName = "jms-destination-definition-ejb-archive-test";

        try {
            doTestEJBArchive();
            stat.addStatus(tcName, stat.PASS);
        } catch(Exception e) {
            stat.addStatus(tcName, stat.FAIL);
            throw e;
        }
    }

    private void doTestEJBArchive() throws IOException, SAXParseException {
        String appArchiveName = "jms-destination-definition-ejb";
        File archive = new File(archiveDir, appArchiveName);
        assertTrue("Do not find the archive: " + archive.getAbsolutePath(), archive.exists());

        ASURLClassLoader classLoader = new ASURLClassLoader(this.getClass().getClassLoader());
        classLoader.addURL(archive.toURL());

        EjbArchivist reader = (EjbArchivist) TestUtil.getByType(EjbArchivist.class);
        reader.setClassLoader(classLoader);
        reader.setAnnotationProcessingRequested(true);
        assertTrue("Archivist should handle annotations.", reader.isAnnotationProcessingRequested());

        EjbBundleDescriptorImpl ejbBundleDesc = reader.open(archive);
        Set<ResourceDescriptor> acturalCRDDs = new HashSet<ResourceDescriptor>();
        for (EjbDescriptor ejbDesc : ejbBundleDesc.getEjbs()) {
            acturalCRDDs.addAll(ejbDesc.getResourceDescriptors(JavaEEResourceType.JMSDD));
        }

        Map<String, JMSDestinationDefinitionDescriptor> expectedJMSDDDs =
                new HashMap<String, JMSDestinationDefinitionDescriptor>();
        JMSDestinationDefinitionDescriptor desc;

        // jms-destination in DD for stateful EJB
        {
            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource to be modified by EJB DD");
            desc.setName("java:global/env/HelloStatefulEJB_ModByDD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource defined in EJB DD");
            desc.setName("java:global/env/HelloStatefulEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("application-scope resource defined in EJB DD");
            desc.setName("java:app/env/HelloStatefulEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("module-scope resource defined in EJB DD");
            desc.setName("java:module/env/HelloStatefulEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("component-scope resource defined in EJB DD");
            desc.setName("java:comp/env/HelloStatefulEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);
        }

        // jms-destination in DD for stateless EJB
        {
            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource to be modified by EJB DD");
            desc.setName("java:global/env/HelloEJB_ModByDD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource defined in EJB DD");
            desc.setName("java:global/env/HelloEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("application-scope resource defined in EJB DD");
            desc.setName("java:app/env/HelloEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("module-scope resource defined in EJB DD");
            desc.setName("java:module/env/HelloEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("component-scope resource defined in EJB DD");
            desc.setName("java:comp/env/HelloEJB_DD_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);
        }

        // jms-destination in annotation for stateful EJB
        {
            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:global/env/HelloStatefulEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("application-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:app/env/HelloStatefulEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("module-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:module/env/HelloStatefulEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("component-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:comp/env/HelloStatefulEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);
        }

        // jms-destination in annotation for stateless EJB
        {
            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("global-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:global/env/HelloEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("application-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:app/env/HelloEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("module-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:module/env/HelloEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Topic");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalTopic");
            expectedJMSDDDs.put(desc.getName(), desc);

            desc = new JMSDestinationDefinitionDescriptor();
            desc.setDescription("component-scope resource defined by @JMSDestinationDefinition");
            desc.setName("java:comp/env/HelloEJB_Annotation_JMSDestination");
            desc.setClassName("javax.jms.Queue");
            desc.setResourceAdapter("jmsra");
            desc.setDestinationName("myPhysicalQueue");
            expectedJMSDDDs.put(desc.getName(), desc);
        }

        TestUtil.compareJMSDDD(expectedJMSDDDs, acturalCRDDs);
    }
}
