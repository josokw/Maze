#ifndef MAZE_H
#define MAZE_H

#include <time.h>

#define FALSE 0
#define TRUE 1

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

typedef struct {
   int ScrnX;
   int ScrnY;
   char Player;
} scrnPosXY_t;

extern scrnPosXY_t player;
extern scrnPosXY_t demons[];

void initPlayerDemons(char *PlayerDemons, char Dmn, int PosX, int PosY);
void loadMaze(const char *Fname);
void viewEcho(void);
int testMovement(const scrnPosXY_t *pPosXY, int Direction);
int testArrowKey(void);
void showTime(time_t startTime, time_t playTime, int Xtxt, int Ytxt);
void drawXY(const scrnPosXY_t *PosXY);
int isAtExit(void);
void moveXY(scrnPosXY_t *pPosXY, int Direction);
void playerAction(void);
void demonAction(scrnPosXY_t *Demon);
int strategyAction(const scrnPosXY_t *pDemon, int Strategy);

#endif
