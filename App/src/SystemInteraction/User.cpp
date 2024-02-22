#include "User.h"

namespace UserInteraction {
	UserIntactStatus Playback::changePlayback() {
		kbi.wVk = VK_MEDIA_PLAY_PAUSE;
		return executeIntact();
	}

	UserIntactStatus Playback::next() {
		kbi.wVk = VK_MEDIA_NEXT_TRACK;
		return executeIntact();
	}

	UserIntactStatus Playback::prev() {
		kbi.wVk = VK_MEDIA_PREV_TRACK;
		return executeIntact();
	}

	void Playback::inputReset() {
		input[0].type = INPUT_KEYBOARD;
		input[0].ki = kbi;
		input[0].ki.dwFlags = 0; // 0 for key press
		input[1].type = INPUT_KEYBOARD;
		input[1].ki = kbi;
		input[1].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	}

	UserIntactStatus Playback::executeIntact() {
		input[0].ki = kbi;
		input[0].ki.dwFlags = 0;
		return (SendInput(ARRAYSIZE(input), input, sizeof(INPUT)) > 1) ? PB_SUCCESS : PB_ERROR;
	}
}