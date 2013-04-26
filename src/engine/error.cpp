#include "engine/error.h"

void check_init(Game_Reqs *reqs) {
   if(!al_init()) {
    std::cerr << "ERROR: Allegro failed to initialize" << std::endl;
    reqs->destroy();
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

void load_booster_sound(Game_Reqs *reqs, std::string path) {
  reqs->booster = al_load_sample(path.c_str());
  if(!reqs->booster) {
    std::cerr << "ERROR: failed to load \"" << path << "\"" << std::endl;
    reqs->destroy();
    exit(SAMPLE_LOAD_FAIL);
  } 
}

void load_blackhole_sound(Game_Reqs *reqs, std::string path) {
  reqs->noise = al_load_sample(path.c_str());
  if(!reqs->noise) {
    std::cerr << "ERROR: failed to load \"" << path << "\"" << std::endl;
    reqs->destroy();
    exit(SAMPLE_LOAD_FAIL);
  } 
}

void check_keyboard(Game_Reqs *reqs) {
  if(!al_install_keyboard()) {
    std::cerr << "ERROR: Allegro failed to install keyboard" << std::endl;
    reqs->destroy();
    exit(KEYBOARD_FAIL);
  }
}

void set_timer(Game_Reqs *reqs, int fps) {
  reqs->timer = al_create_timer(1.0/fps);
  if(!reqs->timer) {
    std::cerr << "ERROR: Failed to create timer" << std::endl;
    reqs->destroy();
    exit(TIMER_FAIL);
  }
}

/*
void set_font(Game_Reqs *reqs, std::string path, int size) {
  al_init_font_addon();
  al_init_ttf_addon();
  reqs->font = al_load_ttf_font(path.c_str(), size, 0);
  if(!reqs->font) {
    std::cout << "Error: Failed to load font at \"" << path << "\"" << std::endl;
    exit(FONT_LOAD_FAIL);
  } 
}
*/

void check_image_addon(Game_Reqs *reqs) {
  if(!al_init_image_addon()) {
    std::cerr << "ERROR: Failed to initialise image addon" << std::endl;
    reqs->destroy();
    exit(IMAGE_ADDON_FAIL);
  }
}

void check_display(Game_Reqs *reqs) {
  if(!reqs->display) {
    std::cerr << "ERROR: Allegro display was not created" << std::endl;
    reqs->destroy();
    exit(DISPLAY_FAIL);
  }
}

void check_event_queue(Game_Reqs *reqs) {
  if(!reqs->event_queue) {
    std::cerr << "ERROR: Allegro failed to create event queue" << std::endl;
    reqs->destroy();
    exit(EVENT_QUEUE_FAIL);
  }
}

void check_sprite(Game_Reqs *reqs, ALLEGRO_BITMAP *sprite) {
  if(!sprite) {
    std::cerr << "ERROR: Allegro failed to load bitmap" << std::endl;
    reqs->destroy();
    exit(BITMAP_LOAD_FAIL);
  }
}
