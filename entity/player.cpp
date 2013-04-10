#include "player.h"
#include <iostream>
using namespace std;

Player::Player(Game_Reqs *reqs, int radius) {
  anim_state = 0;

  r = radius;
  vel_r = 0;
  force_r = 0;
  
  theta = 0.0;
  vel_theta = 0.0;
  force_theta = 0.0;

  sprite_w = 38;
  sprite_h = 38;

  display_w = reqs->get_width();
  display_h = reqs->get_height();
  
  boost_fuel = 100;
  fuel = 10000;
  wait_for_boost = 5;

  sprite = al_load_bitmap("img/ship002.png");
  check_sprite(reqs, sprite);

  for(int i=0; i<5; i++) {
    anim_up[i] = al_create_sub_bitmap(sprite,2+40*i,2,38,38);
    check_sprite(reqs,anim_up[i]);
  }

  for(int i=0; i<3; i++) {
    anim_left[i] = al_create_sub_bitmap(sprite,2+40*i,42,38,38);
    check_sprite(reqs,anim_left[i]);
  }
}

void Player::left(bool move) {
  if(move && boost_fuel > 0) {
    force_theta -= 0.5;
    boost_fuel -= 2;
    wait_for_boost = 0;
  }
}

void Player::right(bool move) {
  if(move && boost_fuel > 0) {
    force_theta += 0.5;
    boost_fuel -= 2;
    wait_for_boost = 0;
  }
}

void Player::up(bool move) {
  if(move && boost_fuel > 0) {
    force_r += 100.0;
    boost_fuel -= 2;
    wait_for_boost = 0;
  }
}
void Player::down(bool move) {
  if(move && boost_fuel > 0) {
    force_r -= 100.0;
    boost_fuel -= 2;
    wait_for_boost = 0;
  }
}

void Player::draw() {
  //al_draw_scaled_rotated_bitmap(anim_up[anim_state],sprite_w/2,sprite_h,display_w/2+r*sin(theta),display_h/2-r*cos(theta),0.75,0.75,theta,0);

  int bw = 2;
  int ox = 30, oy=10;
  //boost fuel meter
  al_draw_filled_rectangle(display_w-ox+bw, oy-bw, display_w-10-ox-bw, 100+bw+oy, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_rectangle(display_w-ox, 100+oy-boost_fuel, display_w-10-ox, 100+oy, al_map_rgb_f(0.3,0.3,0.8));
  al_draw_filled_rectangle(display_w-ox, oy, display_w-10-ox, 100+oy-boost_fuel, al_map_rgb_f(0.1,0.0,0.1));
  al_draw_filled_triangle(display_w-ox-10, 100+bw+5+oy, display_w-ox-10, 100+oy+bw+15, display_w-5-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_triangle(display_w-ox-5, 100+bw+5+oy, display_w-ox-5, 100+oy+bw+15, display_w-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));
  
  ox = 10;
  //overall fuel meter
  al_draw_filled_rectangle(display_w-ox+bw, oy-bw, display_w-10-ox-bw, 100+bw+oy, al_map_rgb_f(0.3,0.3,0.3));
  al_draw_filled_rectangle(display_w-ox, 100+oy-fuel/100, display_w-10-ox, 100+oy, al_map_rgb_f(0.8,0.3,0.3));
  al_draw_filled_rectangle(display_w-ox, oy, display_w-10-ox, 100+oy-fuel/100, al_map_rgb_f(0.1,0.0,0.1));
  al_draw_filled_triangle(display_w-ox-7, 100+bw+5+oy, display_w-ox-7, 100+oy+bw+15, display_w-2-ox, 100+bw+oy+10, al_map_rgb_f(0.3,0.3,0.3));

  al_draw_bitmap(anim_up[anim_state],(display_w-sprite_w)/2,(display_h-sprite_h)/2,0);

  anim_state++;
  anim_state = anim_state % 5;

  vel_theta += (force_theta-vel_theta)/60;
  theta += vel_theta/60+0.5*force_theta/360;
  force_theta = 0.0;

  float grav_force = -10000/pow(r-1500,2);
  if(fuel <= 0) {
    grav_force *=100;
  }

  vel_r += (force_r+grav_force-vel_r)/60;
  r += vel_r/60+force_r/720;
  force_r = 0.0;
  if(boost_fuel < 100 && wait_for_boost == 10) {
    boost_fuel++;
  }
  if(wait_for_boost < 10) {
    wait_for_boost++;
  }
  if(fuel > 0) {
    fuel-=10;
  }
  if(r <= 1500+sprite_h/2) {
    exit(0);
  }
}

void Player::destroy() {
  al_destroy_bitmap(sprite);
}

float Player::get_angle() {
  return theta;
}

float Player::get_radial_position() {
  return r;
}

