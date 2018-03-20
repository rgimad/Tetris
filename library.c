#include "library.h"
void initConsole(void)
{
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible = 0;
    CCI.dwSize = 1;
    SetConsoleCursorInfo(h, &CCI);
}

void setCursor(int y, int x)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

void setChar(char t, int y, int x)
{
    setCursor(y, x);
    printf("%c", t);
}

int getRandom(int lower, int upper)
{
    return rand()%(upper + 1 - lower) + lower;
}

int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

void initFigures()
{
    figures[0].w = 2;
    figures[0].h = 2;
    figures[0].pix[0][0] = 1;
    figures[0].pix[0][1] = 1;
    figures[0].pix[1][0] = 1;
    figures[0].pix[1][1] = 1;

    figures[1].w = 1;
    figures[1].h = 4;
    figures[1].pix[0][0] = 1;
    figures[1].pix[1][0] = 1;
    figures[1].pix[2][0] = 1;
    figures[1].pix[3][0] = 1;

    figures[2].w = 3;
    figures[2].h = 2;
    figures[2].pix[0][0] = 1;
    figures[2].pix[0][1] = 1;
    figures[2].pix[1][1] = 1;
    figures[2].pix[1][2] = 1;

    figures[3].w = 3;
    figures[3].h = 2;
    figures[3].pix[0][2] = 1;
    figures[3].pix[1][0] = 1;
    figures[3].pix[1][1] = 1;
    figures[3].pix[1][2] = 1;

    figures[4].w = 3;
    figures[4].h = 2;
    figures[4].pix[0][0] = 1;
    figures[4].pix[1][0] = 1;
    figures[4].pix[1][1] = 1;
    figures[4].pix[1][2] = 1;
}

void drawMap()
{
    int y, x;
    for (y = 0; y < mapH; y++)
        for (x = 0; x < mapW; x++)
            if (mapBuffer[y][x] != map[y][x])
            {
                mapBuffer[y][x] = map[y][x];
                setChar(map[y][x], y + mapY, x + mapX);
            }
}

void initMap(char t)
{
    int x, y;
    for (y = 0; y < mapH; y++)
        for (x = 0; x < mapW; x++)
        {
            mapBuffer[y][x] = '&';
            map[y][x] = t;
        }
    playerScore = 0;
}

void drawFigure(struct Figure *f, int y, int x, char c)
{
    int i, j;
    for (i = 0; i < f->h; i++)
        for (j = 0; j < f->w; j++)
            if (f->pix[i][j])
                map[y + i][x + j] = c;
}

void rotateFigure(struct Figure *f)
{
    int b[4][4], t, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            b[i][j] = 0;
    for (i = 0; i < f->h; i++)
        for (j = 0; j < f->w; j++)
            b[j][f->h - 1 - i] = f->pix[i][j];
    t = f->w;
    f->w = f->h;
    f->h = t;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            f->pix[i][j] = b[i][j];
}

int getFullLine()
{
    int y;
    for (y = mapH - 1; y >= 0; y--)
    {
        int isFull = 1, x;
        for (x = 0; x < mapW; x++)
        {
            if (map[y][x] != cBlock)
            {
                isFull = 0;
                break;
            }
        }
        if (isFull)
        {
            return y;
        }
    }
    return -1;
}

void delLine(int lineY)
{
    int x, y;
    for (x = 0; x < mapW; x++)
    {
        for (y = lineY; y > 0; y--)
        {
            map[y][x] = map[y - 1][x];
        }
    }
}

void increaseScore(int x)
{
    playerScore += x;
}

void writeText(char *text, int y, int x)
{
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        setChar(text[i], y, x + i);
    }
}

void drawScore(int score)
{
    char s[6], s2[6];
    if (score == 0)
    {
        strcpy(s2, "0");
    } else {
        int t = score, pos = 0;
        while (t > 0)
        {
            int d = t % 10;
            t /= 10;
            s[pos++] = d + '0';
        }
        s[pos] = '\0';
        int i;
        for (i = pos; i >= 0; i--)
        {
            s2[pos - 1 - i] = s[i];
        }
    }
    char resText[100] = "SCORE: ";
    strcat(resText, s2);
    strcat(resText, "   ");
    writeText(resText, 10, 80);
}

int canPut(struct Figure *f, int fy, int fx)
{
    int y, x, res = 1;
    for (y = fy; y < fy + f->h; y++)
    {
        for (x = fx; x < fx + f->w; x++)
        {
            if (map[y][x] != cEmpty)
            {
                res = 0;
                break;
            }
        }
    }
    return res;
}

