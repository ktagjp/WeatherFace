#include <pebble.h>
#include "network.h"
#include "weather_layer.h"
#include "debug_layer.h"

static Layer *weather_layer;

// Buffer the day / night time switch around sunrise & sunset
const int CIVIL_TWILIGHT_BUFFER = 900; // 15 minutes
const int WEATHER_ANIMATION_REFRESH = 1000; // 1 second animation 
const int WEATHER_INITIAL_RETRY_TIMEOUT = 65; // Maybe our initial request failed? Try again!
const int WEATHER_ANIMATION_TIMEOUT = 90; // 60 * WEATHER_ANIMATION_REFRESH = 60s
const int WEATHER_STALE_TIMEOUT = 60 * 60 * 2; // 2 hours in seconds

// Keep pointers to the two fonts we use.
static GFont large_font, small_font;

// Initial animation dots
static AppTimer *weather_animation_timer;
static bool animation_timer_enabled = true;
static int  animation_step = 0;

static char time_h1[] = "00XX";
static char time_h2[] = "00XX";

static void weather_animate_update(Layer *me, GContext *ctx) 
{
  int dots = 3; 
  int spacer = 15;
  
  graphics_context_set_fill_color(ctx, GColorBlack);

  for (int i=1; i<=dots; i++) {
    if (i == animation_step) {
      graphics_fill_circle(ctx, GPoint((i*spacer), 8), 5);
    } else {
      graphics_fill_circle(ctx, GPoint((i*spacer), 8), 3);
    }
  } 
}

static void weather_layer_set_icon(WeatherIcon icon, WeatherDisplayArea area) 
{
  WeatherLayerData *wld = layer_get_data(weather_layer);

  static int size = 0;
  static BitmapLayer *layer = NULL;
  static GBitmap *icons = NULL;

  switch (area) {
    case AREA_PRIMARY:
      size  = wld->primary_icon_size;
      layer = wld->primary_icon_layer;
      icons = wld->primary_icons;
      break;
    case AREA_HOURLY1:
      size  = wld->hourly_icon_size;
      layer = wld->h1_icon_layer;
      icons = wld->hourly_icons;
      break;
    case AREA_HOURLY2:
      size  = wld->hourly_icon_size;
      layer = wld->h2_icon_layer;
      icons = wld->hourly_icons;
      break;
  } 

  GBitmap *new_icon =  gbitmap_create_as_sub_bitmap(
    icons, GRect(icon%5*size, ((int)(icon/5))*size, size, size)
  );
  // Display the new bitmap
  bitmap_layer_set_bitmap(layer, new_icon);

  switch (area) {
    case AREA_PRIMARY:
      if (wld->primary_icon != NULL) gbitmap_destroy(wld->primary_icon);
      wld->primary_icon = new_icon;
      break;
    case AREA_HOURLY1:
      if (wld->h1_icon != NULL) gbitmap_destroy(wld->h1_icon);
      wld->h1_icon = new_icon;
      break;
    case AREA_HOURLY2:
      if (wld->h2_icon != NULL) gbitmap_destroy(wld->h2_icon);
      wld->h2_icon = new_icon;
      break;
  } 
}

static void weather_layer_set_error()
{
  WeatherLayerData *wld = layer_get_data(weather_layer);
  
  layer_set_frame(bitmap_layer_get_layer(wld->primary_icon_layer), PRIMARY_ICON_ERROR_FRAME);
  weather_layer_set_icon(W_ICON_PHONE_ERROR, AREA_PRIMARY);
}

void weather_animate(void *context)
{
  WeatherData *weather_data = (WeatherData*) context;
  WeatherLayerData *wld = layer_get_data(weather_layer);

  if (weather_data->updated == 0 && weather_data->error == WEATHER_E_OK) {    
    
    animation_step = (animation_step % 3) + 1;
    layer_mark_dirty(wld->loading_layer);
    weather_animation_timer = app_timer_register(WEATHER_ANIMATION_REFRESH, weather_animate, weather_data);

    if (animation_step == WEATHER_INITIAL_RETRY_TIMEOUT) {
      // Fire off one last desperate attempt...
      request_weather(weather_data);
    }

    if (animation_step > WEATHER_ANIMATION_TIMEOUT) {
      weather_data->error = WEATHER_E_NETWORK;
    }
  } 
  else if (weather_data->error != WEATHER_E_OK) {
    animation_step = 0;
    layer_set_hidden(wld->loading_layer, true);
    weather_layer_set_error();
  }
}

