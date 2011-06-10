#ifndef ANISPRITE_H
#define ANISPRITE_H

#include "sprite.h"
#include <string>

using namespace std;

class aniSprite : public sprite
{
    public:
        aniSprite(int x,int y, string file, int numFrames);
        void setFrame(int i);
        void advanceFrame();
        void rewindFrame();
        ~aniSprite();
    protected:
        ALLEGRO_BITMAP** frames;
        int currentFrame;
        int numFrames;
        int frame_h;
        int frame_w;

    private:
};

#endif // ANISPRITE_H
