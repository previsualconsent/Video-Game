HEADERS = aniSprite.h coords.h globals.h sprite.h
SOURCES = aniSprite.cpp main.cpp sprite.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CC = g++
CFLAGS= -c -Wall

LIBS = $(shell (pkg-config --libs allegro_image-5.0)) -lBox2D

all: servo

servo: $(OBJECTS)
	        ${CC} $(LIBS) $(OBJECTS) $(HEADERS) -o $@

.cpp.o:
	 $(CC) $(CFLAGS) $< -o $@
