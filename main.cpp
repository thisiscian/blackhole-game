#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "entity/blackhole.h"
#include "entity/player.h"
#include "engine/error.h"
#include "engine/initialise.h"
using namespace std;

  enum MYKEYS {
    KUP,KDOWN,KLEFT,KRIGHT
  };

int main(int argc, char** argv) {
  Game_Reqs reqs(60,640,480);
  ALLEGRO_COLOR background = al_map_rgb_f(0.0,0.0,0.0);

  bool key[4] = {false,false,false,false};
  bool redraw = true;

  al_clear_to_color(background);

  BlackHole blackhole(reqs.get_width(),reqs.get_height(), 1500, 100);
  Player player(&reqs, 1600);
  player.draw();
  blackhole.draw();
  al_flip_display();
  al_start_timer(reqs.timer);

  while(1){
    ALLEGRO_EVENT ev;
    al_wait_for_event(reqs.event_queue, &ev);
    
    if(ev.type == ALLEGRO_EVENT_TIMER) {
      if(key[KLEFT]) {
        player.left(key[KLEFT]);
      }
      if(key[KRIGHT]) {
        player.right(key[KRIGHT]);
      }
      if(key[KUP]) {
        player.up(key[KUP]);
      }
      if(key[KDOWN]) {
        player.down(key[KDOWN]);
      }
      redraw = true;
    } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    } else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          key[KLEFT] = true;
          break;
        case ALLEGRO_KEY_RIGHT:
          key[KRIGHT] = true;
          break;
        case ALLEGRO_KEY_UP:
          key[KUP] = true;
          break;
        case ALLEGRO_KEY_DOWN:
          key[KDOWN] = true;
          break;
      }
    } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          key[KLEFT] = false;
          break;
        case ALLEGRO_KEY_RIGHT:
          key[KRIGHT] = false;
          break;
        case ALLEGRO_KEY_UP:
          key[KUP] = false;
          break;
        case ALLEGRO_KEY_DOWN:
          key[KDOWN] = false;
          break;
      }
    }
    if(redraw && al_is_event_queue_empty(reqs.event_queue)) {
      redraw = false;
      al_clear_to_color(background);
      blackhole.draw();
      player.draw();
      blackhole.change_offset(player.get_angle());
      blackhole.change_height(player.get_radial_position());
      al_flip_display();
    }
  }
  player.destroy();
  reqs.destroy();
  return 0;
}
