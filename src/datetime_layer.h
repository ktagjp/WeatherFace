#ifndef DATETIME_LAYER_H
#define DATETIME_LAYER_H

void TimeSignal(void);
void set_time_signal(int, int);
void enable_time_signal(void);
void disable_time_signal(void);

void date_layer_create(GRect frame, Window *window);
void time_layer_create(GRect frame, Window *window);
void date_layer_update(struct tm *tick_time);
void time_layer_update();
void date_layer_destroy();
void time_layer_destroy();

extern bool Is_TimeSignal_Enable;

#endif