#include "AppInfo.h"
#include "Maze.h"
#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char Maze[SCRNMAXX+1][SCRNMAXY+1] = {{0, 0}};

struct ScrnPosXY PlayerPos;
struct ScrnPosXY DemonsPos[DEMONS];

void initPlayerDemons(char *PlayerDemons, char Dmn, int PosX, int PosY)
{
    static int count = 0;

    if ((count < DEMONS) && (Dmn != ' ')) {
        if (strchr(PlayerDemons, Dmn) != NULL)
        {
            if (Dmn == PlayerDemons[0])
            {
                PlayerPos.Player = Dmn;
                PlayerPos.ScrnX	= PosX;
                PlayerPos.ScrnY	= PosY;
            }
            else
            {
                DemonsPos[count].Player = Dmn;
                DemonsPos[count].ScrnX	= PosX;
                DemonsPos[count].ScrnY	= PosY;
                count++;
            }
        }
    }
}

void loadMaze(const char *Fname)
{
    int X = 0;
    int Y = 0;
    FILE *fp = NULL;
    char PlayerDemons[80] = {'\0'};

    for (Y=0; Y <= SCRNMAXY; Y++)
    {
        for (X=0; X <= SCRNMAXX; X++)
        {
            Maze[X][Y] = SPACE;
        }
    }

    if ((fp = fopen(Fname, "r")) == NULL)
    {
        fprintf(stderr, "\n\tERROR " APPNAME " ");
        perror(Fname);
        fprintf(stderr, "\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (!feof(fp))
        {
            fscanf(fp, "%s", PlayerDemons);
        }
        Y = SCRNMINY;
        while ((!feof(fp)) && (Y <= SCRNMAXY))
        {
            X = SCRNMINX;
            while ((!feof(fp)) && (X <= SCRNMAXX))
            {
                char Temp;
                fscanf(fp, "%c", &Temp);
                initPlayerDemons(PlayerDemons, Temp, X, Y);
                if (Temp != '\n')
                {
                    Maze[X++][Y] = Temp;
                }
                else break;
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
    for (Y = SCRNMINY; Y < SCRNMAXY; Y++)
    {
        for (X = SCRNMINX; X < SCRNMAXX; X++)
        {
            mvprintw(Y, X, "%c", Maze[X][Y]);
        }
    }
    refresh();
}

void showTime(time_t startTime, time_t playTime, int Xtxt, int Ytxt)
{
    mvprintw(Xtxt, Ytxt, "time: %.0lf sec", difftime(playTime, startTime));
    refresh();
}

int TestArrow(void)
{
    switch (getch())
    {
    case KEY_UP: return(UP);
    case KEY_LEFT: return(LEFT);
    case KEY_RIGHT: return(RIGHT);
    case KEY_DOWN: return(DOWN);
    }
    return 0;
}

void DrawXY(struct ScrnPosXY *PosXY)
{
    mvprintw (PosXY->ScrnY, PosXY->ScrnX, "%c", PosXY->Player);
    refresh();
}

int isAtExit(void)
{
    return (((PlayerPos.ScrnX > 64) && (PlayerPos.ScrnY > 18)) ? TRUE : FALSE);
}

int TestMove(struct ScrnPosXY *pPosXY, int Direction)
{
    switch (Direction)
    {
    case UP:
        return (Maze[pPosXY->ScrnX][pPosXY->ScrnY - 1] == ' ');
    case DOWN:
        return (Maze[pPosXY->ScrnX][pPosXY->ScrnY + 1] == ' ');
    case LEFT:
        return (Maze[pPosXY->ScrnX - 1][pPosXY->ScrnY] == ' ');
    case RIGHT:
        return (Maze[pPosXY->ScrnX + 1][pPosXY->ScrnY] == ' ');
    }
    return(-1);
}

void MoveXY(struct ScrnPosXY *pPosXY, int Direction)
{
    mvprintw(pPosXY->ScrnY, pPosXY->ScrnX, " ");
    Maze[pPosXY->ScrnX][pPosXY->ScrnY] = SPACE;
    switch (Direction)
    {
    case UP:
        if ((pPosXY->ScrnY > SCRNMINY) && TestMove(pPosXY, UP))
        {
            (pPosXY->ScrnY)--;
        }
        break;
    case DOWN:
        if ((pPosXY->ScrnY < SCRNMAXY) && TestMove(pPosXY, DOWN))
        {
            (pPosXY->ScrnY)++;
        }
        break;
    case RIGHT:
        if ((pPosXY->ScrnX < SCRNMAXX) && TestMove(pPosXY, RIGHT))
        {
            (pPosXY->ScrnX)++;
        }
        break;
    case LEFT:
        if ((pPosXY->ScrnX > SCRNMINX) && TestMove(pPosXY, LEFT))
        {
            (pPosXY->ScrnX)--;
        }
        break;
    }
    attron(A_BOLD);
    mvprintw(pPosXY->ScrnY, pPosXY->ScrnX, "%c", pPosXY->Player);
    attroff(A_BOLD);
    refresh();
    Maze[pPosXY->ScrnX][pPosXY->ScrnY] = pPosXY->Player;
}

void PlayerAction(void)
{
    switch (getch())
    {
    case KEY_UP: MoveXY(&PlayerPos, UP); break;
    case KEY_LEFT: MoveXY(&PlayerPos, LEFT); break;
    case KEY_RIGHT: MoveXY(&PlayerPos, RIGHT); break;
    case KEY_DOWN: MoveXY(&PlayerPos, DOWN); break;
    }
}

int StrategyAction(struct ScrnPosXY demon, int strategy)
{
    switch (strategy)
    {
    case 0:
        return (0);
    case 1:
        return (randomRange(4) + 1);
    case 2:
        if (demon.ScrnY < PlayerPos.ScrnY)
        {
            return (DOWN);
        }
        if (demon.ScrnY > PlayerPos.ScrnY)
        {
            return (UP);
        }
        break;
    case 3:
        if (demon.ScrnX < PlayerPos.ScrnX)
        {
            return (RIGHT);
        }
        if (demon.ScrnX > PlayerPos.ScrnX)
        {
            return (LEFT);
        }
    }
    return (0);
}

void DemonAction(struct ScrnPosXY *Demon)
{
    MoveXY(Demon, StrategyAction(*Demon, randomRange(5)));
}
