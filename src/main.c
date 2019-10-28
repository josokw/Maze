#include "AppInfo.h"
#include "ConfigMaze.h"
#include "Maze.h"
#include "Utils.h"

#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP_US 50000

#define GRASS ' '
#define GRASS_PAIR 1

void handleResize(int signal)
{
   clear();
   viewEcho();
}

int main(int argc, char *argv[])
{
   struct sigaction sig;
   volatile time_t startTime;

   if (argc != 2) {
      fprintf(stderr, "\n\tUsage " APPNAME ": %s <file name>\n\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   loadMaze(argv[1]);
   initRandom();

   sig.sa_handler = handleResize;
   sig.sa_flags = 0;
   sigaction(SIGWINCH, &sig, 0);

   initscr();
   cbreak();
   noecho();
   nonl();
   intrflush(stdscr, FALSE);
   keypad(stdscr, TRUE);
   curs_set(0);
   nodelay(stdscr, TRUE);

   if (!has_colors()) {
      endwin();
      fprintf(stderr, "\n\tERROR: your terminal does not support color\n\n");
      exit(EXIT_FAILURE);
   }

   start_color();
   init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);

   clear();
   // draw_map();

   drawXY(&player);
   viewEcho();
   /* wait for RIGHT-arrow key */
   while (testArrowKey() != RIGHT) {
      usleep(SLEEP_US);
   }
   startTime = time(NULL);
   while (!isAtExit()) {
      int i = 0;
      /* exit not reached !! */
      for (i = 0; i < DEMONS; i++) {
         playerAction();
         demonAction(&demons[i]);
         playerAction();
         viewEcho();
      }
      showTime(startTime, time(NULL), 1, 15);
      usleep(SLEEP_US);
   }
   refresh();
   nodelay(stdscr, FALSE);

   waitfor('q');

   endwin();

   return 0;
}