void weather_layer_create(GRect frame, Window *window)
{
  // Create a new layer with some extra space to save our custom Layer infos
  weather_layer = layer_create_with_data(frame, sizeof(WeatherLayerData));
  WeatherLayerData *wld = layer_get_data(weather_layer);

  large_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FUTURA_30));
  small_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FUTURA_17));

  wld->primary_icon_size = 45;
  wld->hourly_icon_size = 30;

  // Add background layer
  wld->temp_layer_background = text_layer_create(GRect(0, 0, 144, 80));
  text_layer_set_background_color(wld->temp_layer_background, GColorWhite);
  layer_add_child(weather_layer, text_layer_get_layer(wld->temp_layer_background));

  // Primary temperature layer
  wld->primary_temp_layer = text_layer_create(GRect(2, 38, 70, 35));
  text_layer_set_background_color(wld->primary_temp_layer, GColorClear);
  text_layer_set_text_alignment(wld->primary_temp_layer, GTextAlignmentCenter);
  text_layer_set_font(wld->primary_temp_layer, large_font);
  layer_add_child(weather_layer, text_layer_get_layer(wld->primary_temp_layer));

  
  wld->h1_time_layer = text_layer_create(GRect(68, 5, 30, 20));
  text_layer_set_text_color(wld->h1_time_layer, GColorBlack);
  text_layer_set_text_alignment(wld->h1_time_layer, GTextAlignmentCenter);
  layer_add_child(weather_layer, text_layer_get_layer(wld->h1_time_layer));

  wld->h1_temp_layer = text_layer_create(GRect(67, 47, 38, 20));
  text_layer_set_text_color(wld->h1_temp_layer, GColorBlack);
  text_layer_set_text_alignment(wld->h1_temp_layer, GTextAlignmentCenter);
  text_layer_set_font(wld->h1_temp_layer, small_font);
  layer_add_child(weather_layer, text_layer_get_layer(wld->h1_temp_layer));
  
  // Hour1 bitmap layer
  wld->h1_icon_layer = bitmap_layer_create(GRect(68, 20, wld->hourly_icon_size, wld->hourly_icon_size));
  layer_add_child(weather_layer, bitmap_layer_get_layer(wld->h1_icon_layer));

  
  wld->h2_time_layer = text_layer_create(GRect(108, 5, 30, 20));
  text_layer_set_text_color(wld->h1_time_layer, GColorBlack);
  text_layer_set_text_alignment(wld->h2_time_layer, GTextAlignmentCenter);
  layer_add_child(weather_layer, text_layer_get_layer(wld->h2_time_layer));

  wld->h2_temp_layer = text_layer_create(GRect(106, 47, 38, 20));
  text_layer_set_text_color(wld->h2_temp_layer, GColorBlack);
  text_layer_set_text_alignment(wld->h2_temp_layer, GTextAlignmentCenter);
  text_layer_set_font(wld->h2_temp_layer, small_font);
  layer_add_child(weather_layer, text_layer_get_layer(wld->h2_temp_layer));
   
  // Hour2 bitmap layer
  wld->h2_icon_layer = bitmap_layer_create(GRect(107, 20, wld->hourly_icon_size, wld->hourly_icon_size));
  layer_add_child(weather_layer, bitmap_layer_get_layer(wld->h2_icon_layer));

  // Primary bitmap layer
  wld->primary_icon_layer = bitmap_layer_create(PRIMARY_ICON_NORMAL_FRAME);
  layer_add_child(weather_layer, bitmap_layer_get_layer(wld->primary_icon_layer));

  wld->loading_layer = layer_create(GRect(43, 27, 50, 20));
  layer_set_update_proc(wld->loading_layer, weather_animate_update);
  layer_add_child(weather_layer, wld->loading_layer);

  wld->primary_icons = gbitmap_create_with_resource(RESOURCE_ID_ICON_45X45);
  wld->hourly_icons  = gbitmap_create_with_resource(RESOURCE_ID_ICON_30X30);

  wld->primary_icon = NULL;
  wld->h1_icon = NULL;
  wld->h2_icon = NULL;

  layer_add_child(window_get_root_layer(window), weather_layer);
}



