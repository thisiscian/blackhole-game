#include "entity/entity.h"

Entity::Entity() {};
Entity::Entity(Engine *engine, ALLEGRO_BITMAP *spritesheet, int frame_count, int state_count) {
  int spritesheet_width = al_get_bitmap_width(spritesheet);
  int spritesheet_height = al_get_bitmap_height(spritesheet);

  mass = 1;
  r[0] = r[1] = r[2] = 0;
  s[0] = s[1] = s[2] = 0;
  t[0] = t[1] = t[2] = 0;

  thrust_fuel = 0;
  engine_fuel = 0;
  current_thrust_wait_time = 0;
  maximum_thrust_wait_time = 10;

  current_frame = 0;
  maximum_frames = frame_count;
  current_state = 0;
  maximum_states = state_count;

  display_size[0] = engine->get_width();
  display_size[1] = engine->get_height();

  sprite.resize(maximum_states);
  for(int i=0; i<maximum_states; i++) {
    sprite[i].resize(maximum_frames);
  }

  sprite_size[0] = spritesheet_width/maximum_frames;
  sprite_size[1] = spritesheet_height/maximum_states;
  generate_spritesheet(engine, spritesheet, maximum_frames, maximum_states);
}

void Entity::update() {
  current_frame++;
  current_thrust_wait_time++;
}

void Entity::generate_spritesheet(Engine *engine, ALLEGRO_BITMAP *spritesheet, int maximum_frames, int maximum_states) {
  for(int i=0; i<maximum_states; i++) {
    for(int j=0; j<maximum_frames; j++) {
      sprite[i][j] = al_create_sub_bitmap(spritesheet,sprite_size[0]*j,sprite_size[1]*i,sprite_size[0],sprite_size[1]);
      check_sprite(sprite[i][j], "issues with subsprite");
    }
  }
  return;
}

void Entity::destroy() {
  for(int i=0; i<sprite.size(); i++) {
    for(int j=0; j<sprite[i].size(); j++) {
      al_destroy_bitmap(sprite[i][j]);
    }
  }
  return; 
}
