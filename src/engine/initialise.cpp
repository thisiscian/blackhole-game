#include "engine/initialise.h"
#include "engine/error.h"

BH_ADD_RESOURCE(resources_sound_booster_ogg, booster_mem, booster_size);
BH_ADD_RESOURCE(resources_sound_blackhole_noise_ogg, blackhole_noise_mem, blackhole_noise_size);

Game_Reqs::Game_Reqs(float inFPS, float inWidth, float inHeight) {
  FPS = inFPS;
  screen_w = inWidth;
  screen_h = inHeight;

  check_init(this);
  check_primitives();
  check_audio();
  reserve_audio_samples(2);

  ALLEGRO_FILE *booster_file = al_open_memfile(booster_mem,booster_size, "r");
  ALLEGRO_FILE *blackhole_file = al_open_memfile(blackhole_noise_mem,blackhole_noise_size, "r");

  load_booster_sound(this, booster_file);
  load_blackhole_sound(this, blackhole_file);
  
  check_keyboard(this);
  set_timer(this, FPS);
  //set_font(this, "resources/fonts/LiberationSerif-Bold.ttf", -72);

  check_image_addon(this);
  display = al_create_display(screen_w,screen_h);
  check_display(this);

  event_queue = al_create_event_queue();
  check_event_queue(this);

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void Game_Reqs::destroy() {
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_sample(booster_sample);
  al_destroy_sample(blackhole_noise_sample);
}

float Game_Reqs::get_FPS() {
  return FPS;
}

float Game_Reqs::get_width() {
  return screen_w;
}

float Game_Reqs::get_height() {
  return screen_h;
}
