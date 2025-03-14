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

package com.sun.enterprise.admin.util.cache;

import com.sun.enterprise.admin.util.CachedCommandModel;
import com.sun.enterprise.admin.util.CachedCommandModelTest;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import org.glassfish.api.admin.CommandModel;
import static org.junit.Assert.*;
import org.junit.Test;

/**
 *
 * @author mmares
 */
public class AdminCacheUtilsTest {
    
    private AdminCacheUtils acu = AdminCacheUtils.getInstance();
    
    public AdminCacheUtilsTest() {
    }

//    @BeforeClass
//    public static void setUpClass() throws Exception {
//    }

//    @AfterClass
//    public static void tearDownClass() throws Exception {
//    }
    
    @Test
    public void testSimpleGetProvider() throws IOException {
        DataProvider provider;
        byte[] data;
        //String
        Object o = "The Man Who Sold The World";
        assertNotNull(provider = acu.getProvider(o.getClass()));
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        provider.writeToStream(o, baos);
        assertNotNull(data = baos.toByteArray());
        assertTrue(o.equals(provider.toInstance(new ByteArrayInputStream(data), 
                o.getClass())));
        //byte array
        o = "The Man Who Sold The World".getBytes();
        assertNotNull(provider = acu.getProvider(o.getClass()));
        baos = new ByteArrayOutputStream();
        provider.writeToStream(o, baos);
        assertNotNull(data = baos.toByteArray());
        assertArrayEquals((byte[]) o, data);
        assertArrayEquals((byte[]) o, (byte[]) provider.toInstance(
                new ByteArrayInputStream(data), byte[].class));
    }
    
    @Test
    public void testGetProvider4CommandModel() throws Exception {
        DataProvider provider;
        byte[] data;
        assertNotNull(provider = acu.getProvider(CommandModel.class));
        CachedCommandModel beatles1 = CachedCommandModelTest.createBeateles();
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        provider.writeToStream(beatles1, baos);
        assertNotNull(data = baos.toByteArray());
        System.out.println("BTW: " + new String(data, "UTF-8"));
        CachedCommandModel beatles2 = (CachedCommandModel) provider.toInstance(
                new ByteArrayInputStream(data), CachedCommandModel.class);
        beatles2.setETag(null);
        assertEquals(beatles1.getETag(), CachedCommandModel.computeETag(beatles2));
    }

    @Test
    public void testValidateKey() {
        assertTrue(acu.validateKey("kurt"));
        assertTrue(acu.validateKey("kurt.cobain"));
        assertTrue(acu.validateKey("kurt-cobain"));
        assertTrue(acu.validateKey("kurt_cobain"));
        assertFalse(acu.validateKey("kurt.cobain@nirvana"));
        assertFalse(acu.validateKey("kurt.cobain#nirvana"));
        assertTrue(acu.validateKey("kurt.cobain/smells.like.teen.spirit"));
        assertFalse(acu.validateKey("/kurt.cobain/smells.like.teen.spirit"));
        assertTrue(acu.validateKey("kurt.cobain/smells.like.teen.spirit/"));
    }

}
