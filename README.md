# CS161-Minesweeper Documentation

_*Status: Completed*_

## Overview

> _This project is a Minesweeper game implemented in C++ using the Qt6 framework. The game includes several pages such as the game board, home page, and level selection page. The game state is managed by a Session class, which also handles serialization and deserialization of the game state for saving and loading games._

## Features.

_`Gameboard Page`: The gameboard page is where the Minesweeper game is played. It is implemented with the standard Minesweeper game rule (read more in [Game rule](#gameplay))_

_`Level`: The level of the gameboard is determined by the density of the board_

_`Timing`: As sooner as a game session starts, the timer will start, and upon winning or losing, the timer will stop_

_`Scoring`: The scores are determined by the time it takes to finish a board of a particular level, the high scores will be automatically updated if you win the game and the time it takes to finish it less than your all time shortest duration. The high scores for each level will be saved and loaded in next playing session._

_`Level Selection Page`: The level selection page allows users to select the difficulty of the game. You can choose the pre-determined gameboard grid and mine number, or customize it with the `Custom` button_

_`Session Management`: Your playing session will be saved and you will be able to resume your last not-finished game. Your progress will be saved even if you click the `Exit` button or accidentally choose to play a new game, you can just simply click `Resume` to continue with that session._

## Project Structure

**The project is organized into several directories:**

`src/`: Contains the source code of the project, including:
`main.cpp`: The entry point of the application.
`MainWindow/`: Contains the MainWindow class, which is the main window of the application.
`Pages/`: Contains the different pages of the application, including the gameboard page, home page, and level selection page.
`Session/`: Contains the Session class, which manages the game state.
`Style/`: Contains the Style class, which provides styling for the game.
`Timer/`: Contains the Timer class, which implements the game timer.
`resources.qrc`: Contains the path to icons used in the game
`CMakeLists.txt`: The CMake configuration file for building the project.
`Data/`: Contains data files used by the application, such as saved game states, highscores.
`Images/`: Contains image/icon files used by the application.
`QT6/`: Contains the Qt6 framework used by the application.
`install.sh`: A shell script for installing the application.

## Source code design:

> The project use QT framework to make a full GUI application. It uses the signals and slots mechanism of the QT framework, which make the game more visually appealing, also make interactive.

- `Entry Point`: The entry point of the application is main.cpp where the application is initialized and the main window is created.

- `Main Window`: The MainWindow class is the main window of the application. It contains a QStackedWidget that holds different pages of the application. The MainWindow class also has methods to handle game events like starting a new game, ending a game, and resuming a game.

- `Pages`: The application has different pages, each represented by a class. These pages include the home page, level selection page, and gameboard page. Each page is a QWidget and they are managed by the QStackedWidget in the MainWindow class.

- `Gameboard Page`: The GameboardPage class represents the gameboard page. It contains the gameboard, buttons for starting a new game, replaying, and exiting, a timer, and labels for announcements, level, and high score.

- `HomePage`: The HomePage class represents the homepage. It is a starting point of the game and player can choose between starting a new game, resume the previous, unfinished session, or exit the game.

- `LevelSelectionPage`: The LevelSelectionPage represents the page to select the desired level, you can choose the pre-determined levels or customize it the way you want.

- `Session`: The Session class manages the game state. It keeps track of the current level, score, and game status and also have to mission of serializing and deserializing game session, as well ass the high scores.
- `Style`: The Style class provides styling for the game. It's used to set the visual appearance of the game elements.

- `Timer`: The Timer class implements the game timer. It's likely used to keep track of the time elapsed during a game.

`Resources`: The resources.qrc file contains the path to icons used in the game. The Data/ directory contains data files used by the application, such as saved game states and high scores. The Images/ directory contains image/icon files used by the application.

## Building the Project

> The project uses CMake for building. It is recommended to use `g++` compiler and on `Windows` operating system.

_(Using something other than the recommended configurations may result in user, having to make some changes to the `CMakelists.txt` file be able to build the project)_

> **!!The script below can be used with Windows Command Prompt, Windows PowerShell and Bash( not guarantee it could run on other terminals**
> If you are not using the above terminals, please look at the actually script file and find the relavant command of your terminals

- To configure and build the project, run the following shell script in the root directory of the project:

If you have not had QT framework installed in your system, run:

```
./install.sh
```

- Then paste the path to your `QT6\mingw_64\bin` that has just been installed into your environment path
  **_!!!This step is important to be able to run the Game.exe application!!!_**
  **_Make sure you have QT6\mingw_64\bin in your environment variable Path_**

- To build the Game, run the following shell script in the root directory of the project (you may want to refresh terminal before doing this step):

```
./build.sh
```

_(Make sure you have g++, gcc, cmake and git installed in your system, and they are all put into the system variable path)_

This will build the project, output the executable in the root directory of the project and then run the Game.

##Running the Project

- To only run the project, navigate to the root directory and run the executable:

```
./Game.exe
```

- To install and run the installed version of the game, run the following command in the root diretory:

```
./run.sh
```

This will start the Minesweeper game.
_if you get any error related to dll, please check if you have correctly put to path to `\QT6\mingw_64\bin` into your environment variable_

> _If you struggle in any step, please see this visual manual: [doc/manual.md](doc/manual.md)_

> _If you have any problem in the process of building and run the Game, please contract me via:
> Gmail: tqhuy23@apcs.fitus.edu.vn
> Facebook: https://www.facebook.com/henry.tang.96199
> Phone: +84939781785_

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
4. Chording (Double Left-click on a number): If the correct number of flags are placed around a revealed number, reveal the remaining adjacent cells. If incorrect, the game may end.

#### Winning

To win Minesweeper, reveal all the safe cells without detonating any mines.

#### Losing

You lose the game if you click on a cell containing a mine.

### Tips

1. Use the revealed numbers to strategically identify and avoid mines.
2. Pay attention to the number of flags you've placed and compare it to the number of mines in the game.

Enjoy the game!
