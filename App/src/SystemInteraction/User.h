#include <Windows.h>
#include <mmeapi.h>
#include <stdio.h>

#ifndef USERINTERACTION_H
#define USERINTERACTION_H

namespace UserInteraction {
	enum UserIntactStatus {
		PB_SUCCESS = 1, // The playback interaction succeeded
		PB_ERROR = 2	// The playback interaction failed, the input array has been reset
	};

	class Playback {
	public:
		Playback() {
			inputReset();
		}
		UserIntactStatus changePlayback(); // pause/play
		UserIntactStatus next();
		UserIntactStatus prev();
		void inputReset();
	private:
		UserIntactStatus executeIntact();
		KEYBDINPUT kbi; // keyboard input
		INPUT input[2] = {};
	};
}

#endif
