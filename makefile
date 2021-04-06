
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

BASICLIBRARY = -lm -lstdc++ -pthread -lrt
DIRLIBRARYSEARCH = -L./$(LIBDIR)

all: create_directories
	# [Trasterlabs] Making the default part

NAME_PROGRAM = example_basic_state_pattern

COMPILED_FILES  = $(OBJDIR)/state.o $(OBJDIR)/context.o
COMPILED_FILES += $(OBJDIR)/ConcreteStateA.o $(OBJDIR)/ConcreteStateB.o

$(NAME_PROGRAM): $(COMPILED_FILES)
	# [Trasterlabs] joining the obj files into an executable
	$(CPP) $^ -o $(BINDIR)$@ $(BASICINCLUDE) $(SOURCEINCLUDE)

create_directories:
	if [ ! -d ./$(LIBDIR) ]; then mkdir -p ./$(LIBDIR); fi
	if [ ! -d ./$(BINDIR) ]; then mkdir -p ./$(BINDIR); fi
	if [ ! -d ./$(OBJDIR) ]; then mkdir -p ./$(OBJDIR); fi

default: all
	# [Trasterlabs] Making the default part
