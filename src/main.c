#include "AppInfo.h" 
#include "Maze.h"
#include "Utils.h"

#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void handleResize(int signal) {
    clear();
    viewEcho();
}

int main(int argc, char *argv[]) {
    struct sigaction sig;
    volatile time_t startTime;
    WINDOW* pWindow = NULL;

    if(argc != 2) {
        fprintf(stderr, "\n\tUsage " APPNAME  ": %s <file name>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    loadMaze(argv[1]);
    initRandom();

    sig.sa_handler = handleResize;
    sig.sa_flags = 0;
    sigaction(SIGWINCH, &sig, 0);

    pWindow = initscr();
    //wresize(pWindow, 25, 85);
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    DrawXY(&PlayerPos);
    viewEcho();
    /* wait for RIGHT-arrow */
    while (TestArrow() != RIGHT) {
        usleep(50000);
    }
    startTime = time(NULL);
    while(!isAtExit()) {
        int i = 0;
        /* exit not reached !! */
        for (i = 0; i < DEMONS; i++) {
            PlayerAction();
            DemonAction(&DemonsPos[i]);
            PlayerAction();
            viewEcho();
        }
        showTime(startTime, time(NULL), 1, 15);
        usleep(50000);
    }
    refresh();
    nodelay(stdscr, FALSE);
    while (getchar() != 'q') {
        /* wait for <q> quit */
    }
    endwin();

    return 0;
}
