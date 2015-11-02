#include "network.h"
#include "bluetooth.h"
#include "datetime_layer.h"
#include "debug_layer.h"
#include "battery_layer.h"
#include "config.h"
#include "persist.h"

/**
 * Must happen after layers are created! 
 */ 
void load_persisted_values(WeatherData *weather_data) 
{
  // Debug
  weather_data->debug = persist_exists(KEY_DEBUG_MODE) ? persist_read_bool(KEY_DEBUG_MODE) : DEFAULT_DEBUG_MODE;

  if (weather_data->debug) {
    debug_enable_display();
    debug_update_message("Initializing...");
  } else {
    debug_disable_display();
  }

  // Battery
  weather_data->battery = persist_exists(KEY_DISPLAY_BATTERY) ? persist_read_bool(KEY_DISPLAY_BATTERY) : DEFAULT_DISPLAY_BATTERY; 

  if (weather_data->battery) {
    battery_enable_display();
  } else {
    battery_disable_display();
  }

  // Bluetooth
  weather_data->bluetooth = persist_exists(KEY_ALERT_BLUETOOTH) ? persist_read_bool(KEY_ALERT_BLUETOOTH) : DEFAULT_ALERT_BLUETOOTH; 

  if (weather_data->bluetooth) {
    bluetooth_enable_alert();
  } else {
    bluetooth_disable_alert();
  }

// Vibration Start/End Time
  weather_data->tsstart = persist_exists(KEY_VIBE_START_TIME) ? persist_read_bool(KEY_VIBE_START_TIME) : DEFAULT_VIBE_START_TIME; 
  weather_data->tsend   = persist_exists(KEY_VIBE_END_TIME)   ? persist_read_bool(KEY_VIBE_END_TIME)   : DEFAULT_VIBE_END_TIME; 

  // Hourly Vibration
  weather_data->timesig = persist_exists(KEY_VIBE_TIME_SIGNAL) ? persist_read_bool(KEY_VIBE_TIME_SIGNAL) : DEFAULT_VIBE_TIME_SIGNAL; 

  if (weather_data->timesig) {
	set_time_signal(weather_data->tsstart, weather_data->tsend);
	enable_time_signal();
  } else {
    disable_time_signal();
  }
  
  // Weather Service
  if (persist_exists(KEY_WEATHER_SERVICE)) {
    persist_read_string(KEY_WEATHER_SERVICE, weather_data->service, sizeof(weather_data->service));
  } else {
    strcpy(weather_data->service, DEFAULT_WEATHER_SERVICE);
  }

  // Watchface Color
  if (persist_exists(KEY_FACE_COLOR)) {
    persist_read_string(KEY_FACE_COLOR, weather_data->color, sizeof(weather_data->color));
  } else {
    strcpy(weather_data->color, DEFAULT_FACE_COLOR);
  }

  // Weather Scale
  if (persist_exists(KEY_WEATHER_SCALE)) {
    persist_read_string(KEY_WEATHER_SCALE, weather_data->scale, sizeof(weather_data->scale));
  } else {
    strcpy(weather_data->scale, DEFAULT_WEATHER_SCALE);
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "PersistLoad:  d:%d b:%d t:%d v:%d s:%s c:%s u:%s", 
      weather_data->debug, weather_data->battery, weather_data->bluetooth, weather_data->timesig, weather_data->service, weather_data->color, weather_data->scale);
}

void store_persisted_values(WeatherData *weather_data) 
{
  persist_write_bool(KEY_DEBUG_MODE, weather_data->debug);
  persist_write_bool(KEY_ALERT_BLUETOOTH, weather_data->bluetooth);
  persist_write_bool(KEY_VIBE_TIME_SIGNAL, weather_data->timesig);
  persist_write_bool(KEY_DISPLAY_BATTERY, weather_data->battery);
  persist_write_int(KEY_VIBE_START_TIME, weather_data->tsstart);
  persist_write_int(KEY_VIBE_END_TIME, weather_data->tsend);
  persist_write_string(KEY_WEATHER_SERVICE, weather_data->service);
  persist_write_string(KEY_FACE_COLOR, weather_data->color);
  persist_write_string(KEY_WEATHER_SCALE, weather_data->scale);


  APP_LOG(APP_LOG_LEVEL_DEBUG, "PersistStore:  d:%d b:%d t:%d v:%d s:%s c:%s u:%s", 
      weather_data->debug, weather_data->battery, weather_data->bluetooth, weather_data->timesig, weather_data->service, weather_data->color, weather_data->scale);
}