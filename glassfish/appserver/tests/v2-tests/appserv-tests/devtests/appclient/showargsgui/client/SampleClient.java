/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2018 Oracle and/or its affiliates. All rights reserved.
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
 * SampleClient.java
 *
 * Created on November 1, 2005, 2:02 PM
 */

package com.sun.appserv.test.client;

import java.awt.Color;
import java.lang.reflect.Field;
import java.util.Arrays;

/**
 *
 * @author  tjquinn
 */
public class SampleClient extends javax.swing.JFrame {


    /** Creates new form SampleClient */
    public SampleClient() {
        initComponents();
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jTextArea1 = new javax.swing.JTextArea();
        jScrollPane1 = new javax.swing.JScrollPane();
        argValueList = new javax.swing.JList();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jPanel1.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jPanel1.setLayout(new java.awt.BorderLayout());

        jTextArea1.setBackground(javax.swing.UIManager.getDefaults().getColor("Panel.background"));
        jTextArea1.setEditable(false);
        jTextArea1.setFont(new java.awt.Font("Arial", 0, 13));
        jTextArea1.setLineWrap(true);
        jTextArea1.setText("Below are the command line arguments received during launch");
        jTextArea1.setWrapStyleWord(true);
        jPanel1.add(jTextArea1, java.awt.BorderLayout.NORTH);

        jScrollPane1.setViewportView(argValueList);

        jPanel1.add(jScrollPane1, java.awt.BorderLayout.CENTER);

        getContentPane().add(jPanel1, java.awt.BorderLayout.CENTER);

        jLabel1.setFont(new java.awt.Font("Arial", 0, 18));
        jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel1.setText("Sample Application Client U/I");
        getContentPane().add(jLabel1, java.awt.BorderLayout.NORTH);

        pack();
    }// </editor-fold>//GEN-END:initComponents
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            private SampleClient client;
            public void run() {
                System.out.println("About to set visible to TRUE");
                client.setVisible(true);
                System.out.println("Just set visible to TRUE");
            }
            
            public Runnable init(String args[]) {
                client = new SampleClient();
                client.initArgs(args);
                String overridingColorName = System.getProperty("color");
                if (overridingColorName != null) {
                    final Color overridingColor = toColor(overridingColorName);
                    if (overridingColor != null) {
                        client.argValueList.setBackground(overridingColor);
                    }
                }
                System.out.println("Just finished initArgs call with arguments = " + Arrays.toString(args));
                return this;
            }
        }.init(args));
        System.out.println("About to return from static main");
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JList argValueList;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextArea jTextArea1;
    // End of variables declaration//GEN-END:variables
    
    private void initArgs(String[] args) {
        argValueList.setListData(args);
    }

    private static Color toColor(final String colorName) {
        try {
            final Field colorField = Color.class.getField(colorName);
            return (Color) (colorField.get(null));
        } catch (NoSuchFieldException ex) {
            return null;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}