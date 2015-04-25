#ifndef MAZE_H
#define MAZE_H

#include <time.h>
#include <ncurses.h>

#define FALSE 0
#define TRUE 1
#define FOREVER	TRUE

#define SCRNMINX 4
#define SCRNMAXX 130
#define SCRNMINY 4
#define SCRNMAXY 50

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define SPACE ' '
#define DEMONS 8

typedef struct ScrnPosXY
{
    int ScrnX;
    int ScrnY;
    char Player;
} ScrnPosXY;

extern struct ScrnPosXY PlayerPos;
extern struct ScrnPosXY DemonsPos[DEMONS];

void InitPlayerDemons(char *PlayerDemons, char Dmn, int PosX, int PosY);
void LoadMaze(const char *Fname);
void InitMaze(void);
int TestMove(struct ScrnPosXY *pPosXY, int Direction);
int TestArrow(void);
void ShowTime(time_t StartTime, time_t PlayTime, int Xtxt, int Ytxt);
void DrawXY(struct ScrnPosXY *PosXY);
int IsAtIng(void);
void MoveXY(struct ScrnPosXY *pPosXY, int Direction);
void PlayerAction(void);
void DemonAction(struct ScrnPosXY *Demon);
int StrategyAction(struct ScrnPosXY Demon, int Strategy);
void Play(void);

#endif
