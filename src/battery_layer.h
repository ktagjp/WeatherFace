#ifndef BATTERY_LAYER_H
#define BATTERY_LAYER_H

void battery_layer_create(GRect frame, Window *window);
void battery_enable_display();
void battery_disable_display();
void battery_timer_callback();
void battery_layer_update(Layer *me, GContext *ctx);
void battery_layer_destroy();

#endif