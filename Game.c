#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Pantalla.h"
#include "Game.h"
#include "Balls.h"
#include "Records.h"
#include "Bot.h"

#define GAME_MAX_IMAGES 1
#define GAME_CORNERS 6
#define GAME_CORNERS_DATA 3

#define X 0
#define Y 1
#define RADIUS 2

enum eImages
{
    TABLE
};

enum eCorners
{
    LEFT_UPPER,
    LEFT_BOTTOM,
    MIDDLE_UPPER,
    MIDDLE_BOTTOM,
    RIGHT_UPPER,
    RIGHT_BOTTOM
};


struct CGame
{
    Imagen m_pImages[GAME_MAX_IMAGES];

    float m_fCorners[GAME_CORNERS][GAME_CORNERS_DATA];

    CScreen m_pScreenUtils;
    CBallsContainer m_pBalls;
    CBot m_pBot;

    double m_dTableSX, m_dTableSY, m_dScreenSY;

    int m_iInitialized,
        m_iCanShoot,
        m_iIsShooting,
        m_iIsWBMoving, /// WHITE BALL MOVING
        m_iPlayerTurn,
        m_iScore,
        m_iScorePerShoot,
        m_iLastScore,
        m_iRenderedMsgs,
        m_iGameOver,
        m_iGameWon,
        m_iClosing,
        m_iBallsPlaced;
};

CGame Game_Load(CScreen pScreenUtils, int iAILevel)
{
    CGame pTempGame = malloc(sizeof(struct CGame));
    if (!pTempGame)
        return NULL;

    pTempGame->m_pScreenUtils = pScreenUtils;
    pTempGame->m_dTableSX = Screen_GetSX();
    pTempGame->m_dScreenSY = Screen_GetSY();
    pTempGame->m_dTableSY = 0;
    pTempGame->m_iInitialized = 0;
    pTempGame->m_iCanShoot = 1;
    pTempGame->m_iIsShooting = 0;
    pTempGame->m_iIsWBMoving = 0;
    pTempGame->m_iPlayerTurn = 1;
    pTempGame->m_iScore = 0;
    pTempGame->m_iScorePerShoot = 0;
    pTempGame->m_iLastScore = 0;
    pTempGame->m_iRenderedMsgs = 0;
    pTempGame->m_iGameOver = 0;
    pTempGame->m_iGameWon = 0;
    pTempGame->m_iClosing = 0;
    pTempGame->m_iBallsPlaced = 0;

    pTempGame->m_pBalls = Balls_Load();
    pTempGame->m_pBot = Bot_Load(iAILevel);

    pTempGame->m_fCorners[LEFT_UPPER][X] = 0.f;
    pTempGame->m_fCorners[LEFT_UPPER][Y] = 0.f;
    pTempGame->m_fCorners[LEFT_UPPER][RADIUS] = 0.215f;

    pTempGame->m_fCorners[LEFT_BOTTOM][X] = 0.f;
    pTempGame->m_fCorners[LEFT_BOTTOM][Y] = 1.f;
    pTempGame->m_fCorners[LEFT_BOTTOM][RADIUS] = 0.185f;

    pTempGame->m_fCorners[MIDDLE_UPPER][X] = 0.5018f;
    pTempGame->m_fCorners[MIDDLE_UPPER][Y] = 0.0019f;
    pTempGame->m_fCorners[MIDDLE_UPPER][RADIUS] = 0.165f;

    pTempGame->m_fCorners[MIDDLE_BOTTOM][X] = 0.5037f;
    pTempGame->m_fCorners[MIDDLE_BOTTOM][Y] = 0.998f;
    pTempGame->m_fCorners[MIDDLE_BOTTOM][RADIUS] = 0.13f;

    pTempGame->m_fCorners[RIGHT_UPPER][X] = 1.f;
    pTempGame->m_fCorners[RIGHT_UPPER][Y] = 0.f;
    pTempGame->m_fCorners[RIGHT_UPPER][RADIUS] = 0.215f;

    pTempGame->m_fCorners[RIGHT_BOTTOM][X] = 1.f;
    pTempGame->m_fCorners[RIGHT_BOTTOM][Y] = 1.f;
    pTempGame->m_fCorners[RIGHT_BOTTOM][RADIUS] = 0.188f;

    pTempGame->m_pImages[TABLE] = Pantalla_ImagenLee("data//in_game//table.bmp", 255);

    Balls_Init(pTempGame->m_pBalls);

    return pTempGame;
}

