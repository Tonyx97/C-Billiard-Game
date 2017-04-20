#include <stdio.h>
#include <stdlib.h>

#include "Pantalla.h"
#include "ScreenUtils.h"

enum eFPS
{
    LOW,
    MEDIUM,
    HIGH
};

struct CScreenUtils
{
    int m_iMaxFPS;
};

CScreen Screen_Load()
{
    CScreen pTempScreen = malloc(sizeof(struct CScreenUtils));
    if (!pTempScreen)
        return NULL;

    pTempScreen->m_iMaxFPS = (int)(1000 / 144);

    return pTempScreen;
}

void Screen_SetMaxFPS(CScreen pScreen, int iMaxFPS)
{
    if (iMaxFPS == LOW)
        pScreen->m_iMaxFPS = 1000 / 60;
    else if (iMaxFPS == MEDIUM)
        pScreen->m_iMaxFPS = (int)(1000 / 120);
    else
        pScreen->m_iMaxFPS = (int)(1000 / 144);
}

int Screen_GetMaxFPS(CScreen pScreen)
{
    return pScreen->m_iMaxFPS;
}

float Screen_Sync(CScreen pScreen, float fVal)
{
    return (pScreen->m_iMaxFPS / 1000.f) * fVal;
}

void Screen_Free(CScreen pScreen)
{
    free(pScreen);
}

void Screen_ResizeWindow(int fSX, int fSY)
{
    Pantalla_Libera();
    Pantalla_Crea("Proyecto TP", fSX, fSY);
}

double Screen_ConvertX(double fX)
{
    return Pantalla_Anchura() * fX;
}

double Screen_ConvertY(double fY)
{
    return Pantalla_Altura() * fY;
}

double Screen_GetSX()
{
    return (double)Pantalla_Anchura();
}

double Screen_GetSY()
{
    return (double)Pantalla_Altura();
}
