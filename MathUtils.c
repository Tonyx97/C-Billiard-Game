#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MathUtils.h"

void Maths_VectorNormalize(float* fX, float* fY)
{
    float fMod = Maths_VectorModule(*fX, *fY);
    *fX /= fMod;
    *fY /= fMod;
}

void Maths_SortArray(int iArr[], int iSize)
{
    int i, j, iTemp;

    for (i = 0; i < iSize; ++i)
        for (j = i + 1; j < iSize; ++j)
        {
            if (iArr[i] < iArr[j])
            {
                iTemp = iArr[i];
                iArr[i] = iArr[j];
                iArr[j] = iTemp;
            }
        }

}

float Maths_GetDistance(float fX1, float fY1, float fX2, float fY2)
{
    return sqrtf((fX2 - fX1) * (fX2 - fX1) + (fY2 - fY1) * (fY2 - fY1));
}

float Maths_Interpolate(float fFrom, float fTo, float fFactor)
{
    return fFrom + fFactor * (fTo - fFrom);
}

float Maths_VectorModule(float fX, float fY)
{
    return sqrtf((fX * fX) + (fY * fY));
}

float Maths_AngleBetweenVectors(float x1, float y1, float xf1, float yf1, float x2, float y2, float xf2, float yf2)
{
    return (atan2(xf1 - x1, yf1 - y1) - atan2(xf2 - x2, yf2 - y2));
}

