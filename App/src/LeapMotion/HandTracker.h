#pragma once
#include <LeapC.h>

namespace Gesture {
	class HandTracker {
	public:
		static void Init();
		static void OnTrackingFrame(const LEAP_TRACKING_EVENT* tracking_event);
		static void Millisleep(int milliseconds);

	private:
		static LEAP_CLOCK_REBASER clock_synchronizer;
	};
}