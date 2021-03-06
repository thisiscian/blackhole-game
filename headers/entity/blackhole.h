#ifndef __blackhole_h__
#define __blackhole_h__

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_audio.h"
#include "engine/engine.h"
#include <math.h>

class BlackHole{
  private:
    float center[2];
    float radius;
    float angle;
    ALLEGRO_COLOR colour;
    float time;
    int arc_height;
    int screen_w, screen_h;
    float offset;
    void calculate_arc();
  
  public: 
  BlackHole(int screen_w, int screen_h, int radius, int height);
  void draw();
  void change_offset(float new_offset);
  void change_height(float new_height);
  ALLEGRO_SAMPLE *sample;
  ALLEGRO_SAMPLE_ID sample_id;
};

#endif
