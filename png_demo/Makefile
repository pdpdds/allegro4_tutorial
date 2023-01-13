CFLAGS = -I. -I../allegro/include -I../thirdparty/box2d/include -I../thirdparty/alpng13/src -I../thirdparty/algif13/src

LDFLAGS = -L../allegro/lib -L../thirdparty/alpng13 -L../thirdparty/box2d -L../thirdparty/algif13

CC=$(DJGPP_GCC)


# -------- executable file name --------
PROGRAM = main

# -------- source file --------
SRC = $(PROGRAM).cpp

# -------- basic compile --------
all: $(PROGRAM).cpp
	@echo BUILD... $(PROGRAM).exe 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(PROGRAM).exe  -lalgif -lalpng -lbox2d -lstdc++ -lalleg