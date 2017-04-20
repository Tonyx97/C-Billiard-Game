#ifndef SCREENUTILS_H
#define SCREENUTILS_H

/**
\mainpage Utilidades de pantalla
*/
/**
   \file ScreenUtils.h
   \brief Utilizado para calcular posiciones relativas de pantalla, cambiar el tamaño de la pantalla, FPS etc. TDA simple.
}*/

/**
    \brief TDA CScreen
 */
typedef struct CScreenUtils* CScreen;


/**
  \brief Asigna memoria y retorna un puntero de tipo CScreen
  \return Retorna un puntero a la dirección de memoria asignada por esta.
 */
CScreen Screen_Load();

/**
  \brief Cambia el tamaño de la pantalla.
  \param Int Anchura de la pantalla.
  \param Int Altura de la pantalla.
 */
void Screen_ResizeWindow(int fSX, int fSY);

/**
  \brief Cambia el máximo de frames por segundo.
  \param Pointer Estructura creada de útiles de pantalla.
  \param Int Máximo de frames que se desea definir.
 */
void Screen_SetMaxFPS(CScreen pScreen, int iMaxFPS);

/**
  \brief Libera la memoria asignada por Screen_Load.
  \param Pointer Útiles de pantalla a liberar.
 */
void Screen_Free(CScreen pScreen);

/**
  \brief Retorna el máximo de frames por segundo actual.
  \param Pointer Estructura creada de útiles de pantalla.
  \return Retorna el máximo de frames por segundo.
 */
int Screen_GetMaxFPS(CScreen pScreen);

/**
  \brief Calcula el valor sincronizado para todos los monitores.
  \param Pointer Estructura creada de útiles de pantalla.
  \return Retorna un valor float optimizado para que no dependa de la frecuencia del monitor.
 */
float Screen_Sync(CScreen pScreen, float fVal);

/**
  \brief Obtiene la anchura de la pantalla.
  \return Retorna la anchura de la pantalla.
 */
double Screen_GetSX();

/**
  \brief Obtiene la altura de la pantalla.
  \return Retorna la altura de la pantalla.
 */
double Screen_GetSY();

/**
  \brief Calcula la coordenada X real de la coordenada dada entre 0 y 1 (relativa)
  \param Float Valor relativo X entre 0 y 1.
  \return Retorna el valor en double de la coordenada real X en pantalla.
 */
double Screen_ConvertX(double fX);

/**
  \brief Calcula la coordenada Y real de la coordenada dada entre 0 - 1 (relativa)
  \param Float Valor relativo Y entre 0 y 1.
  \return Retorna el valor en double de la coordenada real Y en pantalla.
 */
double Screen_ConvertY(double fY);


#endif
