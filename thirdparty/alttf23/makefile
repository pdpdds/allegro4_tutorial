PACKAGE  = alttf
VERSION	 = 23
EXAMPLES = examples
INCLUDES = include source
SOURCES  = source source/freetype

EXAMPLESRC := $(wildcard $(EXAMPLES)/*.c)
EXAMPLEEXE := $(EXAMPLESRC:.c=.exe)
ALLDIRS    := . $(EXAMPLES) $(INCLUDES) $(SOURCES)
OS         := $(shell uname -s)

LIBRARY    := $(addprefix lib,$(addsuffix .a,$(PACKAGE)))
LIBRARYC   := $(foreach dir,$(SOURCES),$(wildcard $(dir)/[^_]*.c))
LIBRARYOBJ := $(LIBRARYC:.c=.o)

CC       = gcc
CFLAGS   = -c -O2 -I../../djgpp/allegro/include
CEXTRA   =
LFLAGS   = -L. -lalttf -L../../djgpp/allegro/lib
ifeq "$(OS)" "Linux"
LFLAGS   += `allegro-config --libs`
else
LFLAGS   += -lalleg
endif

.PHONY: all lib examples
.PHONY: clean indent zip

#Compiler targets ------------------------------------------------------------
all : lib examples 

lib : $(LIBRARYOBJ) 
	ar rs $(LIBRARY) $(^F)
	$(RM) $(notdir $(LIBRARYOBJ))

examples : $(EXAMPLEEXE)

#Clean target ----------------------------------------------------------------
EXEFILES1 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.exe))
EXEFILES2 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.EXE))
OBJFILES1 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.o))
OBJFILES2 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.OBJ))
OBJFILES3 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.obj))
LIBFILES1 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.a))
LIBFILES2 := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.lib))

clean:
	$(foreach obj, $(EXEFILES1), $(RM) $(obj))
	$(foreach obj, $(EXEFILES2), $(RM) $(obj))
	$(foreach obj, $(OBJFILES1), $(RM) $(obj))
	$(foreach obj, $(OBJFILES2), $(RM) $(obj))
	$(foreach obj, $(OBJFILES3), $(RM) $(obj))
	$(foreach obj, $(LIBFILES1), $(RM) $(obj))
	$(foreach obj, $(LIBFILES2), $(RM) $(obj))
	-$(RM) $(addsuffix .zip, $(PACKAGE)$(VERSION))
	-$(RM) $(EXAMPLES)/keycode
	-$(RM) $(EXAMPLES)/*.orig
	-$(RM) $(EXAMPLES)/*.gdt
	-$(RM) $(EXAMPLES)/*.dat
	-$(RM) $(EXAMPLES)/*.mak
	-$(RM) $(EXAMPLES)/*.lay
	-$(RM) $(EXAMPLES)/*.dsk
	-$(RM) $(EXAMPLES)/*.tds
	-$(RM) $(EXAMPLES)/*.map
	-$(RM) $(EXAMPLES)/*.mbr
	-$(RM) $(EXAMPLES)/*.mk
	-$(RM) $(EXAMPLES)/*.lk1
	-$(RM) $(EXAMPLES)/*.mk1
	-$(RM) $(EXAMPLES)/*.sym
	-$(RM) $(EXAMPLES)/*.prf
	-$(RM) $(EXAMPLES)/*.cbr
	-$(RM) $(EXAMPLES)/*.swp
	-$(RM) $(EXAMPLES)/*.jpg
	-$(RM) $(EXAMPLES)/*.err
	-$(RM) $(EXAMPLES)/*.smp
	-$(RM) $(EXAMPLES)/rh_opt.*
	-$(RM) *.tds
	-$(RM) *.bat
	-$(RM) *.sh
	-$(RM) rh_opt.*
	-$(RM) *.gdt

#Indent target ---------------------------------------------------------------
define doindent
@echo $(obj)
$(shell indent -l120 --ignore-newlines $(obj))
$(shell indent -kr -ts4 -lp -l120 -bad -fc1 -c0 -npsl -sob -nhnl -bap --ignore-newlines $(obj))
endef

CFILES := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.c))
HFILES := $(foreach dir,$(ALLDIRS),$(wildcard $(dir)/*.h))
INDENTFILES := $(CFILES) $(HFILES)
INDENTBACKUP := $(CFILES:.c=.c~) $(HFILES:.h=.h~)

indent:
	$(foreach obj, $(INDENTFILES), $(doindent))
	$(foreach obj, $(INDENTBACKUP), $(RM) $(obj))

#Zip target ------------------------------------------------------------------
zip: clean
	-zip -r9 $(PACKAGE)$(VERSION) *

#Rules -----------------------------------------------------------------------
%o : %c
	$(CC) $(addprefix -I,$(INCLUDES)) $(CFLAGS) $<
%exe : %o
	$(CC) -o $@ $(?F) $(LFLAGS)
