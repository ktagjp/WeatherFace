#include <pebble.h>
#include <stdlib.h>
#include <errno.h>
#include "network.h"
#include "bluetooth.h"
#include "datetime_layer.h"
#include "battery_layer.h"
#include "weather_layer.h"
#include "debug_layer.h"
#include "main.h"
#include "persist.h"

const  int MAX_RETRY = 2;
static int retry_count = 0;

static void appmsg_in_received(DictionaryIterator *received, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "In received.");

	WeatherData *weather = (WeatherData*) context;

	// Program Control
	Tuple *error_tuple       = dict_find(received, KEY_ERROR);
	Tuple *js_ready_tuple    = dict_find(received, KEY_JS_READY);

	// Current Weather (Via Yahoo, Open Weather Map)
	Tuple *temperature_tuple = dict_find(received, KEY_TEMPERATURE);
	Tuple *condition_tuple   = dict_find(received, KEY_CONDITION);
	Tuple *sunrise_tuple     = dict_find(received, KEY_SUNRISE);
	Tuple *sunset_tuple      = dict_find(received, KEY_SUNSET);
	Tuple *pub_date_tuple    = dict_find(received, KEY_PUB_DATE);
	Tuple *locale_tuple      = dict_find(received, KEY_LOCALE);
	Tuple *tzoffset_tuple    = dict_find(received, KEY_TZOFFSET);

	// Configuration Settings
	Tuple *service_tuple     = dict_find(received, KEY_SERVICE);
	Tuple *color_tuple       = dict_find(received, KEY_COLOR);
	Tuple *debug_tuple       = dict_find(received, KEY_DEBUG);
	Tuple *scale_tuple       = dict_find(received, KEY_SCALE);
	Tuple *battery_tuple     = dict_find(received, KEY_BATTERY);
	Tuple *bluetooth_tuple   = dict_find(received, KEY_BLUETOOTH);
	Tuple *timesig_tuple     = dict_find(received, KEY_TIME_SIGNAL);
	Tuple *stophourly_tuple  = dict_find(received, KEY_STOP_HOURLY);
