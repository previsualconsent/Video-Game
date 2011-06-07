#ifndef sprite_H
#define sprite_H

#include <string>
#include <allegro5/allegro.h>
#include "coords.h"
#include "globals.h"

using namespace std;

class sprite
{
    public:
        sprite(int x,int y,int w,int h);
        sprite(int x,int y,int w,int h,ALLEGRO_COLOR color);
        sprite(int x,int y,string file);
        virtual ~sprite();
        sprite& operator=(const sprite& other);
        //ALLEGRO_BITMAP Getbitmap() { return bitmap; }
        void setCoords(int x, int y);
        void draw();
        ALLEGRO_BITMAP *bitmap;
        //void Setbitmap(ALLEGRO_BITMAP val) { bitmap = val; }
    protected:
        Coords position;
        int height;
        int width;
        string filename;
    private:



};

#endif // sprite_H
