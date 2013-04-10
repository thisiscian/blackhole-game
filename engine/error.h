#ifndef __blackhole_error_h__
#define __blackhole_error_h__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "initialise.h"
#include <iostream>

enum blackhole_errors {
  SYSTEM_OK,
  INIT_FAIL,
  TIMER_FAIL,
  KEYBOARD_FAIL,
  IMAGE_ADDON_FAIL,
  DISPLAY_FAIL,
  EVENT_QUEUE_FAIL,
  BITMAP_LOAD_FAIL
};

void check_init(Game_Reqs *reqs);
void check_keyboard(Game_Reqs *reqs);
void check_timer(Game_Reqs *reqs);
void check_image_addon(Game_Reqs *reqs);
void check_display(Game_Reqs *reqs);
void check_event_queue(Game_Reqs *reqs);
void check_sprite(Game_Reqs *reqs, ALLEGRO_BITMAP *sprite);

#endif
