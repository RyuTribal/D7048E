#include "Connection.h"
#include <iostream>

namespace Gesture {
    struct Callbacks ConnectionCallbacks;
	LEAP_CONNECTION* Connection::OpenConnection()
	{
        if (isRunning) {
            return &connectionHandle;
        }
        if (connectionHandle || LeapCreateConnection(NULL, &connectionHandle) == eLeapRS_Success) {
            eLeapRS result = LeapOpenConnection(connectionHandle);
            if (result == eLeapRS_Success) {
                isRunning = true;
            }
        }
        return &connectionHandle;
	}

    void Connection::OnConnection(const LEAP_CONNECTION_EVENT* connection_event)
    {
        if (ConnectionCallbacks.on_connection) {
            ConnectionCallbacks.on_connection();
            printf("Connected");
            isConnected = true;
        }
    }

    void Connection::OnConnectionLost(const LEAP_CONNECTION_LOST_EVENT* connection_lost_event)
    {
        if (ConnectionCallbacks.on_connection_lost) {
            ConnectionCallbacks.on_connection_lost();
            isConnected = false;
        }
    }


}