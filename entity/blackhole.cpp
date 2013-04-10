#include "blackhole.h"
#define PI 3.1415926

BlackHole::BlackHole(int screen_width, int screen_height, int rad, int height) {
  radius = rad;
  screen_w = screen_width;
  screen_h = screen_height;
  center[0] = screen_w/2;
  center[1] = radius - height + screen_h;
  colour = al_map_rgb_f(0.01,0.0,0.01);
  offset = 0.0;
  calculate_arc();
}

void BlackHole::calculate_arc() {
  arc_height = radius - center[1] + screen_h;
  angle = 2*atan(screen_w/(2*(center[1]-screen_h)));
}

void BlackHole::draw() {
  calculate_arc();
  int max = ceil(angle*36.0/PI);
  if(offset >= PI/72) {
    offset -= PI/36;
  }
  if(offset < -PI/72) {
    offset += PI/36;
  }
  for(int i=-max/2;i<=max/2;i++){
    al_draw_line(center[0],center[1], screen_w/2+center[1]*tan(i*PI/36+offset),0, al_map_rgba_f(0.0,0.0,0.2,0.1),1);
    al_draw_line(center[0],center[1], screen_w/2+center[1]*tan(i*PI/36+offset),0, al_map_rgba_f(0.0,0.0,0.1,0.05),3);
  }
  for(int i=-screen_h+screen_h%100; i<=100; i+=100) {
    al_draw_arc(center[0],center[1],floor(center[1]/100)*100+i,-(angle+PI)/2, angle, al_map_rgba_f(0.0,0.0,0.2,0.1), 1);
    al_draw_arc(center[0],center[1],floor(center[1]/100)*100+i,-(angle+PI)/2, angle, al_map_rgba_f(0.0,0.0,0.1,0.05), 3);
  }
//  for(int i=0;i<300;i++) {
//    al_draw_arc(center[0],center[1],radius+i,-(angle+PI)/2, angle, al_map_rgba_f(0.5*(1.0-i/300.0),0,0.05*(1.0-i/300.0), 0.5),1);
//  }
  for(int i=0;i<50;i++) {
    al_draw_arc(center[0],center[1],radius+i,-(angle+PI)/2, angle, al_map_rgba_f(0.07*(1-i/50.0),0,0.2*(1-i/50.0),0.5),1);
  }
  al_draw_arc(center[0],center[1],radius-arc_height/2,-(angle+PI)/2, angle, colour, arc_height+5);
  
}

void BlackHole::change_offset(float new_offset) {
  offset = new_offset - floor((new_offset*36/PI))*PI/36;
}

void BlackHole::change_height(float height) {
  center[1] = height+screen_h/2;
}

