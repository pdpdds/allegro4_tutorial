//-----------------------------------------------------------------------------
///
/// A simple Demo of using Box2D with SDL2
///
/// @param argc not used
/// @param arv not used
///
///
/// @return EXIT_SUCCESS
//

#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>
#include <allegro.h> 
#include <alpng.h>



b2World* world;

const int MET2PIX = 80; // 640 / 80 = 8

const int WIDTH = 640;
const int HEIGHT = 480;

const int SCALED_WIDTH = WIDTH / MET2PIX; // 4 | 3
const int SCALED_HEIGHT = HEIGHT / MET2PIX;

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /**< pi */
#endif

//1 rad × 180/? = 57,296°
const float RAD2DEG = 180 / M_PI;

volatile long g_speed_counter = 0; //?�도 카운??
void increment_speed_counter() //?�도 카운??값을 증�??�키??카운???�수
{
    g_speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter); //?�?�머 ?�수가 ?�난?�는 것을 명시?�으�??�정

using namespace std;

typedef struct ALLEGRO_Rect
{
    int x, y;
    int w, h;
} ALLEGRO_Rect;

int main(int argc, char* argv[])
{
    allegro_init();
    install_keyboard();
    set_color_depth(16);

#if defined(WIN32)
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, WIDTH, HEIGHT, 0, 0);
#else
    set_gfx_mode(GFX_AUTODETECT, WIDTH, HEIGHT, 0, 0);
