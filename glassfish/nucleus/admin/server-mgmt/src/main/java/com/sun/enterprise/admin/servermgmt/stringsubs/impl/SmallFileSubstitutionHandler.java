/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2013-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.admin.servermgmt.stringsubs.impl;

import java.io.BufferedWriter;
import java.io.CharArrayReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.util.logging.Level;

/**
 * Creates {@link Reader} and {@link Writer} for the String substitution file.
 * Its handles the small files which can be processed differently for faster
 * and better performance comparative to larger files.
 */
public class SmallFileSubstitutionHandler extends FileSubstitutionHandler {
    /**
     * Constructs the {@link SmallFileSubstitutionHandler} for the given input file.
     *
     * @param file Input file.
     * @throws FileNotFoundException If file is not found.
     */
    public SmallFileSubstitutionHandler(File file)throws FileNotFoundException {
        super(file);
    }

    @Override
    public Reader getReader() {
        try {
            if (_reader == null) {
                char[] buffer = new char[(int)_inputFile.length()];
                int count = 0;
                try {
                    _reader = new InputStreamReader(new FileInputStream(_inputFile));
                    count = _reader.read(buffer);
                } finally {
                    _reader.close();
                }
                _reader = new CharArrayReader(buffer, 0, count);
            }
        } catch (IOException e) {
            _logger.log(Level.WARNING, _strings.get("invalidFileLocation", _inputFile.getAbsolutePath()), e);
        }
        return _reader;
    }

    @Override
    public Writer getWriter() {
        try {
            _writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(_inputFile)));
        } catch (FileNotFoundException e) {
            _logger.log(Level.WARNING, _strings.get("invalidFileLocation", _inputFile.getAbsolutePath()), e);
        }
        return _writer;
    }
}
