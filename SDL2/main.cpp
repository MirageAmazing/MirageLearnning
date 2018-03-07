#include <SDL2/SDL.h> 
#include <iostream>
using namespace std;

#define PRINT(msg) cout<<msg<<endl;

int Callback(void* userdata, SDL_Event* event);

int main()  
{  
    cout<<"CPU count:"<<SDL_GetCPUCount()<<endl;

    bool quit = false;
    SDL_Event event;
    SDL_Window* window =0;  
    SDL_Renderer* render=0;  
    SDL_Init(SDL_INIT_EVERYTHING);  
    window=SDL_CreateWindow("hello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);  
    render=SDL_CreateRenderer(window,-1,0);  
    SDL_SetRenderDrawColor(render,0,255,0,255);  
    SDL_RenderClear(render);  
    SDL_RenderPresent(render); 
    SDL_EventFilter ef = Callback; 
    SDL_AddEventWatch((SDL_EventFilter)Callback, nullptr);
  
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: PRINT("SDLK_UP"); break;
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