void Game_Free(CGame pGame)
{
    for (unsigned int i = 0; i < GAME_MAX_IMAGES; ++i)
        Pantalla_ImagenLibera(pGame->m_pImages[i]);

    Balls_Free(pGame->m_pBalls);
    Bot_Free(pGame->m_pBot);

    if (pGame)
        free(pGame);
}

void Game_GetCornerDataByIndex(CGame pGame, int iIndex, float* fX, float* fY, float* fRadius)
{
    if (iIndex < LEFT_UPPER || iIndex > RIGHT_BOTTOM)
        return;

    *fX = pGame->m_fCorners[iIndex][X];
    *fY = pGame->m_fCorners[iIndex][Y];
    *fRadius = pGame->m_fCorners[iIndex][RADIUS];
}

void Game_AddScore(CGame pGame, int iType, int iScore)
{
    if (pGame->m_iPlayerTurn == 1)
    {
        if (iType == 0)
            pGame->m_iScore += iScore;
        else
            pGame->m_iScorePerShoot += iScore;
    }
    pGame->m_iLastScore += iScore;
}

void Game_DrawMsg(CGame pGame, char* szMsg, int r, int g, int b)
{
    if (!pGame->m_iPlayerTurn)
        Pantalla_ColorTrazo(255, 0, 0, 255);
    else
        Pantalla_ColorTrazo(r, g, b, 255);

    Pantalla_DibujaTexto(szMsg, Screen_ConvertX(0.42), Screen_ConvertY(0.30 + (pGame->m_iRenderedMsgs * 0.025)));

    ++pGame->m_iRenderedMsgs;
}

void Game_DrawTurn(CGame pGame)
{
    char* szBuf = (char*)malloc(32);

    sprintf(szBuf, "Turno: %s", pGame->m_iPlayerTurn ? "Tuyo" : "IA");

    Pantalla_ColorTrazo(0, 0, 255, 255);
    Pantalla_DibujaTexto(szBuf, Screen_ConvertX(0.35), Screen_ConvertY(0.01));

    free(szBuf);
}

void Game_SaveRecord(CGame pGame)
{
    if (pGame->m_iScore <= 0)
        return;

    if (!Records_Save(pGame->m_iScore))
        printf("No se pudo guardar el record actual!\n");
}

void Game_GameOver(CGame pGame)
{
    pGame->m_iGameOver = 1;
    Game_SaveRecord(pGame);
}

void Game_WinGame(CGame pGame)
{
    pGame->m_iGameWon = 1;
    Game_SaveRecord(pGame);
}

void Game_StartClosing(CGame pGame)
{
    pGame->m_iClosing = 1;
}

void Game_ToggleTurn(CGame pGame)
{
    pGame->m_iPlayerTurn = !pGame->m_iPlayerTurn;
    pGame->m_iIsShooting = 0;
}

void Game_DrawScore(int iScore)
{
    char* szBuf = (char*)malloc(32);

    sprintf(szBuf, "Puntos: %i", iScore);

    Pantalla_ColorTrazo(0, 0, 0, 255);
    Pantalla_DibujaTexto(szBuf, Screen_ConvertX(0.479), Screen_ConvertY(0.01));

    free(szBuf);
}

void Game_DrawWinner()
{
    Pantalla_ColorTrazo(255, 0, 255, 255);
    Pantalla_DibujaTexto("HAS GANADO!", Screen_ConvertX(0.48), Screen_ConvertY(0.5));
}

