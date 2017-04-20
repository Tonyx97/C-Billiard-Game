#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Pantalla.h"
#include "MainMenu.h"
#include "ScreenUtils.h"
#include "Records.h"
#include "MathUtils.h"

#define GAME_MAIN_MENU_MAX_IMAGES 5
#define GAME_SETTINGS_MAX_IMAGES 3

enum eMenuOptions
{
    GENERAL,
    PLAY,
    RECORDS,
    SETTINGS,
    EXIT
};

enum eSettingsOptions
{
    FRAMERATE,
    AI_LEVEL,
    RESOLUTION,
};

enum eConfigs
{
    LOW,
    MEDIUM,
    HIGH
};

enum eMenuImages
{
    MAIN_MENU_BACKGROUND,
    MAIN_MENU_TEXT,
    MAIN_MENU_ARROW,
    MAIN_MENU_SETTINGS_TEXT,
    MAIN_MENU_RECORDS,
};

struct CMainMenu
{
    Imagen m_pImages[GAME_MAIN_MENU_MAX_IMAGES],
           m_pConfigImages[GAME_SETTINGS_MAX_IMAGES];

    CRecords m_pRecords;

    double m_dScreenSX, m_dScreenSY;

    float m_fX,
          m_fY,
          m_fW,
          m_fH,
          m_fArrowX,
          m_fArrowY,
          m_fArrowTempY,
          m_fBackgroundX,
          m_fBackgroundY;

    int m_iRenderedSection,
        m_iOption,
        m_iSubOption,
        m_iSectionOption,
        m_iSectionSubOption[GAME_SETTINGS_MAX_IMAGES],
        m_iInitialized,
        m_iCurrentTick,
        m_iLastTick,
        m_iClosingMenu;
};

int MainMenu_LoadConfigs(CMainMenu pMenu);

CMainMenu MainMenu_Load(CScreen pScreenUtils, int iRecursiveLoad)
{
    CMainMenu pMenu = malloc(sizeof(struct CMainMenu));

    if (!pMenu)
        return NULL;

    pMenu->m_iRenderedSection = GENERAL;
    pMenu->m_iOption = PLAY;
    pMenu->m_iSubOption = 0;
    pMenu->m_iSectionOption = 0;

    pMenu->m_iSectionSubOption[FRAMERATE] = HIGH;
    pMenu->m_iSectionSubOption[AI_LEVEL] = MEDIUM;
    pMenu->m_iSectionSubOption[RESOLUTION] = HIGH;

    pMenu->m_iInitialized = 0;
    pMenu->m_iCurrentTick = 0;
    pMenu->m_iLastTick = 0;
    pMenu->m_iClosingMenu = 0;
    pMenu->m_fBackgroundX = 0.f;
    pMenu->m_fBackgroundY = 0.f;
    pMenu->m_fY = 0.333f;
    pMenu->m_fX = 0.750f;
    pMenu->m_fY = 0.333f;
    pMenu->m_fW = 0.265f;
    pMenu->m_fH = 0.350f;
    pMenu->m_dScreenSX = Screen_GetSX();
    pMenu->m_dScreenSY = Screen_GetSY();
    pMenu->m_fArrowX = pMenu->m_fX - 0.012f;
    pMenu->m_fArrowY = pMenu->m_fY + 0.040f;
    pMenu->m_fArrowTempY = 0.f;

    pMenu->m_pImages[MAIN_MENU_BACKGROUND] = Pantalla_ImagenLee("data//main_menu//main_menu.bmp", 0);
    pMenu->m_pImages[MAIN_MENU_TEXT] = Pantalla_ImagenLee("data//main_menu//main_menu_text.bmp", 255);
    pMenu->m_pImages[MAIN_MENU_ARROW] = Pantalla_ImagenLee("data//main_menu//main_menu_arrow.bmp", 255);
    pMenu->m_pImages[MAIN_MENU_SETTINGS_TEXT] = Pantalla_ImagenLee("data//main_menu//main_menu_settings_text.bmp", 255);
    pMenu->m_pImages[MAIN_MENU_RECORDS] = Pantalla_ImagenLee("data//main_menu//main_menu_records.bmp", 0);

    pMenu->m_pConfigImages[LOW] = Pantalla_ImagenLee("data//main_menu//low.bmp", 255);
    pMenu->m_pConfigImages[MEDIUM] = Pantalla_ImagenLee("data//main_menu//medium.bmp", 255);
    pMenu->m_pConfigImages[HIGH] = Pantalla_ImagenLee("data//main_menu//high.bmp", 255);

    if (!MainMenu_LoadConfigs(pMenu))
        printf("No se pudo cargar las configuraciones!\n");

    pMenu->m_pRecords = Records_Load();
    if (!pMenu->m_pRecords)
        printf("No se pudo cargar los records!\n");

    if (!iRecursiveLoad)
    {
        Screen_SetMaxFPS(pScreenUtils, pMenu->m_iSectionSubOption[FRAMERATE]);
        if (pMenu->m_iSectionSubOption[RESOLUTION] == LOW)
            Screen_ResizeWindow(1024, 768);
        else if (pMenu->m_iSectionSubOption[RESOLUTION] == MEDIUM)
            Screen_ResizeWindow(1280, 800);
        else
            Screen_ResizeWindow(1600, 1050);
    }

    return pMenu;
}

