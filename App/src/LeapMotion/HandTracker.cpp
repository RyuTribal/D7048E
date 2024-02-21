#include "HandTracker.h"
#include "Connection.h"
#include <time.h>
#include <chrono>
#include <thread>

namespace Gesture {
    LEAP_CLOCK_REBASER HandTracker::clock_synchronizer;
    void HandTracker::Init()
    {
        LeapCreateClockRebaser(&clock_synchronizer);
        Connection::Instance()->GetCallbackStruct()->on_frame = OnTrackingFrame;
    }

    void HandTracker::Millisleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void HandTracker::OnTrackingFrame(const LEAP_TRACKING_EVENT* tracking_event)
	{
        clock_t  cpuTime;
        int64_t targetFrameTime = 0;
        uint64_t targetFrameSize = 0;
        eLeapRS result;

        cpuTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        LeapUpdateRebase(clock_synchronizer, cpuTime, LeapGetNow());

        Millisleep(10);

        cpuTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        //Translate application time to Leap time
        LeapRebaseClock(clock_synchronizer, cpuTime, &targetFrameTime);

        //Get the buffer size needed to hold the tracking data
        result = LeapGetFrameSize(*Connection::Instance()->handle(), targetFrameTime, &targetFrameSize);
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
	}
}