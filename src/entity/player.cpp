#include "entity/player.h"

BH_ADD_RESOURCE(resources_sound_booster_ogg, booster_mem, booster_size);
BH_ADD_RESOURCE(resources_animations_player_ship_png, player_ship_mem, player_ship_size)

Player::Player(Engine *engine, int radius) {
  ALLEGRO_FILE *booster_file = al_open_memfile(booster_mem,booster_size, "r");
  ALLEGRO_FILE *spritesheet_file = al_open_memfile(player_ship_mem,player_ship_size, "r");
  ALLEGRO_BITMAP *spritesheet = al_load_bitmap_f(spritesheet_file, ".png");
  check_sprite(spritesheet, "resources/animations/player_ship.png");
  thruster = get_sample(booster_file, "booster.ogg");

  me = Entity(engine, spritesheet, 5, 32);

  me.r[0] = radius;
  me.mass = 20000;
  
  me.thrust_fuel = 100;
  me.engine_fuel = 1000;
}

void Player::down(bool key_down) {
  int value=1;
  if(key_down && me.thrust_fuel > 0) {
      me.r[2] -= 100.0;
      me.thrust_fuel -= 2;
      me.current_thrust_wait_time = 0;
  }
  if ((me.current_state%(2*value))/value == 0 && key_down) {
    me.current_state+=value;
    al_play_sample(thruster,1.0,0.0,0.9,ALLEGRO_PLAYMODE_ONCE,&thruster_id[0]);
  } else if ((me.current_state%(2*value))/value == 1 && !key_down) {
    me.current_state-=value;
    al_stop_sample(&thruster_id[0]);
  }
}

void Player::right(bool key_down) {
  int value=2;
  if(key_down && me.thrust_fuel > 0) {
      me.s[2] += 0.5;
      me.thrust_fuel -= 2;
      me.current_thrust_wait_time = 0;
  }
  if ((me.current_state%(2*value))/value == 0 && key_down) {
    me.current_state+=value;
    al_play_sample(thruster,1.0,0.0,0.9,ALLEGRO_PLAYMODE_ONCE,&thruster_id[1]);
  } else if ((me.current_state%(2*value))/value == 1 && !key_down) {
    me.current_state-=value;
    al_stop_sample(&thruster_id[1]);
  }
}

void Player::up(bool key_down) {
  int value=4;
  if(key_down && me.thrust_fuel > 0) {
      me.r[2] += 100.0;
      me.thrust_fuel -= 2;
      me.current_thrust_wait_time = 0;
  }
  if ((me.current_state%(2*value))/value == 0 && key_down) {
    me.current_state+=value;
    al_play_sample(thruster,1.0,0.0,0.9,ALLEGRO_PLAYMODE_ONCE,&thruster_id[2]);
  } else if ((me.current_state%(2*value))/value == 1 && !key_down) {
    me.current_state-=value;
    al_stop_sample(&thruster_id[2]);
  }
}

void Player::left(bool key_down) {
  int value=8;
  if(key_down && me.thrust_fuel > 0) {
      me.s[2] -= 0.5;
      me.thrust_fuel -= 2;
      me.current_thrust_wait_time = 0;
  }
  if ((me.current_state%(2*value))/value == 0 && key_down) {
    me.current_state+=value;
    al_play_sample(thruster,1.0,0.0,0.9,ALLEGRO_PLAYMODE_ONCE,&thruster_id[3]);
  } else if ((me.current_state%(2*value))/value == 1 && !key_down) {
    me.current_state-=value;
    al_stop_sample(&thruster_id[3]);
  } 
}

void Player::update() {
  me.update();
  me.current_frame = me.current_frame % me.maximum_frames;

  me.s[1] += (me.s[2]-me.s[1])/60;
  me.s[0] += me.s[1]/60+0.5*me.s[2]/360;
  me.s[2] = 0.0;

  float grav_force = -10000/pow(me.r[0]-1500,2);
  if(me.engine_fuel == 0) {
    grav_force *=100;
    if(me.current_state < 16) {
      me.current_state += 16;
    }
  }

  me.r[1] += (me.r[2]+grav_force-me.r[1])/60;
  me.r[0] += me.r[1]/60+me.r[2]/720;
  me.r[2] = 0.0;

  if(me.thrust_fuel < 100 && me.current_thrust_wait_time >= me.maximum_thrust_wait_time) {
    me.thrust_fuel++;
  }

  if(me.engine_fuel > 0) {
    me.engine_fuel--;
  }
}

void Player::draw() {
  int bw = 2;
  int ox = 30, oy=10;
  //thrust fuel meter
  al_draw_filled_rectangle(me.display_size[0]-ox+bw, oy-bw, me.display_size[0]-10-ox-bw, 100+bw+oy, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_rectangle(me.display_size[0]-ox, 100+oy-me.thrust_fuel, me.display_size[0]-10-ox, 100+oy, al_map_rgb_f(0.3,0.3,0.8));
  al_draw_filled_rectangle(me.display_size[0]-ox, oy, me.display_size[0]-10-ox, 100+oy-me.thrust_fuel, al_map_rgb_f(0.1,0.0,0.1));
  al_draw_filled_triangle(me.display_size[0]-ox-10, 100+bw+5+oy, me.display_size[0]-ox-10, 100+oy+bw+15, me.display_size[0]-5-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_triangle(me.display_size[0]-ox-5, 100+bw+5+oy, me.display_size[0]-ox-5, 100+oy+bw+15, me.display_size[0]-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));
  
  ox = 10;
  //engine fuel meter
  al_draw_filled_rectangle(me.display_size[0]-ox+bw, oy-bw, me.display_size[0]-10-ox-bw, 100+bw+oy, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_rectangle(me.display_size[0]-ox, 100+oy-me.engine_fuel/10, me.display_size[0]-10-ox, 100+oy, al_map_rgb_f(0.8,0.3,0.3));
  al_draw_filled_rectangle(me.display_size[0]-ox, oy, me.display_size[0]-10-ox, 100+oy-me.engine_fuel/10, al_map_rgb_f(0.1,0.0,0.1));
  al_draw_filled_triangle(me.display_size[0]-ox-7, 100+bw+5+oy, me.display_size[0]-ox-7, 100+oy+bw+15, me.display_size[0]-2-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));

  al_draw_bitmap(me.sprite[me.current_state][me.current_frame],(me.display_size[0]-me.sprite_size[0])/2,(me.display_size[1]-me.sprite_size[1])/2,0);

  if(me.r[0] <= 1500+me.sprite_size[1]/2) {
    me.r[0] = 1501;
    al_clear_to_color(al_map_rgb_f(0,0,0));
  }}

float Player::get_r() {
  return me.r[0];
}

float Player::get_s() {
  return me.s[0];
}

void Player::destroy() {
  me.destroy();  
}
