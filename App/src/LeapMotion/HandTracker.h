#pragma once
#include <LeapC.h>
#include "Net/Json.h"

namespace Gesture {
	class HandTracker {
	public:
		static void Init();
		static void OnTrackingFrame(const LEAP_TRACKING_EVENT* tracking_event);
		static void Millisleep(int milliseconds);
		static void PopulateJson(JsonObject& json_obj, LEAP_HAND* hand);

	private:
		static LEAP_CLOCK_REBASER clock_synchronizer;
	};
}