void MainMenu_Free(CMainMenu pMenu)
{
    for (unsigned int i = 0; i < GAME_MAIN_MENU_MAX_IMAGES; ++i)
        Pantalla_ImagenLibera(pMenu->m_pImages[i]);

    for (unsigned int i = 0; i < GAME_SETTINGS_MAX_IMAGES; ++i)
        Pantalla_ImagenLibera(pMenu->m_pConfigImages[i]);

    Records_Free(pMenu->m_pRecords);

    free(pMenu);
}

int MainMenu_SaveConfigs(CMainMenu pMenu)
{
    FILE* fConfigFile = fopen("data//config.cfg", "w+");
    if (fConfigFile)
    {
        fprintf(fConfigFile, "MAX_FRAMERATE = %i\n", pMenu->m_iSectionSubOption[FRAMERATE]);
        fprintf(fConfigFile, "DIFICULTAD_AI = %i\n", pMenu->m_iSectionSubOption[AI_LEVEL]);
        fprintf(fConfigFile, "RESOLUCION = %i\n", pMenu->m_iSectionSubOption[RESOLUTION]);
    }
    else
        printf("El archivo de configuraciones no se pudo guardar correctamente!\n");

    fclose(fConfigFile);

    return !!fConfigFile;
}

int MainMenu_LoadConfigs(CMainMenu pMenu)
{
    FILE* fConfigFile = fopen("data//config.cfg", "r");
    if (fConfigFile)
    {
        const int iSize = 32;

        char line[iSize];

        fscanf(fConfigFile, "MAX_FRAMERATE = %i\n", &pMenu->m_iSectionSubOption[FRAMERATE]);
        fscanf(fConfigFile, "DIFICULTAD_AI = %i\n", &pMenu->m_iSectionSubOption[AI_LEVEL]);
        fscanf(fConfigFile, "RESOLUCION = %i\n", &pMenu->m_iSectionSubOption[RESOLUTION]);

        free(line);

        fclose(fConfigFile);

        return 1;
    }

    fclose(fConfigFile);

    return 0;
}

void MainMenu_InterpolateArrow(CMainMenu pMenu, float fVel)
{
    if (fabs(pMenu->m_fArrowTempY - pMenu->m_fArrowY) > 0.f)
        pMenu->m_fArrowY += (pMenu->m_fArrowTempY - pMenu->m_fArrowY) * fVel;
}

void MainMenu_ChangeConfigs(CMainMenu pMenu, CScreen pScreenUtils)
{
    switch (pMenu->m_iSectionSubOption[pMenu->m_iSubOption])
    {
    case LOW:
        if (pMenu->m_iSubOption == FRAMERATE)
            Screen_SetMaxFPS(pScreenUtils, LOW);
        else if (pMenu->m_iSubOption == RESOLUTION)
            Screen_ResizeWindow(1024, 768);

        break;
    case MEDIUM:
        if (pMenu->m_iSubOption == FRAMERATE)
            Screen_SetMaxFPS(pScreenUtils, MEDIUM);
        else if (pMenu->m_iSubOption == RESOLUTION)
            Screen_ResizeWindow(1280, 800);

        break;
    case HIGH:
        if (pMenu->m_iSubOption == FRAMERATE)
            Screen_SetMaxFPS(pScreenUtils, HIGH);
        else if (pMenu->m_iSubOption == RESOLUTION)
            Screen_ResizeWindow(1600, 1050);

    default:
        break;
    }
}

void MainMenu_ClampConfigs(CMainMenu pMenu)
{
    if (pMenu->m_iSubOption > RESOLUTION)
        pMenu->m_iSubOption = FRAMERATE;
    else if (pMenu->m_iSubOption < FRAMERATE)
        pMenu->m_iSubOption = RESOLUTION;

    if (pMenu->m_iSectionSubOption[pMenu->m_iSubOption] > HIGH)
        pMenu->m_iSectionSubOption[pMenu->m_iSubOption] = LOW;
    else if (pMenu->m_iSectionSubOption[pMenu->m_iSubOption] < LOW)
        pMenu->m_iSectionSubOption[pMenu->m_iSubOption] = HIGH;
}

int MainMenu_ExitGame(CMainMenu pMenu)
{
    Records_Free(pMenu->m_pRecords);

    return -1;
}

