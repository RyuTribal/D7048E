#include "LeapC.h"

namespace Gesture {
	class Connection {
	public:
		LEAP_CONNECTION* OpenConnection();
		bool GetIsRunning() { return isRunning; }
		LEAP_CONNECTION* handle() { return &connectionHandle; }

	private:
		bool isRunning = false;
		LEAP_CONNECTION connectionHandle;
	};
}