#include "Connection.h"

namespace Gesture {
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
}