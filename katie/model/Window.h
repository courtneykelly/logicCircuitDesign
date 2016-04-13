// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "Block.h"
	#include "Gate.h"
	#include "Input.h"
	#include "Wire.h"



class Window {

	public:
		Window();
		~Window();

		int init();
		void draw();
		int eventHandler(SDL_Event);

		void makeWire();
		void moveWire();
		void moveBlocks();
		void drawBlocks();
		void drawWires();

	private:
		int screen_width;
		int screen_height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		vector<Block*> blocks;
		vector<Wire*> wires;
		int action; // 0=none, 1=drawing wires, ...
};


// constructor
Window::Window()
{
    screen_width = 1000;
    screen_height = 600;
    window = NULL;
    renderer = NULL;
	action = 0;
    init();
}


// destructor
Window::~Window()
{
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
}


// initilaizes the window and renderer
int Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
		std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
    }

    // create window
    window = SDL_CreateWindow("Logic Circuit Design", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return -1;
    }

    // set renderer resolution
    SDL_RenderSetLogicalSize (renderer, screen_width, screen_height);

    // set Background color
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);

    return 1;
}


void Window::draw()
{
    SDL_RenderPresent(renderer); // draws it
    SDL_Delay(40); // 40 default
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // clear screen to white
}


// Conditionally call actions based on SDL event and variables
// NEEDS REDESIGN TO WORK FOR LOTS OF THINGS!
int Window::eventHandler(SDL_Event e)
{
	// cout << "e.type: " << e.type << endl;
	switch(e.type)
	{
		case SDL_QUIT:
			return 1; // quits
			break;
		case SDL_MOUSEBUTTONDOWN:

		  //get mouse position
		  int x,y,blockNum;
		  SDL_GetMouseState(&x, &y);

		  //check if mouse is inside a gate
		  bool inside = true;
		  
		  for(int i = 0; i < blocks.size(); i++)
		    {
		      if( x < blocks[i].x && x > (blocks[i].x+ 100) && y < blocks[i].y &&  y > (blocks[i].y + 100)) {
			action=2;
			blockNum = i;
			break;
		      }
		    }
		  else {
		    makeWire();
		    cout << "makeWire" << endl;
		    break;
		  }
		case SDL_MOUSEBUTTONUP:
			action = 0;
			break;
	}
	
	switch (action)
	  {
	  case 1:
	    moveWire();
	    break;
	  case 2:
	    moveGate(blockNum);
	    break;
	  default:
	    break;
	  }

	return 0; // continues
}


// Push back a new wire to vector wires
void Window::makeWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Wire* ptr = new Wire(NULL, x, y); // call constructor

	wires.push_back(ptr);
	action = 1;
}


void Window::moveWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	wires.back()->movePoint(x, y);
}

void Window::moveGate(int i)
{
  int x;
  int y;
  SDL_GetMouseState(&x,&y);
  blocks[i]->moveBlock(x, y);
}

// Draw blocks function!!!
void Window::drawBlocks()
{
  for(int i = 0; i < blocks.size(); i++)
    {
      blocks[i]->draw(renderer);
    }

}


void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		wires[i]->draw(renderer);
	}

	short xPoints[9] = {100, 100, 150, 165, 170, 175, 170, 165, 150};
	short yPoints[9] = {100, 160, 160, 150, 140, 130, 120, 110, 100};

	filledPolygonRGBA(renderer, xPoints, yPoints, 9, 255, 0, 50, 255);
}

