#ifndef BALLS_H
#define BALLS_H

#include "Ball.h"
#include "Game.h"

/**
\mainpage Balls.
*/
/**
   \file Balls.h
   \brief Control de las bolas y TDA Enlazado de bolas, CBallsContainer.
}*/

/**
    \brief TDA CBallContainer
 */
typedef struct CBallContainer* CBallContainer;

/**
    \brief TDA CBallsContainer
 */
typedef struct CBallsContainer* CBallsContainer;

/**
  \brief Asigna memoria y retorna el puntero de tipo CBallsContainer.
  \return Retorna un puntero a la dirección de memoria asignada por esta.
 */
CBallsContainer Balls_Load();

/**
  \brief Obtiene la bola más cercana al punto dado.
  \param CBallsContainer Contendedor de las bolas.
  \param Float Coordenada X del punto.
  \param Float Coordenada Y del punto.
  \param Int Si es 1, ignora la bola 8, de lo contrario, la tiene en cuenta.
  \return Retorna la bola más cercana según el punto dado.
 */
CBall Balls_GetClosestBall(CBallsContainer pBalls, float fPosX, float fPosY, int iIgnore8Ball);

/**
  \brief Obtiene la bola según el tipo dado.
  \param CBallsContainer Contendedor de las bolas.
  \param Int Tipo de la bola.
  \return Retorna la bola del tipo dado.
 */
CBall Balls_GetBallByType(CBallsContainer pBalls, int iType);

/**
  \brief Libera la memoria asignada por Balls_Load.
  \param Pointer Contenedor de bolas a liberar.
 */
void Balls_Free(CBallsContainer pBalls);

/**
  \brief Coloca al principio de la partida las bolas en sus posiciones correspondientes.
  \param Pointer Contenedor de bolas.
 */
void Balls_Init(CBallsContainer pBalls);

/**
  \brief Borra una bola o todo el contenedor entero.
  \param Pointer Contenedor de bolas.
  \param Pointer Bola que se desea borrar (solo si iRemoveAll es 0)
  \param Int Define si se borran o no todas las bolas.
 */
void Balls_Remove(CBallsContainer pBalls, CBall pBall, int iRemoveAll);

/**
  \brief Asigna memoria a una nueva bola en el contenedor dado y la inserta en la lista enlazada.
  \param Pointer Contenedor de bolas donde se va a insertar la bola.
  \param Pointer Bola que se va a insertar.
 */
void Balls_Insert(CBallsContainer pBalls, CBall pBall);

/**
  \brief Coloca a todas las bolas el estado de colisión a 0.
  \param Pointer Contenedor de bolas donde se va a insertar la bola.
 */
void Balls_ResetCols(CBallsContainer pBalls);

/**
  \brief Actualiza las colisiones entre bolas.
  \param Pointer Contenedor de bolas donde se va a insertar la bola.
 */
void Balls_CheckCollisions(CBallsContainer pBalls);

/**
  \brief Actualiza las cinematicas de las bolas y las dibuja en la pantalla.
  \param Pointer Contenedor de bolas donde se va a insertar la bola.
  \param Pointer Bola que se va a insertar.
  \return Retorna el estado de las bolas. 0 = todas las bolas quietas, 1 = alguna bola moviéndose, 2 = la bola blanca se metió, 4 = se metió otra bola que no es la blanca
 */
int Balls_UpdateAndDraw(CBallsContainer pBalls, CGame pGame);

/**
  \brief Obtiene que todas las bolas están paradas o no.
  \param Pointer Contenedor de bolas donde se va a insertar la bola.
  \return Retorna 1 si todas las bolas estan paradas, de lo contrario, retorna 0.
 */
int Balls_AreStopped(CBallsContainer pBalls);


#endif
