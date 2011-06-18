#define ALLEGRO_STATICLINK
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <Box2D/Box2D.h>

#include "globals.h"
#include "sprite.h"
#include "aniSprite.h"

using namespace std;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
};

int main(int argc, char **argv)
{
   //Box2D Rough Test
   b2Vec2 gravity(0.0f, -10.0f);
   bool doSleep = true;

   b2World world(gravity, doSleep);

   b2BodyDef groundBodyDef;
   groundBodyDef.position.Set(0.0f, -10.0f);

   b2Body* groundBody = world.CreateBody(&groundBodyDef);

   b2PolygonShape groundBox;
   b2Vec2 left(-32.0f,-24.0f),right(32.0f,-24.0f);
   groundBox.SetAsEdge(right,left);

   groundBody->CreateFixture(&groundBox,0);

   b2BodyDef bodyDef;

   bodyDef.type = b2_dynamicBody;

   bodyDef.position.Set(0.0f, 0.0f);

   b2Body* body = world.CreateBody(&bodyDef);

   b2PolygonShape dynamicBox;

   dynamicBox.SetAsBox(1.0f, 1.0f);
   b2FixtureDef fixtureDef;

   fixtureDef.shape = &dynamicBox;

   fixtureDef.density = 1.0f;

   fixtureDef.friction = 0.3f;

   body->CreateFixture(&fixtureDef);

   float32 timeStep = 1.0f / 60.0f;

   int32 velocityIterations = 6;
   int32 positionIterations = 2;

   //End Box2d test section
   	 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;

   //ALLEGRO_BITMAP *paddle = NULL;
   float bouncer_startx = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_starty = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_x = bouncer_startx;
   float bouncer_y = bouncer_starty;
   float paddle_startx = SCREEN_W / 2.0 - PADDLE_W / 2.0;
   float paddle_x = paddle_startx;
   float paddle_y = SCREEN_H-PADDLE_H;
   float paddle_speed = 1.0;
   float bouncer_speed=3.0;
   int bouncer_xdir = 1;
   int bouncer_ydir = 1;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;


   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize image addon!\n");
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display");
    }
    //prep display
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

   aniSprite bouncer(bouncer_startx,bouncer_starty,"ball.bmp",2);
   //bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   //if(!bouncer) {
     // fprintf(stderr, "failed to create bouncer bitmap!\n");
     // al_destroy_display(display);
     // al_destroy_timer(timer);
     // return -1;
   //}
    sprite paddle(paddle_startx,0,PADDLE_W,PADDLE_H,al_map_rgb(23,180,78));
   /*if(!paddle) {
      fprintf(stderr, "failed to create paddle bitmap!\n");
      al_destroy_display(display);
      //al_destroy_bitmap(bouncer);
      al_destroy_timer(timer);
      return -1;
   }*/


   //al_set_target_bitmap(bouncer.bitmap);

   //al_clear_to_color(al_map_rgb(255, 0, 255));

   //al_set_target_bitmap(paddle);

   //al_clear_to_color(al_map_rgb(0,255,150));

   //al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();


   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      //al_destroy_bitmap(bouncer);
      //al_destroy_bitmap(paddle);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());


cout << "hello\n";

   al_start_timer(timer);

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      
      //Box2D test start

      world.Step(timeStep, velocityIterations, positionIterations);
      world.ClearForces();
      b2Vec2 position = body->GetPosition();
      float32 angle = body->GetAngle();
      printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

      //Box2D test end

      if(ev.type == ALLEGRO_EVENT_TIMER) {

         if(key[KEY_LEFT]) {
            paddle_x -= paddle_speed;
         }

         if(key[KEY_RIGHT]) {
            paddle_x += paddle_speed;
         }
         bouncer_y+=bouncer_speed*bouncer_ydir;
         bouncer_x+=bouncer_speed*bouncer_xdir;

         if(bouncer_y < 0){
                bouncer_ydir=-bouncer_ydir;
         }
         if(bouncer_y + BOUNCER_SIZE > paddle_y && paddle_x<bouncer_x+BOUNCER_SIZE && paddle_x+PADDLE_W>bouncer_x){
             bouncer_ydir = -bouncer_ydir;
             bouncer_speed = bouncer_speed*1.1;
             bouncer.advanceFrame();
             body->SetLinearVelocity(-body->GetLinearVelocity());
         }
         if(bouncer_y > SCREEN_H - BOUNCER_SIZE){
            bouncer_y=bouncer_starty;
            bouncer_x=bouncer_startx;
            paddle_x=paddle_startx;
            bouncer_ydir=1;
            bouncer_xdir=1;
            bouncer_speed=3.0;
         }
         if(bouncer_x > SCREEN_W - BOUNCER_SIZE || bouncer_x < 0){
                bouncer_xdir=-bouncer_xdir;
         }
         bouncer_y=min(bouncer_y, float(SCREEN_H - BOUNCER_SIZE));
         bouncer_y=max(bouncer_y, float(0));
         bouncer_x=min(bouncer_x, float(SCREEN_W - BOUNCER_SIZE));
         bouncer_x=max(bouncer_x, float(0));
         paddle_x=min(paddle_x, float(SCREEN_W - PADDLE_W));
         paddle_x=max(paddle_x, float(0));
         bouncer_x=floor(position.x*10.0+SCREEN_W/2.0);
         bouncer_y=floor(-position.y*10.0+SCREEN_H/2.0);
         printf("%4.2f %4.2f\n", bouncer_x, bouncer_y);
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
            case ALLEGRO_KEY_J:
                paddle_speed = paddle_speed * 2;
                break;
            case ALLEGRO_KEY_K:
                paddle_speed = paddle_speed / 2;
                break;

         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }

      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
         bouncer.setCoords(bouncer_x,bouncer_y);
         bouncer.draw();

         paddle.setCoords(paddle_x,paddle_y);
         paddle.draw();
         //al_draw_bitmap(paddle, paddle_x, paddle_y, 0);

         al_flip_display();
      }
   }

   //al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);

   al_destroy_event_queue(event_queue);

   al_destroy_display(display);

   return 0;
}
