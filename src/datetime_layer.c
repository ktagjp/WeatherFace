#include <pebble.h>
#include "datetime_layer.h"

bool Is_TimeSignal_Enable = 0;

static int ts_start_time = 7;
static int ts_end_time   = 22;

static TextLayer *time_layer;
static TextLayer *date_layer;

static char date_text[] = "XXX 00";
static char time_text[] = "00:00";

/* Preload the fonts */
GFont font_date;
GFont font_time;

// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:
static const uint32_t const segments[] = { 50, 500, 50 };

static VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

void TimeSignal(void) {
	time_t currentTime = time(NULL);
    
	// Update the time - Fix to deal with 12 / 24 centering bug
	struct tm *currentLocalTime = localtime(&currentTime);

	if (currentLocalTime->tm_min == 0 && Is_TimeSignal_Enable) {
		if (ts_start_time == ts_end_time) {
			vibes_enqueue_custom_pattern(pat); 		 //  When BT is lost connection, vibrate three times.
		} else if (ts_start_time < ts_end_time) {
			if (currentLocalTime->tm_hour >= ts_start_time && currentLocalTime->tm_hour <= ts_end_time)
				vibes_enqueue_custom_pattern(pat);   //  When BT is lost connection, vibrate three times.
		} else {
			if (currentLocalTime->tm_hour >= ts_start_time || currentLocalTime->tm_hour <= ts_end_time)
				vibes_enqueue_custom_pattern(pat);   //  When BT is lost connection, vibrate three times.
		}
	}
}

void set_time_signal(int start, int end) {
	ts_start_time = start;
	ts_end_time   = end;
}

void enable_time_signal(void) {
	Is_TimeSignal_Enable = 1;
}

void disable_time_signal(void) {
	Is_TimeSignal_Enable = 0;
}

void time_layer_create(GRect frame, Window *window)
{
  font_time = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FUTURA_CONDENSED_53));

  time_layer = text_layer_create(frame);
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_font(time_layer, font_time);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

void date_layer_create(GRect frame, Window *window)
{
  font_date = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FUTURA_18));

  date_layer = text_layer_create(frame);
  text_layer_set_text_color(date_layer, GColorWhite);
  text_layer_set_background_color(date_layer, GColorClear);
  text_layer_set_font(date_layer, font_date);
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_layer));
}

void time_layer_update()
{
  time_t currentTime = time(NULL);
    
  // Update the time - Fix to deal with 12 / 24 centering bug
  struct tm *currentLocalTime = localtime(&currentTime);

  // Manually format the time as 12 / 24 hour, as specified
  strftime(   time_text, 
              sizeof(time_text), 
              clock_is_24h_style() ? "%R" : "%I:%M", 
              currentLocalTime);

  // Drop the first char of time_text if needed
  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }

  text_layer_set_text(time_layer, time_text);
}

void date_layer_update(struct tm *tick_time)
{
  // Update the date - Without a leading 0 on the day of the month
  char day_text[4];
  strftime(day_text, sizeof(day_text), "%a", tick_time);
  snprintf(date_text, sizeof(date_text), "%s %i", day_text, tick_time->tm_mday);
  text_layer_set_text(date_layer, date_text);
}

void time_layer_destroy() 
{
  text_layer_destroy(time_layer);
  fonts_unload_custom_font(font_time);
}

void date_layer_destroy() 
{
  text_layer_destroy(date_layer);
  fonts_unload_custom_font(font_date);
}

