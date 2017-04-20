#ifndef BALL_H
#define BALL_H

#include "Pantalla.h"
#include "Game.h"

/**
\mainpage Ball.
*/
/**
   \file Ball.h
   \brief Funciones y datos de una bola.
}*/

/**
    \brief TDA CBall
 */
typedef struct CBall* CBall;

/**
  \brief Asigna memoria y retorna el puntero de tipo CBall.
  \param Int Tipo / Número de bola a cargar.
  \return Retorna un puntero a la dirección de memoria asignada por esta.
 */
CBall Ball_Load(int iBallType);

/**
  \brief Obtiene la imagen de una bola específica.
  \param CBall Bola de la que se quiere sacar la imagen.
  \return Retorna la imagen de la bola dada.
 */
Imagen Ball_GetImage(CBall pBall);

/**
  \brief Obtiene la coordenada X e Y de una bola.
  \param CBall Bola de la que se quiere sacar los valores.
  \param Float* Variable en la que se asignara la coordenada X de la bola.
  \param Float* Variable en la que se asignara la coordenada Y de la bola.
 */
void Ball_GetXY(CBall pBall, float* fX, float* fY);

/**
  \brief Coloca la coordenada X e Y dadas a una bola.
  \param CBall Bola de la que se quiere colocar los valores.
  \param Float Coordenada X en donde se colocará la bola.
  \param Float Coordenada Y en donde se colocará la bola.
 */
void Ball_SetXY(CBall pBall, float fX, float fY);

/**
  \brief Obtiene la velocidad X e Y de una bola.
  \param CBall Bola de la que se quiere sacar los valores.
  \param Float* Variable en la que se asignara la velocidad X de la bola.
  \param Float* Variable en la que se asignara la velocidad Y de la bola.
 */
void Ball_GetVXY(CBall pBall, float* fVX, float* fVY);

/**
  \brief Coloca la velocidad X e Y dadas a una bola.
  \param CBall Bola de la que se quiere colocar los valores.
  \param Float Velocidad X que se le aplicará a la bola.
  \param Float Velocidad Y que se le aplicará a la bola.
*/
void Ball_SetVXY(CBall pBall, float fVX, float fVY);

/**
  \brief Obtiene la an anchura y altura de una bola.
  \param CBall Bola de la que se quiere sacar los valores.
  \param Float* Variable en la que se asignara la anchura de la bola.
  \param Float* Variable en la que se asignara la altura de la bola.
 */
void Ball_GetWH(CBall pBall, float* fW, float* fH);

/**
  \brief Coloca la anchura y altura dadas a una bola.
  \param CBall Bola de la que se quiere colocar los valores.
  \param Float Anchura que se le asignara a la bola.
  \param Float Altura que se le asignara a la bola.
*/
void Ball_SetWH(CBall pBall, float fW, float fH);

/**
  \brief Obtiene la coordenada X e Y del centro de una bola.
  \param CBall Bola de la que se quiere sacar los valores.
  \param Float* Variable en la que se asignara el centro X de la bola.
  \param Float* Variable en la que se asignara el centro Y de la bola.
 */
void Ball_GetCenter(CBall pBall, float* fX, float* fY);

/**
  \brief Le dice a la bola si se esta destruyendo o no.
  \param CBall Bola de la que se quiere cambiar el estado.
  \param Int* Estado de destrucción: 0 = no se esta destruyendo, 1 = destrucción temporal (para bola blanca), 2 = destruyendo totalmente (para las demás bolas)
 */
void Ball_SetDestroying(CBall pBall, int iDestroyed);

/**
  \brief Restaura los valores de anchura y altura por defecto de una bola.
  \param CBall Bola de la que se quiere restaurar los valores.
 */
void Ball_ResetWH(CBall pBall);

/**
  \brief Coloca el estado de colisión a una bola.
  \param CBall Bola de la que se quiere colocar el estado.
  \param Int Estado de colision: 0 = no hay colisión, 1 = si hay colisión.
 */
void Ball_SetCollisionState(CBall pBall, int iState);

/**
  \brief Libera la memoria asignada por Ball_Load.
  \param Pointer Bola a liberar.
 */
void Ball_Free(CBall pBall);

/**
  \brief Obtiene el tipo de la bola dada.
  \param CBall Bola de la que se quiere sacar el tipo.
 */
int Ball_GetType(CBall pBall);

/**
  \brief Obtiene el estado de destrucción de la bola dada.
  \param CBall Bola de la que se quiere sacar el estado de destrucción.
  \return Retorna el estado de destrucción.
 */
int Ball_IsDestroying(CBall pBall);

/**
  \brief Obtiene si la bola ha colisionado o no.
  \param CBall Bola de la que se quiere sacar el estado de destrucción.
  \return Retorna si hay colisionado o no.
 */
int Ball_IsCollided(CBall pBall);

/**
  \brief Obtiene si la bola ha colisionado o no.
  \param CBall Bola de la que se quiere revisar los límites en el tablero.
  \param Pointer Estructura creada de juego.
  \return Retorna si hay colisionado o no con los límites.
 */
int Ball_CheckBounds(CBall pBall, CGame pGame);


#endif
