#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ScreenUtils.h"
#include "MathUtils.h"
#include "Balls.h"
#include "Ball.h"
#include "Game.h"

#define GAME_MAX_BALLS 16

enum eBallImages
{
    BALL_WHITE,     /// 0
    BALL_1,
    BALL_2,
    BALL_3,
    BALL_4,
    BALL_5,
    BALL_6,
    BALL_7,
    BALL_8,
    BALL_9,
    BALL_10,
    BALL_11,
    BALL_12,
    BALL_13,
    BALL_14,
    BALL_15
};

struct CBallContainer
{
    CBall m_pElement;
    CBallContainer m_pNext;
};

struct CBallsContainer
{
    CBallContainer m_pFirst;
    int m_iNum;
};

CBallsContainer Balls_Load()
{
    CBallsContainer pBalls = malloc(sizeof(struct CBallsContainer));
    if (!pBalls)
        return NULL;

    pBalls->m_iNum = 0;
    pBalls->m_pFirst = NULL;

    for (unsigned int i = 0; i < GAME_MAX_BALLS; ++i)
        Balls_Insert(pBalls, Ball_Load(i));

    return pBalls;
}

CBall Balls_GetClosestBall(CBallsContainer pBalls, float fPosX, float fPosY, int iIgnore8Ball)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst->m_pNext;

    CBall pTempBall = NULL;
    float fCenterX, fCenterY, fDist = 9999.f;

    while (pCurrentContainer)
    {
        if (iIgnore8Ball && Ball_GetType(pCurrentContainer->m_pElement) == 8 && pBalls->m_iNum > 2)
        {
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        }

        Ball_GetCenter(pCurrentContainer->m_pElement, &fCenterX, &fCenterY);

        float fActualDist = Maths_GetDistance(Screen_ConvertX((double)fPosX), Screen_ConvertY((double)fPosY), Screen_ConvertX((double)fCenterX), Screen_ConvertY((double)fCenterY));

        if (fActualDist < fDist)
        {
            fDist = fActualDist;
            pTempBall = pCurrentContainer->m_pElement;
        }

        pCurrentContainer = pCurrentContainer->m_pNext;
    }

    return pTempBall;
}

CBall Balls_GetBallByType(CBallsContainer pBalls, int iType)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    while (pCurrentContainer)
    {
        if (Ball_GetType(pCurrentContainer->m_pElement) != 0)
        {
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        }

        return pCurrentContainer->m_pElement;
    }

    return NULL;
}

void Balls_Free(CBallsContainer pBalls)
{
    Balls_Remove(pBalls, NULL, 1);
    if (pBalls)
        free(pBalls);
}

void Balls_Init(CBallsContainer pBalls)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    float x = 0.57, y = 0.5, sx = 0.033, sy = 0.035;

    float fX1 = x,
          fX2 = x + sx,
          fX3 = x + sx * 2,
          fX4 = x + sx * 3,
          fX5 = x + sx * 4,
          fY1 = y - sy * 4,
          fY2 = y - sy * 3,
          fY3 = y - sy * 2,
          fY4 = y - sy,
          fY5 = y,
          fY6 = y + sy,
          fY7 = y + sy * 2,
          fY8 = y + sy * 3,
          fY9 = y + sy * 4;

    while (pCurrentContainer)
    {
        switch(Ball_GetType(pCurrentContainer->m_pElement))
        {
        case BALL_WHITE:
            Ball_SetXY(pCurrentContainer->m_pElement, 0.25f, 0.5f);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_1:
            Ball_SetXY(pCurrentContainer->m_pElement, fX5, fY1);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_2:
            Ball_SetXY(pCurrentContainer->m_pElement, fX5, fY3);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_3:
            Ball_SetXY(pCurrentContainer->m_pElement, fX5, fY5);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
       case BALL_4:
            Ball_SetXY(pCurrentContainer->m_pElement, fX5, fY7);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_5:
            Ball_SetXY(pCurrentContainer->m_pElement, fX5, fY9);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_6:
            Ball_SetXY(pCurrentContainer->m_pElement, fX4, fY2);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_7:
            Ball_SetXY(pCurrentContainer->m_pElement, fX4, fY4);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_8:
            Ball_SetXY(pCurrentContainer->m_pElement, fX4, fY6);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_9:
            Ball_SetXY(pCurrentContainer->m_pElement, fX4, fY8);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_10:
            Ball_SetXY(pCurrentContainer->m_pElement, fX3, fY3);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_11:
            Ball_SetXY(pCurrentContainer->m_pElement, fX3, fY5);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_12:
            Ball_SetXY(pCurrentContainer->m_pElement, fX3, fY7);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_13:
            Ball_SetXY(pCurrentContainer->m_pElement, fX2, fY4);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_14:
            Ball_SetXY(pCurrentContainer->m_pElement, fX2, fY6);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        case BALL_15:
            Ball_SetXY(pCurrentContainer->m_pElement, fX1, fY5);
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;

        default:
            pCurrentContainer = pCurrentContainer->m_pNext;
            continue;
        }
    }
}

