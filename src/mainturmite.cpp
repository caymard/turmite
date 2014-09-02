/* Turmite
	A turmite simulation with SDL printing.
	See the README file to know how to use it.
*/
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "grid.h"
#include "ant.h"
#include "configloader.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")


using std::cout;
using std::cerr;
using std::endl;

/* Main function
	@param config	the path to the configuration file
*/
int SDL_basics(ConfigLoader* config)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "SDL INIT FAILED" << SDL_GetError() << endl;
		exit(1);
	}

	// Create window
	SDL_Window* display;
	display = SDL_CreateWindow("turmite", 100, 100, config->widthW(), config->heightW(), 0);

	// Create event
	SDL_Event event;

	// Set the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(display, -1, 0);

	// Get image
	SDL_Surface* image = SDL_CreateRGBSurface(0, config->widthG(), config->heightG(), 32, 0, 0, 0, 0);
	if (image == nullptr)
	{
		cerr << "bad image" << SDL_GetError() << endl;
		return 1;
	}

	// Make texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	bool quit = false;																	// Loop ending boolean
	bool lockdown = false;																// Security for ant creation
	Grid ant_grid(config->widthG(), config->heightG(), config->color_table());			// Grid of the ants world
	ant_grid.fill_surface(image);														// Fill the initial grid in the surface
	Ant ant1(config->widthG() / 2,														// First ant
		     config->widthG() / 2,
			 config->states(),
			 config->instructions(),
			 &ant_grid, 0, 0, config->border());
	std::vector<Ant> ant_colony(1, ant1);												// Ant colony
	int image_saved = 0;																// Number of saved images
	float window_ratio_x = (float)config->widthW() / config->widthG();					// Horizontal ratio between grid and window
	float window_ratio_y = (float)config->heightW() / config->heightG();				// Vertical ratio between grid and window

	// SDL MAIN LOOP
	while (!quit)
	{
		// SDL events
		SDL_WaitEventTimeout(&event, 1);
		switch (event.type) {
		case SDL_QUIT:												// window has been closed
			quit = true;
			break;
		case SDL_KEYDOWN:											// keyboard pressed
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)	// escape key, quit
				quit = true;
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) { // 's' key, save screenshot
				std::ostringstream ss;
				ss << "turmite_" << image_saved << ".bmp";
				SDL_SaveBMP(image, ss.str().c_str());
				cout << "image saved : " << ss.str() << endl;
				image_saved++;
			}
			break;
		case SDL_MOUSEBUTTONUP:										// security to avoid multiple creation
			if (lockdown)
				lockdown = false;
			break;
		case SDL_MOUSEBUTTONDOWN:									// mouse clic in the window, ant creation
			if (!lockdown) {
				Ant newant((int)event.button.x / window_ratio_x,
						   (int) event.button.y / window_ratio_y,
						   config->states(), config->instructions(),
						   &ant_grid, 0, 0, config->border());
				ant_colony.resize(ant_colony.size() + 1);
				ant_colony[ant_colony.size() - 1] = newant;
				cout << "new ant ! (" << (int) (event.button.x / window_ratio_x) << "," <<
						(int) (event.button.y / window_ratio_y) << ")" << endl;
				lockdown = true;
			}
			break;
		}

		// Run each ant for one step
		for (int i = 0; i < ant_colony.size(); i++) {
			ant_colony[i].run();
		}

		// Update display
		ant_grid.update_surface(image);
		SDL_UpdateTexture(texture, NULL, image->pixels, image->pitch);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}


	// Cleanup SDL context
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);
	SDL_Quit();

	return 0;
}

int main(int argc, char* args[])
{
	ConfigLoader config;

	// Configuration file
	if (argc > 1) {
		config = ConfigLoader(args[1]);
	}
	// Default configuration
	else {
		config = ConfigLoader();
	}

	return SDL_basics(&config);
}