//	Tuple *ts_end_tuple      = dict_find(received, KEY_TS_END);

	// Hourly Weather
	Tuple *h1_temp_tuple = dict_find(received, KEY_H1_TEMP);
	Tuple *h1_cond_tuple = dict_find(received, KEY_H1_COND);
	Tuple *h1_time_tuple = dict_find(received, KEY_H1_TIME);
	Tuple *h1_pop_tuple  = dict_find(received, KEY_H1_POP);
	Tuple *h2_temp_tuple = dict_find(received, KEY_H2_TEMP);
	Tuple *h2_cond_tuple = dict_find(received, KEY_H2_COND);
	Tuple *h2_time_tuple = dict_find(received, KEY_H2_TIME);
	Tuple *h2_pop_tuple  = dict_find(received, KEY_H2_POP);

	Tuple *hourly_enabled_tuple = dict_find(received, KEY_HOURLY_ENABLED);

	// Weather update
	if (temperature_tuple && condition_tuple) {
		weather->temperature = temperature_tuple->value->int32;
		weather->condition   = condition_tuple->value->int32;
		weather->sunrise     = sunrise_tuple->value->int32;
		weather->sunset      = sunset_tuple->value->int32;
		weather->error       = WEATHER_E_OK;
		weather->tzoffset    = tzoffset_tuple->value->int32;

		weather->updated = time(NULL);

		strncpy(weather->pub_date, pub_date_tuple->value->cstring, 6);
		strncpy(weather->locale, locale_tuple->value->cstring, 255);

		if (weather->debug) {
			debug_enable_display();
			debug_update_weather(weather);
		}

		APP_LOG(APP_LOG_LEVEL_DEBUG, "Weather temp:%i cond:%i pd:%s tzos:%i loc:%s", 
			weather->temperature, weather->condition, weather->pub_date, weather->tzoffset, weather->locale);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Weather sunrise:%i sunset:%i", weather->sunrise, weather->sunset);
	}
	// Configuration Update
	else if (service_tuple) {
		char* service =   strcmp(service_tuple->value->cstring, SERVICE_OPEN_WEATHER) == 0 ? SERVICE_OPEN_WEATHER
						: strcmp(service_tuple->value->cstring, SERVICE_YAHOO_WEATHER) == 0 ? SERVICE_YAHOO_WEATHER
						: SERVICE_WUNDER_WEATHER;
		char* color   =   strcmp(color_tuple->value->cstring, COLOR_DUKEBLUE) == 0 ? COLOR_DUKEBLUE
						: strcmp(color_tuple->value->cstring, COLOR_BLACK) == 0 ? COLOR_BLACK
						: COLOR_RED;
		char* scale   = strcmp(scale_tuple->value->cstring, SCALE_CELSIUS) == 0 ? SCALE_CELSIUS : SCALE_FAHRENHEIT;
		strncpy(weather->service, service, 6);
		strncpy(weather->color, color, 6);
		strncpy(weather->scale, scale, 2);

		weather->debug		= (bool)debug_tuple->value->int32;
		weather->battery	= (bool)battery_tuple->value->int32;
		weather->bluetooth	= (bool)bluetooth_tuple->value->int32;
		weather->timesig	= (bool)timesig_tuple->value->int32;
		weather->stophourly	= (bool)stophourly_tuple->value->int32;

//		char **endptr = NULL;
		
//		int tsstart = (int)strtol(ts_start_tuple->value->cstring, endptr, 10);
//		if (tsstart >= 0 && tsstart <= 23 && errno != ERANGE)
//			weather->tsstart = tsstart;
//		else
//			weather->tsstart = 7;
//
//		int tsend   = (int)strtol(ts_end_tuple->value->cstring, endptr, 10);
//		if (tsend >= 0 && tsend <= 23 && errno != ERANGE)
//			weather->tsend = tsend;
//		else
//			weather->tsend = 22;

//		APP_LOG(APP_LOG_LEVEL_DEBUG, "Configuration serv:%s color:%s scale:%s debug:%i batt:%i bt:%i ts:%i tsstart:%i tsend:%i", 
//			weather->service, weather->color, weather->scale, weather->debug, weather->battery, weather->bluetooth,
//			weather->timesig, weather->tsstart, weather->tsend);

		APP_LOG(APP_LOG_LEVEL_DEBUG, "Configuration serv:%s color:%s scale:%s debug:%i batt:%i bt:%i ts:%i  st:%i", 
			weather->service, weather->color, weather->scale, weather->debug, weather->battery, weather->bluetooth,
			weather->timesig, weather->stophourly);

		if (weather->battery) {
			battery_enable_display();
		} else {
			battery_disable_display();
		}

		if (weather->bluetooth) {
			bluetooth_enable_alert();
		} else {
			bluetooth_disable_alert();
		}

		if (weather->timesig) {
			if (weather->stophourly) {
				weather->tsstart = 7;
				weather->tsend   = 22;
			} else {
				weather->tsstart = 0;
				weather->tsend   = 0;
			}
			set_time_signal(weather->tsstart, weather->tsend);
			enable_time_signal();
		} else {
			disable_time_signal();
		}

		if (weather->debug) {
			debug_enable_display();
			debug_update_weather(weather);
		} else {
			debug_disable_display();
		}

		store_persisted_values(weather);
	}
	// Hourly Weather Update
	else if (h1_temp_tuple) {

		weather->h1_temp = h1_temp_tuple->value->int32;
		weather->h1_cond = h1_cond_tuple->value->int32;
		time_t h1_time   = h1_time_tuple->value->int32;
		struct tm *h1_tm = localtime(&h1_time);
		weather->h1_time = mktime(h1_tm);
		weather->h1_pop  = h1_pop_tuple->value->int32;
		weather->h2_temp = h2_temp_tuple->value->int32;
		weather->h2_cond = h2_cond_tuple->value->int32;
		time_t h2_time = h2_time_tuple->value->int32;
		struct tm *h2_tm = localtime(&h2_time);
		weather->h2_time = mktime(h2_tm);
		weather->h2_pop  = h2_pop_tuple->value->int32;

		weather->hourly_enabled = true;
		weather->hourly_updated = time(NULL);
	}
	// Initial Javascript Ready message
	else if (js_ready_tuple) {
		weather->js_ready = true;
		weather->error    = WEATHER_E_OK;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Javascript is ready");
		debug_update_message("JS ready");
		initial_jsready_callback();
	}
	// Hourly enabled
	else if (hourly_enabled_tuple) {
		weather->hourly_enabled = (bool)hourly_enabled_tuple->value->int32;
		weather->hourly_updated = time(NULL);
	}
	else if (error_tuple) {
		weather->error   = WEATHER_E_NETWORK;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Error: %s", error_tuple->value->cstring);
	}
	else {
		weather->error = WEATHER_E_PHONE;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Message with unknown keys: t=%p c=%p e=%p",
		temperature_tuple, condition_tuple, error_tuple);
	}

	weather_layer_update(weather);
	face_color_update(weather, window);

	// Success! reset the retry count...
	retry_count = 0;
}

