/*
 * Copyright (c) 2011-2018 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2004 The Apache Software Foundation
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.catalina.filters;


/**
 * Manifest constants for this Java package.
 *
 *
 * @author Craig R. McClanahan
 * @version $Id: Constants.java 956385 2010-06-20 18:59:51Z markt $
 */

public final class Constants {

    public static final String Package = "org.apache.catalina.filters";
    
    public static final String CSRF_NONCE_SESSION_ATTR_NAME =
        "org.apache.catalina.filters.CSRF_NONCE";
    
    public static final String CSRF_NONCE_REQUEST_PARAM =
        "org.apache.catalina.filters.CSRF_NONCE";

    public static final String METHOD_GET = "GET";
}
