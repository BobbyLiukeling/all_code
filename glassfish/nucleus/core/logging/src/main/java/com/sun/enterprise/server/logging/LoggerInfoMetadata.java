/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2012-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.server.logging;

import java.util.Set;
import java.util.Locale;

import org.jvnet.hk2.annotations.Contract;

@Contract
public interface LoggerInfoMetadata {

    /**
     * Provides a set of logger names for which additional metadata is available.
     * @return
     */
    public Set<String> getLoggerNames();
    
    /**
     * Gets the description for the named logger.
     * @return
     */
    public String getDescription(String logger);
    
    /**
     * Get description for the named logger for given locale
     * @param logger
     * @param locale
     * @return
     */
    public String getDescription(String logger, Locale locale);
    
    /**
     * Gets the subsystem grouping to which a specified logger belongs.
     * @param logger
     * @return
     */
    public String getSubsystem(String logger);
    
    /**
     * Gets whether the specified logger is to be included in the public doc.
     * @param logger
     * @return <code>true</code> if the logger is to be documented otherwise
     * <code>false</code> for internal fine-grained loggers.
     */
    public boolean isPublished(String logger);
    
}
