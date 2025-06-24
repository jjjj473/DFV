CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0 gstreamer-1.0 gstreamer-video-1.0 ges-1.0` -O2 -Wall
LDLIBS=`pkg-config --libs gtk+-3.0 gstreamer-1.0 gstreamer-video-1.0 ges-1.0`

dfv_editor: src/dfv_editor.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

all: dfv_editor

clean:
	rm -f dfv_editor

.PHONY: all clean
