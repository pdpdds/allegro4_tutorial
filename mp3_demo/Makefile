
TARGET=DJGPP_STATIC


CC=gcc
LFLAGS=-s



# DJGPP_STATIC
ifeq ($(TARGET),DJGPP_STATIC)
TARGETFLAGS=-Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math
OUT=main.exe
LIBS=../thirdparty/almp3/lib/djgpp/libalmp3.a ../djgpp/allegro/lib/liballeg.a
OBJDIR=.
endif

# setting compiler flags
CFLAGS=$(TARGETFLAGS) -I../thirdparty/almp3/include -I../djgpp/allegro/include


$(OUT): main.o
	$(CC) $(LFLAGS) $(CFLAGS) $(OBJDIR)/$< -o $@ $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(OBJDIR)/$@



clean:
	rm -f $(OBJDIR)/main.o $(OUT)

