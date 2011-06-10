#include "aniSprite.h"
#include <iostream>

using namespace std;

aniSprite::aniSprite(int x, int y, string file,int frame_number) : sprite(x,y,file)
{
    /*
    bitmap = NULL;
    position.x = x;
    position.y = y;
    filename = file;

    bitmap = al_load_bitmap(filename.c_str());
    width = al_get_bitmap_width(bitmap);
    height = al_get_bitmap_height(bitmap);
    */

    ALLEGRO_BITMAP *tmpBit = NULL;
    numFrames=frame_number;
    width = width/numFrames;
    try
    {
         frames = new ALLEGRO_BITMAP*[numFrames];
    }
    catch(...)
    {
        frames = 0;
    }

    for(int i=0;i<numFrames;i++)
    {
        frames[i] = al_create_sub_bitmap(bitmap,width*i,0,width,height);
    }
    bitmap = frames[0];
    currentFrame=0;

}

void aniSprite::advanceFrame()
{
    currentFrame++;
    if(currentFrame == numFrames) {
        currentFrame=0;
    }

    bitmap = frames[currentFrame];
    draw();
}

void aniSprite::rewindFrame()
{
    currentFrame--;
    if(currentFrame < 0)
    {
        currentFrame+=numFrames;
    }

    bitmap = frames[currentFrame];
    draw();
}

void aniSprite::setFrame(int i)
{
    bitmap = frames[i];
}


aniSprite::~aniSprite()
{
    //dtor
}
