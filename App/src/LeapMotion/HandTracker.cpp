#include "HandTracker.h"
#include "Connection.h"
#include <time.h>
#include <chrono>
#include "Utils/Log.h"
#include <thread>
#include "Net/Request.h"

namespace Gesture {
    LEAP_CLOCK_REBASER HandTracker::clock_synchronizer;
    std::vector<LEAP_HAND> HandTracker::frames = {};
    bool HandTracker::is_recording = false;


    std::string join(const std::vector<std::string>& vec, const std::string& delim) {
        std::string result;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i != 0) {
                result += delim;
            }
            result += vec[i];
        }
        return result;
    }

    void HandTracker::Init()
    {
        LeapCreateClockRebaser(&clock_synchronizer);
        Connection::Instance()->GetCallbackStruct()->on_frame = OnTrackingFrame;
    }

    void HandTracker::Millisleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void HandTracker::PopulateJson(JsonObject& json_obj, const std::vector<LEAP_HAND>& frames) {
        std::vector<std::string> hand_types;
        std::vector<std::string> palm_pos_vecs;
        std::vector<std::string> palm_norm_vecs;
        std::vector<std::string> palm_dir_vecs;
        std::map<std::string, std::vector<std::vector<float>>> finger_positions;

        finger_positions["index"] = std::vector<std::vector<float>>();
        finger_positions["middle"] = std::vector<std::vector<float>>();
        finger_positions["ring"] = std::vector<std::vector<float>>();
        finger_positions["pinky"] = std::vector<std::vector<float>>();
        finger_positions["thumb"] = std::vector<std::vector<float>>();

        for (const auto& hand : frames) {
            hand_types.push_back(hand.type == eLeapHandType_Left ? "1" : "0");
            palm_dir_vecs.push_back("[" + std::to_string(hand.palm.direction.x) + "," + std::to_string(hand.palm.direction.y) + "," + std::to_string(hand.palm.direction.z) + "]");
            palm_pos_vecs.push_back("[" + std::to_string(hand.palm.position.x) + "," + std::to_string(hand.palm.position.y) + "," + std::to_string(hand.palm.position.z) + "]");
            palm_norm_vecs.push_back("[" + std::to_string(hand.palm.normal.x) + "," + std::to_string(hand.palm.normal.y) + "," + std::to_string(hand.palm.normal.z) + "]");


            std::string fingers = "{";

            finger_positions["index"].push_back({ hand.index.bones->next_joint.x, hand.index.bones->next_joint.y, hand.index.bones->next_joint.z });
            finger_positions["middle"].push_back({ hand.middle.bones->next_joint.x, hand.middle.bones->next_joint.y, hand.middle.bones->next_joint.z });
            finger_positions["ring"].push_back({ hand.ring.bones->next_joint.x, hand.ring.bones->next_joint.y, hand.ring.bones->next_joint.z });
            finger_positions["pinky"].push_back({ hand.pinky.bones->next_joint.x, hand.pinky.bones->next_joint.y, hand.pinky.bones->next_joint.z });
            finger_positions["thumb"].push_back({ hand.thumb.bones->next_joint.x, hand.thumb.bones->next_joint.y, hand.thumb.bones->next_joint.z });
        }

        std::string fingers = "{";
        for (const auto& finger : finger_positions) {
            fingers += "\"" + finger.first + "\":[";
            for (size_t i = 0; i < finger.second.size(); ++i) {
                fingers += "[";
                for (size_t j = 0; j < finger.second[i].size(); ++j) {
                    fingers += std::to_string(finger.second[i][j]);
                    if (j < finger.second[i].size() - 1) {
                        fingers += ",";
                    }
                }
                fingers += "]";
                if (i < finger.second.size() - 1) {
                    fingers += ",";
                }
            }
            fingers += "]";
            fingers += ","; // Add a comma after each finger except the last
        }
        // Remove the trailing comma from the last finger entry
        if (!finger_positions.empty()) {
            fingers.pop_back();
        }
        fingers += "}";

        json_obj.SetValue("hand_types", "[" + join(hand_types, ",") + "]");
        json_obj.SetValue("palm_directions", "[" + join(palm_dir_vecs, ",") + "]");
        json_obj.SetValue("palm_normals", "[" + join(palm_norm_vecs, ",") + "]");
        json_obj.SetValue("palm_positions", "[" + join(palm_pos_vecs, ",") + "]");
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
                if ((interpolatedFrame->nHands < 1 && is_recording) || frames.size() > 100) {
                    is_recording = false;
                    Gesture::JsonObject obj;
                    PopulateJson(obj, frames);

                    std::string url = "localhost:8000/api/model/";
                    Gesture::JsonObject response = Request::Post(url, obj);

                    CORE_INFO("Response: {0}", response.ToString());
                    frames.clear();
                }
                else if (interpolatedFrame->nHands >= 1) {
                    is_recording = true;
                }
                for (uint32_t h = 0; h < interpolatedFrame->nHands; h++) {
                    LEAP_HAND* hand = &interpolatedFrame->pHands[h];
                    printf("    Hand id %i is a %s hand with position (%f, %f, %f).\n",
                        hand->id,
                        (hand->type == eLeapHandType_Left ? "left" : "right"),
                        hand->palm.position.x,
                        hand->palm.position.y,
                        hand->palm.position.z);

                    frames.push_back(*hand);
                    
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