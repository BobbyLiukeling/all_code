/*
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.catalina.startup;

import com.sun.logging.LogDomains;
import org.apache.catalina.LogFacade;
import org.apache.tomcat.util.digester.Digester;
import org.apache.tomcat.util.digester.RuleSet;
import javax.inject.Inject;
import javax.inject.Named;
import org.jvnet.hk2.annotations.Optional;
import org.jvnet.hk2.annotations.Service;
import org.xml.sax.EntityResolver;
import org.xml.sax.SAXNotRecognizedException;
import org.xml.sax.SAXNotSupportedException;

import javax.xml.parsers.ParserConfigurationException;
import java.net.URL;
import java.util.logging.Logger;

/**
 * Wrapper class around the Digester that hide Digester's initialization details
 *
 * @author Jean-Francois Arcand
 */
@Service
public class DigesterFactory {

    /**
     * Used to resolve DTDs and XML Schemas of JavaEE.
     */
    @Inject
    @Named("web")
    @Optional
    EntityResolver entityResolver;

    /**
     * Create a <code>Digester</code> parser with no <code>Rule</code>
     * associated and XML validation turned off.
     */
    public Digester newDigester(){
        return newDigester(false, false, null);
    }

    
    /**
     * Create a <code>Digester</code> parser with XML validation turned off.
     * @param rule an instance of <code>Rule</code> used for parsing the xml.
     */
    public Digester newDigester(RuleSet rule){
        return newDigester(false,false,rule);
    }

    /**
     * Create a <code>Digester</code> parser.
     * @param xmlValidation turn on/off xml validation
     * @param xmlNamespaceAware turn on/off namespace validation
     * @param rule an instance of <code>Rule</code??? used for parsing the xml.
     */
    public Digester newDigester(boolean xmlValidation,
                                boolean xmlNamespaceAware,
                                RuleSet rule) {

        Digester digester = new Digester();
        digester.setNamespaceAware(xmlNamespaceAware);
        digester.setValidating(xmlValidation);
        digester.setUseContextClassLoader(true);
        
        String parserName = 
                digester.getFactory().getClass().getName();
        if (parserName.indexOf("xerces")!=-1) {
            digester = patchXerces(digester);
        }

        if (xmlValidation) {
            // Xerces 2.3 and up has a special way to turn on validation
            // for both DTD and Schema
            if (parserName.indexOf("xerces")!=-1) {
                turnOnXercesValidation(digester);
            } else {
                turnOnValidation(digester);
            }
        }

        digester.setEntityResolver(entityResolver);
        if ( rule != null )
            digester.addRuleSet(rule);

        return (digester);
    }


    /**
     * Patch Xerces for backward compatibility.
     */
    private Digester patchXerces(Digester digester){
        // This feature is needed for backward compatibility with old DDs
        // which used Java encoding names such as ISO8859_1 etc.
        // with Crimson (bug 4701993). By default, Xerces does not
        // support ISO8859_1.
        try{
            digester.setFeature(
                "http://apache.org/xml/features/allow-java-encodings", true);
        } catch(ParserConfigurationException e){
                // log("contextConfig.registerLocalSchema", e);
        } catch(SAXNotRecognizedException e){
                // log("contextConfig.registerLocalSchema", e);
        } catch(SAXNotSupportedException e){
                // log("contextConfig.registerLocalSchema", e);
        }
        return digester;
    }

    /**
     * Turn on DTD and/or validation (based on the parser implementation)
     */
    protected void turnOnValidation(Digester digester){
        URL url = DigesterFactory.class.getResource(Constants.WebSchemaResourcePath_24);
        digester.setSchema(url.toString());
    }


    /** 
     * Turn on schema AND DTD validation on Xerces parser.
     */
    protected void turnOnXercesValidation(Digester digester){
        try{
            digester.setFeature(
                "http://apache.org/xml/features/validation/dynamic",
                true);
            digester.setFeature(
                "http://apache.org/xml/features/validation/schema",
                true);
        } catch(ParserConfigurationException e){
            // log("contextConfig.registerLocalSchema", e);
        } catch(SAXNotRecognizedException e){
            // log("contextConfig.registerLocalSchema", e);
        } catch(SAXNotSupportedException e){
            // log("contextConfig.registerLocalSchema", e);
        }
    }

    protected static final Logger _logger = LogFacade.getLogger();
}
