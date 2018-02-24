# Maze
Maze C program using ncurses. The maze, the player and demons are represented by characters.

Build
-----
CMake must be available. Goto the Maze directory.

    cd Maze
    mkdir build
    cd build
    cmake ..
    make
  
Executing
---------
Maze needs a text file containing the maze and a string containing the player and the demons.

    cd ../bin
    ./maze ../data/maze01.dat
  
Example maze data file
----------------------
S (student) must try to reach ing in the most shortest time. The demons are: oOdDvVxX, they will annoy you.

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

TCK == Technische ComputerKunde (Dutch, Computer Engineering).

Ing == HBO ingenieur (Dutch, bachelor engineering degree).
