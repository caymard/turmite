#include "ant.h"

// Ant constructor
Ant::Ant(int x, int y, int nstates, vector < vector<ant_instruction> > instructions, Grid* grid, int state, int direction, int border) {
	m_x = x;
	m_y = y;
	m_nstates = nstates;
	m_instructions = vector<vector<ant_instruction>>(instructions);
	m_grid = grid;
	m_state = state;
	m_direction = direction;
	m_border = border;
	m_is_dead = false;
}

// Update position of the ant according its direction in a fixed world
// (if the ant try to go over the limits, it stays where it is)
void Ant::update_position_fixed() {
	switch (m_direction) {
	// North
	case ANT_N:
		if (m_y != 0) {
			m_y--;
		}
		break;
	// East
	case ANT_E:
		if (m_x != m_grid->width() - 1) {
			m_x++;
		}
		break;
	// South
	case ANT_S:
		if (m_y != m_grid->height() - 1) {
			m_y++;
		}
		break;
	// West
	case ANT_W:
		if (m_x != 0) {
			m_x--;
		}
		break;
	default:
		break;
	}
}

// Update position of the ant according its direction in a torus world
// (left is connected to right and up is connected with bottom)
void Ant::update_position_torus() {
	switch (m_direction) {
		// North
	case ANT_N:
		if (m_y == 0) {
			m_y = m_grid->height() - 1;
		}
		else {
			m_y = m_y--;
		}
		break;
		// East
	case ANT_E:
		m_x = (m_x + 1) % m_grid->width();
		break;
		// South
	case ANT_S:
		m_y = (m_y + 1) % m_grid->height();
		break;
		// West
	case ANT_W:
		if (m_x == 0) {
			m_x = m_grid->width() - 1;
		}
		else {
			m_x--;
		}
		break;
	default:
		break;
	}
}

// Update position of the ant according its direction in an infinite world
// (it died if go through limits)
void Ant::update_position_infinite() {
	switch (m_direction) {
		// North
	case ANT_N:
		if (m_y == 0) {
			m_is_dead = true;
		}
		else {
			m_y--;
		}
		break;
		// East
	case ANT_E:
		if (m_x == m_grid->width() - 1) {
			m_is_dead = true;
		}
		else {
			m_x++;
		}
		break;
		// South
	case ANT_S:
		if (m_y == m_grid->height() - 1) {
			m_is_dead = true;
		}
		else {
			m_y++;
		}
		break;
		// West
	case ANT_W:
		if (m_x == 0) {
			m_is_dead = true;
		}
		else {
			m_x--;
		}
		break;
	default:
		break;
	}
}

// Update direction according to the way (clockwise or note)
void Ant::update_direction(int way) {
	if (way == ANT_CLOCKWISE) {
		m_direction = (m_direction + 1) % 4;
	}
	else {
		m_direction = (m_direction == 0) ? ANT_W : m_direction - 1;
	}
}

// Run the ant's progression
void Ant::run() {
	if (!m_is_dead) {
		// Color of actual cell
		int current_color = m_grid->get_color(m_x, m_y);

		// Change direction
		update_direction(m_instructions[m_state][current_color].way);

		// Change the color
		m_grid->set_color(m_x, m_y, m_instructions[m_state][current_color].color);

		// Change state
		m_state = m_instructions[m_state][current_color].state;

		// Update position
		switch (m_border) {
		case ANT_BORDER_FIXED:
			update_position_fixed();
			break;
		case ANT_BORDER_TORUS:
			update_position_torus();
			break;
		case ANT_BORDER_INFINITE:
			update_position_infinite();
			break;
		default:
			update_position_fixed();
			break;
		}
	}
}