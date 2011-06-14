HEADERS = aniSprite.h coords.h globals.h sprite.h
SOURCES = aniSprite.cpp main.cpp sprite.cpp

CC = g++

LIBS = $(shell (pkg-config --libs allegro_image-5.0))

all: servo

servo: $(SOURCES)
	${CC} $(LIBS) $(SOURCES) $(HEADERS) -o $@
