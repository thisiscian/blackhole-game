CXX=g++
WINC=i486-mingw32-g++
SRC=src/main.cpp $(wildcard src/entity/*.cpp) $(wildcard src/engine/*.cpp)
DEST=blackhole

LINUXFLAGS=-lallegro_main-static -lallegro_color-static -lallegro_acodec-static -lFLAC -logg -lvorbisfile -lvorbis -logg -lallegro_audio-static -lallegro_primitives-static -lallegro_image-static -lpng -lz -ljpeg -lallegro_ttf-static -lfreetype -lz -lallegro_font-static -lallegro-static -lm -lSM -lICE -Wl,-Bdynamic -lpthread -lX11 -lpulse-simple -lpulse -lasound -lopenal -lXext -lXcursor -lXinerama -lXrandr -lXpm  -lGL -lGLU
CPPFLAGS=-Wall -Iheaders/ -Ldeps/linux/ -Wl,-Bstatic -lm $(LINUXFLAGS)
#WINFLAGS=-Bdeps/windows/ -Iheaders/ -I/usr/local/include -static-libgcc -static-libstdc++ -lallegro-5.0.dll -lallegro_image-5.0.dll -lallegro_font-5.0.dll -lallegro_audio-5.0.dll -lallegro_primitives-5.0.dll -lallegro_acodec-5.0.dll
#WINFLAGS=-Bdeps/windows/ -Xlinker "-Ldeps/windows/" -Iheaders/ -I/usr/local/include -static-libgcc -static-libstdc++ -I/usr/i486-mingw32/include -L/usr/i486-mingw32/lib -lallegro_acodec-static -lallegro_audio-static -lpulse-simple -lpulse -lasound -lopenal -lallegro_audio -lallegro -lallegro_color-static -lallegro_image-static -lallegro_primitives-static -lallegro-static -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -lwinmm -lpsapi -lshlwapi -ld3d9 -ldinput8 -lstdc++ -lopengl32 -lglu32 
WINFLAGS=-Bdeps/windows/ -Xlinker "-Ldeps/windows/" -Iheaders/ -I/usr/local/include -static-libgcc -static-libstdc++ -I/usr/i486-mingw32/include -L/usr/i486-mingw32/lib -lallegro_acodec-static -lallegro_audio-static -lallegro_color-static -lallegro_image-static -lallegro_primitives-static -lallegro-static -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -lwinmm -lpsapi -lshlwapi -ld3d9 -ldinput8 -lstdc++ -lopengl32 -lglu32 
#WINFLAGS=-v -Xlinker "-Ldeps/windows/" -Bdeps/windows/ -Iheaders/ -I/usr/local/include -static-libgcc -static-libstdc++ -lallegro-static -lallegro_image-static -lallegro_font-static -lallegro_audio-static -lallegro_primitives-static -lallegro_acodec-static
OBJ=$(SRC:.cpp=.o)

linux-inst: $(OBJ)
	$(CXX) -o $(DEST) $(OBJ) $(CPPFLAGS)

windows-inst: Makefile $(OBJ)
#	$(foreach, file,$(SRC), $(WINC) -c -o $(patsubst %.cpp,%.o, $(file)) $(WINFLAGS))
#	$(WINC) -o $(DEST).exe $(OBJ) $(WINFLAGS)
#	rm -f $(OBJ)
	$(WINC) -o $(DEST).exe $(SRC) $(WINFLAGS)

$(OBJ): Makefile

clean:
	@rm -f $(OBJ) $(DEST)
