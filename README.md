# Maze

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/827f3e14d67f432586e920f4a3009366)](https://www.codacy.com/project/josokw/Maze/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=josokw/Maze&amp;utm_campaign=Badge_Grade_Dashboard)
[![CodeFactor](https://www.codefactor.io/repository/github/josokw/maze/badge)](https://www.codefactor.io/repository/github/josokw/maze)

The maze program uses the ncurses library that allows programmers to write
text-based user interfaces. The maze, the player and the demons are represented
by characters.

Installation __ncurses__ Ubuntu:

    sudo apt install libncurses5-dev libncursesw5-dev

## Build management by CMake

CMake must be installed. Goto the Maze directory.

    mkdir build
    cd build
    cmake ..
    make
  
## Executing 'maze'

Maze needs a text file as input containing the maze and a string containing
the player and the demons. The executable is found in the bin directory.

    cd ../bin
    ./maze ../data/maze01.dat

## Example 'maze' data file

X must try to reach 'exit' in the most shortest time.
The demons are: **o**, **#** and **+**, they will annoy you.

    Xo#+
    ************************            ********************        *********
    *o       *     *       *          ***    *           * *       **       *
    **  **   *  *  *   *   *        *** *       ** ****#   *      **    +   *
    *    *      *****  *   *      ***   ** **      *       *     **         *
    X  * **     *      **  *******              *     ******    **   ***    *
    *  *       **  *   *        *       ************   *   *   **      *  **
    ********   *   **********   **    ***          *   *   *  **    *    **
           *   *  o*        * *  *   **               **   * **    **   **
           *  **   *        *    *   *           * *       ***   ** +  **
           *      **        *        ** ***      * **********    *    **
           **  *   *        * ** *   *           ***           ***   **
           *   *   *        *    *   **                *   *****      **
           *  **   *        ***      ****    #    ******* ***     **   **
           *      **          ***    *  *********  *       ***     *    **
           *   **  *            ***             *     #*   * **   **********
           *    *  *              ***     ****  *  ** **   *  **           *
           ****    *                ***      **    *       *   **    exit  *
           * o     *                  ***       *          *    **         *
           *********                    ********************     ***********
