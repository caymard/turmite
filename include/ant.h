/* Ant class

A ant has its own running function, called by main program.
*/
#ifndef ANT_H
#define ANT_H

#include<vector>

#ifndef GRID_H
#include "grid.h"
#endif // !GRID_H

// cardinal directions
#define ANT_N 0						// North
#define ANT_E 1						// East
#define ANT_S 2						// South
#define ANT_W 3						// West

// rotation ways
#define ANT_CLOCKWISE 0				// Clockwise
#define ANT_COUNTERCLOCKWISE 1		// Counter clockwise

#define ANT_BORDER_FIXED 0			// Fixed space
#define ANT_BORDER_TORUS 1			// Toroidal space
#define ANT_BORDER_INFINITE 2		// Infinite space

using std::vector;

/* Structure to store an ant instruction
	@attr color		color to set on the cell
	@attr way		way to rotate
	@attr state		next state of the ant
	*/
struct ant_instruction {
	int color;
	int way;
	int state;
};

class Ant
{
private:
	int m_x;												// Horizontal position
	int m_y;												// Vertical position
	int m_direction;										// Direction (cardinal)
	int m_state;											// State
	int m_nstates;											// Number of different states
	int m_border;											// Type of border
	vector < vector<ant_instruction> > m_instructions;		// Intructions matrix (line = state, column = color)
	Grid* m_grid;											// Pointer to the grid where the ant evolve
	bool m_is_dead;											// Know if the ant is living or not

	/* Update the position of the ant in a fixed space.
	   If the ant is at a limit, it can't move forward.
		*/
	void update_position_fixed();

	/* Update the position of the ant in a toroidal space.
	If the ant is at a limit, it goes to the other side of the grid.
		*/
	void update_position_torus();

	/* Update the position of the ant in an infinite space.
	If the ant is at a limit, it died.
		*/
	void update_position_infinite();

	/* Update the direction of the ant.
		@param way	direction (ANT_CLOCKWISE / ANT_COUNTERCLOCKWISE)
		*/
	void update_direction(int way);


public:
	/* Main constructor
		@param x				Initial horizontal position
		@param y				Initial vertical position
		@param instructions		Intructions matrix
		@param grid				Pointer to the grid of the ant
		@param state			Initial state
		@param direction		Initial direction
		@param border			Border style
		*/
	Ant(int x, int y, int nstates, vector < vector<ant_instruction> > instructions, Grid* grid, int state, int direction, int border);

	/* Default constructor
	*/
	Ant() { };

	/* Get the horizontal position of the ant
	@return the horizontal position of the ant
	*/
	int x() { return m_x; }

	/* Get the vertical position of the ant
	@return the vertical position of the ant
	*/
	int y() { return m_y; }

	/* Get the direction of the ant
	@return the direction of the ant
	*/
	int direction() { return m_direction; }

	/* Get the state of the ant
	@return the state of the ant
	*/
	int status() { return m_state; }

	/* Know if the ant is dead
		@return true if dead, false if alive
		*/
	bool is_dead();

	/* Run the process
	*/
	void run();
};

#endif // !ANT_H