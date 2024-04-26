// AuxiliaryFunctions.c

#include "../SRLinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 256

char continueServerStart[256];
char continueServerKill[256];




void getTime(char *timestamp, size_t timestamp_size) {
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Zeitstempel wird erstellt..." ANSI_RESET);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(timestamp, timestamp_size, "%d-%02d-%02d_%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Zeitstempel: " ANSI_RESET ANSI_DARK_ORANGE "%s\n"ANSI_RESET, timestamp);
}

void handleServerStart() {

    printf("\n\n--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Server wird gestartet...\n" ANSI_RESET);

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe start-server", androidPlatformToolsPath);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    printf(ANSI_DARK_ORANGE "");
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim starten des Servers!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);
    printf(ANSI_RESET "");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Serverstart beendet.\n" ANSI_RESET);

    printf("\n\nWeitere Aktionen? [y/n]:\n");
    printf("=> ");
    scanf("%s", continueServerStart);

    if (continueServerStart[0] == 'y') {
        showOptions();
    } else {
        main();
    }
}

void handleServerKill() {

    printf("\n\n--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Server wird beendet...\n" ANSI_RESET);

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe kill-server", androidPlatformToolsPath);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim beenden des Servers!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Server wurde beendet.\n" ANSI_RESET);

    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueServerKill);

    if (continueServerKill[0] == 'y') {
        showOptions();
    } else {
        main();
    }
}

void printIncreasingDots(int dots) {
    for (int i = 0; i < dots; i++) {
        printf(ANSI_LIGHT_STEEL_BLUE "." ANSI_RESET);
        sleep(1);
    }
}

void refreshServer() {
    printf("\n\n--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Check Server\n" ANSI_RESET);
    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe start-server", androidPlatformToolsPath);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    printf(ANSI_DARK_ORANGE "");
    adbOutput = popen(adbDevicesCommand, "r");

    pclose(adbOutput);
    printf(ANSI_RESET"  ");
    printIncreasingDots(4);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Check beendet\n\n" ANSI_RESET);
}

void refreshServerLong() {
    printf("\n\n--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Check Server\n" ANSI_RESET);
    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe start-server", androidPlatformToolsPath);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    printf(ANSI_DARK_ORANGE "");
    adbOutput = popen(adbDevicesCommand, "r");

    pclose(adbOutput);
    printf(ANSI_RESET"  ");
    printIncreasingDots(7);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Check beendet\n\n" ANSI_RESET);
}

void requestHandleLogFiles() {
    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueDeviceInfos);
    if (continueDeviceInfos[0] == 'y') {
        handleLogFiles();
    } else {
        showOptions();
    }
}

void requestHandleNetwork() {
    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueDeviceInfos);
    if (continueDeviceInfos[0] == 'y') {
        handleNetwork();
    } else {
        showOptions();
    }
}

void requestHandleProcesses() {
    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueDeviceInfos);
    if (continueDeviceInfos[0] == 'y') {
        handleProcesses();
    } else {
        showOptions();
    }
}

void requestHandleAPKs() {
    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueDeviceInfos);
    if (continueDeviceInfos[0] == 'y') {
        handleAPKs();
    } else {
        showOptions();
    }

}

void requestHandleInteractions() {
    printf("\n\n  Weitere Aktionen? [y/n]:\n");
    printf("  => ");
    scanf("%s", continueDeviceInfos);
    if (continueDeviceInfos[0] == 'y') {
        handleInteractions();
    } else {
        showOptions();
    }
}

void handleExit() {
    printf(ANSI_LIGHT_STEEL_BLUE"\n   Servus\n\n"ANSI_RESET);
    exit(0);
}



