/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright (c) 2001-2018 Oracle and/or its affiliates. All rights reserved.
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

package com.sun.s1peqe.ejb.cmp.roster.ejb;

import java.util.*;
import javax.ejb.EJBObject;
import java.rmi.RemoteException;
import com.sun.s1peqe.ejb.cmp.roster.util.*;

public interface Roster extends EJBObject {
 
    // Players

    public void createPlayer(PlayerDetails details) 
        throws RemoteException;

    public void addPlayer(String playerId, String teamId) 
        throws RemoteException;

    public void removePlayer(String playerId) 
        throws RemoteException;

    public void dropPlayer(String playerId, String teamId) 
        throws RemoteException;

    public PlayerDetails getPlayer(String playerId) 
        throws RemoteException;

    public ArrayList getPlayersOfTeam(String teamId) 
        throws RemoteException;

    public ArrayList getPlayersOfTeamCopy(String teamId) 
        throws RemoteException;

    public ArrayList getPlayersByPosition(String position) 
        throws RemoteException;

    public ArrayList getPlayersByHigherSalary(String name) 
        throws RemoteException;

    public ArrayList getPlayersBySalaryRange(double low, double high) 
        throws RemoteException;

    public ArrayList getPlayersByLeagueId(String leagueId) 
        throws RemoteException;

    public ArrayList getPlayersBySport(String sport) 
        throws RemoteException;

    public ArrayList getPlayersByCity(String city) 
        throws RemoteException;

    public ArrayList getAllPlayers() 
        throws RemoteException;

    public ArrayList getPlayersNotOnTeam() 
        throws RemoteException;

    public ArrayList getPlayersByPositionAndName(String position, 
        String name) throws RemoteException;

    public ArrayList getLeaguesOfPlayer(String playerId)
        throws RemoteException;

    public ArrayList getSportsOfPlayer(String playerId)
        throws RemoteException;

    // Teams

    public ArrayList getTeamsOfLeague(String leagueId) 
        throws RemoteException;

    public void createTeamInLeague(TeamDetails details, String leagueId) 
        throws RemoteException;

    public void removeTeam(String teamId) 
        throws RemoteException;

    public TeamDetails getTeam(String teamId) 
        throws RemoteException;

    // Leagues

    public void createLeague(LeagueDetails details) 
        throws RemoteException;

    public void removeLeague(String leagueId) 
        throws RemoteException;

    public LeagueDetails getLeague(String leagueId) 
        throws RemoteException;

    // Test

    public ArrayList testFinder(String parm1, String parm2, String parm3)
        throws RemoteException;
}