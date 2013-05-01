#ifndef __entity_h__
#define __entity_h__

#define ALLEGRO_STATIC_LINK
#include "engine/engine.h"
#include "entity/blackhole.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <vector>

class Entity {
  public:
  float mass;
  float r[3]; // radial displacement, velocity and acceleration from center of the black hole
  float s[3]; // angular displacement, velocity and acceleration from center of the black hole
  float t[3]; // angular displacement, velocity and acceleration about own axis

  float engine_fuel, thrust_fuel;

  int current_frame, maximum_frames;
  int current_state, maximum_states;
  int current_thrust_wait_time, maximum_thrust_wait_time;

  int display_size[2];
  int sprite_size[2];
  std::vector< std::vector<ALLEGRO_BITMAP*> > sprite;
  
  Entity();
  Entity(Engine *engine, ALLEGRO_BITMAP *spritesheet, int maxmimum_frames, int maxmimum_states);
  void update(), draw(), destroy();
  void generate_spritesheet(Engine *engine, ALLEGRO_BITMAP *spritesheet, int maxmimum_frames, int maxmimum_states);
};

#endif
