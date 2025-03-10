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

package com.sun.jdo.spi.persistence.utility;

import java.util.*;
import java.lang.ref.*;

/**
 * A weak HashSet. An element stored in the WeakHashSet might be garbage collected, 
 * if there is no strong reference to this element. 
 */
public class WeakHashSet 
    extends HashSet
{
    /**
     * Helps to detect garbage collected values.
     */
    ReferenceQueue queue = new ReferenceQueue();
    
    /**
     * Returns an iterator over the elements in this set.  The elements
     * are returned in no particular order.
     *
     * @return an Iterator over the elements in this set.
     */
    public Iterator iterator ()
    {
        // remove garbage collected elements
        processQueue();

        // get an iterator of the superclass WeakHashSet
        final Iterator i = super.iterator();

        return new Iterator () {
            public boolean hasNext () 
            { 
                return i.hasNext(); 
            }
            
            public Object next () 
            {
                // unwrap the element
                return getReferenceObject((WeakReference)i.next()); 
            }
            
            public void remove () 
            {
                // remove the element from the HashSet
                i.remove();
            }
        };
    }
    
    /**
     * Returns <code>true</code> if this set contains the specified element.
     *
     * @param o element whose presence in this set is to be tested.
     * @return <code>true</code> if this set contains the specified element.
     */
    public boolean contains (Object o)
    {
        return super.contains(WeakElement.create(o));
    }

    /**
     * Adds the specified element to this set if it is not already
     * present.
     *
     * @param o element to be added to this set.
     * @return <code>true</code> if the set did not already contain the specified
     * element.
     */
    public boolean add (Object o)
    {
        processQueue();
        return super.add(WeakElement.create(o, this.queue));
    }
    
    /**
     * Removes the given element from this set if it is present.
     *
     * @param o object to be removed from this set, if present.
     * @return <code>true</code> if the set contained the specified element.
     */
    public boolean remove (Object o)
    {
        boolean ret = super.remove(WeakElement.create(o));
        processQueue();
        return ret;
    }

    /**
     * A convenience method to return the object held by the 
     * weak reference or <code>null</code> if it does not exist.
     */
    private final Object getReferenceObject (WeakReference ref)
    {
        return ((ref != null) ? ref.get() : null);
    }
    
    /**
     * Removes all garbage collected values with their keys from the map.
     * Since we don't know how much the ReferenceQueue.poll() operation
     * costs, we should call it only in the put() method.
     */
    private final void processQueue ()
    {
        WeakElement wv = null;
        
        while  ((wv = (WeakElement)this.queue.poll()) != null)
        {
            super.remove(wv);
        }
    }
    
    /**
     * A WeakHashSet stores objects of class WeakElement. 
     * A WeakElement wraps the element that should be stored in the WeakHashSet. 
     * WeakElement inherits from java.lang.ref.WeakReference. 
     * It redefines equals and hashCode which delegate to the corresponding methods 
     * of the wrapped element.
     */
    static private class WeakElement 
        extends WeakReference 
    {
        private int hash;	/* Hashcode of key, stored here since the key
                               may be tossed by the GC */
        
        private WeakElement (Object o) 
        {
            super(o);
            hash = o.hashCode();
        }

        private WeakElement (Object o, ReferenceQueue q) 
        {
            super(o, q);
            hash = o.hashCode();
        }

        private static WeakElement create (Object o) 
        {
            return (o == null) ? null : new WeakElement(o);
        }

        private static WeakElement create (Object o, ReferenceQueue q) 
        {
            return (o == null) ? null : new WeakElement(o, q);
        }

        /* A WeakElement is equal to another WeakElement iff they both refer to objects
               that are, in turn, equal according to their own equals methods */
        public boolean equals (Object o) 
        {
            if (this == o) 
                return true;
            if (!(o instanceof WeakElement)) 
                return false;
            Object t = this.get();
            Object u = ((WeakElement)o).get();
            if ((t == null) || (u == null)) 
                return false;
            if (t == u) 
                return true;
            return t.equals(u);
        }

        public int hashCode ()
        {
            return hash;
        }
        
    }
    
}

