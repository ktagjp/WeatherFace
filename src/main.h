#ifndef MAIN_H
#define MAIN_H

#include "network.h"

void initial_jsready_callback();
void face_color_update(WeatherData *weather_data, Window *win);

extern Window *window;

#endif