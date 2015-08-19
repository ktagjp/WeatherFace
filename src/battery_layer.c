#include <pebble.h>
#include "battery_layer.h"

const uint32_t BATTERY_TIMEOUT = 2000; // 2 second animation 
const uint8_t  MAX_DOTS = 4;

static Layer *battery_layer;

static AppTimer *battery_animation_timer;
static bool is_animating = false;
static bool is_enabled   = false;
static int8_t dots = 4; 

static void handle_battery(BatteryChargeState charge_state) 
{
  if (charge_state.is_charging || charge_state.is_plugged) {

    if (!is_animating) {
       is_animating = true;
       battery_animation_timer = app_timer_register(BATTERY_TIMEOUT, battery_timer_callback, NULL);
    }
    return;

  } 
  else {

    is_animating = false;
    if (battery_animation_timer) {
      app_timer_cancel(battery_animation_timer);
    }
    
    uint8_t charge = charge_state.charge_percent;
    if (charge >= 90) {
      dots = MAX_DOTS;
    } else if (charge >= 65 && charge < 90) {
      dots = 3;
    } else if (charge >= 35 && charge < 65) {
      dots = 2;
    } else {
      dots = 1;
    }
  }

  layer_mark_dirty(battery_layer);
}


void battery_layer_create(GRect frame, Window *window)
{
  battery_layer = layer_create(frame);
  layer_set_update_proc(battery_layer, battery_layer_update);
  layer_add_child(window_get_root_layer(window), battery_layer);
}

void battery_enable_display() 
{
  if (is_enabled) {
    return;
  }

  is_animating = false;
  is_enabled = true;

  // Kickoff first update
  handle_battery(battery_state_service_peek());

  // Subscribe to the battery monitoring service
  battery_state_service_subscribe(&handle_battery);

  layer_set_hidden(battery_layer, false);
}

void battery_disable_display() 
{
  is_animating = false;
  is_enabled = false;

  layer_set_hidden(battery_layer, true);

  // Unsubscribe to the battery monitoring service
  battery_state_service_unsubscribe();

  // Kill the timer
  if (battery_animation_timer) {
    app_timer_cancel(battery_animation_timer);
  }
}

void battery_timer_callback()
{
  dots++;
  if (dots > MAX_DOTS) {
    dots = 1;
  }
  layer_mark_dirty(battery_layer);
  battery_animation_timer = app_timer_register(BATTERY_TIMEOUT, battery_timer_callback, NULL);
}

void battery_layer_update(Layer *me, GContext *ctx) 
{
  int8_t spacer  = 7; // pixels
  int8_t start_x = spacer * MAX_DOTS;
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  for (int i=0; i<MAX_DOTS; i++) {
    if (i<dots) {
      graphics_fill_circle(ctx, GPoint(start_x-(i*spacer), 4), 2);
    } else {
      graphics_draw_circle(ctx, GPoint(start_x-(i*spacer), 4), 2);
    }
  } 
}

void battery_layer_destroy() 
{
  battery_disable_display();
  layer_destroy(battery_layer);
}



