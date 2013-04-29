#define ALLEGRO_STATICLINK
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
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
  ALLEGRO_SAMPLE_ID booster_id[4];
  bool redraw = true;

  al_clear_to_color(background);

  BlackHole blackhole(reqs.get_width(),reqs.get_height(), 1500, 100);
  Player player(&reqs, 1600);
  player.draw();
  blackhole.draw();
  al_play_sample(reqs.blackhole_noise_sample,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP, &reqs.noise_id);
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
          al_play_sample(reqs.booster_sample,1.0,1.0,1.0,ALLEGRO_PLAYMODE_ONCE,&booster_id[KLEFT]);
          break;
        case ALLEGRO_KEY_RIGHT:
          key[KRIGHT] = true;
          al_play_sample(reqs.booster_sample,1.0,-1.0,1.0,ALLEGRO_PLAYMODE_ONCE,&booster_id[KRIGHT]);
          break;
        case ALLEGRO_KEY_UP:
          key[KUP] = true;
          al_play_sample(reqs.booster_sample,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&booster_id[KUP]);
          break;
        case ALLEGRO_KEY_DOWN:
          key[KDOWN] = true;
          al_play_sample(reqs.booster_sample,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&booster_id[KDOWN]);
          break;
        case ALLEGRO_KEY_Q:
          player.destroy();
          reqs.destroy();
          exit(0);
          break;
      }
    } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          key[KLEFT] = false;
          al_stop_sample(&booster_id[KLEFT]);
          break;
        case ALLEGRO_KEY_RIGHT:
          key[KRIGHT] = false;
          al_stop_sample(&booster_id[KRIGHT]);
          break;
        case ALLEGRO_KEY_UP:
          key[KUP] = false;
          al_stop_sample(&booster_id[KUP]);
          break;
        case ALLEGRO_KEY_DOWN:
          key[KDOWN] = false;
          al_stop_sample(&booster_id[KDOWN]);
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
