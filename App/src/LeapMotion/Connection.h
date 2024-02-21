#include <LeapC.h>
#include <Windows.h>
#include <process.h>

typedef void (*connection_callback)     (void);
typedef void (*device_callback)         (const LEAP_DEVICE_INFO* device);
typedef void (*device_lost_callback)    (void);
typedef void (*device_failure_callback) (const eLeapDeviceStatus failure_code,
	const LEAP_DEVICE failed_device);
typedef void (*policy_callback)         (const uint32_t current_policies);
typedef void (*tracking_callback)       (const LEAP_TRACKING_EVENT* tracking_event);
typedef void (*log_callback)            (const eLeapLogSeverity severity,
	const int64_t timestamp,
	const char* message);
typedef void (*config_change_callback)  (const uint32_t requestID, const bool success);
typedef void (*config_response_callback)(const uint32_t requestID, LEAP_VARIANT value);
typedef void (*image_callback)          (const LEAP_IMAGE_EVENT* image_event);
typedef void (*point_mapping_change_callback)(const LEAP_POINT_MAPPING_CHANGE_EVENT* point_mapping_change_event);
typedef void (*head_pose_callback)(const LEAP_HEAD_POSE_EVENT* head_pose_event);
typedef void (*imu_callback)(const LEAP_IMU_EVENT* imu_event);
typedef void (*tracking_mode_callback)(const LEAP_TRACKING_MODE_EVENT* mode_event);

struct Callbacks {
	connection_callback      on_connection;
	connection_callback      on_connection_lost;
	device_callback          on_device_found;
	device_lost_callback     on_device_lost;
	device_failure_callback  on_device_failure;
	policy_callback          on_policy;
	tracking_callback        on_frame;
	log_callback             on_log_message;
	config_change_callback   on_config_change;
	config_response_callback on_config_response;
	image_callback           on_image;
	point_mapping_change_callback on_point_mapping_change;
	head_pose_callback       on_head_pose;
	imu_callback             on_imu;
	tracking_mode_callback   on_tracking_mode;
};

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
		Callbacks* GetCallbackStruct() { return &leap_callbacks; }
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
		Callbacks leap_callbacks{};
	};
}