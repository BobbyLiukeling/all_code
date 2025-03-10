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

package org.glassfish.admin.amx.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
The API that should be used to output from a Cmd running within the framework.
 */
public final class FileUtils
{
    private FileUtils()
    {
    }

    public static String fileToString(final File src)
            throws FileNotFoundException, IOException
    {
        return fileToString(src, 32 * 1024);
    }

    public static String fileToString(final File src, final int readBufferSize)
            throws FileNotFoundException, IOException
    {
        final long length = src.length();
        if (length > 1024 * 1024 * 1024)
        {
            throw new IllegalArgumentException();
        }

        final char[] readBuffer = new char[readBufferSize];

        final StringBuilder result = new StringBuilder((int) length);
        FileReader in = null;

        try
        {
            in = new FileReader(src);
            while (true)
            {
                final int numRead = in.read(readBuffer, 0, readBufferSize);
                if (numRead < 0)
                {
                    break;
                }

                result.append(readBuffer, 0, numRead);
            }
        }
        finally
        {
            if (in != null) {
                in.close();
            }
        }

        return (result.toString());
    }

    public static void stringToFile(final String s, final File dest)
            throws IOException
    {
        final FileWriter out = new FileWriter(dest);

        try
        {
            out.write(s);
        }
        finally
        {
            out.close();
        }
    }

};


