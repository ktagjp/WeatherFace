///////////////////////////////////////////////////////////////////////////////////////
//																				                                        	 //
// This file is added by ktagjp for viblation on bluetooth connection state changing //
//																				                                        	 //
//                                                         Created       8/23/2015	 //
//                                                         Last modified 8/23/2015	 //
//																				                                        	 //
///////////////////////////////////////////////////////////////////////////////////////

#include <pebble.h>
#include "bluetooth.h"

static bool IsConnected_Flag = 1;

// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:
static const uint32_t const segments[] = { 200, 100, 200, 100, 200 };
static VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

void UpdateConnection(bool Connected){
	if (IsConnected_Flag != Connected) {
	
		if (Connected)						//  When BT is recovered connection, vibrate twice. 
			vibes_double_pulse();
		else
			vibes_enqueue_custom_pattern(pat);  //  When BT is lost connection, vibrate three times.

		IsConnected_Flag = Connected;
	}
	//APP_LOG(APP_LOG_LEVEL_INFO, "SmartFace: BT-Connection was updated!");
}

