#include "error.h"

void check_init(Game_Reqs *reqs) {
   if(!al_init()) {
    std::cerr << "ERROR: Allegro failed to initialize" << std::endl;
    reqs->destroy();
    exit(INIT_FAIL);
  }
}

void check_keyboard(Game_Reqs *reqs) {
  if(!al_install_keyboard()) {
    std::cerr << "ERROR: Allegro failed to install keyboard" << std::endl;
    reqs->destroy();
    exit(KEYBOARD_FAIL);
  }
}

void check_timer(Game_Reqs *reqs) {
  if(!reqs->timer) {
    std::cerr << "ERROR: Failed to create timer" << std::endl;
    reqs->destroy();
    exit(TIMER_FAIL);
  }
}

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
