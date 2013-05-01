#ifndef __blackhole_engine_h__
#define __blackhole_engine_h__

#define ALLEGRO_STATICLINK
#include "allegro5/allegro.h"
#include "allegro5/allegro_memfile.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "engine/engine.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#ifdef _WIN32
  #include <windows.h>
  #include "allegro5/allegro_windows.h"
  #define BH_ADD_RESOURCE(path, nick1, nick2) \
    extern unsigned char binary_ ## path ## _start; \
    extern int binary_ ## path ## _size; \
    void *nick1 = & binary_ ## path ## _start;\
    int nick2 = (int) & binary_ ## path ## _size;
#else 
  #define BH_ADD_RESOURCE(path, nick1, nick2) \
    extern unsigned char _binary_ ## path ## _start; \
    extern int _binary_ ## path ## _size; \
    void *nick1 = &_binary_ ## path ## _start; \
    int nick2 = (int) & _binary_ ## path ## _size;
#endif

enum blackhole_errors {
  SYSTEM_OK,
  INIT_FAIL,
  PRIMITIVES_FAIL,
  AUDIO_FAIL,
  AUDIO_CODEC_FAIL,
  RESERVE_SAMPLE_FAIL,
  SAMPLE_LOAD_FAIL,
  KEYBOARD_FAIL,
  TIMER_FAIL,
  FONT_LOAD_FAIL,
  IMAGE_ADDON_FAIL,
  DISPLAY_FAIL,
  EVENT_QUEUE_FAIL,
  BITMAP_LOAD_FAIL
};

class Engine {
  private:
    float FPS;
    float screen_w;
    float screen_h;

  public: 
    Engine(float FPS, float width, float height);
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_SAMPLE_ID noise_id;

    float get_FPS();
    float get_width();
    float get_height();
    void destroy();
};

void check_init();
void check_audio();
void check_primitives();
void reserve_audio_samples(int num);
void load_blackhole_sound(ALLEGRO_FILE *blackhole_file);
void check_keyboard();
void check_image_addon();
void check_sprite(ALLEGRO_BITMAP *sprite, std::string path);

ALLEGRO_TIMER* get_timer(int fps);
ALLEGRO_SAMPLE* get_sample(ALLEGRO_FILE *booster_file, std::string message);
ALLEGRO_DISPLAY* get_display(int screen_w, int screen_h);
ALLEGRO_EVENT_QUEUE* get_event_queue();


#endif
