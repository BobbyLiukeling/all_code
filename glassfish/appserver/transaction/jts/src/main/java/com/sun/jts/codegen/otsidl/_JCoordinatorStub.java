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

package com.sun.jts.codegen.otsidl;


/**
* com/sun/jts/codegen/otsidl/_JCoordinatorStub.java .
* Generated by the IDL-to-Java compiler (portable), version "3.1"
* from com/sun/jts/ots.idl
* Tuesday, February 5, 2002 12:57:23 PM PST
*/


//#-----------------------------------------------------------------------------
public class _JCoordinatorStub extends org.omg.CORBA.portable.ObjectImpl implements com.sun.jts.codegen.otsidl.JCoordinator
{

  public org.omg.CosTransactions.otid_t getGlobalTID ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("getGlobalTID", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.otid_t $result = org.omg.CosTransactions.otid_tHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return getGlobalTID ();
    } finally {
        _releaseReply ($in);
    }
  } // getGlobalTID


  // Returns the global identifier that represents the Coordinator's transaction.
  public long getLocalTID ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("getLocalTID", true);
       $in = _invoke ($out);
       long $result = $in.read_longlong ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return getLocalTID ();
    } finally {
        _releaseReply ($in);
    }
  } // getLocalTID


  // Returns the local identifier that represents the Coordinator's transaction.
  public org.omg.CosTransactions.TransIdentity[] getAncestors ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("getAncestors", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.TransIdentity $result[] = com.sun.jts.codegen.otsidl.TransAncestryHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return getAncestors ();
    } finally {
        _releaseReply ($in);
    }
  } // getAncestors


  // freeing the sequence storage.
  public boolean isRollbackOnly ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("isRollbackOnly", true);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return isRollbackOnly ();
    } finally {
        _releaseReply ($in);
    }
  } // isRollbackOnly

  public org.omg.CosTransactions.Status get_status ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("get_status", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.Status $result = org.omg.CosTransactions.StatusHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return get_status ();
    } finally {
        _releaseReply ($in);
    }
  } // get_status

  public org.omg.CosTransactions.Status get_parent_status ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("get_parent_status", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.Status $result = org.omg.CosTransactions.StatusHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return get_parent_status ();
    } finally {
        _releaseReply ($in);
    }
  } // get_parent_status

  public org.omg.CosTransactions.Status get_top_level_status ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("get_top_level_status", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.Status $result = org.omg.CosTransactions.StatusHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return get_top_level_status ();
    } finally {
        _releaseReply ($in);
    }
  } // get_top_level_status

  public boolean is_same_transaction (org.omg.CosTransactions.Coordinator tc)
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("is_same_transaction", true);
       org.omg.CosTransactions.CoordinatorHelper.write ($out, tc);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return is_same_transaction (tc);
    } finally {
        _releaseReply ($in);
    }
  } // is_same_transaction

  public boolean is_related_transaction (org.omg.CosTransactions.Coordinator tc)
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("is_related_transaction", true);
       org.omg.CosTransactions.CoordinatorHelper.write ($out, tc);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return is_related_transaction (tc);
    } finally {
        _releaseReply ($in);
    }
  } // is_related_transaction

  public boolean is_ancestor_transaction (org.omg.CosTransactions.Coordinator tc)
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("is_ancestor_transaction", true);
       org.omg.CosTransactions.CoordinatorHelper.write ($out, tc);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return is_ancestor_transaction (tc);
    } finally {
        _releaseReply ($in);
    }
  } // is_ancestor_transaction

  public boolean is_descendant_transaction (org.omg.CosTransactions.Coordinator tc)
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("is_descendant_transaction", true);
       org.omg.CosTransactions.CoordinatorHelper.write ($out, tc);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return is_descendant_transaction (tc);
    } finally {
        _releaseReply ($in);
    }
  } // is_descendant_transaction

  public boolean is_top_level_transaction ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("is_top_level_transaction", true);
       $in = _invoke ($out);
       boolean $result = $in.read_boolean ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return is_top_level_transaction ();
    } finally {
        _releaseReply ($in);
    }
  } // is_top_level_transaction

  public int hash_transaction ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("hash_transaction", true);
       $in = _invoke ($out);
       int $result = $in.read_ulong ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return hash_transaction ();
    } finally {
        _releaseReply ($in);
    }
  } // hash_transaction

  public int hash_top_level_tran ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("hash_top_level_tran", true);
       $in = _invoke ($out);
       int $result = $in.read_ulong ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return hash_top_level_tran ();
    } finally {
        _releaseReply ($in);
    }
  } // hash_top_level_tran

  public org.omg.CosTransactions.RecoveryCoordinator register_resource (org.omg.CosTransactions.Resource r) throws org.omg.CosTransactions.Inactive
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("register_resource", true);
       org.omg.CosTransactions.ResourceHelper.write ($out, r);
       $in = _invoke ($out);
       org.omg.CosTransactions.RecoveryCoordinator $result = org.omg.CosTransactions.RecoveryCoordinatorHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/Inactive:1.0"))
          throw org.omg.CosTransactions.InactiveHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return register_resource (r);
    } finally {
        _releaseReply ($in);
    }
  } // register_resource

  public void register_synchronization (org.omg.CosTransactions.Synchronization sync) throws org.omg.CosTransactions.Inactive, org.omg.CosTransactions.SynchronizationUnavailable
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("register_synchronization", true);
       org.omg.CosTransactions.SynchronizationHelper.write ($out, sync);
       $in = _invoke ($out);
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/Inactive:1.0"))
          throw org.omg.CosTransactions.InactiveHelper.read ($in);
       else if (_id.equals ("IDL:omg.org/CosTransactions/SynchronizationUnavailable:1.0"))
          throw org.omg.CosTransactions.SynchronizationUnavailableHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       register_synchronization (sync);
    } finally {
        _releaseReply ($in);
    }
  } // register_synchronization

  public void register_subtran_aware (org.omg.CosTransactions.SubtransactionAwareResource r) throws org.omg.CosTransactions.Inactive, org.omg.CosTransactions.NotSubtransaction
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("register_subtran_aware", true);
       org.omg.CosTransactions.SubtransactionAwareResourceHelper.write ($out, r);
       $in = _invoke ($out);
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/Inactive:1.0"))
          throw org.omg.CosTransactions.InactiveHelper.read ($in);
       else if (_id.equals ("IDL:omg.org/CosTransactions/NotSubtransaction:1.0"))
          throw org.omg.CosTransactions.NotSubtransactionHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       register_subtran_aware (r);
    } finally {
        _releaseReply ($in);
    }
  } // register_subtran_aware

  public void rollback_only () throws org.omg.CosTransactions.Inactive
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("rollback_only", true);
       $in = _invoke ($out);
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/Inactive:1.0"))
          throw org.omg.CosTransactions.InactiveHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       rollback_only ();
    } finally {
        _releaseReply ($in);
    }
  } // rollback_only

  public String get_transaction_name ()
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("get_transaction_name", true);
       $in = _invoke ($out);
       String $result = $in.read_string ();
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return get_transaction_name ();
    } finally {
        _releaseReply ($in);
    }
  } // get_transaction_name

  public org.omg.CosTransactions.Control create_subtransaction () throws org.omg.CosTransactions.SubtransactionsUnavailable, org.omg.CosTransactions.Inactive
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("create_subtransaction", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.Control $result = org.omg.CosTransactions.ControlHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/SubtransactionsUnavailable:1.0"))
          throw org.omg.CosTransactions.SubtransactionsUnavailableHelper.read ($in);
       else if (_id.equals ("IDL:omg.org/CosTransactions/Inactive:1.0"))
          throw org.omg.CosTransactions.InactiveHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return create_subtransaction ();
    } finally {
        _releaseReply ($in);
    }
  } // create_subtransaction

  public org.omg.CosTransactions.PropagationContext get_txcontext () throws org.omg.CosTransactions.Unavailable
  {
    org.omg.CORBA.portable.InputStream $in = null;
    try {
       org.omg.CORBA.portable.OutputStream $out = _request ("get_txcontext", true);
       $in = _invoke ($out);
       org.omg.CosTransactions.PropagationContext $result = org.omg.CosTransactions.PropagationContextHelper.read ($in);
       return $result;
    } catch (org.omg.CORBA.portable.ApplicationException $ex) {
       $in = $ex.getInputStream ();
       String _id = $ex.getId ();
       if (_id.equals ("IDL:omg.org/CosTransactions/Unavailable:1.0"))
          throw org.omg.CosTransactions.UnavailableHelper.read ($in);
       else
            throw new org.omg.CORBA.MARSHAL (_id);
    } catch (org.omg.CORBA.portable.RemarshalException $rm) {
       return get_txcontext ();
    } finally {
        _releaseReply ($in);
    }
  } // get_txcontext

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:otsidl/JCoordinator:1.0", 
    "IDL:omg.org/CosTransactions/Coordinator:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }

  private void readObject (java.io.ObjectInputStream s) throws java.io.IOException
  {
     String str = s.readUTF ();
     String[] args = null;
     java.util.Properties props = null;
     org.omg.CORBA.Object obj = org.omg.CORBA.ORB.init (args, props).string_to_object (str);
     org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl) obj)._get_delegate ();
     _set_delegate (delegate);
  }

  private void writeObject (java.io.ObjectOutputStream s) throws java.io.IOException
  {
     String[] args = null;
     java.util.Properties props = null;
     String str = org.omg.CORBA.ORB.init (args, props).object_to_string (this);
     s.writeUTF (str);
  }
} // class _JCoordinatorStub
