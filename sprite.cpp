#include <string>
#include "sprite.h"
#include "globals.h"

sprite::sprite(int x, int y, int w, int h)
{
    //ctor
    bitmap = NULL;
    position.x = x;
    position.y = y;
    width = w;
    height = h;
    filename = "";

    ALLEGRO_DISPLAY *tempDisp = al_get_current_display();
    bitmap = al_create_bitmap(w,h);
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(255,255,255));
    al_set_target_backbuffer(tempDisp);


}

sprite::sprite(int x, int y, int w, int h, ALLEGRO_COLOR color)
{
    bitmap = NULL;
    position.x = x;
    position.y = y;
    width = w;
    height = h;
    filename = "";
    bitmap = al_create_bitmap(w,h);
    ALLEGRO_DISPLAY *tempDisp = al_get_current_display();
    al_set_target_bitmap(bitmap);
    al_clear_to_color(color);
    al_set_target_backbuffer(tempDisp);
}

sprite::sprite(int x, int y, string file)
{
    bitmap = NULL;
    position.x = x;
    position.y = y;
    filename = file;

    bitmap = al_load_bitmap(filename.c_str());
    width = al_get_bitmap_width(bitmap);
    height = al_get_bitmap_height(bitmap);
}

sprite::~sprite()
{
    //dtor
    al_destroy_bitmap(bitmap);
}

sprite& sprite::operator=(const sprite& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    position=rhs.position;
    bitmap = al_clone_bitmap(rhs.bitmap);
    filename = rhs.filename;
    width = rhs.width;
    height = rhs.height;

    return *this;
}

void sprite::draw()
{
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}

void sprite::setCoords(int x, int y)
{
    position.x = x;
    position.y = y;
}
