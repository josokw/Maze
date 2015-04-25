#include "AppInfo.h" 
#include "Maze.h"
#include "Utils.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    volatile time_t StartTime;
    volatile time_t EndTime;

    initrandom();
    initscr(); /* Start curses mode */
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    clear(); /* Clear screen */
    mvprintw(0, 1, APPNAME_VERSION " ------------------------------------------"
                                   "----------------------");
    mvprintw(2, 1, "S(tudent) as fast a possible to 'ing' exit of maze!");
    refresh();

    if (argc != 2)
    {
        exit(EXIT_FAILURE);
    }
    LoadMaze(argv[1]);
    DrawXY(&PlayerPos);
    /* wait for RIGHT-arrow */
    while (TestArrow() != RIGHT);
    StartTime = time(NULL);
    while (!IsAtIng())
    {
        int i = 0;
        /* ING not reached !! */
        for (i = 0; i < DEMONS; i++)
        {
            PlayerAction();
            DemonAction(&DemonsPos[i]);
            PlayerAction();
        }
        ShowTime(StartTime, time(NULL), 25, 1);
        usleep(50000);
    }
    EndTime = time(NULL);
    mvprintw(20, 27, "Time: %7.0f sec.", difftime(EndTime, StartTime));
    refresh();
    nodelay(stdscr, FALSE);
    getchar();
    endwin();

    return 0;
}