void weather_layer_clear_temperature()
{
  WeatherLayerData *wld = layer_get_data(weather_layer);
  text_layer_set_text(wld->primary_temp_layer, "");
}

void weather_layer_set_temperature(int16_t t, bool is_stale)
{
  WeatherLayerData *wld = layer_get_data(weather_layer);

  snprintf(wld->primary_temp_str, sizeof(wld->primary_temp_str), 
    "%i%s", t, is_stale ? " " : "°");

  text_layer_set_text(wld->primary_temp_layer, wld->primary_temp_str);
}

static bool is_night_time(int sunrise, int sunset, int utc) 
{
  return utc < (sunrise - CIVIL_TWILIGHT_BUFFER) || 
         utc > (sunset  + CIVIL_TWILIGHT_BUFFER);
}

// Update the bottom half of the screen: icon and temperature
void weather_layer_update(WeatherData *weather_data) 
{
  // We have no weather data yet... don't update until we do
  if (weather_data->updated == 0) {
    return;
  }

  WeatherLayerData *wld = layer_get_data(weather_layer);

  if (weather_animation_timer && animation_timer_enabled) {
    app_timer_cancel(weather_animation_timer);
    // this is only needed to stop the error message when cancelling an already cancelled timer... 
    animation_timer_enabled = false;
    layer_set_hidden(wld->loading_layer, true);
  }

  time_t current_time = time(NULL);
  bool stale = false;
  if (current_time - weather_data->updated > WEATHER_STALE_TIMEOUT) {
    stale = true;
  }

  //APP_LOG(APP_LOG_LEVEL_DEBUG, "ct:%i wup:%i, stale:%i", 
  //  (int)current_time, (int)weather_data->updated, (int)WEATHER_STALE_TIMEOUT);

  // Update the weather icon and temperature
  if (weather_data->error) {
    // Only update the error icon if the weather data is stale
    if (stale) {
      weather_layer_clear_temperature();
      switch (weather_data->error) {
        case WEATHER_E_NETWORK:
          weather_layer_set_error();
          debug_update_message("Network error");
          break;
        case WEATHER_E_DISCONNECTED:
        case WEATHER_E_PHONE:
        default:
          weather_layer_set_error();
          debug_update_message("Phone disco / error");
          break;
      }
    }
  } else {

    layer_set_frame(bitmap_layer_get_layer(wld->primary_icon_layer), PRIMARY_ICON_NORMAL_FRAME);

    // Show the temperature as 'stale' if it has not been updated in WEATHER_STALE_TIMEOUT
    weather_layer_set_temperature(weather_data->temperature, stale);

    // Day/night check
    time_t utc = current_time + weather_data->tzoffset;
    bool night_time = is_night_time(weather_data->sunrise, weather_data->sunset, utc);

    /*
    APP_LOG(APP_LOG_LEVEL_DEBUG, 
       "ct:%i, utc:%i sr:%i, ss:%i, nt:%i", 
       (int)current_time, (int)utc, weather_data->sunrise, weather_data->sunset, night_time);
    */

    if (strcmp(weather_data->service, SERVICE_OPEN_WEATHER) == 0) {
      weather_layer_set_icon(open_weather_icon_for_condition(weather_data->condition, night_time), AREA_PRIMARY);
    } else {
      weather_layer_set_icon(yahoo_weather_icon_for_condition(weather_data->condition, night_time), AREA_PRIMARY);
    }

    if (weather_data->hourly_updated != 0 && weather_data->hourly_enabled) {

      time_t h1t = weather_data->h1_time - weather_data->tzoffset;
      time_t h2t = weather_data->h2_time - weather_data->tzoffset;
      strftime(time_h1, sizeof(time_h1), "%I%p", localtime(&h1t));
      strftime(time_h2, sizeof(time_h2), "%I%p", localtime(&h2t));

      if (time_h1[0] == '0') {
        memmove(time_h1, &time_h1[1], sizeof(time_h1) - 1);
      }
      if (time_h2[0] == '0') {
        memmove(time_h2, &time_h2[1], sizeof(time_h2) - 1);
      }

      text_layer_set_text(wld->h1_time_layer, time_h1);
      text_layer_set_text(wld->h2_time_layer, time_h2);

      localtime(&current_time);

      night_time = is_night_time(weather_data->sunrise, weather_data->sunset, weather_data->h1_time);
      weather_layer_set_icon(wunder_weather_icon_for_condition(weather_data->h1_cond, night_time), AREA_HOURLY1);

      night_time = is_night_time(weather_data->sunrise, weather_data->sunset, weather_data->h2_time);
      weather_layer_set_icon(wunder_weather_icon_for_condition(weather_data->h2_cond, night_time), AREA_HOURLY2);

      snprintf(wld->h1_temp_str, sizeof(wld->h1_temp_str), 
        "%i%s", weather_data->h1_temp, "°");
      snprintf(wld->h2_temp_str, sizeof(wld->h2_temp_str), 
        "%i%s", weather_data->h2_temp, "°");

      text_layer_set_text(wld->h1_temp_layer, wld->h1_temp_str);
      text_layer_set_text(wld->h2_temp_layer, wld->h2_temp_str);
    }
  }
}

