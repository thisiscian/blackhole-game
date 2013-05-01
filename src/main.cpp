#define ALLEGRO_STATICLINK
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "entity/blackhole.h"
#include "entity/player.h"
#include "engine/engine.h"
using namespace std;

  enum MYKEYS {
    KUP,KDOWN,KLEFT,KRIGHT
  };

int main(int argc, char** argv) {
  bool key_down[4] = {false,false,false,false};
  bool redraw = true;
  Engine engine(60,640,480);

  ALLEGRO_COLOR background = al_map_rgb_f(0.0,0.0,0.0);
  al_clear_to_color(background);

  BlackHole blackhole(engine.get_width(),engine.get_height(), 1500, 100);
  Player player(&engine, 1600);
  player.draw();
  blackhole.draw();

  al_flip_display();
  al_start_timer(engine.timer);

  while(1){
    ALLEGRO_EVENT ev;
    al_wait_for_event(engine.event_queue, &ev);
    
    if(ev.type == ALLEGRO_EVENT_TIMER) {
      player.left(key_down[KLEFT]);
      player.right(key_down[KRIGHT]);
      player.up(key_down[KUP]);
      player.down(key_down[KDOWN]);
      redraw = true;
    } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    } else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          key_down[KLEFT] = true;
          break;
        case ALLEGRO_KEY_RIGHT:
          key_down[KRIGHT] = true;
          break;
        case ALLEGRO_KEY_UP:
          key_down[KUP] = true;
          break;
        case ALLEGRO_KEY_DOWN:
          key_down[KDOWN] = true;
          break;
        case ALLEGRO_KEY_Q:
          player.destroy();
          engine.destroy();
          exit(0);
          break;
      }
    } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          key_down[KLEFT] = false;
          break;
        case ALLEGRO_KEY_RIGHT:
          key_down[KRIGHT] = false;
          break;
        case ALLEGRO_KEY_UP:
          key_down[KUP] = false;
          break;
        case ALLEGRO_KEY_DOWN:
          key_down[KDOWN] = false;
          break;
      }
    }
    if(redraw && al_is_event_queue_empty(engine.event_queue)) {
      redraw = false;
      al_clear_to_color(background);
      blackhole.draw();
      player.update();
      player.draw();
      blackhole.change_height(player.get_r());
      blackhole.change_offset(player.get_s());
      al_flip_display();
    }
  }
  player.destroy();
  engine.destroy();
  return 0;
}