void Game_DrawLoser()
{
    Pantalla_ColorTrazo(255, 0, 0, 255);
    Pantalla_DibujaTexto("HAS PERDIDO!", Screen_ConvertX(0.48), Screen_ConvertY(0.5));
}

void Game_RenderWinner(CGame pGame)
{
    if (pGame->m_iPlayerTurn)
    {
        if (pGame->m_iGameOver)
            Game_DrawLoser();
        else
            Game_DrawWinner();
    }
    else
    {
        if (pGame->m_iGameOver)
            Game_DrawWinner();
        else
            Game_DrawLoser();
    }
}

int Game_ShootWhiteBall(CGame pGame)
{
    static double dToMouseX, dToMouseY, fDrawMouseX, fDrawMouseY;
    static CBall pWhiteBall = NULL;
    static float fCenterX, fCenterY;

    int iResult = 0;

    pWhiteBall = Balls_GetBallByType(pGame->m_pBalls, 0);

    if (pGame->m_iPlayerTurn == 0)
    {
        Ball_GetCenter(pWhiteBall, &fCenterX, &fCenterY);
        Pantalla_DibujaTexto("Controlada por IA", Screen_ConvertX(fCenterX - 0.05), Screen_ConvertY(fCenterY - 0.0325));
    }

    if (pWhiteBall && pGame->m_iCanShoot)
    {
        if (pGame->m_iPlayerTurn)
        {
            if (Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT) && !pGame->m_iIsShooting)
            {
                Ball_GetCenter(pWhiteBall, &fCenterX, &fCenterY);
                pGame->m_iIsShooting = 1;
            }
            else if (!Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT) && pGame->m_iIsShooting)
            {
                Pantalla_RatonCoordenadas(&dToMouseX, &dToMouseY);

                Ball_SetVXY(pWhiteBall, ((float)dToMouseX / Screen_GetSX() - fCenterX) * 0.05f, ((float)dToMouseY / Screen_GetSY() - fCenterY) * 0.05f);

                pGame->m_iCanShoot = pGame->m_iIsShooting = 0;
                pGame->m_iIsWBMoving = iResult = 1;
            }

            if (pGame->m_iIsShooting)
            {
                Pantalla_RatonCoordenadas(&fDrawMouseX, &fDrawMouseY);

                Pantalla_ColorTrazo(0, 0, 255, 255);
                Pantalla_DibujaLinea(Screen_ConvertX((double)fCenterX), Screen_ConvertY((double)fCenterY), fDrawMouseX, fDrawMouseY);
            }
        }
        else
        {
            if (!pGame->m_iIsShooting && Pantalla_RatonBotonPulsado(SDL_BUTTON_RIGHT))
            {
                Ball_GetCenter(pWhiteBall, &fCenterX, &fCenterY);

                CBall pClosestBall = Balls_GetClosestBall(pGame->m_pBalls, fCenterX, fCenterY, 1);
                if (pClosestBall)
                {
                    float fBallPosX, fBallPosY;

                    Ball_GetCenter(pClosestBall, &fBallPosX, &fBallPosY);

                    pGame->m_iIsShooting = iResult = pGame->m_iIsWBMoving = 1;
                    pGame->m_iCanShoot = 0;
                    Bot_Launch(pWhiteBall, pGame->m_pBot, ((float)fBallPosX - fCenterX) * 0.05f, ((float)fBallPosY - fCenterY) * 0.05f);
                }
            }
        }
    }

    return iResult;
}

int Game_CanShoot(CGame pGame)
{
    return pGame->m_iCanShoot;
}

int Game_IsGameOver(CGame pGame)
{
    return pGame->m_iGameOver;
}

int Game_IsClosing(CGame pGame)
{
    return pGame->m_iClosing;
}

int Game_GetTurn(CGame pGame)
{
    return pGame->m_iPlayerTurn;
}

