
CPP         = gcc
CPPFLAGSD   = -Wall -g -O0
CPPFLAGS11D = $(CPPFLAGSD) -std=gnu++11

DIRINCLUDE = include/
DIRSOURCE  = src/
BINDIR     = bin/
LIBDIR     = lib/
OBJDIR     = obj/

BASICINCLUDE = -I./$(DIRINCLUDE)
SOURCEINCLUDE = -I./$(DIRSOURCE)


all: create_directories

create_directories:
	if [ ! -d ./$(LIBDIR) ]; then mkdir -p ./$(LIBDIR); fi
	if [ ! -d ./$(BINDIR) ]; then mkdir -p ./$(BINDIR); fi
	if [ ! -d ./$(OBJDIR) ]; then mkdir -p ./$(OBJDIR); fi

default: all
	# [Trasterlabs] Making the default part
