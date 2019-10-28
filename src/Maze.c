#include "Maze.h"
#include "AppInfo.h"
#include "Utils.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char maze[SCRNMAXX + 1][SCRNMAXY + 1] = {{0, 0}};

scrnPosXY_t player;
scrnPosXY_t demons[DEMONS];

static void initMaze(void)
{
   int X = 0;
   int Y = 0;

   for (Y = 0; Y <= SCRNMAXY; Y++) {
      for (X = 0; X <= SCRNMAXX; X++) {
         maze[X][Y] = SPACE;
      }
   }
}

void initPlayerDemons(char *PlayerDemons, char demon, int posX, int posY)
{
   static int idx = 0;

   if ((idx < DEMONS) && (demon != ' ')) {
      if (strchr(PlayerDemons, demon) != NULL) {
         if (demon == PlayerDemons[0]) {
            player.Player = demon;
            player.ScrnX = posX;
            player.ScrnY = posY;
         } else {
            demons[idx].Player = demon;
            demons[idx].ScrnX = posX;
            demons[idx].ScrnY = posY;
            idx++;
         }
      }
   }
}

void loadMaze(const char *mazeFileName)
{
   int X = 0;
   int Y = 0;
   FILE *fp = NULL;
   char playerDemons[80] = {'\0'};

   initMaze();
   if ((fp = fopen(mazeFileName, "r")) == NULL) {
      fprintf(stderr, "\n\tERROR " APPNAME " ");
      perror(mazeFileName);
      fprintf(stderr, "\n");
      exit(EXIT_FAILURE);
   } else {
      if (!feof(fp)) {
         fscanf(fp, "%s", playerDemons);
      }
      Y = SCRNMINY;
      while ((!feof(fp)) && (Y <= SCRNMAXY)) {
         X = SCRNMINX;
         while ((!feof(fp)) && (X <= SCRNMAXX)) {
            char temp;
            fscanf(fp, "%c", &temp);
            initPlayerDemons(playerDemons, temp, X, Y);
            if (temp != '\n') {
               maze[X++][Y] = temp;
            } else
               break;
         }
         Y++;
      }
      fclose(fp);
   }
}

void viewEcho(void)
{
   int X = 0;
   int Y = 0;

   mvprintw(1, 1, APPNAME_VERSION);
   for (Y = SCRNMINY; Y < SCRNMAXY; Y++) {
      for (X = SCRNMINX; X < SCRNMAXX; X++) {
         mvprintw(Y, X, "%c", maze[X][Y]);
      }
   }
   refresh();
}

void showTime(time_t startTime, time_t playTime, int Xtxt, int Ytxt)
{
   mvprintw(Xtxt, Ytxt, "time: %.0lf sec", difftime(playTime, startTime));
   refresh();
}

int testArrowKey(void)
{
   switch (getch()) {
      case KEY_UP:
         return (UP);
      case KEY_LEFT:
         return (LEFT);
      case KEY_RIGHT:
         return (RIGHT);
      case KEY_DOWN:
         return (DOWN);
   }
   return 0;
}

void drawXY(const scrnPosXY_t *posXY)
{
   mvprintw(posXY->ScrnY, posXY->ScrnX, "%c", posXY->Player);
   refresh();
}

int isAtExit(void)
{
   return (player.ScrnX > 64) && (player.ScrnY > 18);
}

int testMovement(const scrnPosXY_t *pPosXY, int direction)
{
   switch (direction) {
      case UP:
         return (maze[pPosXY->ScrnX][pPosXY->ScrnY - 1] == ' ');
      case DOWN:
         return (maze[pPosXY->ScrnX][pPosXY->ScrnY + 1] == ' ');
      case LEFT:
         return (maze[pPosXY->ScrnX - 1][pPosXY->ScrnY] == ' ');
      case RIGHT:
         return (maze[pPosXY->ScrnX + 1][pPosXY->ScrnY] == ' ');
   }
   return (-1);
}

void moveXY(scrnPosXY_t *pPosXY, int Direction)
{
   mvprintw(pPosXY->ScrnY, pPosXY->ScrnX, " ");
   maze[pPosXY->ScrnX][pPosXY->ScrnY] = SPACE;
   switch (Direction) {
      case UP:
         if ((pPosXY->ScrnY > SCRNMINY) && testMovement(pPosXY, UP)) {
            (pPosXY->ScrnY)--;
         }
         break;
      case DOWN:
         if ((pPosXY->ScrnY < SCRNMAXY) && testMovement(pPosXY, DOWN)) {
            (pPosXY->ScrnY)++;
         }
         break;
      case RIGHT:
         if ((pPosXY->ScrnX < SCRNMAXX) && testMovement(pPosXY, RIGHT)) {
            (pPosXY->ScrnX)++;
         }
         break;
      case LEFT:
         if ((pPosXY->ScrnX > SCRNMINX) && testMovement(pPosXY, LEFT)) {
            (pPosXY->ScrnX)--;
         }
         break;
   }
   attron(A_BOLD);
   mvprintw(pPosXY->ScrnY, pPosXY->ScrnX, "%c", pPosXY->Player);
   attroff(A_BOLD);
   refresh();
   maze[pPosXY->ScrnX][pPosXY->ScrnY] = pPosXY->Player;
}

void playerAction(void)
{
   switch (getch()) {
      case KEY_UP:
         moveXY(&player, UP);
         break;
      case KEY_LEFT:
         moveXY(&player, LEFT);
         break;
      case KEY_RIGHT:
         moveXY(&player, RIGHT);
         break;
      case KEY_DOWN:
         moveXY(&player, DOWN);
         break;
   }
}

int strategyAction(const scrnPosXY_t *pDemon, int strategy)
{
   switch (strategy) {
      case 0:
         return (0);
      case 1:
         return (randomRange(4) + 1);
      case 2:
         if (pDemon->ScrnY < player.ScrnY) {
            return (DOWN);
         }
         if (pDemon->ScrnY > player.ScrnY) {
            return (UP);
         }
         break;
      case 3:
         if (pDemon->ScrnX < player.ScrnX) {
            return (RIGHT);
         }
         if (pDemon->ScrnX > player.ScrnX) {
            return (LEFT);
         }
   }
   return (0);
}

void demonAction(scrnPosXY_t *pDemon)
{
   moveXY(pDemon, strategyAction(pDemon, randomRange(5)));
}
