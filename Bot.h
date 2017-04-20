#ifndef BOT_H
#define BOT_H

#include "Ball.h"

/**
\mainpage Bot.
*/
/**
   \file Bot.h
   \brief Inteligencia Artificial simple para controlar el bot enemigo.
}*/

/**
    \brief TDA CBot
 */
typedef struct CBot* CBot;

/**
  \brief Asigna memoria y retorna el puntero de tipo CBot.
  \param Int Nivel de dificultad de la IA.
  \return Retorna un puntero a la dirección de memoria asignada por esta.
 */
CBot Bot_Load(int iLevel);

/**
  \brief Libera la memoria asignada por Bot_Load.
  \param Pointer Bot a liberar.
 */
void Bot_Free(CBot pBot);

/**
  \brief Hace lanzar el bot.
  \param CBall Bola a la que golpear.
  \param CBot Estructura creada de records.
  \param Float Dirección X a ser lanzada la bola.
  \param Float Dirección Y a ser lanzada la bola.
 */
void Bot_Launch(CBall pBall, CBot pBot, float fDirX, float fDirY);



#endif
