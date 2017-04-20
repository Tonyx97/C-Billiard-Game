#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ScreenUtils.h"
#include "Pantalla.h"
#include "MainMenu.h"
#include "Game.h"

int RenderScene_1(CScreen pScreenUtils, int iRecursive)         /// main menu
{
    CMainMenu pMenu = MainMenu_Load(pScreenUtils, iRecursive);  /// Load Main menu

    int iResult = 0;

    if (!pMenu || !pScreenUtils)
    {
        printf("No se pudo cargar los recursos principales!\n");
        Pantalla_Libera();

        return -1;
    }

    while (Pantalla_Activa() && !iResult)
    {
        Pantalla_DibujaRellenoFondo(255, 255, 255, 255);

        iResult = MainMenu_UpdateMenu(pMenu, pScreenUtils);

        if (iResult > 0)
            break;

        Pantalla_Actualiza();
        Pantalla_Espera(Screen_GetMaxFPS(pScreenUtils));
    }

    MainMenu_SaveConfigs(pMenu);

    MainMenu_Free(pMenu);

    return iResult;
}

int RenderScene_2(CScreen pScreenUtils, int iAILevel)                         /// In-Game
{
    CGame pGame = Game_Load(pScreenUtils, iAILevel);

    int iResult = 0;

    if (!pGame)
    {
        printf("No se pudo cargar el juego!\n");
        return -1;
    }

    while (Pantalla_Activa() && !iResult)
    {
        Pantalla_DibujaRellenoFondo(255, 255, 255, 255);

        iResult = Game_Render(pGame);

        Pantalla_Actualiza();
        Pantalla_Espera(Screen_GetMaxFPS(pScreenUtils));
    }

    Pantalla_Espera(2000);

    Game_Free(pGame);

    return iResult;
}

void GoScene1(CScreen pScreenUtils, int iRecursive)
{
    int iAILevel = RenderScene_1(pScreenUtils, iRecursive);
    if (iAILevel != -1)
    {
        if (RenderScene_2(pScreenUtils, iAILevel) == 1)
            GoScene1(pScreenUtils, 1);
    }
}

int main(int argc, char* argv[])
{
    srand(time(0));

    Pantalla_Crea("Proyecto TP", 1600, 1050);

    CScreen pScreenUtils = Screen_Load();                           /// Load Screen Utils

    GoScene1(pScreenUtils, 0);

    Pantalla_Libera();

    return 0;
}







/*


        static double t1, t2;
        if (Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT)) ///DEBUG
        {
            Pantalla_RatonCoordenadas(&t1, &t2);
            printf("%f %f\n", (float)t1 / Screen_GetSX(), (float)t2 / Screen_GetSY());
        }
    static float x = 0, y = 0, sx = 0, sy = 0;

        if (Pantalla_TeclaPulsada(SDL_SCANCODE_LEFT))
            x -= 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_RIGHT))
            x += 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP))
            y -= 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN))
            y += 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_KP_4))
            sx -= 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_KP_6))
            sx += 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_KP_5))
            sy -= 0.001f;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_KP_2))
            sy += 0.001f;

        Pantalla_ColorTrazo(0, 255, 0, 255);
        char buf[128] = { 0 };
        sprintf(buf, "Position: (%.3f, %.3f, %.3f, %.3f)", x, y, sx, sy);
        Pantalla_DibujaTexto(buf, 10.0, 10.0);
*/
