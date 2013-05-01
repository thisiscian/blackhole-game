#ifndef __player_h__
#define __player_h__

#include <math.h>
#include "entity/entity.h"
#include "allegro5/allegro_memfile.h"
#include "engine/engine.h"

class Player {
  private:
  ALLEGRO_SAMPLE *thruster;
  ALLEGRO_SAMPLE_ID thruster_id[4];
  Entity me;
  int display_size[2];

  public:
  Player(Engine *engine, int radius);
  void up(bool move);
  void right(bool move);
  void down(bool move);
  void left(bool move);

  float get_r(), get_s();
  void draw(), update(), destroy();
};

#endif
