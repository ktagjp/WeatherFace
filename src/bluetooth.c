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
#include "battery_layer.h"

bool Is_BT_Connected_Flag = 1;
bool Is_BT_Alert_Enable_Flag = 1;

// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:
static const uint32_t const segments[] = { 200, 100, 200, 100, 200 };
static VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

void UpdateConnection(bool Connected){

	if (Is_BT_Alert_Enable_Flag) {
		if (Is_BT_Connected_Flag != Connected) {
	
			if (Connected)							//  When BT is recovered connection, vibrate twice. 
				vibes_double_pulse();
			else
				vibes_enqueue_custom_pattern(pat);  //  When BT is lost connection, vibrate three times.

			Is_BT_Connected_Flag = Connected;
			layer_mark_dirty(battery_layer);		// Force to redraw battery layer in "battery_layer.c"
		}
	}
	//APP_LOG(APP_LOG_LEVEL_INFO, "SmartFace: BT-Connection was updated!");
}

void bluetooth_enable_alert(void) {
	Is_BT_Alert_Enable_Flag = 1;
}

void bluetooth_disable_alert(void) {
	Is_BT_Alert_Enable_Flag = 0;
}
