#include "configloader.h"

ConfigLoader::ConfigLoader(char* file) {
	// Load config file
	std::fstream configfile(file);
	std::string line;

	while (std::getline(configfile, line)) {
		// Break if we start to read the table
		if (line.rfind("table") != std::string::npos)
			break;

		// Else, extract key/value and store results
		std::string key = line.substr(0, line.find(' '));
		std::string value = line.substr(line.find(' ') + 1);

		// Parse and store values
		if (key.rfind("states") != std::string::npos) {			// States
			m_states = atoi(value.c_str());
		}
		else if (key.rfind("colors") != std::string::npos) {	// Colors
			m_colors = atoi(value.c_str());
		}
		else if (key.rfind("border") != std::string::npos) {	// Border
			if (value.rfind("fixed") != std::string::npos) {
				m_border = ANT_BORDER_FIXED;
			}
			else if (value.rfind("torus") != std::string::npos) {
				m_border = ANT_BORDER_TORUS;
			}
			else if (value.rfind("infinite") != std::string::npos) {
				m_border = ANT_BORDER_INFINITE;
			}
			else {
				m_border = ANT_BORDER_TORUS;
			}
		}
		else if (key.rfind("width") != std::string::npos) {		// Width
			m_widthG = atoi(value.c_str());
			m_widthW = m_widthG > 512 ? m_widthG : 512;
		}
		else if (key.rfind("height") != std::string::npos) {	// Height
			m_heightG = atoi(value.c_str());
			m_heightW = m_heightG > 512 ? m_heightG : 512;
		}
	}

	// Then parse the instruction table (nstates x ncolors)
	ant_instruction zero_instruction = {0,0,0};
	m_instructions = vector<vector<ant_instruction> >(m_states, vector<ant_instruction>(m_colors,  zero_instruction));
	for (int st = 0; st < m_states; st++) {
		std::getline(configfile, line);
		for (int col = 0; col < m_colors; col++) {
			char c = line.at(6 * col);
			m_instructions[st][col].color = atoi(&c);			// Color
			c = line.at(6 * col + 2);
			m_instructions[st][col].way = atoi(&c);				// Way
			c = line.at(6 * col + 4);
			m_instructions[st][col].state = atoi(&c);			// State
		}
	}

	// Define a color table (limit = 5)
	switch (m_colors)
	{
	case 2:								// White / Black
		m_color_table.resize(2);
		m_color_table[0] = 0xffffffff;
		m_color_table[1] = 0xff000000;
		break;
	case 3:								// White / Red / Blue
		m_color_table.resize(3);
		m_color_table[0] = 0xffffffff;
		m_color_table[1] = 0xffff0000;
		m_color_table[2] = 0xff0000ff;
		break;
	case 4:								// White / Red / Green / Blue
		m_color_table.resize(4);
		m_color_table[0] = 0xffffffff;
		m_color_table[1] = 0xffff0000;
		m_color_table[2] = 0xff00ff00;
		m_color_table[3] = 0xff0000ff;
		break;
	case 5:								// White / Black / Red / Green / Blue
		m_color_table.resize(5);
		m_color_table[0] = 0xffffffff;
		m_color_table[1] = 0xff000000;
		m_color_table[2] = 0xffff0000;
		m_color_table[3] = 0xff00ff00;
		m_color_table[4] = 0xff0000ff;
		break;
	default:							// White / Black
		m_color_table.resize(2);
		m_color_table[0] = 0xffffffff;
		m_color_table[1] = 0xff000000;
		break;
	}

	configfile.close();
}

ConfigLoader::ConfigLoader() {
	m_states = 1;
	m_colors = 3;
	m_border = ANT_BORDER_TORUS;
	m_widthG = 128;
	m_heightG = 128;
	m_widthW = 512;
	m_heightW = 512;
	
	m_instructions.resize(m_states, vector<ant_instruction>(m_colors));
	m_instructions[0][0].color = 1;
	m_instructions[0][0].way = 0;
	m_instructions[0][0].state = 0;
	m_instructions[0][1].color = 0;
	m_instructions[0][1].way = 1;
	m_instructions[0][1].state = 0;

	m_color_table.resize(m_colors);
	m_color_table[0] = 0xffffffff;
	m_color_table[1] = 0xffff0000;
}