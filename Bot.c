#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bot.h"
#include "Ball.h"
#include "MathUtils.h"

struct CBot
{
    float m_fPushVelocity;
};

CBot Bot_Load(int iLevel)
{
    CBot pTempBot = malloc(sizeof(struct CBot));
    if (!pTempBot)
        return NULL;

    pTempBot->m_fPushVelocity = (float)iLevel * 0.01f;

    return pTempBot;
}

void Bot_Free(CBot pBot)
{
    free(pBot);
}

void Bot_Launch(CBall pBall, CBot pBot, float fDirX, float fDirY)
{
    Maths_VectorNormalize(&fDirX, &fDirY);

    fDirX *= pBot->m_fPushVelocity;
    fDirY *= pBot->m_fPushVelocity;

    Ball_SetVXY(pBall, fDirX, fDirY);
}
