/*
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
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

package org.apache.catalina.fileupload;

import java.io.IOException;
import java.io.OutputStream;


/**
 * An output stream which triggers an event when a specified number of bytes of
 * data have been written to it. The event can be used, for example, to throw
 * an exception if a maximum has been reached, or to switch the underlying
 * stream type when the threshold is exceeded.
 * <p>
 * This class overrides all <code>OutputStream</code> methods. However, these
 * overrides ultimately call the corresponding methods in the underlying output
 * stream implementation.
 * <p>
 * NOTE: This implementation may trigger the event <em>before</em> the threshold
 * is actually reached, since it triggers when a pending write operation would
 * cause the threshold to be exceeded.
 *
 * @author <a href="mailto:martinc@apache.org">Martin Cooper</a>
 *
 * @version $Id: ThresholdingOutputStream.java 540714 2007-05-22 19:39:44Z niallp $
 */
abstract class ThresholdingOutputStream
    extends OutputStream
{

    // ----------------------------------------------------------- Data members


    /**
     * The threshold at which the event will be triggered.
     */
    private int threshold;


    /**
     * The number of bytes written to the output stream.
     */
    private long written;


    /**
     * Whether or not the configured threshold has been exceeded.
     */
    private boolean thresholdExceeded;


    // ----------------------------------------------------------- Constructors


    /**
     * Constructs an instance of this class which will trigger an event at the
     * specified threshold.
     *
     * @param threshold The number of bytes at which to trigger an event.
     */
    public ThresholdingOutputStream(int threshold)
    {
        this.threshold = threshold;
    }


    // --------------------------------------------------- OutputStream methods


    /**
     * Writes the specified byte to this output stream.
     *
     * @param b The byte to be written.
     *
     * @exception IOException if an error occurs.
     */
    public void write(int b) throws IOException
    {
        checkThreshold(1);
        getStream().write(b);
        written++;
    }


    /**
     * Writes <code>b.length</code> bytes from the specified byte array to this
     * output stream.
     *
     * @param b The array of bytes to be written.
     *
     * @exception IOException if an error occurs.
     */
    public void write(byte b[]) throws IOException
    {
        checkThreshold(b.length);
        getStream().write(b);
        written += b.length;
    }


    /**
     * Writes <code>len</code> bytes from the specified byte array starting at
     * offset <code>off</code> to this output stream.
     *
     * @param b   The byte array from which the data will be written.
     * @param off The start offset in the byte array.
     * @param len The number of bytes to write.
     *
     * @exception IOException if an error occurs.
     */
    public void write(byte b[], int off, int len) throws IOException
    {
        checkThreshold(len);
        getStream().write(b, off, len);
        written += len;
    }


    /**
     * Flushes this output stream and forces any buffered output bytes to be
     * written out.
     *
     * @exception IOException if an error occurs.
     */
    public void flush() throws IOException
    {
        getStream().flush();
    }


    /**
     * Closes this output stream and releases any system resources associated
     * with this stream.
     *
     * @exception IOException if an error occurs.
     */
    public void close() throws IOException
    {
        try
        {
            flush();
        }
        catch (IOException ignored)
        {
            // ignore
        }
        getStream().close();
    }


    // --------------------------------------------------------- Public methods


    /**
     * Returns the threshold, in bytes, at which an event will be triggered.
     *
     * @return The threshold point, in bytes.
     */
    public int getThreshold()
    {
        return threshold;
    }


    /**
     * Returns the number of bytes that have been written to this output stream.
     *
     * @return The number of bytes written.
     */
    public long getByteCount()
    {
        return written;
    }


    /**
     * Determines whether or not the configured threshold has been exceeded for
     * this output stream.
     *
     * @return <code>true</code> if the threshold has been reached;
     *         <code>false</code> otherwise.
     */
    public boolean isThresholdExceeded()
    {
        return (written > threshold);
    }


    // ------------------------------------------------------ Protected methods


    /**
     * Checks to see if writing the specified number of bytes would cause the
     * configured threshold to be exceeded. If so, triggers an event to allow
     * a concrete implementation to take action on this.
     *
     * @param count The number of bytes about to be written to the underlying
     *              output stream.
     *
     * @exception IOException if an error occurs.
     */
    protected void checkThreshold(int count) throws IOException
    {
        if (!thresholdExceeded && (written + count > threshold))
        {
            thresholdExceeded = true;
            thresholdReached();
        }
    }

    /**
     * Resets the byteCount to zero.  You can call this from 
     * {@link #thresholdReached()} if you want the event to be triggered again. 
     */
    protected void resetByteCount() 
    {
        this.thresholdExceeded = false;
        this.written = 0;
    }

    // ------------------------------------------------------- Abstract methods


    /**
     * Returns the underlying output stream, to which the corresponding
     * <code>OutputStream</code> methods in this class will ultimately delegate.
     *
     * @return The underlying output stream.
     *
     * @exception IOException if an error occurs.
     */
    protected abstract OutputStream getStream() throws IOException;


    /**
     * Indicates that the configured threshold has been reached, and that a
     * subclass should take whatever action necessary on this event. This may
     * include changing the underlying output stream.
     *
     * @exception IOException if an error occurs.
     */
    protected abstract void thresholdReached() throws IOException;
}
