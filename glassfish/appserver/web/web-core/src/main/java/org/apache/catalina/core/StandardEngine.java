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

package org.apache.catalina.core;

import org.apache.catalina.*;
import org.apache.catalina.realm.JAASRealm;
import static com.sun.logging.LogCleanerUtil.neutralizeForLog;

import javax.management.MalformedObjectNameException;
import javax.management.ObjectName;
import java.util.logging.Level;

/**
 * Standard implementation of the <b>Engine</b> interface.  Each
 * child container must be a Host implementation to process the specific
 * fully qualified host name of that virtual host.
 *
 * @author Craig R. McClanahan
 * @version $Revision: 1.5 $ $Date: 2006/03/12 01:27:01 $
 */

public class StandardEngine
    extends ContainerBase
    implements Engine {



    // ----------------------------------------------------------- Constructors


    /**
     * Create a new StandardEngine component with the default basic Valve.
     */
    public StandardEngine() {

        super();
        pipeline.setBasic(new StandardEngineValve());
        /* Set the jmvRoute using the system property jvmRoute */
        try {
            setJvmRoute(System.getProperty("jvmRoute"));
        } catch(Exception ex) {
        }
        // By default, the engine will hold the reloading thread
        backgroundProcessorDelay = 10;

    }


    // ----------------------------------------------------- Instance Variables


    /**
     * Host name to use when no server host, or an unknown host,
     * is specified in the request.
     */
    private String defaultHost = null;


    /**
     * The descriptive information string for this implementation.
     */
    private static final String info =
        "org.apache.catalina.core.StandardEngine/1.0";


    /**
     * The <code>Service</code> that owns this Engine, if any.
     */
    private Service service = null;

    /** Allow the base dir to be specified explicitly for
     * each engine. In time we should stop using catalina.base property -
     * otherwise we loose some flexibility.
     */
    private String baseDir = null;

    /**
     * The JVM Route ID for this Tomcat instance. All Route ID's must be unique
     * across the cluster.
     */
    private String jvmRouteId;


    // ------------------------------------------------------------- Properties

    /** Provide a default in case no explicit configuration is set
     *
     * @return configured realm, or a JAAS realm by default
     */
    public Realm getRealm() {
        Realm configured=super.getRealm();
        // If no set realm has been called - default to JAAS
        // This can be overridden at engine, context and host level  
        if( configured==null ) {
            configured=new JAASRealm();
            this.setRealm( configured );
        }
        return configured;
    }


    /**
     * Return the default host.
     */
    public String getDefaultHost() {

        return (defaultHost);

    }


    /**
     * Set the default host.
     *
     * @param host The new default host
     */
    public void setDefaultHost(String host) {

        String oldDefaultHost = this.defaultHost;
        if (host == null) {
            this.defaultHost = null;
        } else {
            // START OF PE 4989789
            //this.defaultHost = host.toLowerCase();
            this.defaultHost = host;
            // END OF PE 4989789
        }
        support.firePropertyChange("defaultHost", oldDefaultHost,
                                   this.defaultHost);

    }
    
    public void setName(String name ) {
        if( domain != null ) {
            // keep name==domain, ignore override
            // we are already registered
            super.setName( domain );
            return;
        }
        // The engine name is used as domain
        domain=name; // XXX should we set it in init() ? It shouldn't matter
        super.setName( name );
    }


    /**
     * Set the cluster-wide unique identifier for this Engine.
     * This value is only useful in a load-balancing scenario.
     * <p>
     * This property should not be changed once it is set.
     */
    public void setJvmRoute(String routeId) {
        jvmRouteId = routeId;
    }


    /**
     * Retrieve the cluster-wide unique identifier for this Engine.
     * This value is only useful in a load-balancing scenario.
     */
    public String getJvmRoute() {
        return jvmRouteId;
    }


    /**
     * Return the <code>Service</code> with which we are associated (if any).
     */
    public Service getService() {

        return (this.service);

    }


    /**
     * Set the <code>Service</code> with which we are associated (if any).
     *
     * @param service The service that owns this Engine
     */
    public void setService(Service service) {
        this.service = service;
    }

    public String getBaseDir() {
        if( baseDir==null ) {
            baseDir=System.getProperty("catalina.base");
        }
        if( baseDir==null ) {
            baseDir=System.getProperty("catalina.home");
        }
        return baseDir;
    }

    public void setBaseDir(String baseDir) {
        this.baseDir = baseDir;
    }

    // --------------------------------------------------------- Public Methods


    /**
     * Add a child Container, only if the proposed child is an implementation
     * of Host.
     *
     * @param child Child container to be added
     */
    public void addChild(Container child) {

        if (!(child instanceof Host))
            throw new IllegalArgumentException(rb.getString(LogFacade.CHILD_OF_ENGINE_MUST_BE_HOST_EXCEPTION));
        super.addChild(child);

    }


    /**
     * Return descriptive information about this Container implementation and
     * the corresponding version number, in the format
     * <code>&lt;description&gt;/&lt;version&gt;</code>.
     */
    public String getInfo() {

        return (info);

    }

    /**
     * Disallow any attempt to set a parent for this Container, since an
     * Engine is supposed to be at the top of the Container hierarchy.
     *
     * @param container Proposed parent Container
     */
    public void setParent(Container container) {

        throw new IllegalArgumentException
                (rb.getString(LogFacade.CANNOT_HAVE_PARENT_CONTAINER_EXCEPTION));

    }


    /* CR 6368085
    private boolean initialized=false;
    */
    
    public void init() {
        if( initialized ) return;
        /* CR 6368085
        initialized=true;
        */

        if( oname==null ) {
            // not registered in JMX yet - standalone mode
            try {
                if (domain==null) {
                    domain=getName();
                }
                if (log.isLoggable(Level.FINE)) {
                    log.log(Level.FINE, "Register " + neutralizeForLog(domain));
                }
                oname=new ObjectName(domain + ":type=Engine");
                controller=oname;
            } catch (Throwable t) {
                log.log(Level.INFO, LogFacade.ERROR_REGISTERING_EXCEPTION, t);
            }
        }
        
        if( service==null ) {
            // for consistency...: we are probably in embedded mode
            try {
                service=new StandardService();
                service.setContainer( this );
                service.initialize();
                // Use same name for Service
                service.setName(getName());
            } catch( Throwable t ) {
                log.log(Level.SEVERE, t.toString());
            }
        }
        // START CR 6368085
        initialized = true;
        // END CR 6368085
        
    }

    /* CR 6368085    
    public void destroy() throws LifecycleException {
    */
    // START CR 6368085
    public void destroy() throws Exception {
    // END CR 6368085
        if( ! initialized ) return;
        /* CR 6368085
        initialized=false;
        */
        // START CR 6368085
        super.destroy();
        // END CR 6368085

        // if we created it, make sure it's also destroyed
        ((StandardService)service).destroy();
    }
    
    /**
     * Start this Engine component.
     *
     * @exception LifecycleException if a startup error occurs
     */
    public void start() throws LifecycleException {
        if( started ) {
            return;
        }
        if( !initialized ) {
            init();
        }

        /* PWC 6296256
        // Log our server identification information
        log.info( "Starting Servlet Engine: " + ServerInfo.getServerInfo());
        */
        // START PWC 6296256
        if (log.isLoggable(Level.FINE)) {
            log.log(Level.FINE, "Starting Servlet Engine");
        }
        // END PWC 6296256

        // Standard container startup
        super.start();

    }
    
    public void stop() throws LifecycleException {
        super.stop();
    }


    /**
     * Return a String representation of this component.
     */
    public String toString() {

        StringBuilder sb = new StringBuilder("StandardEngine[");
        sb.append(getName());
        sb.append("]");
        return (sb.toString());

    }


    // ------------------------------------------------------ Protected Methods


    // FIXME Remove -- not used 
    public ObjectName getParentName() throws MalformedObjectNameException {
        if (getService()==null) {
            return null;
        }
        String name = getService().getName();
        ObjectName serviceName=new ObjectName(domain +
                        ":type=Service,serviceName="+name);
        return serviceName;                
    }
    
    public ObjectName createObjectName(String domain, ObjectName parent)
        throws Exception
    {
        if (log.isLoggable(Level.FINE))
            log.log(Level.FINE, "Create ObjectName " + domain + " " + parent);
        return new ObjectName( domain + ":type=Engine");
    }
    
    public String getDomain() {
        if (domain!=null) {
            return domain;
        } else { 
            return getName();
        }
    }
    
    public void setDomain(String domain) {
        this.domain = domain;
    }
    
}
