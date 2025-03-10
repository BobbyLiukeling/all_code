/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2008-2017 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.enterprise.admin.util;

import java.lang.annotation.Annotation;
import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;
import org.glassfish.api.Param;
import org.glassfish.api.ParamDefaultCalculator;
import org.glassfish.api.admin.CommandModel;
import org.glassfish.api.admin.ExecuteOn;

/**
 * A command and parameter model that allows the data to be supplied directly.
 *
 * @author Jerome Dochez
 * @author Bill Shannon
 */
public class CommandModelData extends CommandModel {

    // use a LinkedHashMap so params appears in the order they are added
    private final Map<String, CommandModel.ParamModel> params =
                                new LinkedHashMap<String, ParamModel>();
    private final String commandName;
    public boolean managedJob = false;
    public boolean dashOk = false;

    public CommandModelData(String name) {
        commandName = name;
    }

    CommandModelData() {
        commandName = null;
    }

    @Override
    public String getLocalizedDescription() {
        return null;
    }

    @Override
    public String getUsageText() {
        return null;
    }

    @Override
    public String getCommandName() {
        return commandName;
    }

    @Override
    public CommandModel.ParamModel getModelFor(String paramName) {
        return params.get(paramName);
    }

    @Override
    public Collection<String> getParametersNames() {
        return params.keySet();
    }

    @Override
    public Class getCommandClass() {
        return null;
    }

    @Override
    public ExecuteOn getClusteringAttributes() {
        return null;
    }
    
    @Override
    public boolean isManagedJob() {
        return this.managedJob;
    }

    /**
     * Should an unknown option be considered an operand by asadmin?
     */
    @Override
    public boolean unknownOptionsAreOperands() {
	return dashOk;
    }

    /**
     * Add the ParamModel to this CommandModel.
     */
    public void add(ParamModel model) {
        if (!params.containsKey(model.getName())) {
            params.put(model.getName(), model);
        }
    }

    /**
     * A parameter model that's just data.
     */
    public static class ParamModelData extends ParamModel {

        public String    name;
        public ParamData param;
        public Class     type;
        // from the server, for password fields
        public String    prompt;
        public String    promptAgain;

        public ParamModelData(String name, Class type, boolean optional,
                                String def) {
            this(name, type, optional, def, null);
        }

        public ParamModelData(String name, Class type, boolean optional,
                                String def, String shortName) {
	    this(name, type, optional, def, shortName, false);
	}

        public ParamModelData(String name, Class type, boolean optional,
			    String def, String shortName, boolean obsolete) {
	    this(name, type, optional, def, shortName, obsolete, "");
	}

        public ParamModelData(String name, Class type, boolean optional,
		String def, String shortName, boolean obsolete, String alias) {
            ParamData param = new ParamData();
            param._name = name;
            param._optional = optional;
            param._defaultValue = def;
            if (shortName == null)
                shortName = "";
            param._shortName = shortName;
            param._obsolete = obsolete;
	    if (alias == null)
		alias = "";
            param._alias = alias;
            ParamModelData.this.name = name;
            ParamModelData.this.type = type;
            ParamModelData.this.param = param;
        }

        @Override
        public String getName() {
            return name;
        }

        @Override
        public String getLocalizedDescription() {
            return "";
        }

        @Override
        public String getLocalizedPrompt() {
            return getPrompt();
        }

        @Override
        public String getLocalizedPromptAgain() {
            return getPromptAgain();
        }
        
        @Override
        public Param getParam() {
            return param;
        }


        @Override
        public Class getType() {
            return type;
        }

        // unique to ParamModelData
        public String getPrompt() {
            return prompt;
        }
        
        public String getPromptAgain() {
            return promptAgain;
        }

        @Override
        public String toString() {
            return "ParamModelData: name=" + name + ", type=" + type +
                ", i18n=" + getLocalizedDescription() + ", param=" + param.toString();
        }
    }

    /**
     * A Param annotation simulated with data.
     */
    public static class ParamData implements Param {
        public String _name = "";
        public String _acceptableValues = "";
        public boolean _optional = false;
        public String _shortName = "";
        public boolean _primary = false;
        public String _defaultValue = "";
        public boolean _password = false;
        public char _separator = ',';
        public boolean _multiple = false;
        public boolean _obsolete = false;
        public String _alias = "";

        @Override
        public Class<? extends Annotation> annotationType() {
            return Param.class;
        }

        @Override
        public String name() { return _name; }
        @Override
        public String acceptableValues() { return _acceptableValues; }
        @Override
        public boolean optional() { return _optional; }
        @Override
        public String shortName() { return _shortName; }
        @Override
        public boolean primary() { return _primary; }
        @Override
        public String defaultValue() { return _defaultValue; }
        @Override
        public Class<? extends ParamDefaultCalculator> defaultCalculator() { 
            return ParamDefaultCalculator.class;
        }
        @Override
        public boolean password() { return _password; }
        @Override
        public char separator() { return _separator; }
        @Override
        public boolean multiple() { return _multiple; }
        @Override
        public boolean obsolete() { return _obsolete; }
        @Override
        public String alias() { return _alias; }

        @Override
        public String toString() {
            return "ParamData: name=" + _name +
                ", acceptableValues=" + _acceptableValues +
                ", optional=" + _optional +
                ", shortName=" + _shortName +
                ", primary=" + _primary +
                ", defaultValue=" + _defaultValue +
                ", password=" + _password +
                ", separator=" + _separator +
                ", multiple=" + _multiple +
                ", obsolete=" + _obsolete +
                ", alias=" + _alias;
        }
    }
}
