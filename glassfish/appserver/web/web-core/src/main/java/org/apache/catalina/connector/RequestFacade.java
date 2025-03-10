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

package org.apache.catalina.connector;

import org.apache.catalina.LogFacade;
import org.apache.catalina.Globals;
import org.apache.catalina.core.RequestFacadeHelper;
import org.apache.catalina.security.SecurityUtil;

import javax.servlet.*;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpUpgradeHandler;
import javax.servlet.http.Part;
import javax.servlet.http.PushBuilder;
import java.io.BufferedReader;
import java.io.IOException;
import java.security.AccessControlException;
import java.security.AccessController;
import java.security.PrivilegedAction;
import java.security.SecurityPermission;
import java.util.*;
import javax.servlet.http.HttpServletMapping;


/**
 * Facade class that wraps a Coyote request object.  
 * All methods are delegated to the wrapped request.
 *
 * @author Craig R. McClanahan
 * @author Remy Maucherat
 * @author Jean-Francois Arcand
 * @version $Revision: 1.7 $ $Date: 2007/08/01 19:04:28 $
 */
public class RequestFacade 
    implements HttpServletRequest {

    private static final ResourceBundle rb = LogFacade.getLogger().getResourceBundle();

        
    // ----------------------------------------------------------- DoPrivileged
    
    private final class GetAttributePrivilegedAction
            implements PrivilegedAction<Enumeration<String>> {
        
        public Enumeration<String> run() {
            return request.getAttributeNames();
        }            
    }
     
    
    private final class GetParameterMapPrivilegedAction
            implements PrivilegedAction<Map<String, String[]>> {
        
        public Map<String, String[]> run() {
            return request.getParameterMap();
        }        
    }    
    
    
    private final class GetRequestDispatcherPrivilegedAction
            implements PrivilegedAction<RequestDispatcher> {

        private String path;

        public GetRequestDispatcherPrivilegedAction(String path){
            this.path = path;
        }
        
        public RequestDispatcher run() {   
            return request.getRequestDispatcher(path);
        }           
    }    
    
    
    private final class GetParameterPrivilegedAction
            implements PrivilegedAction<String> {

        public String name;

        public GetParameterPrivilegedAction(String name){
            this.name = name;
        }

        public String run() {       
            return request.getParameter(name);
        }           
    }    
    
     
    private final class GetParameterNamesPrivilegedAction
            implements PrivilegedAction<Enumeration<String>> {
        
        public Enumeration<String> run() {          
            return request.getParameterNames();
        }           
    } 
    
    
    private final class GetParameterValuePrivilegedAction
            implements PrivilegedAction<String[]> {

        public String name;

        public GetParameterValuePrivilegedAction(String name){
            this.name = name;
        }

        public String[] run() {       
            return request.getParameterValues(name);
        }           
    }    
  
    
    private final class GetCookiesPrivilegedAction
            implements PrivilegedAction<Cookie[]> {
        
        public Cookie[] run() {       
            return request.getCookies();
        }           
    }      
    
    
    private final class GetCharacterEncodingPrivilegedAction
            implements PrivilegedAction<String> {
        
        public String run() {       
            return request.getCharacterEncoding();
        }           
    }   
        
    
    private final class GetHeadersPrivilegedAction
            implements PrivilegedAction<Enumeration<String>> {

        private String name;

        public GetHeadersPrivilegedAction(String name){
            this.name = name;
        }
        
        public Enumeration<String> run() {       
            return request.getHeaders(name);
        }           
    }    
        
    
    private final class GetHeaderNamesPrivilegedAction
            implements PrivilegedAction<Enumeration<String>> {

        public Enumeration<String> run() {       
            return request.getHeaderNames();
        }           
    }  
            
    
    private final class GetLocalePrivilegedAction
            implements PrivilegedAction<Locale> {

        public Locale run() {       
            return request.getLocale();
        }           
    }    
            
    
    private final class GetLocalesPrivilegedAction
            implements PrivilegedAction<Enumeration<Locale>> {

        public Enumeration<Locale> run() {       
            return request.getLocales();
        }           
    }    
    
    private final class GetSessionPrivilegedAction
            implements PrivilegedAction<HttpSession> {

        private boolean create;
        
        public GetSessionPrivilegedAction(boolean create){
            this.create = create;
        }
                
        public HttpSession run() {  
            return request.getSession(create);
        }           
    }

    private final class ChangeSessionIdPrivilegedAction
            implements PrivilegedAction<String> {

        public String run() {
            return request.changeSessionId();
        }
    }


    // ----------------------------------------------------------- Constructors


    /**
     * Construct a wrapper for the specified request.
     *
     * @param request The request to be wrapped
     */
    public RequestFacade(Request request) {
        this(request, false);
    }


    /**
     * Construct a wrapper for the specified request.
     *
     * @param request The request to be wrapped
     * @param maskDefaultContextMapping true if the fact that a request
     * received at the root context was mapped to a default-web-module will
     * be masked, false otherwise
     */
    public RequestFacade(Request request,
                         boolean maskDefaultContextMapping) {
        this.request = request;
        this.maskDefaultContextMapping = maskDefaultContextMapping;
        this.reqFacHelper = new RequestFacadeHelper(request);
    }


    // ----------------------------------------------- Class/Instance Variables


    private static final SecurityPermission
        GET_UNWRAPPED_COYOTE_REQUEST_PERMISSION =
            new SecurityPermission("getUnwrappedCoyoteRequest");




    /**
     * The wrapped request.
     */
    protected Request request = null;


    /*
     * True if the fact that a request received at the root context was
     * mapped to a default-web-module will be masked, false otherwise.
     *
     * For example, if set to true, this request facade's getContextPath()
     * method will return "/", rather than the context root of the
     * default-web-module, for requests received at the root context that
     * were mapped to a default-web-module.
     */
    private boolean maskDefaultContextMapping = false;

    private RequestFacadeHelper reqFacHelper = null;
 

    // --------------------------------------------------------- Public Methods
   
    
    /**
    * Prevent cloning the facade.
    */
    protected Object clone()
        throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }
    
    
    /**
     * Clear facade.
     */
    public void clear() {
        request = null;
        if (reqFacHelper != null) {
            reqFacHelper.clear();
        }
        reqFacHelper = null;
    }


    RequestFacadeHelper getRequestFacadeHelper() {
        return reqFacHelper;
    }
    

    // ------------------------------------------------- ServletRequest Methods

    @Override
    public Object getAttribute(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getAttribute(name);
    }

    @Override
    public Enumeration<String> getAttributeNames() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetAttributePrivilegedAction());        
        } else {
            return request.getAttributeNames();
        }
    }

    @Override
    public String getCharacterEncoding() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetCharacterEncodingPrivilegedAction());
        } else {
            return request.getCharacterEncoding();
        }         
    }

    @Override
    public void setCharacterEncoding(String env)
            throws java.io.UnsupportedEncodingException {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        request.setCharacterEncoding(env);
    }

    @Override
    public int getContentLength() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getContentLength();
    }

    @Override
    public long getContentLengthLong() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getContentLengthLong();
    }

    @Override
    public String getContentType() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getContentType();
    }

    @Override
    public ServletInputStream getInputStream() throws IOException {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getInputStream();
    }
    
    public HttpServletMapping getHttpServletMapping() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getHttpServletMapping();
    }
    
    public String getParameter(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetParameterPrivilegedAction(name));
        } else {
            return request.getParameter(name);
        }
    }

    @Override
    public Enumeration<String> getParameterNames() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetParameterNamesPrivilegedAction());
        } else {
            return request.getParameterNames();
        }
    }

    @Override
    public String[] getParameterValues(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        String[] ret = null;

        /*
         * Clone the returned array only if there is a security manager
         * in place, so that performance won't suffer in the non-secure case
         */
        if (SecurityUtil.isPackageProtectionEnabled()){
            ret = AccessController.doPrivileged(
                new GetParameterValuePrivilegedAction(name));
            if (ret != null) {
                ret = (String[]) ret.clone();
            }
        } else {
            ret = request.getParameterValues(name);
        }

        return ret;
    }

    @Override
    public Map<String, String[]> getParameterMap() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetParameterMapPrivilegedAction());        
        } else {
            return request.getParameterMap();
        }
    }

    @Override
    public String getProtocol() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getProtocol();
    }

    @Override
    public String getScheme() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getScheme();
    }

    @Override
    public String getServerName() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getServerName();
    }

    @Override
    public int getServerPort() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getServerPort();
    }

    @Override
    public BufferedReader getReader() throws IOException {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getReader();
    }

    @Override
    public String getRemoteAddr() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRemoteAddr();
    }

    @Override
    public String getRemoteHost() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRemoteHost();
    }

    @Override
    public void setAttribute(String name, Object o) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        request.setAttribute(name, o);
    }

    @Override
    public void removeAttribute(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        request.removeAttribute(name);
    }

    @Override
    public Locale getLocale() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetLocalePrivilegedAction());
        } else {
            return request.getLocale();
        }        
    }

    @Override
    public Enumeration<Locale> getLocales() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetLocalesPrivilegedAction());
        } else {
            return request.getLocales();
        }        
    }

    @Override
    public boolean isSecure() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isSecure();
    }

    @Override
    public RequestDispatcher getRequestDispatcher(String path) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetRequestDispatcherPrivilegedAction(path));
        } else {
            return request.getRequestDispatcher(path);
        }
    }

    @Override
    public String getRealPath(String path) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRealPath(path);
    }

    @Override
    public String getAuthType() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getAuthType();
    }

    @Override
    public Cookie[] getCookies() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        Cookie[] ret = null;

        /*
         * Clone the returned array only if there is a security manager
         * in place, so that performance won't suffer in the non-secure case
         */
        if (SecurityUtil.isPackageProtectionEnabled()){
            ret = AccessController.doPrivileged(
                new GetCookiesPrivilegedAction());
            if (ret != null) {
                ret = (Cookie[]) ret.clone();
            }
        } else {
            ret = request.getCookies();
        }

        return ret;
    }

    @Override
    public long getDateHeader(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getDateHeader(name);
    }

    @Override
    public String getHeader(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getHeader(name);
    }

    @Override
    public Enumeration<String> getHeaders(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetHeadersPrivilegedAction(name));
        } else {
            return request.getHeaders(name);
        }         
    }

    @Override
    public Enumeration<String> getHeaderNames() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.doPrivileged(
                new GetHeaderNamesPrivilegedAction());
        } else {
            return request.getHeaderNames();
        }             
    }

    @Override
    public int getIntHeader(String name) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getIntHeader(name);
    }

    @Override
    public Map<String, String> getTrailerFields() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getTrailerFields();
    }

    @Override
    public boolean isTrailerFieldsReady() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isTrailerFieldsReady();
    }

    @Override
    public String getMethod() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getMethod();
    }

    @Override
    public String getPathInfo() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getPathInfo();
    }

    @Override
    public String getPathTranslated() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getPathTranslated();
    }


    /**
     * Gets the servlet context to which this servlet request was last
     * dispatched.
     *
     * @return the servlet context to which this servlet request was last
     * dispatched
     */
    @Override
    public ServletContext getServletContext() {
        return request.getServletContext();
    }

    @Override
    public String getContextPath() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getContextPath(maskDefaultContextMapping);
    }


    public String getContextPath(boolean maskDefaultContextMapping) {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getContextPath(maskDefaultContextMapping);
    }

    @Override
    public String getQueryString() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getQueryString();
    }

    @Override
    public String getRemoteUser() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRemoteUser();
    }

    @Override
    public boolean isUserInRole(String role) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isUserInRole(role);
    }

    @Override
    public java.security.Principal getUserPrincipal() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getUserPrincipal();
    }

    @Override
    public String getRequestedSessionId() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRequestedSessionId();
    }

    @Override
    public String getRequestURI() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRequestURI(maskDefaultContextMapping);
    }

    @Override
    public StringBuffer getRequestURL() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRequestURL(maskDefaultContextMapping);
    }

    @Override
    public String getServletPath() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getServletPath();
    }

    @Override
    public HttpSession getSession(boolean create) {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.
                doPrivileged(new GetSessionPrivilegedAction(create));
        } else {
            return request.getSession(create);
        }
    }

    @Override
    public HttpSession getSession() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return getSession(true);
    }

    @Override
    public String changeSessionId() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        if (SecurityUtil.isPackageProtectionEnabled()){
            return AccessController.
                    doPrivileged(new ChangeSessionIdPrivilegedAction());
        } else {
            return request.changeSessionId();
        }
    }

    @Override
    public boolean isRequestedSessionIdValid() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isRequestedSessionIdValid();
    }

    @Override
    public boolean isRequestedSessionIdFromCookie() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isRequestedSessionIdFromCookie();
    }

    @Override
    public boolean isRequestedSessionIdFromURL() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isRequestedSessionIdFromURL();
    }

    @Override
    public boolean isRequestedSessionIdFromUrl() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.isRequestedSessionIdFromURL();
    }

    @Override
    public String getLocalAddr() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getLocalAddr();
    }

    @Override
    public String getLocalName() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getLocalName();
    }

    @Override
    public int getLocalPort() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getLocalPort();
    }

    @Override
    public int getRemotePort() {

        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }

        return request.getRemotePort();
    }

    @Override
    public DispatcherType getDispatcherType() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getDispatcherType();
    }


    /**
     * Starts async processing on this request.
     */
    @Override
    public AsyncContext startAsync() throws IllegalStateException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.startAsync();
    }


    /**
     * Starts async processing on this request.
     */
    @Override
    public AsyncContext startAsync(ServletRequest sreq,
                                   ServletResponse sresp)
            throws IllegalStateException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.startAsync(sreq, sresp);
    }
        

    /**
     * Checks whether async processing has started on this request.
     */
    @Override
    public boolean isAsyncStarted() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.isAsyncStarted();
    }


    /**
     * Checks whether this request supports async.
     */
    @Override
    public boolean isAsyncSupported() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.isAsyncSupported();
    }


    /**
     * Gets the AsyncContext of this request.
     */
    @Override
    public AsyncContext getAsyncContext() {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getAsyncContext();
    }


    @Override
    public Collection<Part> getParts() throws IOException, ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getParts();
    }


    @Override
    public Part getPart(String name) throws IOException, ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.getPart(name);
    }

    @Override
    public boolean authenticate(HttpServletResponse response)
            throws IOException, ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.authenticate(response);
    }

    @Override
    public void login(String username, String password)
            throws ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        request.login(username, password);
    }

    @Override
    public void logout() throws ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        request.logout();
    }

    @Override
    public <T extends HttpUpgradeHandler> T upgrade(Class<T> handlerClass) throws IOException, ServletException {
        if (request == null) {
            throw new IllegalStateException(rb.getString(LogFacade.CANNOT_USE_REQUEST_OBJECT_OUTSIDE_SCOPE_EXCEPTION));
        }
        return request.upgrade(handlerClass);
    }

    @Override
    public PushBuilder newPushBuilder() {
        return request.newPushBuilder();
    }


    //START S1AS 4703023
    /**
     * Return the original <code>CoyoteRequest</code> object.
     */
    public Request getUnwrappedCoyoteRequest()
        throws AccessControlException {

        // tomcat does not have any Permission types so instead of
        // creating a TomcatPermission for this, use SecurityPermission.
        if (Globals.IS_SECURITY_ENABLED) {
            AccessController.checkPermission(
                GET_UNWRAPPED_COYOTE_REQUEST_PERMISSION);
        }

        return request;
    }
    //END S1AS 4703023
}
