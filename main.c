// main.c

#include "SRLinker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char androidPlatformToolsPath[256];
char androidRechte[256];
char input[256];
char inputWrongInput[256];




void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void initialExpenses()
{
    clearScreen();
    showLogo();

    printf(ANSI_BOLD "\n  Gib den Pfad zu den Android Platform Tools ein:" ANSI_RESET_BOLD);
    printf("\n--------------------------------------------------\n\n");

    printf(ANSI_LIGHT_STEEL_BLUE "  Info: Die Android SDK Platform-Tools koennen unter folgender URL heruntergeladen werden:\n\n  => " "https://developer.android.com/tools/releases/platform-tools?hl=de" "\n\n\n  Bei einer vorhandenen Installation von Android-Studio kann der Pfad wie folgt aussehen:" ANSI_RESET);
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => " "Beispiel: C:/Users/USERNAME/AppData/Local/Android/Sdk/platform-tools/ \n  => Wichtig ist die .\\adb.exe unter Windows! \n\n\n" ANSI_RESET);
    printf(ANSI_DEEP_PINK "  [c]" ANSI_RESET " Farbpalette anzeigen\n");
    printf(ANSI_TOMATO_RED "  [q]" ANSI_RESET " Exit\n\n");
    printf("--------------------------------------------------\n");
    printf("\n  Pfad eingeben:\n");
    printf("  => ");

    scanf("%s", androidPlatformToolsPath);

    if (androidPlatformToolsPath[0] == 'q') {
        handleExit();

    } else if (androidPlatformToolsPath[0] == 'c') {
        clearScreen();
        showLogo();

        printf(ANSI_BOLD ANSI_LIME"\n  Verfuegbare Farbpalette"ANSI_RESET_BOLD ANSI_RESET);
        printf("\n--------------------------------------------------\n\n");

        printf("\n\n\n=> Test");
        printf(ANSI_RED"\n=> Rot"ANSI_RESET);
        printf(ANSI_GREEN"\n=> Gruen"ANSI_RESET);
        printf(ANSI_YELLOW"\n=> Gelb"ANSI_RESET);
        printf(ANSI_BLUE"\n=> Blau"ANSI_RESET);
        printf(ANSI_MAGENTA"\n=> Magenta"ANSI_RESET);
        printf(ANSI_CYAN"\n=> Cyan"ANSI_RESET);
        printf(ANSI_WHITE"\n=> Weiss"ANSI_RESET);

        printf(ANSI_ORANGE"\n=> Orange"ANSI_RESET);
        printf(ANSI_DARK_ORANGE"\n=> Dunkelorange"ANSI_RESET);
        printf(ANSI_LIGHT_ORANGE"\n=> Hellorange"ANSI_RESET);
        printf(ANSI_GOLD"\n=> Gold"ANSI_RESET);
        printf(ANSI_TOMATO_RED"\n=> Tomatenrot"ANSI_RESET);
        printf(ANSI_CORAL_RED"\n=> Korallenrot"ANSI_RESET);
        printf(ANSI_DEEP_PINK"\n=> Tiefrosa"ANSI_RESET);
        printf(ANSI_LIGHT_PINK"\n=> Hellrosa"ANSI_RESET);
        printf(ANSI_VIOLET"\n=> Violett"ANSI_RESET);
        printf(ANSI_ORCHID"\n=> Orchidee"ANSI_RESET);

        printf(ANSI_LIME"\n=> Limette"ANSI_RESET);
        printf(ANSI_FOREST_GREEN"\n=> Waldgruen"ANSI_RESET);
        printf(ANSI_TEAL"\n=> Teal"ANSI_RESET);
        printf(ANSI_AQUA"\n=> Aqua"ANSI_RESET);
        printf(ANSI_NAVY"\n=> Navy"ANSI_RESET);
        printf(ANSI_PURPLE"\n=> Lila"ANSI_RESET);
        printf(ANSI_INDIGO"\n=> Indigo"ANSI_RESET);
        printf(ANSI_MAROON"\n=> Maroon"ANSI_RESET);
        printf(ANSI_SALMON"\n=> Lachs"ANSI_RESET);
        printf(ANSI_SIENNA"\n=> Sienna"ANSI_RESET);
        printf(ANSI_CORNFLOWER"\n=> Kornblume"ANSI_RESET);
        printf(ANSI_SKY_BLUE"\n=> Himmelblau"ANSI_RESET);
        printf(ANSI_MEDIUM_BLUE"\n=> Mittelblau"ANSI_RESET);
        printf(ANSI_DARK_TURQUOISE"\n=> Dunkeltuerkis"ANSI_RESET);
        printf(ANSI_SLATE_BLUE"\n=> Schieferblau"ANSI_RESET);
        printf(ANSI_ROYAL_BLUE"\n=> Koenigsblau"ANSI_RESET);
        printf(ANSI_MEDIUM_PURPLE"\n=> Mittelviolett"ANSI_RESET);
        printf(ANSI_DARK_OLIVE"\n=> Dunkeloliv"ANSI_RESET);
        printf(ANSI_LIGHT_SKY_BLUE"\n=> Hellhimmelblau"ANSI_RESET);
        printf(ANSI_MIDNIGHT_BLUE"\n=> Mitternachtsblau"ANSI_RESET);
        printf(ANSI_DARK_MAGENTA"\n=> Dunkelmagenta"ANSI_RESET);
        printf(ANSI_CHOCOLATE"\n=> Schokolade"ANSI_RESET);
        printf(ANSI_MEDIUM_SEA_GREEN"\n=> Mittleresgruen"ANSI_RESET);
        printf(ANSI_SLATE_GRAY"\n=> Schiefergrau"ANSI_RESET);
        printf(ANSI_DIM_GRAY"\n=> Dunkelgrau"ANSI_RESET);
        printf(ANSI_LIGHT_SLATE_GRAY"\n=> Hellgrau"ANSI_RESET);
        printf(ANSI_LIGHT_STEEL_BLUE"\n=> Hellstahlblau"ANSI_RESET);
        printf(ANSI_LIGHT_GRAY"\n=> Hellgrau"ANSI_RESET);
        printf(ANSI_GAINSBORO"\n=> Gainsboro"ANSI_RESET);

        printf("\n\n\n");
        printf("Zurueck zum Hauptmenue: [Enter]\n");
        getchar();
        getchar();
        initialExpenses();
    }
}

int main() {

    while (1) {

        initialExpenses();
        showOptions();
    }

    printf("\nProgramm wurde beendet.\n");
    return 0;
}