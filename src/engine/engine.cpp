#include "engine/engine.h"

Engine::Engine(float in_FPS, float in_screen_w, float in_screen_h) {
  FPS = in_FPS;
  screen_w = in_screen_w;
  screen_h = in_screen_h;

  check_init();
  check_primitives();
  check_audio();
  reserve_audio_samples(5);
  check_keyboard();
  timer = get_timer(FPS);
  display = get_display(screen_w, screen_h);
  check_image_addon();
  event_queue = get_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void Engine::destroy() {
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
}

float Engine::get_FPS() {
  return FPS;
}

float Engine::get_width() {
  return screen_w;
}

float Engine::get_height() {
  return screen_h;
}

void check_init() {
   if(!al_init()) {
    std::cerr << "ERROR: Allegro failed to initialize" << std::endl;
    exit(INIT_FAIL);
  }
}

void check_audio() {
   if(!al_install_audio()){
    std::cerr << "ERROR: Allegro failed to install audio" << std::endl;
    exit(AUDIO_FAIL);
  }
  if(!al_init_acodec_addon()) {
    std::cerr << "ERROR: Allegro failed to install audio codecs" << std::endl;
    exit(AUDIO_CODEC_FAIL);
  }
}

void reserve_audio_samples(int num) {
  if (!al_reserve_samples(2)){
   std::cerr << "ERROR: Allegro failed to allocate audio samples" << std::endl;
   exit(RESERVE_SAMPLE_FAIL);
  }
}

ALLEGRO_SAMPLE* get_sample(ALLEGRO_FILE *file, std::string message) {
  ALLEGRO_SAMPLE *sample = al_load_sample_f(file, ".ogg");
  if(!sample) {
    std::cerr << "ERROR: failed to load sample: " << message << std::endl;
    exit(SAMPLE_LOAD_FAIL);
  } 
  return sample;
}

void check_keyboard() {
  if(!al_install_keyboard()) {
    std::cerr << "ERROR: Allegro failed to install keyboard" << std::endl;
    exit(KEYBOARD_FAIL);
  }
}

ALLEGRO_TIMER *get_timer(int fps) {
  ALLEGRO_TIMER *timer = al_create_timer(1.0/fps);
  if(!timer) {
    std::cerr << "ERROR: Failed to create timer" << std::endl;
    exit(TIMER_FAIL);
  }
  return timer;
}

void check_primitives() {
  if(!al_init_primitives_addon()) {
    std::cerr << "ERROR: Failed to initialise primitives" << std::endl;
    exit(PRIMITIVES_FAIL);
  }
}

void check_image_addon() {
  if(!al_init_image_addon()) {
    std::cerr << "ERROR: Failed to initialise image addon" << std::endl;
    exit(IMAGE_ADDON_FAIL);
  }
}

ALLEGRO_DISPLAY* get_display(int screen_w, int screen_h) {
  ALLEGRO_DISPLAY *display = al_create_display(screen_w,screen_h);
  if(!display) {
    std::cerr << "ERROR: Allegro display was not created" << std::endl;
    exit(DISPLAY_FAIL);
  }
  return display;
}

ALLEGRO_EVENT_QUEUE* get_event_queue() {
  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  if(!event_queue) {
    std::cerr << "ERROR: Allegro failed to create event queue" << std::endl;
    exit(EVENT_QUEUE_FAIL);
  }
  return event_queue;
}

void check_sprite(ALLEGRO_BITMAP *sprite, std::string path) {
  if(!sprite) {
    std::cerr << "ERROR: Allegro failed to load bitmap: " << path << std::endl;
    exit(BITMAP_LOAD_FAIL);
  }
}
