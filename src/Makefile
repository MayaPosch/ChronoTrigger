# Makefile for the ChronoTrigger library.
#
# Allows one to build the library as a .a file, or
# build the test application.
#
# (c) 2019 Nyanko.ws

export TOP := $(CURDIR)

GCC = g++
MAKEDIR = mkdir -p
RM = rm
AR = ar

OUTPUT = libchronotrigger.a
INCLUDE = -I src
CFLAGS := $(INCLUDE) -g3 -std=c++11 -O0

# Check for MinGW
# The OS variable is only set on Windows.
ifdef OS
	#CFLAGS := $(CFLAGS) -U__STRICT_ANSI__
	#LIBS += -lws2_32
endif

SOURCES := $(wildcard cpp/*.cpp)
OBJECTS := $(addprefix obj/,$(notdir) $(SOURCES:.cpp=.o))

all: lib test

lib: makedir $(OBJECTS) lib/$(OUTPUT)
	
obj/%.o: %.cpp
	$(GCC) -c -o $@ $< $(CFLAGS)
	
lib/$(OUTPUT): $(OBJECTS)
	-rm -f $@
	$(AR) rcs $@ $^
	
makedir:
	$(MAKEDIR) lib
	$(MAKEDIR) obj
	$(MAKEDIR) obj/cpp
	
test: test-app
	
test-app:
	$(MAKE) -C ./cpp-test

clean: clean-lib clean-test

clean-test: clean-test-app

clean-lib:
	$(RM) $(OBJECTS)
	
clean-test-app:
	$(MAKE) -C ./cpp-test clean
	