#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define cBlock '#'
#define cEmpty '-'
//size of game map
#define mapW 20
#define mapH 20
//the position of the left top corner of the map on the screen
#define mapX 50
#define mapY 3
char mapBuffer[mapH][mapW], map[mapH][mapW];
/*
    mapBuffer - previous map image
    map - map image now
*/

struct Figure
{
    int w, h;
    int pix[4][4];
};
struct Figure figures[5];
int playerScore;

HANDLE h;
void initConsole(void);
void setCursor(int y, int x);
void setChar(char t, int y, int x);
int getRandom(int lower, int upper);//from [lower, upper]
int maximum(int a, int b);

void initFigures();
void drawMap();
void initMap(char t);
void drawFigure(struct Figure *f, int y, int x, char c);
void rotateFigure(struct Figure *f);//90^ right
int getFullLine();//returns 1 if last line is full, else returns 0
void delLastLine();//deletes last line and shifts some elements down
void increaseScore(int x);
void drawScore(int score);
void writeText(char *text, int y, int x);
int canPut(struct Figure *f, int fy, int fx);


#endif // LIBRARY_H_INCLUDED
