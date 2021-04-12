
CPP          = gcc
CPPFLAGSD    = -Wall -g -O0
CPPFLAGS11D  = $(CPPFLAGSD) -std=gnu++11
CPPFLAGS11DT = $(CPPFLAGS11D) -pedantic -ftest-coverage -fprofile-arcs --coverage


DIRINCLUDE = include/
DIRSOURCE  = src/
BINDIR     = bin/
LIBDIR     = lib/
OBJDIR     = obj/

BASICINCLUDE = -I./$(DIRINCLUDE)
SOURCEINCLUDE = -I./$(DIRSOURCE)

BASICLIBRARY = -lm -lstdc++ -pthread -lrt
DIRLIBRARYSEARCH = -L./$(LIBDIR)

TESTLIBRARY = $(BASICLIBRARY) -lgtest -lgcov
TESTINCLUDE = $(BASICINCLUDE) -I./include/gtest -I./include/gmock

all: create_directories \
     execute_program
	# [Trasterlabs] Making the default part

NAME_PROGRAM = example_basic_state_pattern

COMPILED_FILES  = $(OBJDIR)state.o $(OBJDIR)context.o
COMPILED_FILES += $(OBJDIR)ConcreteStateA.o $(OBJDIR)ConcreteStateB.o
COMPILED_FILES += $(OBJDIR)main.o

$(NAME_PROGRAM): $(COMPILED_FILES)
	# [Trasterlabs] joining the obj files into an executable
	$(CPP) $^ -o $(BINDIR)$@ $(BASICINCLUDE) $(SOURCEINCLUDE) $(BASICLIBRARY) $(DIRLIBRARYSEARCH)

execute_program: $(NAME_PROGRAM)
	# executing $<
	./$(BINDIR)/$(NAME_PROGRAM)

create_directories:
	if [ ! -d ./$(LIBDIR) ]; then mkdir -p ./$(LIBDIR); fi
	if [ ! -d ./$(BINDIR) ]; then mkdir -p ./$(BINDIR); fi
	if [ ! -d ./$(OBJDIR) ]; then mkdir -p ./$(OBJDIR); fi

$(OBJDIR)%.o: $(DIRSOURCE)%.cpp
	# [Trasterlabs] Compile $<
	$(CPP) $(CPPFLAGS11D) $(BASICINCLUDE) -c $< -o $@

default: all
