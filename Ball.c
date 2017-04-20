#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ScreenUtils.h"
#include "MathUtils.h"
#include "Ball.h"

struct CBall
{
    Imagen m_pImage;

    float m_fX, m_fY, m_fW, m_fH, m_fVX, m_fVY;

    int m_iType, m_iDestroying, m_iCollided;
};

CBall Ball_Load(int iBallType)
{
    CBall pBall = malloc(sizeof(struct CBall));
    if (!pBall)
        return NULL;

    char szBuf[64];
    sprintf(szBuf, "data//in_game//ball_%i.bmp", iBallType);

    pBall->m_fX = 0.f;
    pBall->m_fY = 0.f;
    pBall->m_fW = 0.025f;
    pBall->m_fH = 0.038f;
    pBall->m_fVX = 0.f;
    pBall->m_fVY = 0.f;
    pBall->m_iType = iBallType;
    pBall->m_iDestroying = 0;
    pBall->m_iCollided = 0;
    pBall->m_pImage = Pantalla_ImagenLee(szBuf, 255);

    return pBall;
}

Imagen Ball_GetImage(CBall pBall)
{
    if (!pBall)
        return NULL;

    return pBall->m_pImage;
}

void Ball_GetXY(CBall pBall, float* fX, float* fY)
{
    if (!pBall)
        return;

    *fX = pBall->m_fX;
    *fY = pBall->m_fY;
}

void Ball_SetXY(CBall pBall, float fX, float fY)
{
    if (!pBall)
        return;

    pBall->m_fX = fX;
    pBall->m_fY = fY;
}

void Ball_GetVXY(CBall pBall, float* fVX, float* fVY)
{
    if (!pBall)
        return;

    *fVX = pBall->m_fVX;
    *fVY = pBall->m_fVY;
}

void Ball_SetVXY(CBall pBall, float fVX, float fVY)
{
    if (!pBall)
        return;

    pBall->m_fVX = fVX;
    pBall->m_fVY = fVY;
}

void Ball_GetWH(CBall pBall, float* fW, float* fH)
{
    if (!pBall)
        return;

    *fW = pBall->m_fW;
    *fH = pBall->m_fH;
}

void Ball_SetWH(CBall pBall, float fW, float fH)
{
    if (!pBall)
        return;

    pBall->m_fW = fW;
    pBall->m_fH = fH;
}

void Ball_GetCenter(CBall pBall, float* fX, float* fY)
{
    if (!pBall)
        return;

    *fX = pBall->m_fX + (pBall->m_fW / 2.f);
    *fY = pBall->m_fY + (pBall->m_fH / 2.f);
}

void Ball_SetDestroying(CBall pBall, int iDestroyed)
{
    if (!pBall)
        return;

    pBall->m_iDestroying = iDestroyed;
}

void Ball_Free(CBall pBall)
{
    if (!pBall)
        return;

    printf("Ball %i destroyed\n", pBall->m_iType);

    Pantalla_ImagenLibera(pBall->m_pImage);
    if (pBall)
        free(pBall);
}

int Ball_GetType(CBall pBall)
{
    if (!pBall)
        return 0;

    return pBall->m_iType;
}

int Ball_IsDestroying(CBall pBall)
{
    if (!pBall)
        return 0;

    return pBall->m_iDestroying;
}

int Ball_IsCollided(CBall pBall)
{
    if (!pBall)
        return 0;

    return pBall->m_iCollided;
}

void Ball_ResetWH(CBall pBall)
{
    if (!pBall)
        return;

    pBall->m_fW = 0.025f;
    pBall->m_fH = 0.038f;
}

void Ball_SetCollisionState(CBall pBall, int iState)
{
    if (!pBall)
        return;

    pBall->m_iCollided = iState;
}

int Ball_CheckBounds(CBall pBall, CGame pGame)
{
    if (!pBall)
        return 0;

    float x1 = 0.09000f,
          y1 = 0.20381f,
          y2 = 0.82952f,
          x3 = 0.12437f,
          y3 = 0.14285f,
          x4 = 0.47687f,
          y4 = 0.88952f,
          x5 = 0.53125f,
          x6 = 0.88062f,
          x7 = 0.91500f;

    if (pBall->m_fY + pBall->m_fH >= y1 && pBall->m_fY <= y2 && pBall->m_fX <= x1)
    {
        pBall->m_fX = x1;
        pBall->m_fVX *= -1;
    }
    else if (pBall->m_fY + pBall->m_fH >= y1 && pBall->m_fY <= y2 && pBall->m_fX + pBall->m_fW >= x7)
    {
        pBall->m_fX = x7 - pBall->m_fW;
        pBall->m_fVX *= -1;
    }
    else if ((pBall->m_fX + pBall->m_fW >= x3 && pBall->m_fX <= x4) || (pBall->m_fX + pBall->m_fW >= x5 && pBall->m_fX <= x6))
    {
        if (pBall->m_fY <= y3)
        {
            pBall->m_fY = y3;
            pBall->m_fVY *= -1;
        }
        else if (pBall->m_fY + pBall->m_fH >= y4)
        {
            pBall->m_fY = y4 - pBall->m_fH;
            pBall->m_fVY *= -1;
        }
    }

    float fCenterX, fCenterY;

    Ball_GetCenter(pBall, &fCenterX, &fCenterY);

    for (unsigned int i = 0; i < 6; ++i)
    {
        float fCornerX, fCornerY, fCornerRadius;

        Game_GetCornerDataByIndex(pGame, i, &fCornerX, &fCornerY, &fCornerRadius);

        if (Maths_GetDistance(fCenterX, fCenterY, fCornerX, fCornerY) <= fCornerRadius)
        {
            Game_AddScore(pGame, 1, 1);
            return (pBall->m_iDestroying = 1);
        }
    }

    return 0;
}










