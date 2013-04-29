#ifndef __blackhole_error_h__
#define __blackhole_error_h__

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "initialise.h"
#include <string>
#include <iostream>

enum blackhole_errors {
  SYSTEM_OK,
  INIT_FAIL,
  PRIMITIVES_FAIL,
  AUDIO_FAIL,
  AUDIO_CODEC_FAIL,
  RESERVE_SAMPLE_FAIL,
  SAMPLE_LOAD_FAIL,
  KEYBOARD_FAIL,
  TIMER_FAIL,
  FONT_LOAD_FAIL,
  IMAGE_ADDON_FAIL,
  DISPLAY_FAIL,
  EVENT_QUEUE_FAIL,
  BITMAP_LOAD_FAIL
};

void check_init(Game_Reqs *reqs);
void check_audio();
void check_primitives();
void reserve_audio_samples(int num);
void load_booster_sound(Game_Reqs *reqs, ALLEGRO_FILE *booster_file);
void load_blackhole_sound(Game_Reqs *reqs, ALLEGRO_FILE *blackhole_file);
void check_keyboard(Game_Reqs *reqs);
void set_timer(Game_Reqs *reqs, int fps);
//void set_font(Game_Reqs *reqs, std::string path, int size);
void check_image_addon(Game_Reqs *reqs);
void check_display(Game_Reqs *reqs);
void check_event_queue(Game_Reqs *reqs);
void check_sprite(Game_Reqs *reqs, ALLEGRO_BITMAP *sprite);

#endif