void weather_layer_destroy() 
{
  if (weather_animation_timer && animation_timer_enabled) {
    app_timer_cancel(weather_animation_timer);
    animation_timer_enabled = false;
  }

  WeatherLayerData *wld = layer_get_data(weather_layer);

  text_layer_destroy(wld->primary_temp_layer);
  text_layer_destroy(wld->temp_layer_background);
  bitmap_layer_destroy(wld->primary_icon_layer);
  bitmap_layer_destroy(wld->h1_icon_layer);
  bitmap_layer_destroy(wld->h2_icon_layer);
  text_layer_destroy(wld->h1_time_layer);
  text_layer_destroy(wld->h2_time_layer);
  text_layer_destroy(wld->h1_temp_layer);
  text_layer_destroy(wld->h2_temp_layer);
  layer_destroy(wld->loading_layer);

  // Destroy the previous bitmap if we have one
  if (wld->primary_icon != NULL) {
    gbitmap_destroy(wld->primary_icon);
  }
  if (wld->primary_icons != NULL) {
    gbitmap_destroy(wld->primary_icons);
  }
  if (wld->h1_icon != NULL) {
    gbitmap_destroy(wld->h1_icon);
  }
  if (wld->h2_icon != NULL) {
    gbitmap_destroy(wld->h2_icon);
  }
  if (wld->hourly_icons != NULL) {
    gbitmap_destroy(wld->hourly_icons);
  }
  layer_destroy(weather_layer);

  fonts_unload_custom_font(large_font);
  fonts_unload_custom_font(small_font);
}

/*
 * Converts an API Weather Condition into one of our icons.
 * Refer to: http://bugs.openweathermap.org/projects/api/wiki/Weather_Condition_Codes
 */
