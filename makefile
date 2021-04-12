
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

TESTLIBRARY =  -lgtest_main -lgtest -lgcov $(BASICLIBRARY)
TESTINCLUDE = $(BASICINCLUDE) -I./include/gtest -I./include/gmock

all: create_directories \
     execute_program_test

NAME_PROGRAM = example_basic_state_pattern
NAME_PROGRAM_TEST = example_basic_state_pattern_test

COMPILED_FILES  = $(OBJDIR)state.o $(OBJDIR)context.o
COMPILED_FILES += $(OBJDIR)ConcreteStateA.o $(OBJDIR)ConcreteStateB.o
COMPILED_FILES += $(OBJDIR)main.o

$(NAME_PROGRAM): $(COMPILED_FILES)
	# [Trasterlabs] joining the obj files into an executable
	$(CPP) $^ -o $(BINDIR)$@ $(BASICINCLUDE) $(SOURCEINCLUDE) $(BASICLIBRARY) $(DIRLIBRARYSEARCH)

COMPILED_FILES_TEST  = $(OBJDIR)state.o11dt $(OBJDIR)context.o11dt
COMPILED_FILES_TEST += $(OBJDIR)ConcreteStateA.o11dt $(OBJDIR)ConcreteStateB.o11dt

$(NAME_PROGRAM_TEST): $(COMPILED_FILES_TEST)
	# [Trasterlabs] joining the obj files into an executable
	$(CPP) $^ -o $(BINDIR)$@ $(TESTINCLUDE) $(SOURCEINCLUDE) $(TESTLIBRARY) $(DIRLIBRARYSEARCH)

execute_program: $(NAME_PROGRAM)
	# executing $<
	./$(BINDIR)/$(NAME_PROGRAM)

execute_program_test: $(NAME_PROGRAM_TEST)
	# executing $<
	./$(BINDIR)/$(NAME_PROGRAM_TEST)

create_directories:
	if [ ! -d ./$(LIBDIR) ]; then mkdir -p ./$(LIBDIR); fi
	if [ ! -d ./$(BINDIR) ]; then mkdir -p ./$(BINDIR); fi
	if [ ! -d ./$(OBJDIR) ]; then mkdir -p ./$(OBJDIR); fi

$(OBJDIR)%.o: $(DIRSOURCE)%.cpp
	# [Trasterlabs] Compile $<
	$(CPP) $(CPPFLAGS11D) $(BASICINCLUDE) -c $< -o $@

$(OBJDIR)%.o11dt: $(DIRSOURCE)%.cpp
	# [Trasterlabs] Compile $< with testing enabled
	$(CPP) $(CPPFLAGS11DT) $(TESTINCLUDE) -c $< -o $@

default: all
