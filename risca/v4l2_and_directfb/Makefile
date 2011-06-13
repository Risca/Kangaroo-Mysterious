SOURCES    = v4l2_and_directfb.c v4l2_inc.c directfb_inc.c
EXECUTABLE = v4l2_and_directfb

CC=gcc
PKGCONFIG=pkg-config

CFLAGS  += $(shell $(PKGCONFIG) --cflags directfb)
LDFLAGS +=
LIBS    += $(shell $(PKGCONFIG) --libs directfb) -lv4l2

all: $(EXECUTABLE)

%: %.c
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(LIBS)

clean:
	@rm -rf $(EXECUTABLE)