void Balls_Remove(CBallsContainer pBalls, CBall pBall, int iRemoveAll)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    if (iRemoveAll == 1)
    {
        while (pCurrentContainer)
        {
            Ball_Free(pCurrentContainer->m_pElement);
            pCurrentContainer = pCurrentContainer->m_pNext;
            --pBalls->m_iNum;
        }

        free(pBalls->m_pFirst);
    }
    else
    {
        while (pCurrentContainer)
        {
            if (pCurrentContainer->m_pNext && pCurrentContainer->m_pNext->m_pElement == pBall)
            {
                CBallContainer pTempContainer = pCurrentContainer->m_pNext;
                pCurrentContainer->m_pNext = pCurrentContainer->m_pNext->m_pNext;

                Ball_Free(pTempContainer->m_pElement);
                free(pTempContainer);

                --pBalls->m_iNum;

                return;
            }

            pCurrentContainer = pCurrentContainer->m_pNext;
        }
    }
}

void Balls_Insert(CBallsContainer pBalls, CBall pBall)
{
    if (!pBalls->m_pFirst)
    {
        pBalls->m_pFirst = malloc(sizeof(struct CBallContainer));
        pBalls->m_pFirst->m_pElement = pBall;
        pBalls->m_pFirst->m_pNext = NULL;

        ++pBalls->m_iNum;

        return;
    }

    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    while (pCurrentContainer)
    {
        if (!pCurrentContainer->m_pNext)
        {
            pCurrentContainer->m_pNext = malloc(sizeof(struct CBallContainer));
            pCurrentContainer->m_pNext->m_pElement = pBall;
            pCurrentContainer->m_pNext->m_pNext = NULL;

            ++pBalls->m_iNum;

            return;
        }

        pCurrentContainer = pCurrentContainer->m_pNext;
    }
}

void Balls_ResetCols(CBallsContainer pBalls)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    while (pCurrentContainer)
    {
        Ball_SetCollisionState(pCurrentContainer->m_pElement, 0);
        pCurrentContainer = pCurrentContainer->m_pNext;
    }
}