static char *translate_error(AppMessageResult result) 
{
  switch (result) {
    case APP_MSG_OK: return "APP_MSG_OK";
    case APP_MSG_SEND_TIMEOUT: return "APP_MSG_SEND_TIMEOUT";
    case APP_MSG_SEND_REJECTED: return "APP_MSG_SEND_REJECTED";
    case APP_MSG_NOT_CONNECTED: return "APP_MSG_NOT_CONNECTED";
    case APP_MSG_APP_NOT_RUNNING: return "APP_MSG_APP_NOT_RUNNING";
    case APP_MSG_INVALID_ARGS: return "APP_MSG_INVALID_ARGS";
    case APP_MSG_BUSY: return "APP_MSG_BUSY";
    case APP_MSG_BUFFER_OVERFLOW: return "APP_MSG_BUFFER_OVERFLOW";
    case APP_MSG_ALREADY_RELEASED: return "APP_MSG_ALREADY_RELEASED";
    case APP_MSG_CALLBACK_ALREADY_REGISTERED: return "APP_MSG_CALLBACK_ALREADY_REGISTERED";
    case APP_MSG_CALLBACK_NOT_REGISTERED: return "APP_MSG_CALLBACK_NOT_REGISTERED";
    case APP_MSG_OUT_OF_MEMORY: return "APP_MSG_OUT_OF_MEMORY";
    case APP_MSG_CLOSED: return "APP_MSG_CLOSED";
    case APP_MSG_INTERNAL_ERROR: return "APP_MSG_INTERNAL_ERROR";
    default: return "UNKNOWN ERROR";
  }
}

static void appmsg_in_dropped(AppMessageResult reason, void *context)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "In dropped: %s", translate_error(reason));
}

static void appmsg_out_sent(DictionaryIterator *sent, void *context) 
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Out sent.");
}

static void appmsg_out_failed(DictionaryIterator *failed, AppMessageResult reason, void *context) 
{
  WeatherData *weather_data = (WeatherData*) context;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Out failed: %s", translate_error(reason));

  retry_count++;
  
  switch (reason) {
    case APP_MSG_NOT_CONNECTED:
      weather_data->error = WEATHER_E_DISCONNECTED;
      request_weather(weather_data);
      break;
    case APP_MSG_SEND_REJECTED:
    case APP_MSG_SEND_TIMEOUT:
    default:
      weather_data->error = WEATHER_E_PHONE;
      request_weather(weather_data);
      break;
  }
}

void init_network(WeatherData *weather_data)
{
  int max_in  = 1200; //app_message_inbox_size_maximum();
  int max_out = 500; //app_message_outbox_size_maximum();

  app_message_register_inbox_received(appmsg_in_received);
  app_message_register_inbox_dropped(appmsg_in_dropped);
  app_message_register_outbox_sent(appmsg_out_sent);
  app_message_register_outbox_failed(appmsg_out_failed);
  app_message_set_context(weather_data);
  app_message_open(max_in, max_out);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage max_IN: %i, max_OUT: %i", max_in, max_out);

  weather_data->error    = WEATHER_E_OK;
  weather_data->updated  = 0;
  weather_data->js_ready = false;

  weather_data->hourly_updated = 0;
  weather_data->hourly_enabled = false;

  retry_count = 0;
}

void close_network()
{
  app_message_deregister_callbacks();
}

void request_weather(WeatherData *weather_data) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Request weather, retry: %i", retry_count);

	if (retry_count > MAX_RETRY) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Too many retries");
		retry_count = 0;
		return;
	}

	if (!bluetooth_connection_service_peek()) {
		weather_data->error = WEATHER_E_DISCONNECTED;
		return;
	}

	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
  
	if (iter == NULL) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Null iter");
		return;
	}

	dict_write_cstring(iter, KEY_SERVICE, weather_data->service);
	dict_write_cstring(iter, KEY_COLOR, weather_data->color);
	dict_write_cstring(iter, KEY_SCALE, weather_data->scale);
	dict_write_uint8(iter, KEY_DEBUG, (uint8_t)weather_data->debug);
	dict_write_uint8(iter, KEY_BATTERY, (uint8_t)weather_data->battery);
	dict_write_uint8(iter, KEY_BLUETOOTH, (uint8_t)weather_data->bluetooth);
	dict_write_uint8(iter, KEY_TIME_SIGNAL, (uint8_t)weather_data->timesig);
	dict_write_uint8(iter, KEY_STOP_HOURLY, (uint8_t)weather_data->stophourly);

	dict_write_end(iter);

	app_message_outbox_send();
}
