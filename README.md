# CS161-Minesweeper Documentation

## Overview

> **_This project is a Minesweeper game implemented in C++ using the Qt6 framework. The game includes several pages such as the game board, home page, and level selection page. The game state is managed by a Session class, which also handles serialization and deserialization of the game state for saving and loading games._**

## Features

_Gameboard Page: The gameboard page is where the Minesweeper game is played. It is implemented in the GameboardPage class._

_Home Page: The home page is the first page that users see when they start the game. It is implemented in the HomePage class._

_Level Selection Page: The level selection page allows users to select the difficulty of the game. It is implemented in the LevelSelectionPage class._

_Session Management: The Session class manages the game state, including the game board, the number of mines, and the game timer. It also handles serialization and deserialization of the game state for saving and loading games._

_Timer: The game includes a timer that tracks how long the player has been playing the current game. It is implemented in the Timer class._

_Style: The Style class provides styling for the game, including colors._

## Project Structure

**The project is organized into several directories:**

`src/`: Contains the source code of the project.
`main.cpp`: The entry point of the application.
`MainWindow/`: Contains the MainWindow class, which is the main window of the application.
`Pages/`: Contains the different pages of the application, including the game board, home page, and level selection page.
`Session/`: Contains the Session class, which manages the game state.
`Style/`: Contains the Style class, which provides styling for the game.
`Timer/`: Contains the Timer class, which implements the game timer.
`CMakeLists.txt`: The CMake configuration file for building the project.
`Data/`: Contains data files used by the application, such as saved game states.
`Images/`: Contains image files used by the application.
`QT6/`: Contains the Qt6 framework used by the application.
`build/`: The output directory for the built application.
`.vscode/`: Contains configuration files for the Visual Studio Code IDE.
`.gitignore`: Specifies which files and directories to ignore in Git version control.
`install.sh`: A shell script for installing the application.

##Building the Project
The project uses CMake for building. To build the project, run the following command in the root directory of the project:

This will build the project and output the executable in the build/ directory.

##Running the Project
**To run the project, navigate to the build/ directory and run the executable:**

```
./Game.exe
```

This will start the Minesweeper game.

## Minesweeper Rules

### Objective

The objective of Minesweeper is to clear the playing area without detonating any hidden mines.

### Game Setup

1. A grid of cells is presented, and some of the cells contain hidden mines.
2. The size of the grid and the number of mines are predetermined or customizable.

### Gameplay

1. Left-click on a cell to reveal its content.
   - If the cell contains a mine, the game ends, and you lose.
   - If the cell is empty, a number is revealed, indicating how many mines are in the adjacent cells (diagonals included).
2. Right-click on a cell to flag it as a mine.
   - Flagging helps you keep track of potential mine locations.
3. If all non-mine cells are revealed, you win the game.

### Winning

To win Minesweeper, reveal all the safe cells without detonating any mines.

### Losing

You lose the game if you click on a cell containing a mine.

### Tips

1. Use the revealed numbers to strategically identify and avoid mines.
2. Pay attention to the number of flags you've placed and compare it to the number of mines in the game.

Enjoy playing Minesweeper!
