#include "library.h"

int main()
{

    srand(time(0));
    initFigures();
    initConsole();

    writeText("PRESS ENTER TO START THE GAME", 2, 40);
    while (getch() != VK_RETURN) {}
    writeText("                             ", 2, 40);

    START:
    initMap(cEmpty);
    drawMap();
    int figureY = -1, figureX = 10, movingHorizontal, isSpacePressed = 0;
    struct Figure fig = figures[getRandom(0, 4)];
    drawScore(playerScore);
    while (1)
    {
        int isObstacle = 0;
        if (figureY + fig.h == mapH)
        {
            isObstacle = 1;
        } else
        {
            int x;
            for (x = 0; x < fig.w; x++)
            {
                int pos = fig.h - 1;
                while (fig.pix[pos][x] == 0)
                    pos--;
                if (map[figureY + pos + 1][figureX + x] != cEmpty)
                {
                    isObstacle = 1;
                    break;
                }
            }
        }
        if (isObstacle)
        {
            figureY = 0;
            figureX = getRandom(0, mapW - 5);
            fig = figures[getRandom(0, 4)];
            if (!canPut(&fig, figureY, figureX))
            {
                writeText("GAME OVER! PRESS C TO CONTINUE", 2, 45);
                while (getch() != 'c') {}
                writeText("                              ", 2, 45);
                goto START;
            }
            srand(time(0));
        } else
        {
            drawFigure(&fig, figureY, figureX, cEmpty);
            if (!movingHorizontal)
                figureY++;
        }
        if (GetKeyState(VK_UP) >= 0)
        {
            if (isSpacePressed && figureY + maximum(fig.w, fig.h) < mapH && figureX + maximum(fig.w, fig.h) < mapW)
            {
                isSpacePressed = 0;
                rotateFigure(&fig);
            }
        }
        movingHorizontal = 0;
        if(GetKeyState(VK_LEFT) < 0)
        {
            int isObstacle = 0, y;
            for (y = 0; y < fig.h; y++)
            {
                int pos = 0;
                while (fig.pix[y][pos] == 0)
                    pos++;
                if (map[figureY + y][figureX + pos - 1] != cEmpty)
                {
                    isObstacle = 1;
                    break;
                }
            }
            if (figureX > 0 && !isObstacle)
            {
                movingHorizontal = 1;
                figureX--;
            }
        }
        if (GetKeyState(VK_RIGHT) < 0)
        {
            int isObstacle = 0, y;
            for (y = 0; y < fig.h; y++)
            {
                int pos = fig.w - 1;
                while (fig.pix[y][pos] == 0)
                    pos--;
                if (map[figureY + y][figureX + pos + 1] != cEmpty)
                {
                    isObstacle = 1;
                    break;
                }
            }
            if (figureX + fig.w < mapW && !isObstacle)
            {
                movingHorizontal = 1;
                figureX++;
            }
        }
        if (GetKeyState(VK_UP) < 0)
        {
            isSpacePressed = 1;
        }
        drawFigure(&fig, figureY, figureX, cBlock);
        drawMap();
        if (GetKeyState(VK_DOWN) < 0)
            Sleep(80);
        else
            Sleep(190);

        int fl;
        while ((fl = getFullLine()) != -1)
        {
            delLine(fl);
            increaseScore(mapW*5);
            drawFigure(&fig, figureY, figureX, cBlock);
            drawMap();
            drawScore(playerScore);
            Sleep(50);
        }
    }
    return 0;
}
