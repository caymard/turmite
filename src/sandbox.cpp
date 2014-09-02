#include <SDL.h>
#include <iostream>
#include <map>
#include <list>
#include <ctime>
#include <string>
#include <array>
#include <Windows.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#define BLACK 0;
#define WHITE 255;

using std::cout;
using std::cerr;
using std::endl;

using std::pair;
using std::map;
using std::list;

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

int SDL_basics()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "SDL INIT FAILED" << SDL_GetError() << endl;
		exit(1);
	}

	// Create window
	SDL_Window* display;
	display = SDL_CreateWindow("turmite", 100, 100, 512, 512, 0);

	// Create event
	SDL_Event event;

	// Set the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(display, -1, 0);

	// Get image
	SDL_Surface* image = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
	if (image == nullptr)
	{
		cerr << "bad image" << SDL_GetError() << endl;
		return 1;
	}

	// Make texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	bool quit = false;
	int cur_x = 0, cur_y = 0;
	std::array < std::array<int, 128>, 128 > model;
	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 128; j++) {
			model[i][j] = 0;
		}
	}

	while (!quit)
	{
		SDL_WaitEventTimeout(&event, 10);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			putpixel(image, event.button.x / 4, event.button.y / 4, 0x00ff00ff);
			break;
		}

		model[cur_x][cur_y] = 1;
		for (int i = 0; i < 128; i++){
			for (int j = 0; j < 128; j++) {
				if (model[i][j] == 0)
					putpixel(image, i, j, 0x00000000);
				else
					putpixel(image, i, j, 0xffffffff);
			}
		}

		cur_x++;
		if (cur_x >= 128) {
			cur_x = 0;
			cur_y++;
			if (cur_y >= 128) {
				cur_y = 0;
			}
		}

		SDL_UpdateTexture(texture, NULL, image->pixels, image->pitch);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}


	// Cleanup this mess
	//SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);

	SDL_Quit();

	return 0;
}

int main(int argc, char* args[])
{
	//SDL_basics();

	Uint32 test1 = 0xff000000;
	Uint32 test2 = 0xffffff;
	Uint32 test3 = test1 | test2;

	cout << test1 << endl << test2 << endl;
	cout << (test3 == 0xffffffff) << endl;


	Sleep(10000);

	return 0;
}
