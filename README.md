# Maze

The maze program uses the ncurses library that allows programmers to write
text-based user interfaces.
The maze, the player and the demons are represented by characters.

Installation ncurses Ubuntu:

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

S (student) must try to reach 'ing' in the most shortest time.
The demons are: oOdDvVxX, they will annoy you.

    SoOdDvVxX
    ************************            ********************        *********
    *X       *     *       *          ***    *           * *       **       *
    **  **   *  *  *   *   *        *** *       ** ****D   *      **    d   *
    *    *      *****  *   *      ***   ** **      *       *     **         *
    S  * **     *      **  *******              *     ******    **   ***    *
    *  *       **  *   *        *       ************   *   *   **      *  **
    ********   *   **********   **    ***          *   *   *  **    *    **
           *   *  o*        * *  *   **               **   * **    **   **
           *  **   *        *    *   *           * *       ***   ** V  **
           *      **        *        ** ***      * **********    *    **
           **  *   *        **** *   *           ***           ***   **
           *   *   *        *    *   **                *   *****      **
           *  **   *        ***      ****    x    ******* ***     **   **
           *      **          ***    *  *********  *       ***     *    **
           *   **  *            ***             *     v*   * **   **********
           *    *  *              ***     ****  *  ** **   *  **           *
           ****    *                ***      **    *       *   **    Ing   *
           * O     *                  ***       *          *    **         *
           *********                    ********************     ***********

### TCK == Technische ComputerKunde (Dutch, Computer Engineering)

### Ing == HBO ingenieur (Dutch, bachelor of engineering degree)
