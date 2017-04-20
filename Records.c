#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Records.h"
#include "MathUtils.h"

#define GAME_MAX_RECORDS 10
#define GAME_MAX_RECORDS_REST 1024

struct CRecords
{
    int m_iRecords[GAME_MAX_RECORDS];
    int m_iNumRecords;
};

CRecords Records_Load()
{
    CRecords pRecords = malloc(sizeof(struct CRecords));
    if (!pRecords)
        return NULL;

    memset(pRecords->m_iRecords, 0, GAME_MAX_RECORDS * 4);
    pRecords->m_iNumRecords = -1;

    FILE* fRecordsFile = fopen("data//records.cfg", "r");
    if (!fRecordsFile)                                          /// CREATE RECORDS FILE IF DOES NOT EXIST
    {
        fRecordsFile = fopen("data//records.cfg", "w");
        fprintf(fRecordsFile, "----RECORDS----\n");
        pRecords->m_iNumRecords = 0;
    }
    else
    {
        const int iSize = 32;

        char szBuf[iSize];
        int iUnorderedRecords[GAME_MAX_RECORDS_REST];

        int r2, index = -1;

        while(fgets(szBuf, iSize, fRecordsFile) != NULL && !feof(fRecordsFile))
        {
            fscanf(fRecordsFile, "%i", &r2);
            iUnorderedRecords[++index] = r2;
            if (index > GAME_MAX_RECORDS_REST)
                break;
        }

        Maths_SortArray(iUnorderedRecords, index);

        for (unsigned int i = 0; i < (index < GAME_MAX_RECORDS ? index : GAME_MAX_RECORDS) ; ++i)
            pRecords->m_iRecords[++pRecords->m_iNumRecords] = iUnorderedRecords[i];

        ++pRecords->m_iNumRecords;
    }

    fclose(fRecordsFile);

    return pRecords;
}

void Records_Free(CRecords pRecords)
{
    if (pRecords)
        free(pRecords);
}

int Records_Save(int iRecord)
{
    FILE* fRecordsFile = fopen("data//records.cfg", "a+");
    if (fRecordsFile)
        fprintf(fRecordsFile, "%i\n", iRecord);

    fclose(fRecordsFile);

    return !!fRecordsFile;
}

int Records_GetRecords(CRecords pRecords)
{
    return pRecords->m_iNumRecords;
}

int Records_GetRecordByIndex(CRecords pRecords, int index)
{
    if (pRecords->m_iNumRecords > 0 && index >= 0 && index < GAME_MAX_RECORDS)
        return pRecords->m_iRecords[index];
    return -1;
}
