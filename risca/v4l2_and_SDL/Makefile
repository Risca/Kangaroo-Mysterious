SOURCES    = v4l2_and_SDL.c v4l2_inc.c SDL_inc.c
EXECUTABLE = v4l2_and_SDL

CC=gcc
PKGCONFIG=pkg-config

CFLAGS  += $(shell $(PKGCONFIG) --cflags sdl) -Wall
LDFLAGS +=
LIBS    += $(shell $(PKGCONFIG) --libs sdl) -lv4l2

all: $(EXECUTABLE)

%: %.c
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(LIBS)

clean:
	@rm -rf $(EXECUTABLE)