#endif
    install_timer(); 
	LOCK_VARIABLE(g_speed_counter);
    LOCK_FUNCTION(increment_speed_counter);

    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60)); 
    int Width = WIDTH;
    int Height = HEIGHT;
    
    cout << "Width of the Screen: " << Width << endl;
    cout << "Height of the Screen: " << Height << endl;
    
    
    
    world = new b2World(b2Vec2(0.0f, 9.81f)); // new b2World(b2Vec2(0.0f, 9.81f));
    
    // cartesian origin
    float ground_x = 0.0f;
    float ground_y = 0.0f;
    
    // start ground point
    b2Vec2 startpoint;
    startpoint.x = -3.0f;
    startpoint.y = 2.0;
    
    // end ground point
    b2Vec2 endpoint;
    endpoint.x = 3;
    endpoint.y = 2.0;
    
    // LineGround
    b2BodyDef myGroundDef;
    myGroundDef.type = b2_staticBody;
    myGroundDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
    myGroundDef.angle = 0;
    
    b2Body* groundLineBody = world->CreateBody(&myGroundDef);
    
    b2EdgeShape edgeShape;
    edgeShape.SetTwoSided( startpoint, endpoint ); // length -> coordinate vector from to vector
    
    b2FixtureDef edgeFixtureDef;
    edgeFixtureDef.shape = &edgeShape;
    groundLineBody->CreateFixture(&edgeFixtureDef);
    
    BITMAP* pBitmap = 0;
    pBitmap = load_png("assets/box.png", NULL);

    BITMAP* buffer;
    buffer = create_bitmap(WIDTH, HEIGHT);
    
    
    // cartesian origin box
    float x_box = -2.5f;
    float y_box = -2.5f;
    
    // size of box
    float w_box = 0.3;
    float h_box = 0.3;
    
    // angle of the box
    float angle_box = 45.0f; //45.0f;
    
    // Box
    ALLEGRO_Rect box;
    b2Body* Body;

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.angle = angle_box; // flips the whole thing -> 180 grad drehung
    //boxBodyDef.angle = 0;
    boxBodyDef.position.Set(x_box, y_box);
    b2Vec2 vel;
    vel.Set(0, 0.2f);
    
    Body = world->CreateBody(&boxBodyDef);
    Body->SetLinearVelocity(vel);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((w_box / 2.0f) - dynamicBox.m_radius, (h_box / 2.0f) - dynamicBox.m_radius); // will be 0.5 x 0.5
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    Body->CreateFixture(&fixtureDef);
    
    // box: convert Metres back to Pixels for width and height
    box.w = w_box * MET2PIX;
    box.h = h_box * MET2PIX;
    
    // cartesian origin of _0019_PLATF.png 89 x 22
    float x_plat = -3.6f; // to edge
    float y_plat = -0.14f;// to edge
    
    // size of the platform
    float w_plat = 89.0f / MET2PIX;
    float h_plat = 22.0f / MET2PIX;
    
    // define a Rect for this platform and its body def
    ALLEGRO_Rect platform;
    b2Body* Body_platform;
    
    b2BodyDef platformBoyDef;
    platformBoyDef.type = b2_staticBody;
    platformBoyDef.position.Set(x_plat, y_plat);
    
    Body_platform = world->CreateBody(&platformBoyDef);
    
    b2PolygonShape platformTile;    // subtracting radius fixes the incorrect little gap that can appear when working with really small resolutions
    platformTile.SetAsBox((w_plat / 2.0f) - platformTile.m_radius, (h_plat / 2.0f) - platformTile.m_radius); // subtracting the radius kills the gap issue:
    b2FixtureDef fixturePlat;
    fixturePlat.shape = &platformTile;
    fixturePlat.density = 1.0f;
    fixturePlat.friction = 0.3f;
    fixturePlat.restitution = 0.5f;
    Body_platform->CreateFixture(&fixturePlat);
    
    // set the SDL_RECT rendering values
    platform.w = w_plat * MET2PIX;
    platform.h = h_plat * MET2PIX;
    platform.x = ((SCALED_WIDTH / 2.0f) + x_plat) * MET2PIX - platform.w / 2;
    platform.y = ((SCALED_HEIGHT / 2.0f) + y_plat) * MET2PIX - platform.h / 2;
    
   
    while (!key[KEY_ESC])
    {
				while(g_speed_counter == 0) {
        rest(1); //Wait for a full tick
      }
	  
        b2Vec2 pos = Body->GetPosition(); // Body = Body from box
        float angle = Body->GetAngle();

        // RAD2Degree
        angle *= RAD2DEG;

        while (g_speed_counter > 0)
        {
	
	  
            if (key[KEY_R])
            {
                Body->SetTransform(b2Vec2(x_box, y_box), angle_box);
                Body->SetLinearVelocity(vel);
            }

            g_speed_counter--;
        }

        // question box, update x and y destination
        box.x = ((SCALED_WIDTH / 2.0f) + pos.x) * MET2PIX - box.w / 2;
        box.y = ((SCALED_HEIGHT / 2.0f) + pos.y) * MET2PIX - box.h / 2;

     

        line(buffer, ((SCALED_WIDTH / 2.0f) + edgeShape.m_vertex1.x)* MET2PIX, ((SCALED_HEIGHT / 2.0f) + edgeShape.m_vertex1.y)* MET2PIX, ((SCALED_WIDTH / 2.0f) + edgeShape.m_vertex2.x)* MET2PIX, ((SCALED_HEIGHT / 2.0f) + edgeShape.m_vertex2.y)* MET2PIX, makecol(255, 0, 0));
        //rotate_sprite(BITMAP * bmp, BITMAP * sprite, int x, int y, fixed angle);
        
        //rotate_sprite(buffer, pBitmap, box.x, box.y, itofix(Body->GetAngle() * RAD2DEG));

        float stretch = box.w / (float)pBitmap->w;
        rotate_scaled_sprite(buffer, pBitmap, box.x, box.y, itofix(Body->GetAngle() * RAD2DEG), itofix(stretch));
        
        //rotate_sprite(buffer, datafile[31].dat, bodymovex - 50, tankypos - 56, itofix(bodyangle));
        //SDL_RenderCopyEx(renderer, texture_box, NULL, &box, Body->GetAngle() * RAD2DEG, NULL, SDL_FLIP_NONE);

        // Draw ziegl_3

        // Draw box angle 45
        //Body->SetAngularVelocity(10.0f);
        //Body->SetFixedRotation(true);
        //SDL_RenderDrawRect(renderer, &box);
        //SDL_RenderFillRect(renderer, &box);

        vsync();
        acquire_screen();
        blit(buffer, screen, 0, 0, 0, 0, 640, 480);
        release_screen();
       
        clear_bitmap(buffer);

        world->Step(1.0f / 60.0f, 6.0f, 2.0f); // update

       // RenderBall(buffer, pBall); //?�블 버퍼링을 ?�용?�서 ?�면??갱신?�다.
    }

    // box2D delete whole world and free memory
    delete world;

    destroy_bitmap(pBitmap);
    destroy_bitmap(buffer);

    return 0;

    return EXIT_SUCCESS;
}
END_OF_MAIN()


