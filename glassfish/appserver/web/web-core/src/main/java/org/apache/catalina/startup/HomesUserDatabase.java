/*
 * Copyright (c) 1997-2018 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.catalina.startup;


import java.io.File;
import java.util.Enumeration;
import java.util.Hashtable;


/**
 * Concrete implementation of the <strong>UserDatabase</code> interface
 * considers all directories in a directory whose pathname is specified
 * to our constructor to be "home" directories for those users.
 *
 * @author Craig R. McClanahan
 * @version $Revision: 1.2 $ $Date: 2005/12/08 01:28:08 $
 */

public final class HomesUserDatabase
    implements UserDatabase {


    // --------------------------------------------------------- Constructors


    /**
     * Initialize a new instance of this user database component.
     */
    public HomesUserDatabase() {

        super();

    }


    // --------------------------------------------------- Instance Variables


    /**
     * The set of home directories for all defined users, keyed by username.
     */
    private Hashtable<String, String> homes = new Hashtable<String, String>();


    /**
     * The UserConfig listener with which we are associated.
     */
    private UserConfig userConfig = null;


    // ----------------------------------------------------------- Properties


    /**
     * Return the UserConfig listener with which we are associated.
     */
    public UserConfig getUserConfig() {

        return (this.userConfig);

    }


    /**
     * Set the UserConfig listener with which we are associated.
     *
     * @param userConfig The new UserConfig listener
     */
    public void setUserConfig(UserConfig userConfig) {

        this.userConfig = userConfig;
        init();

    }


    // ------------------------------------------------------- Public Methods


    /**
     * Return an absolute pathname to the home directory for the specified user.
     *
     * @param user User for which a home directory should be retrieved
     */
    public String getHome(String user) {

        return homes.get(user);

    }


    /**
     * Return an enumeration of the usernames defined on this server.
     */
    public Enumeration<String> getUsers() {

        return (homes.keys());

    }


    // ------------------------------------------------------ Private Methods


    /**
     * Initialize our set of users and home directories.
     */
    private void init() {

        String homeBase = userConfig.getHomeBase();
        File homeBaseDir = new File(homeBase);
        if (!homeBaseDir.exists() || !homeBaseDir.isDirectory())
            return;
        String homeBaseFiles[] = homeBaseDir.list();

        for (int i = 0; i < homeBaseFiles.length; i++) {
            File homeDir = new File(homeBaseDir, homeBaseFiles[i]);
            if (!homeDir.isDirectory() || !homeDir.canRead())
                continue;
            homes.put(homeBaseFiles[i], homeDir.toString());
        }


    }


}