void Balls_CheckCollisions(CBallsContainer pBalls)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    float fCenter1X, fCenter1Y, fCenter2X, fCenter2Y;

    while (pCurrentContainer)
    {
        CBallContainer pCurrentContainer_2 = pBalls->m_pFirst;

        Ball_GetCenter(pCurrentContainer->m_pElement, &fCenter1X, &fCenter1Y);

        while (pCurrentContainer_2)
        {
            CBall pBall_1 = pCurrentContainer->m_pElement;
            CBall pBall_2 = pCurrentContainer_2->m_pElement;

            if (pBall_1 == pBall_2)
            {
                pCurrentContainer_2 = pCurrentContainer_2->m_pNext;
                continue;
            }

            Ball_GetCenter(pBall_1, &fCenter1X, &fCenter1Y);
            Ball_GetCenter(pBall_2, &fCenter2X, &fCenter2Y);

            if (fabs(fCenter1X - fCenter2X) < 0.024483f &&
                fabs(fCenter1Y - fCenter2Y) < 0.035278f &&
                Ball_IsCollided(pBall_1) == 0 &&
                !Ball_IsDestroying(pBall_1) &&
                !Ball_IsDestroying(pBall_2))
            {
                float fVX, fVY, fVX2, fVY2, fDirX, fDirY;

                Ball_GetVXY(pBall_1, &fVX, &fVY);
                Ball_GetVXY(pBall_2, &fVX2, &fVY2);

                fDirX = fCenter2X - fCenter1X;
                fDirY = fCenter2Y - fCenter1Y;

                float x1 = fDirX, y1 = fDirY;
                float angle = Maths_AngleBetweenVectors(0.5f, 0.5f, 1.f, 0.5f, fCenter2X, fCenter2Y, fCenter2X - x1, fCenter2Y - y1);

                fDirX = fCenter2X - (fCenter2X + x1 * 0.025f);
                fDirY = fCenter2Y - (fCenter2Y + y1 * 0.038f);

                float vel = Maths_VectorModule(fVX, fVY);
                if (vel <= 0.f)
                {
                    Ball_GetVXY(pBall_2, &fVX, &fVY);
                    vel = Maths_VectorModule(fVX, fVY);
                }

                Maths_VectorNormalize(&x1, &y1);

                float fFinalX1 = x1 * vel, fFinalY1 = y1 * vel;
                float fFinalX2 = vel * cos(angle), fFinalY2 = vel * sin(angle);

                float fFinalV1 = vel;
                float fFinalV2 = Maths_VectorModule(fVX2, fVY2);

                if (fFinalV1 < fFinalV2)
                {
                    fFinalX2 *= 1.35;
                    fFinalY2 *= 1.35;
                }
                else
                {
                    fFinalX1 *= 0.7;
                    fFinalY1 *= 0.7;
                }

                Ball_SetVXY(pBall_2, fFinalX1, fFinalY1);
                Ball_SetVXY(pBall_1, fFinalX2,
                                     fFinalY2);

                Ball_SetCollisionState(pBall_1, 1);
            }

            pCurrentContainer_2 = pCurrentContainer_2->m_pNext;
        }

        pCurrentContainer = pCurrentContainer->m_pNext;
    }

    Balls_ResetCols(pBalls);
}

