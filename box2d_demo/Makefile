CFLAGS = -I. -I../allegro/include -I../thirdparty/box2d/include -I../thirdparty/alpng13/src

LDFLAGS = -L../allegro/lib -L../thirdparty/alpng13 -L../thirdparty/box2d

CC=$(DJGPP_GCC)


# -------- executable file name --------
PROGRAM = main

# -------- source file --------
SRC = $(PROGRAM).cpp

# -------- basic compile --------
all: $(PROGRAM).cpp
	@echo BUILD... $(PROGRAM).exe 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(PROGRAM).exe  -lalpng -lbox2d -lstdc++ -lalleg