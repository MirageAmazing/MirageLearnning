#ifdef _WIN32
#include "../SDL2-2.0.8/include/SDL.h"
#include "../SDL2-2.0.8/include/SDL_main.h"
#pragma comment(lib, "../SDL2-2.0.8/lib/x86/SDL2.lib")
#pragma comment(lib, "../SDL2-2.0.8/lib/x86/SDL2main.lib")
#pragma comment(lib, "../SDL2-2.0.8/lib/x86/SDL2test.lib")
#pragma comment(linker, "/entry:SDL_main")
#pragma comment(linker, "/INCLUDE:_mainCRTStartup")
#define SDL_MAIN_HANDLED
#elif __linux__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <chrono>
using namespace std;

#define PRINT(msg) cout<<msg<<endl;

int Callback(void* userdata, SDL_Event* event);
void ComputeColor(float& color, bool& control);

bool gGreenSwitch = false;
double gFrames = 0;
float width = 640;
float height = 800;

int main(int argc, char* argv[])
{
	float green = 0;

	bool quit = false;
	SDL_Event event;
	SDL_Window* window = 0;
	SDL_Renderer* render = 0;
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);	
	window = SDL_CreateWindow("Mirage-Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	render = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
	SDL_EventFilter ef = Callback;
	SDL_AddEventWatch((SDL_EventFilter)Callback, nullptr);

	std::chrono::system_clock::time_point timeA = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point timeB = timeA;

	float ratio = width / height;  
    // Our shading model--Gouraud (smooth).  
    glShadeModel( GL_SMOOTH );  
    // Set the clear color.  
    glClearColor( 0, 0, 0, 0 );  
    // Setup our viewport.  
    glViewport( 0, 0, width, height );  
    //Change to the projection matrix and set our viewing volume.  
    glMatrixMode( GL_PROJECTION );  
    glLoadIdentity();  
    gluPerspective( 60.0, ratio, 1.0, 100.0 );  

	while (quit == false)
	{
		timeB = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(timeB - timeA).count();
		gFrames = 1.0 / ((double)(diff) / 1000000.0);
		timeA = timeB;

		//If there's an event to handle
		if (SDL_PollEvent(&event))
		{
			//If a key was pressed
			if (event.type == SDL_KEYDOWN)
			{
				//Set the proper message surface
				switch (event.key.keysym.sym)
				{
				case SDLK_UP: PRINT("SDLK_UP"); 
                    PRINT(gFrames); 
                    break;
				case SDLK_DOWN: PRINT("SDLK_DOWN"); 
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mirage", "Message from ME", window);
                    break;
				case SDLK_LEFT: PRINT("SDLK_LEFT"); break;
				case SDLK_RIGHT: PRINT("SDLK_RIGHT"); break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{

			}
			//If the user has Xed out the window
			else if (event.type == SDL_QUIT)
			{
				//Quit the program
				quit = true;
			}
		}
		else
		{
			ComputeColor(green, gGreenSwitch);
			glClearColor( 0, green/255.0, 1, 1); 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode( GL_MODELVIEW );  
			glLoadIdentity( );  
			// Move down the z-axis.  
			glTranslatef( 0.0, 0.0, -5.0 );  
			//Draw a square  
			glBegin(GL_QUADS);  
			glColor3f(green,0.0f,0.0f);  
			glVertex3f(-1.0f  , -1.0f  ,  1.0f  );  
			glColor3f(0.0f,green,0.0f);  
			glVertex3f( 1.0f  , -1.0f  ,  1.0f  );  
			glColor3f(0.0f,0.0f,1.0f);  
			glVertex3f( 1.0f  ,  1.0f  ,  1.0f  );  
			glColor3f(1.0f,1.0f,0.0f);  
			glVertex3f(-1.0f  ,  1.0f  ,  1.0f  );  
			glEnd();  
			SDL_GL_SwapWindow(window);
			//SDL_SetRenderDrawColor(render, 0, green, 0, 255);
			//SDL_RenderClear(render);
			//SDL_RenderPresent(render);
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

void ComputeColor(float& color, bool& control)
{
	if (color>255)
	{
		control = true;
		color = 255;
	}
	else if (color < 0)
	{
		control = false;
		color = 0;
	}

	if (control)
		color -= 0.05;
	else
		color += 0.05;
}