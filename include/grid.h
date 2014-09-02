/* Grid class

	A grid is composed of cells which all have a color.
*/

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <SDL.h>

using std::vector;
using std::list;
using std::pair;

class Grid
{
private:
	int m_width;							// Width of the grid
	int m_height;							// Height of the grid
	vector<vector<int>> m_cells;			// Cells matrix
	vector<Uint32> m_color_table;			// Color table to link color index & hexadecimal code
	list<pair<int, int>> m_update_cells;	// List for the rendering optimization


public:
	
	/* Main constructor
		@param width		the width of the grid (in cells)
		@param height		the height of the grid (in cells)
		@param color_table	the color table
		*/
	Grid(int width, int height, vector<Uint32> color_table);
	
	/* Default constructor
		*/
	Grid() { };

	/* Get the width of the grid
		@return the width of the grid
		*/
	int width() { return m_width; }

	/* Get the height of the grid
		@return the height of the grid
		*/
	int height() { return m_height; }

	/* Get the color of a cell
		@param x	horizontal position of the cell
		@param y	vertical position of the cell
		@return		the color of the cell
		*/
	int get_color(int x, int y);

	/* Set the color of a cell
		@param x		horizontal position of the cell
		@param y		vertical position of the cell
		@param color	the color
		*/
	void set_color(int x, int y, int color);

	/* Fill a SDL Surface with the whole grid
		@param surface	pointer to the SDL surface
		*/
	void fill_surface(SDL_Surface* surface);

	/* Update a SDL Surface with points stocked in the update list
	   It allows to gain some time for rendering
		@param surface	pointer to the SDL Surface
		*/
	void update_surface(SDL_Surface* surface);

};

#endif // !GRID_H