uint8_t open_weather_icon_for_condition(int c, bool night_time) 
{
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "In Open Weather icon selection. c: %i, night: %i", c, night_time);

  if (c < 100) {
    return W_ICON_NOT_AVAILABLE;
  }
  // Thunderstorm
  else if (c < 300) {
    return W_ICON_THUNDER;
  }
  // Drizzle
  else if (c < 500) {
    return W_ICON_DRIZZLE;
  }
  // Freezing Rain
  else if (c == 511) {
    return W_ICON_RAIN_SLEET;
  }
  // Rain / Freezing rain / Shower rain
  else if (c < 600) {
    return W_ICON_RAIN;
  }
  // Sleet
  else if (c == 611 || c == 612) {
    return W_ICON_SNOW_SLEET;
  }
  // Rain and snow
  else if (c == 615 || c == 616) {
    return W_ICON_RAIN_SNOW;
  }
  // Rain and snow
  else if (c == 622) {
    return W_ICON_HEAVY_SNOW;
  }
  // Snow
  else if (c < 700) {
    return W_ICON_SNOW;
  }
  // Fog / Mist / Haze / etc.
  else if (c < 771) {
    return W_ICON_FOG;
  }
  // Tornado / Squalls
  else if (c < 800) {
    return W_ICON_WIND;
  }
  // Sky is clear
  else if (c == 800) {
    if (night_time)
      return W_ICON_CLEAR_NIGHT;
    else
      return W_ICON_CLEAR_DAY;
  }
    // Few clouds
  else if (c == 801) {
    if (night_time)
      return W_ICON_FAIR_NIGHT;
    else
      return W_ICON_FAIR_DAY;
  }
  // scattered clouds
  else if (c == 802) {
    if (night_time)
      return W_ICON_PARTLY_CLOUDY_NIGHT;
    else
      return W_ICON_PARTLY_CLOUDY_DAY;
  }
  // broken clouds
  else if (c == 803) {
    if (night_time)
      return W_ICON_CLOUDY;
    else
      return W_ICON_MOSTLY_CLOUDY_DAY;
  }
  // overcast clouds
  else if (c == 804) {
    return W_ICON_CLOUDY;
  }
  // Hail
  else if (c == 906) {
    return W_ICON_SLEET;
  }
  // Extreme
  else if ((c >= 900 && c <= 902) || c == 905 || (c >= 957 && c <= 962)) {
    return W_ICON_WIND;
  }
  // Cold
  else if (c == 903) {
      return W_ICON_COLD;
  }
  // Hot
  else if (c == 904) {
      return W_ICON_HOT;
  }
  // Gentle to strong breeze
  else if (c >= 950 && c <= 956) {
    if (night_time)
      return W_ICON_FAIR_NIGHT;
    else
      return W_ICON_FAIR_DAY;
  }
  else {
    // Weather condition not available
    return W_ICON_NOT_AVAILABLE;
  }
}

/*
 * Converts the Yahoo API Weather Condition into one of our icons.
 * Refer to: https://developer.yahoo.com/weather/#codes
 */
uint8_t yahoo_weather_icon_for_condition(int c, bool night_time) 
{
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "In Yahoo Weather icon selection. c: %i, night: %i", c, night_time);
  
  // Tornado / Hurricane / Wind
  if ((c >= 0 && c <= 2) || c == 23 || c == 24) {
    return W_ICON_WIND;
  }
  // Thunderstorm
  else if (c == 3 || c == 4 || c == 38 || c == 39) {
    return W_ICON_THUNDER;
  }
  // Rain & Snow
  else if (c == 5) {
    return W_ICON_RAIN_SNOW;
  }
  // Rain & Sleet / Mixed 
  else if (c == 6 || c == 8 || c == 10 || c == 35) {
    return W_ICON_RAIN_SLEET;
  }
  // Snow & Sleet
  else if (c == 7) {
    return W_ICON_SNOW_SLEET;
  }
  // Drizzle // Showers
  else if (c == 9 || c == 11) {
    return W_ICON_DRIZZLE;
  }
  // Rain / Scattered Showers / Thundershowers
  else if (c == 12 || c == 45) {
    return W_ICON_RAIN;
  }
  // Snow / Scattered Snow / Show Showers
  else if (c == 13 || c == 14 || c == 16 || c == 42 || c == 46) {
    return W_ICON_SNOW;
  }
  // Heavy Snow / Blowing Snow
  else if (c == 15 || c == 41 || c == 43) {
    return W_ICON_HEAVY_SNOW;
  }
  // Sleet
  else if (c == 17 || c == 18) {
    return W_ICON_SLEET;
  }
  // Fog / Mist / Haze / etc.
  else if (c >= 19 && c <= 22) {
    return W_ICON_FOG;
  }
  // Cold
  else if (c == 25) {
    return W_ICON_COLD;
  }
  // Cloudy
  else if (c == 26) {
    return W_ICON_CLOUDY;
  }
  // Mostly Cloudy
  else if (c == 27 || c == 28) {
    if (night_time)
      return W_ICON_CLOUDY;
    else
      return W_ICON_MOSTLY_CLOUDY_DAY;
  }
  // Partly Cloudy or Fair
  else if (c == 29 || c == 30 || c == 44) {
    if (night_time)
      return W_ICON_PARTLY_CLOUDY_NIGHT;
    else
      return W_ICON_PARTLY_CLOUDY_DAY;
  }
  // Clear Day Night
  else if (c == 31 || c == 32) {
    if (night_time)
      return W_ICON_CLEAR_NIGHT;
    else
      return W_ICON_CLEAR_DAY;
  }
  // Fair Day Night
  else if (c == 33 || c == 34) {
    if (night_time)
      return W_ICON_FAIR_NIGHT;
    else
      return W_ICON_FAIR_DAY;
  }
  // Hot
  else if (c == 36) {
      return W_ICON_HOT;
  }
  // Isolated / Scattered Thunderstorm
  else if ((c >= 37 && c <= 39) || c == 47) {
    if (night_time)
      return W_ICON_THUNDER;
    else
      return W_ICON_THUNDER_SUN;
  }
  // Scattered Showers
  else if (c == 40) {
    if (night_time)
      return W_ICON_RAIN;
    else
      return W_ICON_RAIN_SUN;
  }
  // Weather condition not available
  else {
    return W_ICON_NOT_AVAILABLE;
  }
}

