#include "initialise.h"
#include "error.h"

Game_Reqs::Game_Reqs(float inFPS, float inWidth, float inHeight) {
  FPS = inFPS;
  screen_w = inWidth;
  screen_h = inHeight;

  check_init(this);
  check_audio();
  reserve_audio_samples(2);

  load_booster_sound(this, "resources/sound/booster.ogg");
  load_blackhole_sound(this, "resources/sound/blackhole_noise.ogg");
  
  check_keyboard(this);
  set_timer(this, FPS);
  set_font(this, "resources/fonts/LiberationSerif-Bold.ttf", -72);

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
  al_destroy_sample(booster);
  al_destroy_sample(noise);
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
