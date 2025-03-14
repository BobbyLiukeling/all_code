/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2003-2018 Oracle and/or its affiliates. All rights reserved.
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

/*
 * $Header: /m/jws/appserv-tests/devtests/ee/admin/mbeanapi/samples/samples/amx/LineReaderImpl.java,v 1.1 2005/01/27 21:34:04 llc Exp $
 * $Revision: 1.1 $
 * $Date: 2005/01/27 21:34:04 $
 */
 
package samples.amx;


import java.io.InputStream;
import java.io.InputStreamReader;

/**
	Reads a line from the specified input stream, outputs
	the prompt to System.out.
 */
public class LineReaderImpl
{
	final InputStreamReader	mInputStreamReader;
	
		public 
	LineReaderImpl( InputStream inputStream )
	{
		mInputStreamReader	= new InputStreamReader( inputStream );
	}

		public String
	readLine( String prompt )
		throws java.io.IOException
	{
		final StringBuffer	line	= new StringBuffer();
		
		if ( prompt != null )
		{
			System.out.print( prompt );
		}
		
		while ( true )
		{
			final int	value	= mInputStreamReader.read();
			if ( value < 0 )
			{
				if ( line.length() != 0 )
				{
					// read a line but saw EOF before a newline
					break;
				}
				return( null );
			}
			
			final char	theChar	= (char)value;
			if ( theChar == '\n' )
				break;
			
			line.append( theChar );
		}
		
		return( line.toString().trim() );
	}
}




