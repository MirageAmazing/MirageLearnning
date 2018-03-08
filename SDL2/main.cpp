#include <sys/time.h>  
#include <SDL2/SDL.h> 
#include <iostream>
using namespace std;

#define PRINT(msg) cout<<msg<<endl;

int Callback(void* userdata, SDL_Event* event);
void ComputeColor(float& color, bool& control);
long getCurrentTime();

bool gGreenSwitch = false;
double gFrames = 0;

int main()  
{  
    float green = 0;

    bool quit = false;
    SDL_Event event;
    SDL_Window* window =0;  
    SDL_Renderer* render=0;  
    SDL_Init(SDL_INIT_EVERYTHING);  
    window=SDL_CreateWindow("Mirage-Application",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);  
    render=SDL_CreateRenderer(window,-1,0);  
    SDL_SetRenderDrawColor(render,0,255,0,255);  
    SDL_RenderClear(render);  
    SDL_RenderPresent(render); 
    SDL_EventFilter ef = Callback; 
    SDL_AddEventWatch((SDL_EventFilter)Callback, nullptr);
  
    struct timeval tv;
    gettimeofday(&tv,NULL);
    auto timeA = ((double)(tv.tv_sec*1000 + tv.tv_usec/1000))/1000.0;
    auto timeB = timeA;
   
    while( quit == false )
    {     
        gettimeofday(&tv,NULL);
        timeB = ((double)(tv.tv_sec*1000 + tv.tv_usec/1000))/1000.0;
        gFrames = 1.0f/(timeB - timeA);
        timeA = timeB;

        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: PRINT("SDLK_UP"); PRINT(gFrames); break;
                    case SDLK_DOWN: PRINT("SDLK_DOWN"); break;
                    case SDLK_LEFT: PRINT("SDLK_LEFT"); break;
                    case SDLK_RIGHT: PRINT("SDLK_RIGHT"); break;
                }
            }

            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        else
        {
            ComputeColor(green, gGreenSwitch);
            SDL_SetRenderDrawColor(render,0,green,0,255);  
            SDL_RenderClear(render);  
            SDL_RenderPresent(render); 
        }

        gFrames = 1.0f/(timeB - timeA);
    }

    SDL_DestroyWindow(window);  
    SDL_DestroyRenderer(render);  
    SDL_Quit();  
    return 0;  
} 

int Callback(void* userdata, SDL_Event* event)
{
    printf("\nLog on callback@@@\n");
    return 0;
}

void ComputeColor(float& color, bool& control)
{
    if(color>255)
    {
        control = true;
        color = 255;
    }
    else if(color < 0)
    {
        control = false;
        color = 0;
    }

    if(control)
        color-=0.01;
    else
        color+=0.01;
}

long getCurrentTime()    
{    
   struct timeval tv;    
   gettimeofday(&tv,NULL);    
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
} 