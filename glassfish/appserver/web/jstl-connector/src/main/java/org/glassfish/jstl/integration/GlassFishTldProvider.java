/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 1997-2017 Oracle and/or its affiliates. All rights reserved.
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

package org.glassfish.jstl.integration;

import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLClassLoader;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Pattern;
import javax.inject.Inject;
import javax.inject.Singleton;
import com.sun.enterprise.module.Module;
import com.sun.enterprise.module.ModulesRegistry;
import com.sun.enterprise.util.net.JarURIPattern;
import org.glassfish.api.web.TldProvider;
import org.glassfish.hk2.api.PostConstruct;
import org.glassfish.web.loader.LogFacade;
import org.jvnet.hk2.annotations.Service;


/**
 * Implementation of TldProvider for JSTL.
 * @author Shing Wai Chan
 * @author Sahoo
 */

@Service(name="jstlTld")
@Singleton
public class GlassFishTldProvider implements TldProvider, PostConstruct {

    private static final Logger logger = LogFacade.getLogger();

    private static final ResourceBundle rb = logger.getResourceBundle();

    @Inject
    ModulesRegistry registry;

    private Map<URI, List<String>> tldMap = new HashMap<URI, List<String>>();

    /**
     * Gets the name of this TldProvider
     */
    public String getName() {
        return "jstlTld";
    }

    /**
     * Gets a mapping from JAR files to their TLD resources.
     */
    @SuppressWarnings("unchecked")
    public Map<URI, List<String>> getTldMap() {
        return (Map<URI, List<String>>)((HashMap)tldMap).clone();
    }

    /**
     * Gets a mapping from JAR files to their TLD resources
     * that are known to contain listener declarations.
     */
    public Map<URI, List<String>> getTldListenerMap() {
        // None of the JSTL TLDs declare any listeners
        return null;
    }
 
    public void postConstruct() {

        
        Class jstlImplClass = org.apache.taglibs.standard.Version.class;

        URI[] uris = null;
        Module m = null;
        if (jstlImplClass != null) {
            m = registry.find(jstlImplClass);
        }
        if (m != null) {
            uris = m.getModuleDefinition().getLocations();
        } else {
            ClassLoader classLoader = getClass().getClassLoader();
            if (classLoader instanceof URLClassLoader) {
                URL[] urls = ((URLClassLoader)classLoader).getURLs();
                if (urls != null && urls.length > 0) {
                    uris = new URI[urls.length];
                    for (int i = 0; i < urls.length; i++) {
                        try {
                            uris[i] = urls[i].toURI();
                        } catch(URISyntaxException e) {
                            String msg = rb.getString(LogFacade.TLD_PROVIDER_IGNORE_URL);
                            msg = MessageFormat.format(msg, urls[i]);
                            logger.log(Level.WARNING, msg, e);
                        }
                    }
                }
            } else {
                logger.log(Level.WARNING,
                    LogFacade.UNABLE_TO_DETERMINE_TLD_RESOURCES,
                    new Object[] {"JSTL", classLoader,
                        GlassFishTldProvider.class.getName()});
            }
        }

        if (uris != null && uris.length > 0) {
            Pattern pattern = Pattern.compile("META-INF/.*\\.tld");
            for (URI uri : uris) {
                List<String> entries =  JarURIPattern.getJarEntries(uri, pattern);
                if (entries != null && entries.size() > 0) {
                    tldMap.put(uri, entries);
                }
            }
        }
    }
}
