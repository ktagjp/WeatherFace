#include <pebble.h>

#define KEY_TEMPERATURE 0
#define KEY_CONDITION 1
#define KEY_SUNRISE 2
#define KEY_SUNSET 3
#define KEY_PUB_DATE 4
#define KEY_ERROR 5
#define KEY_SERVICE 6
#define KEY_LOCALE 7
#define KEY_DEBUG 8
#define KEY_JS_READY 9
#define KEY_SCALE 10
#define KEY_BATTERY 11
#define KEY_TZOFFSET 12
#define KEY_H1_TEMP 13
#define KEY_H1_COND 14
#define KEY_H1_TIME 15
#define KEY_H1_POP 16
#define KEY_H2_TEMP 17
#define KEY_H2_COND 18
#define KEY_H2_TIME 19
#define KEY_H2_POP 20
#define KEY_HOURLY_ENABLED 21

#define SERVICE_OPEN_WEATHER "open"
#define SERVICE_YAHOO_WEATHER "yahoo"
#define SCALE_FAHRENHEIT "F"
#define SCALE_CELSIUS "C"

typedef enum {
  WEATHER_E_OK = 0,
  WEATHER_E_DISCONNECTED,
  WEATHER_E_PHONE,
  WEATHER_E_NETWORK
} WeatherError;

typedef struct {
  int temperature;
  int condition;
  int sunrise;
  int sunset;
  char pub_date[6];
  int tzoffset;
  char locale[255];
  
  char service[6];
  char scale[2];
  bool debug;
  bool battery;

  int h1_temp;
  int h1_cond;
  int h1_time;
  int h1_pop;
  int h2_temp;
  int h2_cond;
  int h2_time;
  int h2_pop;
  bool hourly_enabled;
  time_t hourly_updated;

  bool js_ready; 
  time_t updated;
  WeatherError error;
} WeatherData;

void init_network(WeatherData *weather_data);
void close_network();
void request_weather(WeatherData *weather_data);
