PREFIX := .

CFLAGS := -Isrc -I. -I../../allegro/include 
LDFLAGS = src/icon.res -L../../allegro/lib
LDLIBS := -L. -lalgif -lalleg

# When compiled with Allegro 4.1, don't warn about all the deprecated 4.0
# functions.
CFLAGS += -Wno-deprecated-declarations

default: libalgif.a

%.o: %.c
	gcc -I../../allegro/include -c -o $@ $<

libalgif.a: src\algif.o src\gif.o src\lzw.o
	ar -rcs $@ $^

algif_examples: load_gif load_animation load_raw_animation save_raw_animation

load_gif: examples\load_gif\main.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)

load_animation: examples\load_animation\main.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)

load_raw_animation: examples\load_raw_animation\main.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)

save_raw_animation: examples\save_raw_animation\main.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)

install:
	copy libalgif.a $(PREFIX)\lib
	copy src\algif.h $(PREFIX)\include

uninstall:
	del $(PREFIX)\lib\libalgif.a
	del $(PREFIX)\include\algif.h