/*
 * Converts the Weather Underground API Weather Condition into one of our icons.
 * Refer to: http://www.wunderground.com/weather/api/d/docs?d=resources/phrase-glossary#forecast_description_numbers
 */
uint8_t wunder_weather_icon_for_condition(int c, bool night_time) 
{
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "In Yahoo Weather icon selection. c: %i, night: %i", c, night_time);
  
  // Clear
  if (c == 1) {
    if (night_time)
      return W_ICON_CLEAR_NIGHT;
    else
      return W_ICON_CLEAR_DAY;
  }
  // Partly Cloudy
  else if (c == 2) {
    if (night_time)
      return W_ICON_FAIR_NIGHT;
    else
      return W_ICON_FAIR_DAY;
  }
  // Mostly CLoudly
  else if (c == 3) {
    if (night_time)
      return W_ICON_PARTLY_CLOUDY_NIGHT;
    else
      return W_ICON_PARTLY_CLOUDY_DAY;
  }
  // Cloudly
  else if (c == 4) {
    return W_ICON_CLOUDY;
  }
  // Haze / Fog
  else if (c == 5 || c == 6) {
    return W_ICON_FOG;
  }
  // Very Warm
  else if (c == 7) {
      return W_ICON_HOT;
  }
  // Very Cold
  else if (c == 8) {
    return W_ICON_COLD;
  }
  // Blowing Snow
  else if (c == 9 || c == 20 || c == 21 || c == 24) {
    return W_ICON_SNOW;
  }
  // Chance of Showers
  else if (c == 10) {
    if (night_time)
      return W_ICON_DRIZZLE;
    else
      return W_ICON_RAIN_SUN;
  }
  // Showers
  else if (c == 11) {
    return W_ICON_DRIZZLE;
  }
  // Chance of Rain
  else if (c == 12) {
    if (night_time)
      return W_ICON_RAIN;
    else
      return W_ICON_RAIN_SUN;
  }
  // Rain
  else if (c == 13) {
    return W_ICON_RAIN;
  }
  // Chance of Thunderstorm
  else if (c == 14) {
    if (night_time)
      return W_ICON_THUNDER;
    else
      return W_ICON_THUNDER_SUN;
  }
  // Thunderstorms
  else if (c == 15) {
    return W_ICON_THUNDER;
  }
  // Flurries 
  else if (c == 16) {
    return W_ICON_SLEET;
  }
  // Chance of Snow Showers, Snow Showers (wtf)
  else if (c == 18 || c == 19) {
    return W_ICON_SNOW_SLEET;
  }
  // Chance of Ice Pellets, Ice Pellets
  else if (c == 22 || c == 23) {
    return W_ICON_SLEET;
  }
  else {
    return W_ICON_NOT_AVAILABLE;
  }
}