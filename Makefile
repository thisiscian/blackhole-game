CC=g++
SRC=main.cpp $(wildcard entity/*.cpp) $(wildcard engine/*.cpp)
DEST=blackhole
CFLAGS=-Wall -lm `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
OBJ=$(SRC:.cpp=.o)

opengl-test: $(OBJ)
	$(CC) -o $(DEST) $(OBJ) $(CFLAGS)

$(OBJ): Makefile

clean:
	@rm -f $(OBJ) $(DEST)