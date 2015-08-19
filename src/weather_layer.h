#define PRIMARY_ICON_NORMAL_FRAME  (GRect(9, 0, 45, 45))
#define PRIMARY_ICON_ERROR_FRAME   (GRect(50, 12, 45, 45))

#ifndef W_LAYER_H
#define W_LAYER_H

typedef struct {
	Layer *loading_layer;
	TextLayer *temp_layer_background;
	TextLayer *primary_temp_layer;

	GBitmap *primary_icons;
	GBitmap *hourly_icons;

	int primary_icon_size;
	int hourly_icon_size;

	GBitmap *primary_icon;
	BitmapLayer *primary_icon_layer;

	GBitmap *h1_icon;
	BitmapLayer *h1_icon_layer;
	TextLayer *h1_time_layer;
	TextLayer *h1_temp_layer;
	TextLayer *h1_pop_layer;

    GBitmap *h2_icon;
	BitmapLayer *h2_icon_layer;
	TextLayer *h2_time_layer;
	TextLayer *h2_temp_layer;
	TextLayer *h2_pop_layer;

	char primary_temp_str[6];
	char h1_temp_str[6];
	char h2_temp_str[6];
} WeatherLayerData;

typedef enum {
	W_ICON_CLEAR_DAY = 0,
    W_ICON_FAIR_DAY,
	W_ICON_PARTLY_CLOUDY_DAY,
	W_ICON_MOSTLY_CLOUDY_DAY,
	W_ICON_CLOUDY,
	W_ICON_CLEAR_NIGHT,
    W_ICON_FAIR_NIGHT,
	W_ICON_PARTLY_CLOUDY_NIGHT,
	W_ICON_WIND,
	W_ICON_FOG,
	W_ICON_DRIZZLE,
	W_ICON_RAIN,
	W_ICON_RAIN_SLEET,
	W_ICON_SLEET,
	W_ICON_SNOW_SLEET,
	W_ICON_HEAVY_SNOW,
	W_ICON_SNOW,
	W_ICON_RAIN_SNOW,
    W_ICON_RAIN_SUN,
    W_ICON_THUNDER_SUN,
	W_ICON_THUNDER,
	W_ICON_COLD,
	W_ICON_HOT,
	W_ICON_PHONE_ERROR,
	W_ICON_NOT_AVAILABLE,
	W_ICON_COUNT
} WeatherIcon;

typedef enum {
	AREA_PRIMARY = 0,
	AREA_HOURLY1,
	AREA_HOURLY2
} WeatherDisplayArea;

void weather_layer_create(GRect frame, Window *window);
void weather_animate(void *context);
void weather_layer_update(WeatherData *weather_data);
void weather_layer_destroy();
void weather_layer_set_temperature(int16_t t, bool is_stale);
void weather_layer_clear_temperature();
uint8_t open_weather_icon_for_condition(int condition, bool night_time);
uint8_t yahoo_weather_icon_for_condition(int condition, bool night_time);
uint8_t wunder_weather_icon_for_condition(int c, bool night_time);

#endif
