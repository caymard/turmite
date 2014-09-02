#include "grid.h"

// Grid constructor
Grid::Grid(int width, int height, vector<Uint32> color_table) {
	// Width and height private attributes
	m_width = width;
	m_height = height;
	m_color_table = vector<Uint32>(color_table);

	// Cells map
	m_cells.resize(width);
	for (int i = 0; i < m_cells.size(); i++) {
		m_cells[i].resize(height, 0);
	}
}

// Get the color of a cell
int Grid::get_color(int x, int y) {
	// Return -1 if position asked is out of range
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
		std::cerr << "Error in Grid::get_color : position is out of range." << std::endl;
		std::cerr << "x = " << x << ", y = " << y << std::endl;
		return -1;
	}
	// Return color if not
	else {
		return m_cells[x][y];
	}
	
}

// Set the color of a cell
void Grid::set_color(int x, int y, int color) {
	// Do nothing if position or color submitted is out of range
	if (x < 0 || x >= m_width || y < 0 || y >= m_height || color < 0) {
		std::cerr << "Error in Grid::set_color : position or color is out of range." << std::endl;
		std::cerr << "x = " << x << ", y = " << y << ", color = " << color << std::endl;
		return;
	}
	// Return color if not
	else {
		m_cells[x][y] = color;
		m_update_cells.push_front(pair<int, int>(x, y));
	}

}

// Fill a SDL surface
void Grid::fill_surface(SDL_Surface* surface){
	// Check dimensions compatibility
	if (surface->w != m_width || surface->h != m_height) {
		std::cerr << "Error in Grid::update_surface : size are different." << std::endl;
		std::cerr << "grid = (" << m_width << "x" << m_height << "), surface = (" << surface->w << "x" << surface->h << std::endl;
	}
	// Update colors
	else {
		for (int i = 0; i < surface->w; i++) {
			for (int j = 0; j < surface->h; j++) {
				int bpp = surface->format->BytesPerPixel;
				Uint8 *p = (Uint8 *)surface->pixels + j * surface->pitch + i * bpp;
				// Change color depending on color table
				*(Uint32 *)p = m_color_table[m_cells[i][j]];
			}
		}
	}
}

// Update a SDL surface
void Grid::update_surface(SDL_Surface* surface){
	// Check dimensions compatibility
	if (surface->w != m_width || surface->h != m_height) {
		std::cerr << "Error in Grid::update_surface : size are different." << std::endl;
		std::cerr << "grid = (" << m_width << "x" << m_height << "), surface = (" << surface->w << "x" << surface->h << std::endl;
	}
	// Fill colors
	else {
		while (!m_update_cells.empty()) {
			int bpp = surface->format->BytesPerPixel;
			Uint8 *p = (Uint8 *)surface->pixels + m_update_cells.front().second * surface->pitch + m_update_cells.front().first * bpp;
			// Change color depending on color table
			*(Uint32 *)p = m_color_table[m_cells[m_update_cells.front().first][m_update_cells.front().second]];
			m_update_cells.pop_front();
		}
	}
}