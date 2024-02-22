#include "HandTracker.h"
#include "Connection.h"
#include <time.h>
#include <chrono>
#include "Utils/Log.h"
#include <thread>
#include "Net/Request.h"

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

    void HandTracker::PopulateJson(JsonObject& json_obj, LEAP_HAND* hand)
    {
        json_obj.SetValue("hand_type", hand->type == eLeapHandType_Left ? "left" : "right");
        json_obj.SetValue("hand_finger_nr", 5);

        std::string rotation_vec = "[" + std::to_string(hand->palm.direction.x) + "," + std::to_string(hand->palm.direction.y) + "," + std::to_string(hand->palm.direction.z) + "]";
        json_obj.SetValue("hand_direction", rotation_vec);

        std::string palm_pos_vec = "[" + std::to_string(hand->palm.position.x) + "," + std::to_string(hand->palm.position.y) + "," + std::to_string(hand->palm.position.z) + "]";
        json_obj.SetValue("palm_position", palm_pos_vec);

        std::string palm_normal_vec = "[" + std::to_string(hand->palm.normal.x) + "," + std::to_string(hand->palm.normal.y) + "," + std::to_string(hand->palm.normal.z) + "]";
        json_obj.SetValue("palm_normal", palm_normal_vec);

        std::string fingers = "{";

        fingers += "\"index\": [" + std::to_string(hand->index.bones->next_joint.x) + ", "
            + std::to_string(hand->index.bones->next_joint.y) + ", "
            + std::to_string(hand->index.bones->next_joint.z) + "], ";

        fingers += "\"middle\": [" + std::to_string(hand->middle.bones->next_joint.x) + ", "
            + std::to_string(hand->middle.bones->next_joint.y) + ", "
            + std::to_string(hand->middle.bones->next_joint.z) + "], ";

        fingers += "\"ring\": [" + std::to_string(hand->ring.bones->next_joint.x) + ", "
            + std::to_string(hand->ring.bones->next_joint.y) + ", "
            + std::to_string(hand->ring.bones->next_joint.z) + "], ";

        fingers += "\"pinky\": [" + std::to_string(hand->pinky.bones->next_joint.x) + ", "
            + std::to_string(hand->pinky.bones->next_joint.y) + ", "
            + std::to_string(hand->pinky.bones->next_joint.z) + "], ";

        fingers += "\"thumb\": [" + std::to_string(hand->thumb.bones->next_joint.x) + ", "
            + std::to_string(hand->thumb.bones->next_joint.y) + ", "
            + std::to_string(hand->thumb.bones->next_joint.z) + "]";

        fingers += "}";
        json_obj.SetValue("fingers", fingers);

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
        if (result == eLeapRS_Success) {
            LEAP_TRACKING_EVENT* interpolatedFrame = (LEAP_TRACKING_EVENT*)malloc((size_t)targetFrameSize);
            result = LeapInterpolateFrame(*Gesture::Connection::Instance()->handle(), targetFrameTime, interpolatedFrame, targetFrameSize);
            if (result == eLeapRS_Success) {
                /*printf("Frame %lli with %i hands with delay of %lli microseconds.\n",
                    (long long int)interpolatedFrame->tracking_frame_id,
                    interpolatedFrame->nHands,
                    (long long int)LeapGetNow() - interpolatedFrame->info.timestamp);*/
                for (uint32_t h = 0; h < interpolatedFrame->nHands; h++) {
                    LEAP_HAND* hand = &interpolatedFrame->pHands[h];
                    /*printf("    Hand id %i is a %s hand with position (%f, %f, %f).\n",
                        hand->id,
                        (hand->type == eLeapHandType_Left ? "left" : "right"),
                        hand->palm.position.x,
                        hand->palm.position.y,
                        hand->palm.position.z);*/
                    Gesture::JsonObject obj;
                    PopulateJson(obj, hand);

                    std::string url = "localhost:8000/api/model/";
                    Gesture::JsonObject response = Request::Post(url, obj);

                    CORE_INFO("Response: {0}", response.ToString());
                }
                //Free the allocated buffer when done.
                free(interpolatedFrame);
            }
            else {
                CORE_WARN("LeapInterpolateFrame() result was {0}", Gesture::Connection::ResultString(result));
            }
        }
        else {
            CORE_WARN("LeapGetFrameSize() result was {0}", Gesture::Connection::ResultString(result));
        }
	}
}