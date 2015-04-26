#include "AppInfo.h" 
#include "Maze.h"
#include "Utils.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    volatile time_t StartTime;
    volatile time_t EndTime;
    WINDOW* pWindow = NULL;

    if(argc != 2) {
        fprintf(stderr, "\n\tUsage " APPNAME  ": %s <file name>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    LoadMaze(argv[1]);
    initrandom();

    pWindow = initscr();
    wresize(pWindow, 35, 100);
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    DrawXY(&PlayerPos);
    /* wait for RIGHT-arrow */
    while (TestArrow() != RIGHT) {
        clear();
        mvprintw(0, 1, APPNAME_VERSION " ------------------------------------------"
                                       "----------------------");
        mvprintw(2, 1, "S(tudent) as fast a possible to 'ing' exit of maze!");
        viewEcho();
        usleep(10000);
    }
    StartTime = time(NULL);
    while(!IsAtIng()) {
        int i = 0;
        /* Ing not reached !! */
        for (i = 0; i < DEMONS; i++) {
            PlayerAction();
            DemonAction(&DemonsPos[i]);
            PlayerAction();
            clear();
            mvprintw(0, 1, APPNAME_VERSION " ------------------------------------------"
                                           "----------------------");
            mvprintw(2, 1, "S(tudent) as fast a possible to 'ing' exit of maze!");
            viewEcho();
        }
        ShowTime(StartTime, time(NULL), 25, 1);
        usleep(50000);
    }
    EndTime = time(NULL);
    mvprintw(25, 1, "Time: %7.0f sec.", difftime(EndTime, StartTime));
    refresh();
    nodelay(stdscr, FALSE);
    getchar();
    endwin();

    return 0;
}

