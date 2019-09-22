# Makefile for the ChronoTrigger test client.
#
# (c) 2019 Nyanko.ws

GCC = g++
MAKEDIR = mkdir -p
RM = rm

OUTPUT = chronotrigger_test
INCLUDE = -I $(TOP)/src
LIB := -L ../lib -lchronotrigger
CFLAGS := $(INCLUDE) -std=c++11 -g3

# Check for MinGW 
# The OS variable is only set on Windows.
ifdef OS
	#CFLAGS := $(CFLAGS) 
	#LIBS += -lws2_32
endif

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix obj/,$(notdir) $(SOURCES:.cpp=.o))

all: makedir $(OBJECTS) bin/$(OUTPUT)

makedir:
	$(MAKEDIR) obj
	$(MAKEDIR) bin

obj/%.o: %.cpp
	$(GCC) -c -o $@ $< $(CFLAGS)
	
bin/$(OUTPUT):
	$(GCC) -o $@ $(OBJECTS) $(LIB)

clean:
	$(RM) $(OBJECTS)
	