int Balls_UpdateAndDraw(CBallsContainer pBalls, CGame pGame)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    int iResult = 0;

    Balls_CheckCollisions(pBalls);

    float fScreenW = (float)Screen_GetSX();
    float fScreenH = (float)Screen_GetSY();

    while (pCurrentContainer)
    {
        float fX, fY, fW, fH, fVX, fVY;

        CBall pBall = pCurrentContainer->m_pElement;

        Ball_GetXY(pBall, &fX, &fY);
        Ball_GetVXY(pBall, &fVX, &fVY);

        int iBallType = Ball_GetType(pBall);
        int iRemoved = 0;

        if (Ball_IsDestroying(pBall) == 1)
        {
            Ball_GetWH(pBall, &fW, &fH);

            int iComboScore = Game_GetScore(pGame, 1);
            int iGameWon = pBalls->m_iNum <= 2;

            if (fW <= 0.f && fH <= 0.f)
            {
                if (iBallType == 0)
                {
                    if (Game_CanShoot(pGame))
                    {
                        Ball_SetVXY(pBall, 0.f, 0.f);
                        Ball_SetXY(pBall, 0.25f, 0.5f);
                        Ball_ResetWH(pBall);
                        Ball_SetDestroying(pBall, 0);

                        iResult = 2;
                    }
                }
                else
                {
                    if (iBallType == 8)
                    {
                        if (iGameWon)
                            Game_WinGame(pGame);
                        else
                            Game_GameOver(pGame);
                    }
                    else
                        Game_AddScore(pGame, 0, iBallType * iComboScore);

                    Ball_SetXY(pBall, -1.f, -1.f);
                    Ball_SetDestroying(pBall, 2);
                    Balls_Remove(pBalls, pBall, 0);

                    iResult = 4;

                    iRemoved = 1;
                }
            }
            else
            {
                Ball_SetXY(pBall, fX + 0.15f / fScreenW, fY + 0.15f / fScreenH);
                Ball_SetWH(pBall, fW - 0.3f / fScreenW, fH - 0.3f / fScreenH);

                if (iBallType == 8)
                {
                    if (iGameWon)
                        Game_DrawMsg(pGame, "BOLA 8 DENTRO!", 0, 0, 255);
                    else
                        Game_DrawMsg(pGame, "BOLA 8 DENTRO!", 255, 0, 0);

                    Game_StartClosing(pGame);
                }

                if (!Game_IsClosing(pGame))
                {
                    if (iBallType == 0)
                        Game_DrawMsg(pGame, "BOLA BLANCA DENTRO! (CAMBIO DE TURNO)", 255, 0, 0);
                    else
                    {
                        char szBuf[64] = { 0 };
                        if (iComboScore <= 1)
                        {
                            if (Game_GetTurn(pGame))
                                sprintf(szBuf, "BOLA %i DENTRO! (+%i PUNTOS)", iBallType, iBallType);
                            else
                                sprintf(szBuf, "BOLA %i DENTRO POR LA IA", iBallType, iBallType);
                        }
                        else
                            sprintf(szBuf, "BOLA %i DENTRO! (+%i x %i COMBO PUNTOS)", iBallType, iBallType, iComboScore);

                        Game_DrawMsg(pGame, szBuf, 0, 0, 255);
                    }
                }
            }
        }
        else
        {
            Ball_GetXY(pBall, &fX, &fY);
            Ball_GetVXY(pBall, &fVX, &fVY);

            fVX = Maths_Interpolate(fVX, 0.f, 0.01f);
            fVY = Maths_Interpolate(fVY, 0.f, 0.01f);

            if (fabs(fVX) <= 0.00018f && fabs(fVY) <= 0.00018f)
                fVX = fVY = 0.f;
            else
                iResult = 1;

            Ball_SetXY(pCurrentContainer->m_pElement, fX + fVX, fY + fVY);
            Ball_SetVXY(pCurrentContainer->m_pElement, fVX, fVY);

            Ball_CheckBounds(pCurrentContainer->m_pElement, pGame);
        }

        if (!iRemoved)
        {
            if (iBallType >= 0 && iBallType <= 15)
            {
                Ball_GetXY(pCurrentContainer->m_pElement, &fX, &fY);
                Ball_GetWH(pCurrentContainer->m_pElement, &fW, &fH);

                Pantalla_DibujaImagen(Ball_GetImage(pCurrentContainer->m_pElement),
                                      Screen_ConvertX((double)fX),
                                      Screen_ConvertY((double)fY),
                                      Screen_ConvertX((double)fW),
                                      Screen_ConvertY((double)fH));
            }
        }

        pCurrentContainer = pCurrentContainer->m_pNext;
    }

    return iResult;
}

int Balls_AreStopped(CBallsContainer pBalls)
{
    CBallContainer pCurrentContainer = pBalls->m_pFirst;

    int iResult = 1;

    while (pCurrentContainer)
    {
        float fVX, fVY;

        Ball_GetVXY(pCurrentContainer->m_pElement, &fVX, &fVY);

        if (fabs(fVX) > 0.00018f || fabs(fVY) > 0.00018f)
            iResult = 0;

        pCurrentContainer = pCurrentContainer->m_pNext;
    }

    return iResult;
}





