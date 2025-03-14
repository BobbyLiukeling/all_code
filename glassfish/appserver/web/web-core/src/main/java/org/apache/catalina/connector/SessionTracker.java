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

package org.apache.catalina.connector;

import org.apache.catalina.Session;
import org.apache.catalina.SessionEvent;
import org.apache.catalina.SessionListener;

import java.util.ArrayList;

/**
 * Class responsible for keeping track of the total number of active sessions
 * associated with an HTTP request.
 *
 * <p>A given HTTP request may be associated with more than one active
 * session if it has been dispatched to one or more foreign contexts.
 *
 * <p>The number of active sessions being tracked is used to determine whether
 * or not any session information needs to be reflected in the response (e.g.,
 * in the form of a response cookie). If no active sessions are associated
 * with the request by the time the response is committed, no session
 * information will be reflected in the response.
 *
 * See GlassFish Issue 896 for additional details.
 */
public class SessionTracker implements SessionListener {

    // The number of currently tracked sessions
    private volatile int count;

    // The session id that is shared by all tracked sessions
    private volatile String trackedSessionId;

    private Response response;

    /*
     * The list of contexts whose sessions we're tracking.
     *
     * The size of this list will be greater than one only in cross
     * context request dispatch scenarios
     */
    private ArrayList<String> contextNames = new ArrayList<String>(2);

    /**
     * Processes the given session event, by unregistering this SessionTracker
     * as a session listener from the session that is the source of the event,
     * and by decrementing the counter of currently tracked sessions.
     *
     * @param event The session event
     */
    public void sessionEvent(SessionEvent event) {

        if (!Session.SESSION_DESTROYED_EVENT.equals(event.getType())) {
            return;
        }

        Session session = event.getSession();

        synchronized (this) {
            if (session.getIdInternal() != null
                    && session.getIdInternal().equals(trackedSessionId)
                    && session.getManager() != null
                    && session.getManager().getContainer() != null
                    && contextNames.contains(
                            session.getManager().getContainer().getName())) {
                count--;
                if (count == 0) {
                    trackedSessionId = null;
                    if (response != null) {
                        response.removeSessionCookies();
                    }
                }
            }

            session.removeSessionListener(this);
        }
    }

    /**
     * Gets the number of active sessions that are being tracked.
     *
     * @return The number of active sessions being tracked
     */
    public int getActiveSessions() {
        return count;
    }

    /**
     * Gets the id of the sessions that are being tracked.
     *
     * Notice that since all sessions are associated with the same request,
     * albeit in different context, they all share the same id.
     *
     * @return The id of the sessions that are being tracked
     */
    public String getSessionId() {
        return trackedSessionId;
    }

    /**
     * Tracks the given session, by registering this SessionTracker as a
     * listener with the given session, and by incrementing the counter of
     * currently tracked sessions.
     *
     * @param session The session to track
     */
    public synchronized void track(Session session) {

        if (trackedSessionId == null) {
            trackedSessionId = session.getIdInternal();
        } else if (!trackedSessionId.equals(session.getIdInternal())) {
            throw new IllegalArgumentException("Should never reach here");
        }

        count++;

        if (session.getManager() != null
                && session.getManager().getContainer() != null
                && session.getManager().getContainer().getName() != null) {
            contextNames.add(session.getManager().getContainer().getName());
        }

        session.addSessionListener(this);
    }

    /**
     * Associates the given response with this SessionTracker.
     *
     * If the number of tracked sessions drops to zero, this SessionTracker
     * will remove the Set-Cookie from the given response.
     *
     * @param response The response from which to remove the Set-Cookie
     * header if the number of tracked sessions drops to zero
     */
    public synchronized void setResponse(Response response) {
        this.response = response;
    }

    /**
     * Resets this session tracker.
     */
    public synchronized void reset() {
        count = 0;
        trackedSessionId = null;
        contextNames.clear();
    }

}
