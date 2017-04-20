#ifndef MATHUTILS_H
#define MATHUTILS_H

#define PI 3.14159265359

/**
\mainpage Utilidades matemáticas
*/
/**
   \file MathUtils.h
   \brief Utilizado para organizar el código y tener varias funciones matemáticas útiles de acceso fácil.
}*/

/**
  \brief Normaliza un vector dadas sus coordenadas X e Y.
  \param Float Componente X del vector a normalizar.
  \param Float Componente Y del vector a normalizar.
 */
void Maths_VectorNormalize(float* fX, float* fY);

/**
  \brief Ordena de mayor a menor una array de ints.
  \param Int* Array de ints a ordenar.
  \param Int Tamaño de la array que se quiere ordenar.
 */
void Maths_SortArray(int iArr[], int iSize);

/**
  \brief Retorna la distancia que hay entre dos puntos 2D dados.
  \param Float Coordenada X del primer punto.
  \param Float Coordenada Y del primer punto.
  \param Float Coordenada X del segundo punto.
  \param Float Coordenada Y del segundo punto.
 */
float Maths_GetDistance(float fX1, float fY1, float fX2, float fY2);

/**
  \brief Interpolación entre dos valores.
  \param Float Valor de donde se parte.
  \param Float Valor a donde se quiere llegar.
  \param Float Factor de velocidad de interpolación.
 */
float Maths_Interpolate(float from, float to, float factor);

/**
  \brief Retorna el módulo del vector dado.
  \param Float Coordenada X del vector.
  \param Float Coordenada Y del vector.
 */
float Maths_VectorModule(float fX, float fY);

/**
  \brief Retorna el ángulo dado entre dos lineas según sus puntos
  \param Float Primera coordenada X del vector 1.
  \param Float Primera coordenada Y del vector 1.
  \param Float Segunda coordenada X del vector 1.
  \param Float Segunda coordenada Y del vector 1.
  \param Float Primera coordenada X del vector 2.
  \param Float Primera coordenada Y del vector 2.
  \param Float Segunda coordenada X del vector 2.
  \param Float Segunda coordenada Y del vector 2.
 */
float Maths_AngleBetweenVectors(float x1, float y1, float xf1, float yf1, float x2, float y2, float xf2, float yf2);




#endif