int Game_GetScore(CGame pGame, int iType)
{
    if (iType == 0)
        return pGame->m_iScore;

    return pGame->m_iScorePerShoot;
}

int Game_Render(CGame pGame)
{
    Pantalla_DibujaImagen(pGame->m_pImages[TABLE], 0.0, 0.0, pGame->m_dTableSX, pGame->m_dTableSY);

    static int iTutorial = 1;

    if (pGame->m_iInitialized)
    {
        int iUpdateResult = Balls_UpdateAndDraw(pGame->m_pBalls, pGame);

        if (!pGame->m_iGameOver && iUpdateResult == 0)
        {
            pGame->m_iScorePerShoot = 0;
            pGame->m_iCanShoot = 1;
        }
        else
        {
            Pantalla_ColorTrazo(255, 0, 0, 255);
            Pantalla_DibujaTexto("Espera a que todas las bolas paren", Screen_ConvertX(0.6), Screen_ConvertY(0.01));
        }

        if (Balls_AreStopped(pGame->m_pBalls) && pGame->m_iIsWBMoving && iUpdateResult != 2)
        {
            pGame->m_iIsWBMoving = 0;
            pGame->m_iIsShooting = 0;

            if (pGame->m_iLastScore <= 0)
            {
                Game_ToggleTurn(pGame);
            }
            else
                pGame->m_iLastScore = 0;

            pGame->m_iScorePerShoot = 0;
        }
        else if (iUpdateResult == 2)
        {
            pGame->m_iScorePerShoot = 0;
            pGame->m_iCanShoot = 1;
            pGame->m_iIsShooting = 0;

            Game_ToggleTurn(pGame);
        }

        Game_DrawTurn(pGame);
        Game_DrawScore(pGame->m_iScore);

        if (Game_ShootWhiteBall(pGame) && iTutorial)
            iTutorial = 0;
        if (iTutorial)
        {
            Pantalla_ColorTrazo(255, 0, 0, 255);
            Pantalla_DibujaTexto("*Instrucciones*", Screen_ConvertX(0.46), Screen_ConvertY(0.18));
            Pantalla_DibujaTexto("Haz click en la bola blanca", Screen_ConvertX(0.43), Screen_ConvertY(0.22));
            Pantalla_DibujaTexto("arrastra el final de la linea", Screen_ConvertX(0.43), Screen_ConvertY(0.24));
            Pantalla_DibujaTexto("hasta donde quieras disparar y", Screen_ConvertX(0.43), Screen_ConvertY(0.26));
            Pantalla_DibujaTexto("suelta el click. Pulsa el boton", Screen_ConvertX(0.43), Screen_ConvertY(0.28));
            Pantalla_DibujaTexto("derecho del raton para lanzar la", Screen_ConvertX(0.43), Screen_ConvertY(0.3));
            Pantalla_DibujaTexto("pelota en el turno de la IA", Screen_ConvertX(0.43), Screen_ConvertY(0.32));
            Pantalla_DibujaTexto("Pulsa ESCAPE para volver al menu", Screen_ConvertX(0.43), Screen_ConvertY(0.34));
        }

        pGame->m_iRenderedMsgs = 0;

        if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE))
        {
            Pantalla_ColorTrazo(0, 0, 255, 255);
            Pantalla_DibujaTexto("SALIENDO AL MENU...", Screen_ConvertX(0.46), Screen_ConvertY(0.4));
            Game_SaveRecord(pGame);

            return 1;
        }
    }
    else
    {
        pGame->m_dTableSY += Screen_Sync(pGame->m_pScreenUtils, 1500.f);
        if (pGame->m_dTableSY >= pGame->m_dScreenSY)
            pGame->m_iInitialized = 1;
    }

    if (pGame->m_iGameWon || pGame->m_iGameOver)
    {
        Game_RenderWinner(pGame);
        return 1;
    }

    return 0;
}