int MainMenu_DispatchKeys(CMainMenu pMenu, CScreen pScreenUtils)
{
	if (pMenu->m_iRenderedSection == GENERAL)
	{
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP))
		{
			--pMenu->m_iOption;
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN))
		{
			++pMenu->m_iOption;
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN))
		{
			switch (pMenu->m_iOption)
			{
			case PLAY:
				return -2;
			case RECORDS:
				pMenu->m_iRenderedSection = RECORDS;
				return 0;
			case SETTINGS:
				pMenu->m_iRenderedSection = SETTINGS;
				return 0;
			case EXIT:
			    MainMenu_ExitGame(pMenu);
				return -1;

			default:
				break;
			}
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_LALT) && Pantalla_TeclaPulsada(SDL_SCANCODE_F4))
            return MainMenu_ExitGame(pMenu);

		if (pMenu->m_iOption > EXIT)
			pMenu->m_iOption = PLAY;
		else if (pMenu->m_iOption < PLAY)
			pMenu->m_iOption = EXIT;
	}
	else if (pMenu->m_iRenderedSection == SETTINGS)
	{
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP))
		{
			--pMenu->m_iSubOption;
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN))
		{
			++pMenu->m_iSubOption;
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_RIGHT))
		{
			++pMenu->m_iSectionSubOption[pMenu->m_iSubOption];
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
			MainMenu_ClampConfigs(pMenu);
			MainMenu_ChangeConfigs(pMenu, pScreenUtils);
		}
		else if (Pantalla_TeclaPulsada(SDL_SCANCODE_LEFT))
		{
			--pMenu->m_iSectionSubOption[pMenu->m_iSubOption];
			pMenu->m_iLastTick = pMenu->m_iCurrentTick;
			MainMenu_ClampConfigs(pMenu);
			MainMenu_ChangeConfigs(pMenu, pScreenUtils);
		}

        if (pMenu->m_iSubOption > RESOLUTION)
            pMenu->m_iSubOption = FRAMERATE;
        else if (pMenu->m_iSubOption < FRAMERATE)
            pMenu->m_iSubOption = RESOLUTION;
	}

	if (pMenu->m_iRenderedSection != GENERAL && (Pantalla_TeclaPulsada(SDL_SCANCODE_BACKSPACE) || Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)))
	{
		pMenu->m_iRenderedSection = GENERAL;
		pMenu->m_iSubOption = 0;
	}

	return 0;
}

int MainMenu_UpdateGeneral(CMainMenu pMenu, CScreen pScreenUtils)
{
    int iResult = 0;

    Pantalla_DibujaImagen(pMenu->m_pImages[MAIN_MENU_TEXT], Screen_ConvertX((double)pMenu->m_fX), Screen_ConvertY((double)pMenu->m_fY), Screen_ConvertX((double)pMenu->m_fW), Screen_ConvertY((double)pMenu->m_fH));

    if (pMenu->m_iInitialized)
    {
        pMenu->m_fArrowX = pMenu->m_fX;

        switch (pMenu->m_iOption)
        {
        case PLAY:
            pMenu->m_fArrowTempY = pMenu->m_fY + 0.04f;
            break;
        case RECORDS:
            pMenu->m_fArrowTempY = pMenu->m_fY + 0.108f;
            break;
        case SETTINGS:
            pMenu->m_fArrowTempY = pMenu->m_fY + 0.173f;
            break;
        case EXIT:
            pMenu->m_fArrowTempY = pMenu->m_fY + 0.24f;
            break;

        default:
            break;
        }

        MainMenu_InterpolateArrow(pMenu, Screen_Sync(pScreenUtils, 20.f));

        Pantalla_DibujaImagen(pMenu->m_pImages[MAIN_MENU_ARROW], Screen_ConvertX((double)pMenu->m_fArrowX), Screen_ConvertY((double)pMenu->m_fArrowY), Screen_ConvertX(0.035), Screen_ConvertY(0.047));

        if (pMenu->m_iCurrentTick - pMenu->m_iLastTick >= 15 && !pMenu->m_iClosingMenu)
            iResult = MainMenu_DispatchKeys(pMenu, pScreenUtils);

        if (pMenu->m_iClosingMenu)
        {
            pMenu->m_fX -= Screen_Sync(pScreenUtils, 1.f);
            pMenu->m_fBackgroundX -= Screen_Sync(pScreenUtils, 3.f);
            if (Screen_ConvertX((double)pMenu->m_fBackgroundX) <= -(float)pMenu->m_dScreenSX)
                iResult = 1 + pMenu->m_iSectionSubOption[AI_LEVEL];
        }
        else if (iResult == -2)
        {
            pMenu->m_iClosingMenu = 1;
            iResult = 0;
        }
    }
    else
    {
        if (!pMenu->m_iInitialized && pMenu->m_fX > 0.02f)
            pMenu->m_fX -= Screen_Sync(pScreenUtils, 2.f);
        else
            pMenu->m_iInitialized = 1;
    }

    return iResult;
}

