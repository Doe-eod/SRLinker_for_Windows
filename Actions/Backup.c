// Backup.c

#include "../SRLinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_TIMESTAMP_LENGTH 20

char actionRequestCreate[256];
char actionRequestRestore[256];



void createBackup() {
    printf("--------------------------------------------");

    char backupCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(backupCommand, "%s/adb.exe backup -all -f SRLinker_Backups/backup_%s.ab -all", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Backups... " ANSI_RESET);
    int status = system("mkdir SRLinker_Backups");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Backup... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(backupCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Erstellen des Backups!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET "");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Das Backup wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Backups/backup_%s.ab'\n" ANSI_RESET, timestamp);

    printf("\n\n  Aktion wiederholen? [y/n]:\n");
    printf("  => ");
    scanf("%s", actionRequestCreate);
    if (actionRequestCreate[0] == 'y') {
        createBackup();
    } else {
        showOptions();
    }
}

void restoreBackup() {
    printf("--------------------------------------------");

    char backupPath[MAX_LINE_LENGTH];
    char restoreCommand[MAX_LINE_LENGTH];

    printf("\n  => Pfad zum Backup eingeben:\n");
    printf("  => ");
    scanf("%s", backupPath);

    sprintf(restoreCommand, "%s/adb.exe restore %s", androidPlatformToolsPath, backupPath);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Wiederherstellung von %s... \n" ANSI_RESET, backupPath);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(restoreCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Wiederherstellen von %s!\n" ANSI_RESET, backupPath);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET "");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Wiederherstellung von %s beendet." ANSI_RESET, backupPath);


    printf("  Aktion wiederholen? [y/n]:\n");
    printf("  => ");
    scanf("%s", actionRequestCreate);
    if (actionRequestCreate[0] == 'y') {
        createBackup();
    } else {
        showOptions();
    }   
}