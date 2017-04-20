#ifndef RECORDS_H
#define RECORDS_H

/**
\mainpage Records.
*/
/**
   \file Records.h
   \brief Utilizado para guardar y cargar los records del usuario. TDA contenedor de los records.
}*/

/**
    \brief TDA CRecords
 */
typedef struct CRecords* CRecords;

/**
  \brief Asigna memoria y retorna el puntero de tipo CRecords.
  \return Retorna un puntero a la dirección de memoria asignada por esta.
 */
CRecords Records_Load();

/**
  \brief Libera la memoria asignada por Records_Load.
  \param Pointer Records a liberar.
  \return Retorna el máximo de frames por segundo.
 */
void Records_Free(CRecords pRecords);

/**
  \brief Guarda el record actual en el archivo de records.
  \param Int Record a guardar.
  \return Retorna 1 si se guardo correctamente, de lo contrario retorna 0.
 */
int Records_Save(int iRecord);

/**
  \brief Obtiene la cantidad de records.
  \param Pointer Estructura creada de records.
  \return Retorna la cantidad de records cargados del archivo de records.
 */
int Records_GetRecords(CRecords pRecords);

/**
  \brief Obtiene un record concreto según si índice.
  \param Pointer Estructura creada de records.
  \param Int Índice del record.
  \return Retorna el record según el índice dado.
 */
int Records_GetRecordByIndex(CRecords pRecords, int index);

#endif
