#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "LeapC.h"
#include "LeapMotion/Connection.h"

LEAP_CLOCK_REBASER clockSynchronizer;

const char* ResultString(eLeapRS r) {
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


int main(int argc, char** argv) {
	Gesture::Connection connection = Gesture::Connection{};
  LEAP_CONNECTION* connHandle = connection.OpenConnection();
  eLeapRS result;
  LEAP_CONNECTION_MESSAGE msg;
  while (connection.GetIsRunning()) {
	  unsigned int timeout = 1000;
      result = LeapPollConnection(*connection.handle(), timeout, &msg);

      if (result != eLeapRS_Success) {
          printf("Haram");
          printf("\n");
      }

      printf(ResultString(result));
      printf("\n");
  }
  
  return 0;
}

// This code is halal certified