int MainMenu_UpdateRecords(CMainMenu pMenu, CScreen pScreenUtils)
{
    if (!pMenu->m_pRecords)
        return -1;

    Pantalla_ColorTrazo(0, 255, 0, 255);

    if (Records_GetRecords(pMenu->m_pRecords) > 0)
    {
        char szBuf[128] = { 0 };
        for (unsigned int i = 0; i < Records_GetRecords(pMenu->m_pRecords); ++i)
        {
            sprintf(szBuf, "-%i. %i", i + 1, Records_GetRecordByIndex(pMenu->m_pRecords, i));
            Pantalla_DibujaTexto(szBuf, Screen_ConvertX(0.462), Screen_ConvertY(0.17 + (i * 0.03)));
        }
    }
    else
        Pantalla_DibujaTexto("No Records", Screen_ConvertX(0.462), Screen_ConvertY(0.17));

    if (pMenu->m_iCurrentTick - pMenu->m_iLastTick >= 15)
        return MainMenu_DispatchKeys(pMenu, pScreenUtils);

    return 0;
}

int MainMenu_UpdateSettings(CMainMenu pMenu, CScreen pScreenUtils)
{
    float fSettingsX = pMenu->m_fX + 0.035f, fSettingsY = pMenu->m_fY + 0.01f;
    double dConfigValuesX = Screen_ConvertX((double)pMenu->m_fX + 0.25),
           dConfigW = Screen_ConvertX(0.3),
           dConfigH = Screen_ConvertY(0.4);

    Pantalla_DibujaImagen(pMenu->m_pImages[MAIN_MENU_SETTINGS_TEXT], Screen_ConvertX(fSettingsX), Screen_ConvertY(fSettingsY), Screen_ConvertX(0.265), Screen_ConvertY(0.350));

    Pantalla_DibujaImagen(pMenu->m_pConfigImages[pMenu->m_iSectionSubOption[FRAMERATE]], dConfigValuesX, Screen_ConvertY((double)pMenu->m_fY - 0.094), dConfigW, dConfigH);
    Pantalla_DibujaImagen(pMenu->m_pConfigImages[pMenu->m_iSectionSubOption[AI_LEVEL]], dConfigValuesX, Screen_ConvertY((double)pMenu->m_fY - 0.029), dConfigW, dConfigH);
    Pantalla_DibujaImagen(pMenu->m_pConfigImages[pMenu->m_iSectionSubOption[RESOLUTION]], dConfigValuesX, Screen_ConvertY((double)pMenu->m_fY + 0.04), dConfigW, dConfigH);

    pMenu->m_fArrowX = fSettingsX - 0.041f;

    switch (pMenu->m_iSubOption)
    {
    case FRAMERATE:
        pMenu->m_fArrowTempY = pMenu->m_fY + 0.033f;
        break;
    case AI_LEVEL:
        pMenu->m_fArrowTempY = pMenu->m_fY + 0.101f;
        break;
    case RESOLUTION:
        pMenu->m_fArrowTempY = pMenu->m_fY + 0.166f;
        break;

    default:
        break;
    }

    MainMenu_InterpolateArrow(pMenu, Screen_Sync(pScreenUtils, 20.f));

    Pantalla_DibujaImagen(pMenu->m_pImages[MAIN_MENU_ARROW], Screen_ConvertX((double)pMenu->m_fArrowX), Screen_ConvertY((double)pMenu->m_fArrowY), Screen_ConvertX(0.035), Screen_ConvertY(0.047));

    if (pMenu->m_iCurrentTick - pMenu->m_iLastTick >= 15)
        return MainMenu_DispatchKeys(pMenu, pScreenUtils);

    return 0;
}

int MainMenu_UpdateMenu(CMainMenu pMenu, CScreen pScreenUtils)
{
    int iImage = pMenu->m_iRenderedSection == RECORDS ? MAIN_MENU_RECORDS : MAIN_MENU_BACKGROUND;

    Pantalla_DibujaImagen(pMenu->m_pImages[iImage], Screen_ConvertX((double)pMenu->m_fBackgroundX), Screen_ConvertX((double)pMenu->m_fBackgroundY), pMenu->m_dScreenSX, pMenu->m_dScreenSY);

    ++pMenu->m_iCurrentTick;

    switch(pMenu->m_iRenderedSection)
    {
    case RECORDS:
        return MainMenu_UpdateRecords(pMenu, pScreenUtils);
    case GENERAL:
        return MainMenu_UpdateGeneral(pMenu, pScreenUtils);
    case SETTINGS:
        return MainMenu_UpdateSettings(pMenu, pScreenUtils);

    default:
        return 0;
    }
}
