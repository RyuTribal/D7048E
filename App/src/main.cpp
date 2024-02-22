#include <Windows.h>
#include "LeapMotion/Connection.h"
#include "LeapMotion/HandTracker.h"
#include "Utils/Log.h"
#include "Utils/TaskQueue.h"
#include "SystemInteraction/User.h"


int main(int argc, char** argv) {
	Gesture::Log::Init();
	CORE_INFO("Log initialized!");

	Gesture::Connection::Instance()->OpenConnection();
	Gesture::HandTracker::Init();

	while (Gesture::Connection::Instance()->GetIsRunning()) {
		std::function<void()> task;
		while (Gesture::TaskQueue::Instance()->TryDequeueTask(task)) {
			task();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Avoid busy waiting
	}
	return 0;
}

// This code is halal certified