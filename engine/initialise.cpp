#include "initialise.h"
#include "error.h"

Game_Reqs::Game_Reqs(float inFPS, float inWidth, float inHeight) {
  FPS = inFPS;
  screen_w = inWidth;
  screen_h = inHeight;

  check_init(this);
  check_keyboard(this);

  timer = al_create_timer(1.0/FPS);
  check_timer(this);

  al_init_font_addon();
  al_init_ttf_addon();
  font = al_load_ttf_font("engine/LiberationSerif-Bold.ttf", -72,0);
  if(!font) {
    std::cout << "oi" << std::endl;
  }

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
