/* Configuration loader class

It loads from a file (or default values) parameters for the turmite simulation.
It has a role of parameters containers for the program.
*/
#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

#ifndef ANT_H
#include "ant.h"
#endif // !ANT_H

#ifndef GRID_H
#include "grid.h"
#endif // !GRID_H

class ConfigLoader
{
private:
	int m_states;												// Number of states for an ant
	int m_colors;												// Number of colors for a cell
	int m_border;												// Type of border (cf. grid.h)
	int m_widthG;												// Width of the grid
	int m_heightG;												// Height of the grid
	int m_widthW;												// Width of the window
	int m_heightW;												// Height of the window
	vector<vector<ant_instruction>> m_instructions;				// Instructions table for the ant
	vector<Uint32> m_color_table;								// Color table for display



public:
	/* Constructor from an ASCII file (see README)
		@param file	the ASCII file
		*/
	ConfigLoader(char* file);

	/* Constructor from default values. Langton ant (2 colors, 1 state)
		*/
	ConfigLoader();	

	/* Get the number of states
	@return the number of states
		*/
	int states() { return m_states; }

	/* Get the number of colors
	@return the number of colors
	*/
	int colors() { return m_colors; }

	/* Get the border type
	@return the border type
	*/
	int border() { return m_border; }

	/* Get the width of the grid
	@return the width of the grid
	*/
	int widthG() { return m_widthG; }

	/* Get the height of the grid
	@return the height of the grid
	*/
	int heightG() { return m_heightG; }

	/* Get the width of the window
	@return the width of the window
	*/
	int widthW() { return m_widthW; }

	/* Get the height of the window
	@return the height of the window
	*/
	int heightW() { return m_heightW; }

	/* Get the instructions matrix
	@return the instructions matrix
		*/
	vector<vector<ant_instruction>> instructions() { return m_instructions; }

	/* Get the colors table
	@return the colors table
	*/
	vector<Uint32> color_table() { return m_color_table; }	
};

#endif // !CONFIGLOADER_H