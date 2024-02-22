#include "Connection.h"
#include "Utils/Log.h"
#include "Utils/TaskQueue.h"

namespace Gesture {
    Connection* Connection::instance = nullptr;
    HANDLE Connection::pollingThread = nullptr;
    CRITICAL_SECTION Connection::dataLock;
	void Connection::OpenConnection()
	{
        if (isRunning) {
            return;
        }
        if (connectionHandle || LeapCreateConnection(nullptr, &connectionHandle) == eLeapRS_Success) {
            eLeapRS result = LeapOpenConnection(connectionHandle);
            if (result == eLeapRS_Success) {
                CORE_INFO("Connected!!");
                isRunning = true;
                InitializeCriticalSection(&dataLock);
                pollingThread = (HANDLE)_beginthread(Connection::MessageServiceLoop, 0, NULL);
            }
        }
	}
    void Connection::MessageServiceLoop(void* unused)
    {
        while (Instance()->isRunning) {
            unsigned int timeout = 1000;
            Instance()->latest_result = LeapPollConnection(Instance()->connectionHandle, timeout, &Instance()->latest_message);

            if (Instance()->latest_result != eLeapRS_Success) {
                CORE_WARN("LeapC PollConnection call was {0}", ResultString(Instance()->latest_result));
                continue;
            }

            // CORE_INFO("Message: {0}", MessageTypeString(Instance()->latest_message.type));

            switch (Instance()->latest_message.type) {
            case eLeapEventType_Tracking:
                if (Instance()->GetCallbackStruct()->on_frame) {
                    auto tracking_event = Instance()->latest_message.tracking_event;
                    TaskQueue::Instance()->EnqueueTask([tracking_event]() {
                        Instance()->GetCallbackStruct()->on_frame(tracking_event); // This will be sent to the main thread for execution
                       });
                }
                break;
            }
        }
    }


    const char* Connection::ResultString(eLeapRS r) {
        switch (r) {
        case eLeapRS_Success:                  return "eLeapRS_Success";
        case eLeapRS_UnknownError:             return "eLeapRS_UnknownError";
        case eLeapRS_InvalidArgument:          return "eLeapRS_InvalidArgument";
        case eLeapRS_InsufficientResources:    return "eLeapRS_InsufficientResources";
        case eLeapRS_InsufficientBuffer:       return "eLeapRS_InsufficientBuffer";
        case eLeapRS_Timeout:                  return "eLeapRS_Timeout";
        case eLeapRS_NotConnected:             return "eLeapRS_NotConnected";
        case eLeapRS_HandshakeIncomplete:      return "eLeapRS_HandshakeIncomplete";
        case eLeapRS_BufferSizeOverflow:       return "eLeapRS_BufferSizeOverflow";
        case eLeapRS_ProtocolError:            return "eLeapRS_ProtocolError";
        case eLeapRS_InvalidClientID:          return "eLeapRS_InvalidClientID";
        case eLeapRS_UnexpectedClosed:         return "eLeapRS_UnexpectedClosed";
        case eLeapRS_UnknownImageFrameRequest: return "eLeapRS_UnknownImageFrameRequest";
        case eLeapRS_UnknownTrackingFrameID:   return "eLeapRS_UnknownTrackingFrameID";
        case eLeapRS_RoutineIsNotSeer:         return "eLeapRS_RoutineIsNotSeer";
        case eLeapRS_TimestampTooEarly:        return "eLeapRS_TimestampTooEarly";
        case eLeapRS_ConcurrentPoll:           return "eLeapRS_ConcurrentPoll";
        case eLeapRS_NotAvailable:             return "eLeapRS_NotAvailable";
        case eLeapRS_NotStreaming:             return "eLeapRS_NotStreaming";
        case eLeapRS_CannotOpenDevice:         return "eLeapRS_CannotOpenDevice";
        default:                               return "unknown result type.";
        }
    }

    const char* Connection::MessageTypeString(eLeapEventType message_type) {
        switch (message_type) {
        case eLeapEventType_None:              return "eLeapEventType_None";
        case eLeapEventType_Connection:        return "eLeapEventType_Connection";
        case eLeapEventType_ConnectionLost:    return "eLeapEventType_ConnectionLost";
        case eLeapEventType_Device:            return "eLeapEventType_Device";
        case eLeapEventType_DeviceFailure:     return "eLeapEventType_DeviceFailure";
        case eLeapEventType_Policy:            return "eLeapEventType_Policy";
        case eLeapEventType_Tracking:          return "eLeapEventType_Tracking";
        case eLeapEventType_ImageRequestError: return "eLeapEventType_ImageRequestError";
        case eLeapEventType_ImageComplete:     return "eLeapEventType_ImageComplete";
        case eLeapEventType_LogEvent:          return "eLeapEventType_LogEvent";
        case eLeapEventType_DeviceLost:        return "eLeapEventType_DeviceLost";
        case eLeapEventType_ConfigResponse:    return "eLeapEventType_ConfigResponse";
        case eLeapEventType_ConfigChange:      return "eLeapEventType_ConfigChange";
        case eLeapEventType_DeviceStatusChange:return "eLeapEventType_DeviceStatusChange";
        case eLeapEventType_DroppedFrame:      return "eLeapEventType_DroppedFrame";
        case eLeapEventType_Image:             return "eLeapEventType_Image";
        case eLeapEventType_PointMappingChange:return "eLeapEventType_PointMappingChange";
        case eLeapEventType_TrackingMode:      return "eLeapEventType_TrackingMode";
        case eLeapEventType_LogEvents:         return "eLeapEventType_LogEvents";
        case eLeapEventType_HeadPose:          return "eLeapEventType_HeadPose";
        case eLeapEventType_Eyes:              return "eLeapEventType_Eyes";
        case eLeapEventType_IMU:               return "eLeapEventType_IMU";
        case eLeapEventType_NewDeviceTransform:return "eLeapEventType_NewDeviceTransform";
        default:                               return "unknown message type.";
        }
    }
}