# Turmite Simulator
Author: Clément Aymard

Date  : 08/31/2014


## Introduction
Turmite simulator is a program which simulate the turmite; it's a Turing machine where each subject (ants) has an orientation, a state and an instruction table. It evolves in a 2D grid composed of cells which have a color. Given its state and the color of the cell where it is, the ant look on its instruction table to know which color it has to put on the cell, with direction it has to have and which state it has to get.

## Usage
The simulator can be lauched on its own (Langton's ant configuration) or with a configuration file. To do so, open a terminal, go to the program folder (release) and launch the command:

`./turmite.exe <path to the configuration file>`

Some examples configuration files are provided. You can create your own configuration file, cf. the next section.

When the program starts, an ant is put at the center of the space. You can add more ants by clicking in the window.

To save a screenshot of the window, press the 's' key on your keyboard.

To quit the program, press the escape key on your keyboard or close the window.


## Configuration file convention
The configuration file should respect this pattern:

```
states 2
colors 2
border torus
width 256
width 256
table
1 0 1 0 0 1
1 1 1 0 0 0
```

* states: number of states for an ant. min = 1, max = 10.
* colors: number of colors for a cell. min = 2, max = 5.
* border: type of border for the grid. fixed, torus, infinite.
* width:  the width of the grid
* height: the height of the grid
* table:  delimitation to start the intruction table. There is as many lines as states and as many colums as colors. Each element of the table is triplet with : color = the new color of the cell, way = the way to rotate the ant (0 clockwise, 1 counter clockwise), state = the new state of the ant. In this table, for the state 0 and color 1, the triplet '0 0 1' means "put color 1, turn clockwise, pass state 1".

- Only one space between an identifier and a value /!\
- All the above values have to be wrote in the config file /!\


## Building
To build the program you will need SDL 2.0. Windows users can download it here. https://www.libsdl.org/download-2.0.php). For Linux users, SDL should be in your distribution.

### Windows (Visual Studio):
To build the program easily you need CMake : http://www.cmake.org/

Open a terminal and go in the 'project' folder. Run the command :

`cmake -G <your VS version> ..`

Build the program by opening the Visual Solution.

To know the code of your VS version, see 'cmake /?'.

### Linux
There is actually some incompatibilities with gcc. Working on it.


## Known bugs
Launching program with double-clic can create an additional ant at (0,0) during startup.
