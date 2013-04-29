LINXX=g++
LINLD=ld
LINOBJCOPY=objcopy
WINXX=i486-mingw32-g++
WINLD=i486-mingw32-ld
WINOBJCOPY=/usr/i486-mingw32/bin/objcopy
SRC=src/main.cpp $(wildcard src/entity/*.cpp) $(wildcard src/engine/*.cpp)
DEST=blackhole

RESOURCES=resources/animations/player_ship.png resources/sound/booster.ogg resources/sound/blackhole_noise.ogg
RESOURCESBIN=$(subst png,o,$(subst ogg,o,$(RESOURCES)))

ALLEGROLIBS= allegro_main-static-5.0, allegro_memfile-static-5.0 allegro_color-static-5.0 allegro_acodec-static-5.0 allegro_audio-static-5.0 allegro_primitives-static-5.0 allegro_image-static-5.0 allegro-static-5.0

LINALLEGROPATH = /usr/local/lib/pkgconfig
WINALLEGROPATH = /usr/i486-mingw32/lib/pkgconfig

STARTFLAGS=-Iheaders/ -Wl,-Bstatic
ENDFLAGS=-Wl,-Bdynamic

#WINFLAGS=-Iheaders/ -I/usr/i486-mingw32/include -L/usr/i486-mingw32/lib -lallegro_memfile-static -lallegro_acodec-static -lallegro_audio-static -ldsound -lallegro_color-static -lallegro_image-static -lallegro_primitives-static -lallegro-static -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -lwinmm -lpsapi -lshlwapi -ld3d9 -ldinput8 -lopengl32 -lglu32  -static-libgcc -static-libstdc++ 

linux: set_lin compile

windows: set_win compile

compile: test-exist $(OBJ) convert-resources
	$(CXX) -o $(DEST) $(SRC) $(CPPFLAGS) $(RESOURCESBIN)

set_lin:
	@ echo "Linux mode" $(eval CXX=$(LINXX)) \
  $(eval LD=$(LINLD)) \
  $(eval ALLEGRO_L=$(shell export PKG_CONFIG_PATH=$(LINALLEGROPATH); pkg-config --static --cflags --libs-only-L $(ALLEGROLIBS))) \
  $(eval ALLEGRO_l=$(filter-out $(ALLEGRO_L), $(shell export PKG_CONFIG_PATH=$(LINALLEGROPATH); pkg-config --static --libs-only-l --cflags $(ALLEGROLIBS)))) \
  $(eval OBJCOPY=$(LINOBJCOPY))

set_win:
	@ echo "Windows mode" $(eval CXX=$(WINXX)) \
	$(eval CPPFLAGS=$(CPPFLAGS)) \
  $(eval LD=$(WINLD)) \
  $(eval ALLEGRO_L=$(shell export PKG_CONFIG_PATH=$(WINALLEGROPATH); pkg-config --static --cflags --libs-only-L $(ALLEGROLIBS))) \
  $(eval ALLEGRO_l=$(filter-out $(ALLEGRO_L), $(shell export PKG_CONFIG_PATH=$(WINALLEGROPATH); pkg-config --static --libs-only-l --cflags $(ALLEGROLIBS)))) \
  $(eval DEST=$(DEST).exe) \
	$(eval OBJCOPY=$(WINOBJCOPY))\


test-exist:
	@$(foreach lib, $(ALLEGRO_l), $(if $(shell ($(LD) $(ALLEGRO_L) -o lib-test -Bstatic $(lib) 2>/dev/null && (echo true && rm lib-test))), printf "" $(eval STARTFLAGS=$(STARTFLAGS) $(lib)), echo "Cannot find $(lib) as static library, using shared library instead" $(eval ENDFLAGS=$(ENDFLAGS) $(lib)));)
	$(eval CPPFLAGS=$(STARTFLAGS) $(ENDFLAGS) -static-libgcc -static-libstdc++)

convert-resources:
	$(foreach resource, $(RESOURCES), $(OBJCOPY) --input binary --output elf32-i386 -B i386 $(resource) `echo $(resource) | sed 's/\.png//;s/\.ogg//;'`.o;)

$(OBJ): Makefile

clean:
	@rm -f $(OBJ) $(DEST) $(DEST).exe $(RESOURCESBIN)
