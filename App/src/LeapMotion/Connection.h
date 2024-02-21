#include "LeapC.h"
#include <Windows.h>
#include <process.h>

namespace Gesture {
	class Connection {
	public:
		static Connection* Instance()
		{
			if (!instance)
			{
				instance = new Connection();
			}

			return instance;
		}

		void OpenConnection();
		bool GetIsRunning() const { return isRunning; }
		eLeapRS GetLatestResult() const { return latest_result; }
		const LEAP_CONNECTION_MESSAGE& GetLatestMessage() const { return latest_message; }
		static void MessageServiceLoop(void* unused); // This has to be here because otherwise the camera blocks the application thread and we will get "not connected" errors
		LEAP_CONNECTION* handle() { return &connectionHandle; }
		static const char* ResultString(eLeapRS r);
		static const char* MessageTypeString(eLeapEventType message_type);

	private:
		static Connection* instance;
		bool isRunning = false;
		bool isConnected = false;
		LEAP_CONNECTION connectionHandle;
		eLeapRS latest_result;
		LEAP_CONNECTION_MESSAGE latest_message;
		static HANDLE pollingThread;
		static CRITICAL_SECTION dataLock;
	};
}