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

package com.sun.enterprise.admin.monitor.stats;
import org.glassfish.j2ee.statistics.Stats;
import org.glassfish.j2ee.statistics.CountStatistic;
import org.glassfish.j2ee.statistics.BoundedRangeStatistic;

/** A Stats interface to represent the statistical data exposed by an EJB Bean Pool.
 * These are based on the statistics exposed in S1AS7.0. 
 * All the EJB Pool implementations should expose statistical data by implementing this interface.
 * @author Muralidhar Vempaty
 * @author Kedar Mhaswade
 * @since S1AS8.0
 * @version 1.0
 */

public interface EJBPoolStats extends Stats {

	/** Returns the statistical information about the number of EJBs in the associated pool, as an instance of BoundedRangeStatistic.
	 * This returned value gives an idea about how the pool is changing.
	 * @return		an instance of {@link BoundedRangeStatistic}
     */
    public BoundedRangeStatistic getNumBeansInPool();
    
    /** Returns the number of threads waiting for free Beans, as an instance of CountStatistic.
	 * This indicates the congestion of requests.
	 * @return		an instance of {@link BoundedRangeStatistic}
     */
    public BoundedRangeStatistic getNumThreadsWaiting();
    
    /** Returns the number of Beans created in associated pool so far over time, since the gathering of data started, as a CountStatistic.
	 * @return		an instance of {@link CountStatistic}
     */
    public CountStatistic getTotalBeansCreated();
    
    /** Returns the number of Beans destroyed from associated pool so far over time, since the gathering of data started, as a CountStatistic.
	 * @return		an instance of {@link CountStatistic}
     */
    public CountStatistic getTotalBeansDestroyed();
    
    /** Returns the maximum number of messages to load into a JMS session, at a time, as a CountStatistic.
	 * @return		an instance of {@link CountStatistic}
     */
    public CountStatistic getJmsMaxMessagesLoad();
}
