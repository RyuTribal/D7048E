#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "LeapC.h"
#include "LeapMotion/Connection.h"
#include "Utils/Log.h"

LEAP_CLOCK_REBASER clockSynchronizer;

void millisleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


int main(int argc, char** argv) {
    Gesture::Log::Init();
    CORE_INFO("Log initialized!");

  Gesture::Connection::Instance()->OpenConnection();
  LEAP_CLOCK_REBASER clockSynchronizer;
  LeapCreateClockRebaser(&clockSynchronizer);
  clock_t  cpuTime;
  int64_t targetFrameTime = 0;
  uint64_t targetFrameSize = 0;
  eLeapRS result;
  while (Gesture::Connection::Instance()->GetIsRunning()) {

      cpuTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() ;
      LeapUpdateRebase(clockSynchronizer, cpuTime, LeapGetNow());

      millisleep(10);

      cpuTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

      //Translate application time to Leap time
      LeapRebaseClock(clockSynchronizer, cpuTime, &targetFrameTime);

      //Get the buffer size needed to hold the tracking data
      result = LeapGetFrameSize(*Gesture::Connection::Instance()->handle(), targetFrameTime, &targetFrameSize);
      //Simulate delay (i.e. processing load, v-sync, etc)
      if (result == eLeapRS_Success) {
          LEAP_TRACKING_EVENT* interpolatedFrame = (LEAP_TRACKING_EVENT*)malloc((size_t)targetFrameSize);
          //Get the frame
          result = LeapInterpolateFrame(*Gesture::Connection::Instance()->handle(), targetFrameTime, interpolatedFrame, targetFrameSize);
          if (result == eLeapRS_Success) {
              //Use the data...
              printf("Frame %lli with %i hands with delay of %lli microseconds.\n",
                  (long long int)interpolatedFrame->tracking_frame_id,
                  interpolatedFrame->nHands,
                  (long long int)LeapGetNow() - interpolatedFrame->info.timestamp);
              for (uint32_t h = 0; h < interpolatedFrame->nHands; h++) {
                  LEAP_HAND* hand = &interpolatedFrame->pHands[h];
                  printf("    Hand id %i is a %s hand with position (%f, %f, %f).\n",
                      hand->id,
                      (hand->type == eLeapHandType_Left ? "left" : "right"),
                      hand->palm.position.x,
                      hand->palm.position.y,
                      hand->palm.position.z);
              }
              //Free the allocated buffer when done.
              free(interpolatedFrame);
          }
          else {
              printf("LeapInterpolateFrame() result was %s.\n", Gesture::Connection::ResultString(result));
          }
      }
      else {
          printf("LeapGetFrameSize() result was %s.\n", Gesture::Connection::ResultString(result));
      }

      // std::cout << "Message: " << MessageTypeString(msg.type) << std::endl;
      
  }
 
  return 0;
}

// This code is halal certified