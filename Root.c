// Root.c

#include "SRLinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_TIMESTAMP_LENGTH 20

char continueDeviceInfos[256];
char inputRootOptions[256];
char actionLogFiles[256];
char rootCommand[MAX_LINE_LENGTH];

bool defaultP;






// ------------------------------------------ Logs ------------------------------------------


void catLogcat() {

    printf("--------------------------------------------");

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe logcat", androidPlatformToolsPath);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    printf(ANSI_DARK_ORANGE "");
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RESET"");
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen des Logcat!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
}

void saveLogcat() {

    printf("--------------------------------------------");

    char timestamp[MAX_TIMESTAMP_LENGTH];
    getTime(timestamp, sizeof(timestamp));

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe logcat -d > SRLinker_Logs/Logcat/%s_logcat.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Logs/Logcat...  " ANSI_RESET);

    int status = system("mkdir SRLinker_Logs\\Logcat");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Logcat wird gesichert...\n" ANSI_RESET);
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen des Logcat!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Logcat wurde unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'%s_logcat.txt'\n" ANSI_RESET, timestamp);
}

void saveBugReport() {

    printf("--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Bug-Report wird erstellt...\n" ANSI_RESET);

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe bugreport", androidPlatformToolsPath);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Erstellen des Bug-Reports!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Bug-Report wurde erstellt.\n" ANSI_RESET);
}

void catDumpsys() {

    printf("--------------------------------------------");

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell dumpsys", androidPlatformToolsPath);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen des Dumpsys!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
}

void saveDumpsys() {

    printf("--------------------------------------------");

    char timestamp[MAX_TIMESTAMP_LENGTH];
    getTime(timestamp, sizeof(timestamp));

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell dumpsys > SRLinker_Logs/Dumpsys/%s_dumpsys.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Logs/Dumpsys...  " ANSI_RESET);

    int status = system("mkdir SRLinker_Logs\\Dumpsys");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Dumpsys wird gesichert...\n\n" ANSI_RESET);

    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen des Dumpsys!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Dumpsys wurde unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'%s_dumpsys.txt'\n" ANSI_RESET, timestamp);
}

// Only root
void catKernelLogs() {

    printf("--------------------------------------------");

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell su -c dmesg", androidPlatformToolsPath);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen der Kernel-Logs!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
}

// Only root
void saveKernelLogs() {

    printf("--------------------------------------------");
    char timestamp[MAX_TIMESTAMP_LENGTH];
    getTime(timestamp, sizeof(timestamp));

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell su -c dmesg > SRLinker_Logs/KernelLogs/%s_kernel_logs.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Logs/KernelLogs...  " ANSI_RESET);

    int status = system("mkdir SRLinker_Logs\\KernelLogs");

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Kernel-Logs werden gesichert...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen der Kernel-Logs!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Kernel-Logs wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'%s_kernel_logs.txt'\n" ANSI_RESET, timestamp);
}

void catPackages() {

    printf("--------------------------------------------");

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell pm list packages ", androidPlatformToolsPath);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen der Packages!\n" ANSI_RESET);
    }

    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
}

void savePackages() {

    printf("--------------------------------------------");
    char timestamp[MAX_TIMESTAMP_LENGTH];
    getTime(timestamp, sizeof(timestamp));

    char adbDevicesCommand[MAX_LINE_LENGTH];
    sprintf(adbDevicesCommand, "%s/adb.exe shell pm list packages > SRLinker_Logs/Packages/%s_packages.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Logs/Packages...  " ANSI_RESET);

    int status = system("mkdir SRLinker_Logs\\Packages");

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Packages werden gesichert...   \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");

    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen der Packages!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Packages wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'%s_packages.txt'\n" ANSI_RESET, timestamp);
}

// Only root
void saveAllFromDataLog() {
    
    printf("--------------------------------------------");
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Sicherung von Logs aus /data/log/..." ANSI_RESET);
    
    char adbDevicesCommand[MAX_LINE_LENGTH];
    char copyCommand[MAX_LINE_LENGTH];
    char rootCommand[MAX_LINE_LENGTH];
    char deleteCommand[MAX_LINE_LENGTH];

    sprintf(adbDevicesCommand, "%s/adb.exe shell su -c 'mkdir -p /sdcard/SRLinker_data_log'", androidPlatformToolsPath);
    sprintf(copyCommand, "%s/adb.exe shell su -c 'cp /data/log/* /sdcard/SRLinker_data_log'", androidPlatformToolsPath);
    sprintf(rootCommand, "%s/adb.exe pull /sdcard/SRLinker_data_log SRLinker_Logs", androidPlatformToolsPath);
    sprintf(deleteCommand, "%s/adb.exe shell su -c 'rm -r /sdcard/SRLinker_data_log'", androidPlatformToolsPath);
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Logs/...  " ANSI_RESET);

    int status = system("mkdir SRLinker_Logs");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis /sdcard/SRLinker_data_log...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(adbDevicesCommand, "r");
    
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler Erstellen des Verzeichnisses /sdcard/SRLinker_data_log!\n" ANSI_RESET);
    }

    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE"\n  => Start Kopieren der Logs aus /data/log/ auf die SD-Karte...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* copyOutput;
    char copyOutputLine[MAX_LINE_LENGTH];
    copyOutput = popen(copyCommand, "r");

    if (!copyOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Kopieren der Logs aus /data/log/ auf die SD-Karte!\n" ANSI_RESET);
    }

    pclose(copyOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Start pull von /sdcard/SRLinker_data_log/ auf den PC...  " ANSI_RESET);
    printf(ANSI_RED "");
    FILE* rootOutput;
    char rootOutputLine[MAX_LINE_LENGTH];
    rootOutput = popen(rootCommand, "r");

    if (!rootOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Pullen der Logs aus /sdcard/SRLinker_data_log!\n" ANSI_RESET);
    }

    pclose(rootOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Start Loeschen der Logs aus /sdcard/SRLinker_data_log...  "ANSI_RESET);
    printf(ANSI_RED "");
    FILE* deleteOutput;
    char deleteOutputLine[MAX_LINE_LENGTH];
    deleteOutput = popen(deleteCommand, "r");

    if (!deleteOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Loeschen der Logs aus /sdcard/SRLinker_data_log!\n" ANSI_RESET);
    }

    pclose(deleteOutput);
    printf(ANSI_RESET"");
        
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Logs wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Logs/SRLinker_data_log'\n" ANSI_RESET);
}

// Only root
void saveAllLogDatas() {
    
    printf("--------------------------------------------");
    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Sicherung aller .log-Dateien..." ANSI_RESET);
    
    char createFolderCommand[MAX_LINE_LENGTH];
    char createFolderOnAndroidCommand[MAX_LINE_LENGTH];
    char findCommand[MAX_LINE_LENGTH];
    char copyCommand[MAX_LINE_LENGTH];
    char pullCommand[MAX_LINE_LENGTH];
    char deleteCommand[MAX_LINE_LENGTH];

    sprintf(createFolderCommand, "mkdir SRLinker_logs");
    sprintf(createFolderOnAndroidCommand, "%s/adb.exe shell su -c 'mkdir -p /sdcard/SRLinker_logs'", androidPlatformToolsPath);
    sprintf(findCommand, "%s/adb.exe shell su -c 'find -name *.log' > SRLinker_logs/findQuerries.txt", androidPlatformToolsPath);
    sprintf(pullCommand, "%s/adb.exe pull /sdcard/SRLinker_logs SRLinker_logs", androidPlatformToolsPath);
    sprintf(deleteCommand, "%s/adb.exe shell su -c 'rm -r /sdcard/SRLinker_logs'", androidPlatformToolsPath);
    

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_logs/...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* createFolderOutput;
    char createFolderOutputLine[MAX_LINE_LENGTH];
    createFolderOutput = popen(createFolderCommand, "r");

    if (!createFolderOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Erstellen des Verzeichnisses SRLinker_logs!\n" ANSI_RESET);
    }

    pclose(createFolderOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE"\n  => Erstelle Verzeichnis /sdcard/SRLinker_logs auf Android-Device...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* createFolderOnAndroidOutput;
    char createFolderOnAndroidOutputLine[MAX_LINE_LENGTH];
    createFolderOnAndroidOutput = popen(createFolderOnAndroidCommand, "r");

    if (!createFolderOnAndroidOutput) {
        printf(ANSI_RED"\n\n  => Fehler beim Erstellen des Verzeichnisses /sdcard/SRLinker_logs auf Android-Device!\n" ANSI_RESET);
    }

    pclose(createFolderOnAndroidOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Suche nach .log-Dateien...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* findOutput;
    char findOutputLine[MAX_LINE_LENGTH];
    findOutput = popen(findCommand, "r");

    if (!findOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Suchen nach .log-Dateien!\n" ANSI_RESET);
    }

    pclose(findOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Kopiervorgang der .log-Dateien auf dem Android-Device...  \n" ANSI_RESET);

    printf(ANSI_DARK_ORANGE "");
    FILE *filelist = fopen("SRLinker_logs/findQuerries.txt", "r");

    if (filelist == NULL) {
        printf(ANSI_RED"\n\n  => Fehler beim Öffnen der Datei mit den Dateipfaden!\n" ANSI_RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), filelist)) {

        strtok(line, "\n");

        sprintf(copyCommand, "%s/adb.exe shell su -c 'cp -r \"%s\" /sdcard/SRLinker_logs/'", androidPlatformToolsPath, line);

        printf(ANSI_DARK_ORANGE "\nKopiere %s...  "ANSI_RESET, line);
        printf(ANSI_RED "");
        FILE* copyOutput;
        char copyOutputLine[MAX_LINE_LENGTH];
        copyOutput = popen(copyCommand, "r");

        if (!copyOutput) {
            printf(ANSI_RED "\n\n  => Fehler beim Kopieren der Datei %s!\n"ANSI_RESET, line);
        }

        pclose(copyOutput);
        printf(ANSI_RESET"");
    }

    fclose(filelist);
    printf(ANSI_RESET"");

    printf("\n\n-----------------------------------------------------------------------");

    printf(ANSI_LIGHT_STEEL_BLUE"\n\n  => Starte pull der .log-Dateien in 'SRLinker_logs/'...  " ANSI_RESET);
    printf(ANSI_DARK_ORANGE "");
    FILE* pullOutput;
    char pullOutputLine[MAX_LINE_LENGTH];
    pullOutput = popen(pullCommand, "r");
    
    if (!pullOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Pullen der .log-Dateien in 'SRLinker_logs/'!\n" ANSI_RESET);
    }

    pclose(pullOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Loeschen der .log-Dateien unter SRLinker_logs/ auf Android-Device..." ANSI_RESET);
    printf(ANSI_DARK_ORANGE "");
    FILE* deleteOutput;
    char deleteOutputLine[MAX_LINE_LENGTH];
    deleteOutput = popen(deleteCommand, "r");

    if (!deleteOutput) {
        printf(ANSI_RED"\n\n  => Fehler beim Loeschen der .log-Dateien unter SRLinker_logs/ auf Android-Device!\n" ANSI_RESET);
    }

    pclose(deleteOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => .log-Dateien wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_logs/Sicherung/'\n" ANSI_RESET);
}


// ------------------------------------------ Network ------------------------------------------


void handleNetstatTulpen() {
    printf("--------------------------------------------");

    char netstatShowCommand[MAX_LINE_LENGTH];
    char netstatSaveCommand[MAX_LINE_LENGTH];
    char netstatShowWithoutRootCommand[MAX_LINE_LENGTH];
    char nestatSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(netstatSaveCommand, "%s/adb.exe shell su -c 'netstat -tulpen' > SRLinker_Netzwerk/Netstat_Tulpen/%s_netstat_tulpen_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(nestatSaveWithoutRootCommand, "%s/adb.exe shell netstat -tulpen > SRLinker_Netzwerk/Netstat_Tulpen/%s_netstat_tulpen_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Netzwerk/Netstat_Tulpen..." ANSI_RESET);

    int status = system("mkdir SRLinker_Netzwerk\\Netstat_Tulpen");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte 'netstat -tulpen' mit Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(netstatSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -tulpen!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Netstat_Tulpen/%s_netstat_tulpen_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte 'netstat -tulpen' ohne Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(nestatSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -tulpen!\n" ANSI_RESET);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Netstat_Tulpen/%s_netstat_tulpen_unroot.txt'\n" ANSI_RESET, timestamp);
    
    if (defaultP) {
        sprintf(netstatShowCommand, "%s/adb.exe shell su -c 'netstat -tulpen'", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von netstat -tulpen mit Root-Permissions:\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(netstatShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -tulpen!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        sprintf(netstatShowWithoutRootCommand, "%s/adb.exe shell netstat -tulpen", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von netstat -tulpen ohne Root-Permissions:\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(netstatShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED"\n\n  => Fehler beim Auslesen von netstat -tulpen!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handleNetstatShowRoutingTable() {
    printf("--------------------------------------------");

    char netstatShowCommand[MAX_LINE_LENGTH];
    char netstatSaveCommand[MAX_LINE_LENGTH];
    char netstatSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char netstatShowWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(netstatSaveCommand, "%s/adb.exe shell su -c 'netstat -r' > SRLinker_Netzwerk/Netstat_Routing/%s_netstat_routing_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(netstatSaveWithoutRootCommand, "%s/adb.exe shell netstat -r > SRLinker_Netzwerk/Netstat_Routing/%s_netstat_routing_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Netzwerk/Netstat_Routing...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Netzwerk\\Netstat_Routing");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte netstat -r... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(netstatSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -r!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Netstat_Routing/%s_netstat_routing_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte netstat -r ohne Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(netstatSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -r!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Netstat_Routing/%s_netstat_routing_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        char netstatShowCommand[MAX_LINE_LENGTH];
        sprintf(netstatShowCommand, "%s/adb.exe shell su -c 'netstat -r'", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE"\n  => Ausgabe von netstat -r:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(netstatShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -r!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        char netstatShowWithoutRootCommand[MAX_LINE_LENGTH];
        sprintf(netstatShowWithoutRootCommand, "%s/adb.exe shell netstat -r", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von netstat -r ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(netstatShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von netstat -r!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handleIfconfig() {
    printf("--------------------------------------------");

    char ifconfigShowCommand[MAX_LINE_LENGTH];
    char ifconfigSaveCommand[MAX_LINE_LENGTH];
    char ifconfigShowWithoutRootCommand[MAX_LINE_LENGTH];
    char ifconfigSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(ifconfigSaveCommand, "%s/adb.exe shell su -c 'ifconfig' > SRLinker_Netzwerk/Ifconfig/%s_ifconfig_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(ifconfigSaveWithoutRootCommand, "%s/adb.exe shell ifconfig > SRLinker_Netzwerk/Ifconfig/%s_ifconfig_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE"\n  => Erstelle Verzeichnis SRLinker_Netzwerk/Ifconfig...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Netzwerk\\Ifconfig");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ifconfig... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(ifconfigSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ifconfig!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Ifconfig/%s_ifconfig_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE"\n  => Starte ifconfig ohne Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(ifconfigSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ifconfig!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Ifconfig/%s_ifconfig_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        char ifconfigShowCommand[MAX_LINE_LENGTH];
        sprintf(ifconfigShowCommand, "%s/adb.exe shell su -c 'ifconfig'", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von ifconfig:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(ifconfigShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED"\n\n  => Fehler beim Auslesen von ifconfig!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        char ifconfigShowWithoutRootCommand[MAX_LINE_LENGTH];
        sprintf(ifconfigShowWithoutRootCommand, "%s/adb.exe shell ifconfig", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n=> Ausgabe von ifconfig ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(ifconfigShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n=> Fehler beim Auslesen von ifconfig!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handleIpAddrShow() {
    printf("--------------------------------------------");

    char ipAddrShowCommand[MAX_LINE_LENGTH];
    char ipAddrSaveCommand[MAX_LINE_LENGTH];
    char ipAddrShowWithoutRootCommand[MAX_LINE_LENGTH];
    char ipAddrSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(ipAddrSaveCommand, "%s/adb.exe shell su -c 'ip addr show' > SRLinker_Netzwerk/IpAddr/%s_ip_addr_show_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(ipAddrSaveWithoutRootCommand, "%s/adb.exe shell ip addr show > SRLinker_Netzwerk/IpAddr/%s_ip_addr_show_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Netzwerk/IpAddr...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Netzwerk\\IpAddr");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ip addr show... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(ipAddrSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip addr show!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/IpAddr/%s_ip_addr_show_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ip addr show ohne Root-Permissions...\n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(ipAddrSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip addr show!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/IpAddr/%s_ip_addr_show_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        char ipAddrShowCommand[MAX_LINE_LENGTH];
        sprintf(ipAddrShowCommand, "%s/adb.exe shell su -c 'ip addr show'", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von ip addr show:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(ipAddrShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip addr show!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von ip addr show ohne Root-Permissions:\n\n\n" ANSI_RESET);

        char ipAddrShowWithoutRootCommand[MAX_LINE_LENGTH];
        sprintf(ipAddrShowWithoutRootCommand, "%s/adb.exe shell ip addr show", androidPlatformToolsPath);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(ipAddrShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip addr show!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

// Only root
void handleIpTables() {
    printf("--------------------------------------------");

    char ipTablesShowCommand[MAX_LINE_LENGTH];
    char ipTablesSaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(ipTablesSaveCommand, "%s/adb.exe shell su -c 'iptables -L' > SRLinker_Netzwerk/IpTables/iptables_%s.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Netzwerk/IpTables...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Netzwerk\\IpTables");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte iptables -L...  " ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(ipTablesSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von iptables -L!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/IpTables/iptables_%s.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        char ipTablesShowCommand[MAX_LINE_LENGTH];
        sprintf(ipTablesShowCommand, "%s/adb.exe shell su -c 'iptables -L'", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von iptables -L:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(ipTablesShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von iptables -L!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");
    }
}

// Only root
void handleIpv6Tables() {
    printf("--------------------------------------------");

    char ip6TablesShowCommand[MAX_LINE_LENGTH];
    char ip6TablesSaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(ip6TablesSaveCommand, "%s/adb.exe shell su -c 'ip6tables -L' > SRLinker_Netzwerk/Ip6Tables/ip6tables_%s.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Netzwerk/Ip6Tables...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Netzwerk\\Ip6Tables");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ip6tables -L..." ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(ip6TablesSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip6tables -L!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Netzwerk/Ip6Tables/ip6tables_%s.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        char ip6TablesShowCommand[MAX_LINE_LENGTH];
        sprintf(ip6TablesShowCommand, "%s/adb.exe shell su -c 'ip6tables -L'", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von ip6tables -L:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(ip6TablesShowCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ip6tables -L!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");
    }
}


// ------------------------------------------ Processes ------------------------------------------


void handlePsTree() {
    printf("--------------------------------------------");

    char psTreeCommand[MAX_LINE_LENGTH];
    char psTreeSaveCommand[MAX_LINE_LENGTH];
    char psTreeWithoutRootCommand[MAX_LINE_LENGTH];
    char psTreeSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(psTreeSaveCommand, "%s/adb.exe shell su -c 'pstree' > SRLinker_Prozesse/PSTree/%s_pstree_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(psTreeSaveWithoutRootCommand, "%s/adb.exe shell pstree > SRLinker_Prozesse/PSTree/%s_pstree_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n=> Erstelle Verzeichnis SRLinker_Prozesse...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Prozesse\\PSTree");

    printf(ANSI_LIGHT_STEEL_BLUE "\n=> Starte pstree mit Root-Permissions...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(psTreeSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von pstree!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PSTree/%s_pstree_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte pstree ohne Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(psTreeSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von pstree!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PSTree/%s_pstree_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        sprintf(psTreeCommand, "%s/adb.exe shell su -c 'pstree'", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von pstree:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(psTreeCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von pstree!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        sprintf(psTreeWithoutRootCommand, "%s/adb.exe shell pstree", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von pstree ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(psTreeWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von pstree!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handlePs() {
    printf("--------------------------------------------");

    char psCommand[MAX_LINE_LENGTH];
    char psSaveCommand[MAX_LINE_LENGTH];
    char psShowWithoutRootCommand[MAX_LINE_LENGTH];
    char psSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(psSaveCommand, "%s/adb.exe shell su -c 'ps' > SRLinker_Prozesse/PS/%s_ps_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(psSaveWithoutRootCommand, "%s/adb.exe shell ps > SRLinker_Prozesse/PS/%s_ps_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Prozesse...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Prozesse\\PS");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ps with root permissions...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(psSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED"\n\n  => Fehler beim Auslesen von ps!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PS/%s_ps_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ps without root permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(psSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ps!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PS/%s_ps_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        sprintf(psCommand, "%s/adb.exe shell su -c 'ps'", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von ps:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(psCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ps!\n" ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        sprintf(psShowWithoutRootCommand, "%s/adb.exe shell ps", androidPlatformToolsPath);

        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von ps ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(psShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n=> Fehler beim Auslesen von ps!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handlePsEF() {
    printf("--------------------------------------------");

    char psEFCommand[MAX_LINE_LENGTH];
    char psEFSaveCommand[MAX_LINE_LENGTH];
    char psEFShowWithoutRootCommand[MAX_LINE_LENGTH];
    char psEFSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];


    getTime(timestamp, sizeof(timestamp));

    sprintf(psEFSaveCommand, "%s/adb.exe shell su -c 'ps -ef' > SRLinker_Prozesse/PSEF/%s_ps_ef_root.txt", androidPlatformToolsPath, timestamp);
    sprintf(psEFSaveWithoutRootCommand, "%s/adb.exe shell ps -ef > SRLinker_Prozesse/PSEF/%s_ps_ef_unroot.txt", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Prozesse...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Prozesse\\PSEF");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ps -ef mit Root-Permissions...  \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(psEFSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ps -ef!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PSEF/%s_ps_ef_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte ps -ef ohne Root-Permissions... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(psEFSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ps -ef!\n" ANSI_RESET);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/PSEF/%s_ps_ef_unroot.txt'\n" ANSI_RESET, timestamp);

    if (defaultP) {
        sprintf(psEFCommand, "%s/adb.exe shell su -c 'ps -ef'", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von ps -ef:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(psEFCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von ps -ef!\n " ANSI_RESET);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        sprintf(psEFShowWithoutRootCommand, "%s/adb.exe shell ps -ef", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von ps -ef ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(psEFShowWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n => Fehler beim Auslesen von ps -ef!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}

void handleTop() {
    printf("--------------------------------------------");

    char topCommand[MAX_LINE_LENGTH];
    char topSaveCommand[MAX_LINE_LENGTH];
    char topWithoutRootCommand[MAX_LINE_LENGTH];
    char topSaveWithoutRootCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];
    char topCount[MAX_TIMESTAMP_LENGTH];
    bool showResults = true;

    getTime(timestamp, sizeof(timestamp));

    if (!defaultP) {
        strcpy(topCount, "1");
        showResults = false;
    } else {
        printf(ANSI_LIGHT_STEEL_BLUE "\n  Anzahl der Ausgaben von top eingeben:\n");
        printf("  => " ANSI_RESET);
        scanf("%s", topCount);
    }

    sprintf(topSaveCommand, "%s/adb.exe shell su -c 'top -n %s -b -H' > SRLinker_Prozesse/Top/%s_top_root.txt", androidPlatformToolsPath, topCount, timestamp);
    sprintf(topSaveWithoutRootCommand, "%s/adb.exe shell top -n %s -b -H > SRLinker_Prozesse/Top/%s_top_unroot.txt", androidPlatformToolsPath, topCount, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Prozesse...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Prozesse\\Top");
    
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte top -n %s mit Root-Permissions...  \n"ANSI_RESET, topCount);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(topSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von top -n %s!\n"ANSI_RESET, topCount);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/Top/%s_top_root.txt'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte top -n %s ohne Root-Permissions...  \n"ANSI_RESET, topCount);
    printf(ANSI_RED "");
    FILE* adbOutputWithoutRoot;
    char outputLineWithoutRoot[MAX_LINE_LENGTH];
    adbOutputWithoutRoot = popen(topSaveWithoutRootCommand, "r");
    if (!adbOutputWithoutRoot) {
        printf(ANSI_RED "\n\n  => Fehler beim Auslesen von top -n %s!\n"ANSI_RESET, topCount);
    }
    while (fgets(outputLineWithoutRoot, MAX_LINE_LENGTH, adbOutputWithoutRoot)) {
        printf("%s", outputLineWithoutRoot);
    }
    pclose(adbOutputWithoutRoot);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Prozesse/Top/%s_top_unroot.txt'\n" ANSI_RESET, timestamp);

    if (showResults) {
        sprintf(topCommand, "%s/adb.exe shell su -c 'top -n 1 -b -H'", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe von top -n %s:\n\n\n"ANSI_RESET, topCount);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShow;
        char outputLineShow[MAX_LINE_LENGTH];
        adbOutputShow = popen(topCommand, "r");
        if (!adbOutputShow) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von top -n %s!\n"ANSI_RESET, topCount);
        }
        while (fgets(outputLineShow, MAX_LINE_LENGTH, adbOutputShow)) {
            printf("%s", outputLineShow);
        }
        pclose(adbOutputShow);
        printf(ANSI_RESET"");

        sprintf(topWithoutRootCommand, "%s/adb.exe shell top -n 1 -b -H", androidPlatformToolsPath);
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n\n\n  => Ausgabe von top -n 1 ohne Root-Permissions:\n\n\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutputShowWithoutRoot;
        char outputLineShowWithoutRoot[MAX_LINE_LENGTH];
        adbOutputShowWithoutRoot = popen(topWithoutRootCommand, "r");
        if (!adbOutputShowWithoutRoot) {
            printf(ANSI_RED "\n\n  => Fehler beim Auslesen von top -n 1!\n" ANSI_RESET);
        }
        while (fgets(outputLineShowWithoutRoot, MAX_LINE_LENGTH, adbOutputShowWithoutRoot)) {
            printf("%s", outputLineShowWithoutRoot);
        }
        pclose(adbOutputShowWithoutRoot);
        printf(ANSI_RESET"");
    }
}


// ------------------------------------------ APKs ------------------------------------------


void installAPKs() {
    printf("--------------------------------------------");

    char apkPath[MAX_LINE_LENGTH];
    char apkInstallCommand[MAX_LINE_LENGTH];

    printf(ANSI_DARK_ORANGE "\n\n  * Info: Die APK-Datei muss sich im gleichen Verzeichnis wie das Tool befinden.");
    printf("\n  * Beispiel ohne Unterordner: 'MyApp.apk'");
    printf("\n  * Beispiel mit Unterordner: 'MyFolder/MyApp.apk'\n" ANSI_RESET);

    printf("\n----------------------------------------------------\n");
    printf("\n  Pfad zur APK-Datei eingeben:\n");
    printf("  => ");
    scanf("%s", apkPath);

    sprintf(apkInstallCommand, "%s/adb.exe install %s", androidPlatformToolsPath, apkPath);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Installation von %s... \n" ANSI_RESET, apkPath);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(apkInstallCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED"\n\n  => Fehler beim Installieren von %s!\n" ANSI_RESET, apkPath);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Installation von %s beendet." ANSI_RESET, apkPath);
}

void uninstallAPKs() {
    printf("--------------------------------------------");

    char apkName[MAX_LINE_LENGTH];
    char apkUninstallCommand[MAX_LINE_LENGTH];

    // Informationen für den Benutzer
    printf(ANSI_DARK_ORANGE "\n\n  * Info: Der Name der APK-Datei unter Android ist nicht '.apk'.");
    printf("\n  * Mit der Option [1] koennen die Packages auch erst angezeigt werden.'");
    printf("\n  * Beispiel: 'com.example.myapp'" ANSI_RESET);

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  Name der APK-Datei eingeben\n");
    printf("  oder\n" ANSI_RESET);
    printf(ANSI_DARK_ORANGE "  [1]" ANSI_RESET " Packages anzeigen\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", apkName);

    if (apkName[0] == '1') {
        catPackages();
        printf("\n\n  Name der APK-Datei eingebe:\n");
        printf("  => ");
        scanf("%s", apkName);
    }


    sprintf(apkUninstallCommand, "%s/adb.exe uninstall %s", androidPlatformToolsPath, apkName);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Deinstallation von %s... \n"ANSI_RESET, apkName);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(apkUninstallCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Deinstallieren von %s!\n"ANSI_RESET, apkName);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Deinstallation von %s beendet."ANSI_RESET, apkName);

}

void updateAPKs() {
    printf("--------------------------------------------");

    char apkPath[MAX_LINE_LENGTH];
    char apkUpdateCommand[MAX_LINE_LENGTH];

    printf(ANSI_DARK_ORANGE "\n\n  * Bitte beachten: Die APK-Datei muss sich im gleichen Verzeichnis wie das Tool befinden.");
    printf("\n  * Beispiel ohne Unterordner: 'MyApp.apk'");
    printf("\n  * Beispiel mit Unterordner: 'MyFolder/MyApp.apk'\n" ANSI_RESET);

    printf("\n----------------------------------------------------\n");
    
    printf("\n  Pfad zur APK-Datei eingeben:\n");
    printf("  => ");
    scanf("%s", apkPath);

    sprintf(apkUpdateCommand, "%s/adb.exe install -r %s", androidPlatformToolsPath, apkPath);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Update von %s... \n"ANSI_RESET, apkPath);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(apkUpdateCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Updaten von %s!\n"ANSI_RESET, apkPath);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Update von %s beendet."ANSI_RESET, apkPath);
}

// Only root
void backupAPKs() {
    printf("--------------------------------------------");

    char apkName[MAX_LINE_LENGTH];
    char apkSaveTmpInSdcardCommand[MAX_LINE_LENGTH];
    char apkBackupCommand[MAX_LINE_LENGTH];
    char deleteTmpCommand[MAX_LINE_LENGTH];

    // Informationen für den Benutzer
    printf(ANSI_DARK_ORANGE "\n\n  * Bitte beachten: Der Name der APK-Datei unter Android ist nicht '.apk'.");
    printf("\n  * Mit der Option [1] koennen die Packages auch erst angezeigt werden.'");
    printf("\n  * Beispiel: 'com.example.myapp'");
    printf("\n  * Es wird das Package unter '/data/data/' gesichert." ANSI_RESET);

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  Name der APK-Datei eingeben\n");
    printf("  oder\n" ANSI_RESET);
    printf(ANSI_DARK_ORANGE "  [1]" ANSI_RESET " Packages anzeigen'\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", apkName);


    if (apkName[0] == '1') {
        catPackages();
        printf("\n\n  Name der APK-Datei eingeben:\n");
        printf("  => ");
        scanf("%s", apkName);
    }


    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_App_Sicherungen... " ANSI_RESET);
    int status = system("mkdir SRLinker_App_Sicherungen");

    sprintf(apkSaveTmpInSdcardCommand, "%s/adb.exe shell su -c 'cp -r /data/data/%s /sdcard/'", androidPlatformToolsPath, apkName);
    sprintf(apkBackupCommand, "%s/adb.exe pull /sdcard/%s SRLinker_App_Sicherungen/%s", androidPlatformToolsPath, apkName, apkName);
    sprintf(deleteTmpCommand, "%s/adb.exe shell su -c 'rm -r /sdcard/%s'", androidPlatformToolsPath, apkName);


    printf(ANSI_LIGHT_STEEL_BLUE "\n=> Starte Sicherung von %s in /sdcard/...  \n"ANSI_RESET, apkName);
    printf(ANSI_RED "");
    FILE* adbSicherung;
    char outputLineSicherung[MAX_LINE_LENGTH];
    adbSicherung = popen(apkSaveTmpInSdcardCommand, "r");
    if (!adbSicherung) {
        printf(ANSI_RED "\n\n  => Fehler beim Sichern von %s!\n"ANSI_RESET, apkName);
    }
    while (fgets(outputLineSicherung, MAX_LINE_LENGTH, adbSicherung)) {
        printf("%s", outputLineSicherung);
    }
    pclose(adbSicherung);
    printf(ANSI_RESET"");



    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Pull von %s... \n"ANSI_RESET, apkName);
    printf(ANSI_RED "");
    FILE* adbPull;
    char outputLinePull[MAX_LINE_LENGTH];
    adbPull = popen(apkBackupCommand, "r");
    if (!adbPull) {
        printf(ANSI_RED "\n\n  => Fehler beim Sichern von %s!\n"ANSI_RESET, apkName);
    }
    while (fgets(outputLinePull, MAX_LINE_LENGTH, adbPull)) {
        printf("%s", outputLinePull);
    }
    pclose(adbPull);
    printf(ANSI_RESET"");



    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Loeschen von %s in /sdcard/... \n"ANSI_RESET, apkName);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(deleteTmpCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Loeschen von %s!\n"ANSI_RESET, apkName);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Sicherung von %s beendet."ANSI_RESET, apkName);
}


// ------------------------------------------ Interactions ------------------------------------------


void restartDevice() {
    printf("--------------------------------------------");

    char restartCommand[MAX_LINE_LENGTH];

    sprintf(restartCommand, "%s/adb.exe reboot", androidPlatformToolsPath);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Vorbereitung zum Neustart des Geraets... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(restartCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Neustarten des Geraets!\n " ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Neustart des Geraets wird durchgeführt." ANSI_RESET);
}

void startShell() {
    char shellCommand[MAX_LINE_LENGTH];
    char shellCommandFull[MAX_LINE_LENGTH];
    
    printf(ANSI_DARK_ORANGE "\n\n  [1]" ANSI_RESET " Shell starten\n");
    printf(ANSI_TOMATO_RED "  [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", shellCommand);

    if (shellCommand[0] == 'q') {
        handleInteractions();
    } else if (shellCommand[0] == '1') {
        sprintf(shellCommandFull, "%s/adb.exe shell", androidPlatformToolsPath, shellCommand);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Shell wird gestartet... \n"ANSI_RESET, shellCommand);
        printf(ANSI_MEDIUM_SEA_GREEN "");
        FILE* adbOutput;
        char outputLine[MAX_LINE_LENGTH];
        adbOutput = popen(shellCommandFull, "r");
        printf("\nBitte Command eingeben:\n");
        if (!adbOutput) {
            printf(ANSI_RED "\n\n  => Fehler beim Ausfuehren des Shell-Befehls!\n" ANSI_RESET);
        }
        while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
            printf("%s", outputLine);
        }
        pclose(adbOutput);
        printf(ANSI_RESET"");

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Shell beendet." ANSI_RESET);
        
        startShell();
    } else {
        printf(ANSI_RED "");
        printf("\n  Na na na, '%s' ist nicht vorgesehen.\n", shellCommand);
        printf("  Nochmal? [y/n]:\n");
        printf("  => " ANSI_RESET);
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            startShell();
        } else {
            handleInteractions();
        }
    }
}

void handleScreenshot() {
    printf("--------------------------------------------");

    char newScreenshot[MAX_LINE_LENGTH];
    char screenshotCommand[MAX_LINE_LENGTH];
    char screenshotSaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];
    char deleteScreenshotCommand[MAX_LINE_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(screenshotSaveCommand, "%s/adb.exe shell screencap -p /sdcard/screenshot_%s.png", androidPlatformToolsPath, timestamp);
    sprintf(screenshotCommand, "%s/adb.exe pull /sdcard/screenshot_%s.png SRLinker_Screenshots/screenshot_%s.png", androidPlatformToolsPath, timestamp, timestamp);
    sprintf(deleteScreenshotCommand, "%s/adb.exe shell rm /sdcard/screenshot_%s.png", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Screenshots...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Screenshots");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Screenshot... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(screenshotSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Erstellen des Screenshots!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Pull des Screenshots... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputPull;
    char outputLinePull[MAX_LINE_LENGTH];
    adbOutputPull = popen(screenshotCommand, "r");
    if (!adbOutputPull) {
        printf(ANSI_RED "\n\n  => Fehler beim Pullen des Screenshots!\n" ANSI_RESET);
    }
    while (fgets(outputLinePull, MAX_LINE_LENGTH, adbOutputPull)) {
        printf("%s", outputLinePull);
    }
    pclose(adbOutputPull);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Der Screenshot wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Screenshots/screenshot_%s.png'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Starte Loeschen des Screenshots... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputDelete;
    char outputLineDelete[MAX_LINE_LENGTH];
    adbOutputDelete = popen(deleteScreenshotCommand, "r");
    if (!adbOutputDelete) {
        printf(ANSI_RED "\n  => Fehler beim Loeschen des Screenshots!\n" ANSI_RESET);
    }
    while (fgets(outputLineDelete, MAX_LINE_LENGTH, adbOutputDelete)) {
        printf("%s", outputLineDelete);
    }
    pclose(adbOutputDelete);
    printf(ANSI_RESET"");

    printf("\n\n=> Neuer Screenshot? [y/n]:\n");
    printf("=> ");
    scanf("%s", newScreenshot);
    if (newScreenshot[0] == 'y') {
        handleScreenshot();
    } else {
        handleInteractions();
    }
}

void handleScreenrecord() {
    printf("--------------------------------------------");

    char newScreenshot[MAX_LINE_LENGTH];
    //char breakRecord[MAX_LINE_LENGTH];
    char screenrecordCommand[MAX_LINE_LENGTH];
    char screenrecordSaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];
    char deleteScreenrecordCommand[MAX_LINE_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    sprintf(screenrecordSaveCommand, "%s/adb.exe shell screenrecord /sdcard/screenrecord_%s.mp4", androidPlatformToolsPath, timestamp);
    sprintf(screenrecordCommand, "%s/adb.exe pull /sdcard/screenrecord_%s.mp4 SRLinker_Screenrecords/screenrecord_%s.mp4", androidPlatformToolsPath, timestamp, timestamp);
    sprintf(deleteScreenrecordCommand, "%s/adb.exe shell rm /sdcard/screenrecord_%s.mp4", androidPlatformToolsPath, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Screenrecords...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Screenrecords");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Screenrecord... \n" ANSI_RESET);
    printf(ANSI_LIGHT_STEEL_BLUE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(screenrecordSaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Starten des Screenrecords!\n" ANSI_RESET);
    }

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Screenrecord laeuft... \n");
    printf("\n  => Beenden? [ENTER]" ANSI_RESET);
    getchar();
    getchar();

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Beende Screenrecord... \n" ANSI_RESET);
    printf(ANSI_GREEN "");
    FILE* adbOutputBreak;
    char outputLineBreak[MAX_LINE_LENGTH];
    adbOutputBreak = popen("taskkill /IM adb.exe /F", "r");
    if (!adbOutputBreak) {
        printf(ANSI_RED "\n\n  => Fehler beim Beenden des Screenrecords!\n" ANSI_RESET);
    }
    while (fgets(outputLineBreak, MAX_LINE_LENGTH, adbOutputBreak)) {
        printf("%s", outputLineBreak);
    }
    pclose(adbOutput);
    pclose(adbOutputBreak);
    printf(ANSI_RESET"");

    refreshServerLong();

  
    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Pull des Screenrecords... \n" ANSI_RESET);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutputPull;
    char outputLinePull[MAX_LINE_LENGTH];
    adbOutputPull = popen(screenrecordCommand, "r");
    if (!adbOutputPull) {
        printf(ANSI_RED "\n\n  => Fehler beim Pullen des Screenrecords!\n" ANSI_RESET);
    }
    while (fgets(outputLinePull, MAX_LINE_LENGTH, adbOutputPull)) {
        printf("%s", outputLinePull);
    }
    pclose(adbOutputPull);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Der Screenrecord wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Screenrecords/screenrecord_%s.mp4'\n" ANSI_RESET, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Starte Loeschvorgang des Screenrecords... \n" ANSI_RESET);
    printf(ANSI_RED "");
    FILE* adbOutputDelete;
    char outputLineDelete[MAX_LINE_LENGTH];
    adbOutputDelete = popen(deleteScreenrecordCommand, "r");
    printf(ANSI_RESET"");


    printf("\n\n  => Neuer Screenrecord? [y/n]:\n");
    printf("  => ");
    scanf("%s", newScreenshot);
    if (newScreenshot[0] == 'y') {
        handleScreenrecord();
    } else {
        handleInteractions();
    }
}

void handlePhoneCall() {
    printf("--------------------------------------------");

    char phoneNumber[MAX_LINE_LENGTH];
    char phoneCallCommand[MAX_LINE_LENGTH];
    char cancleCallCommand[MAX_LINE_LENGTH];

    printf("\n\n  => Telefonnummer eingeben:\n");
    printf("  => ");
    scanf("%s", phoneNumber);

    sprintf(phoneCallCommand, "%s/adb.exe shell am start -a android.intent.action.CALL -d tel:%s", androidPlatformToolsPath, phoneNumber);
    sprintf(cancleCallCommand, "%s/adb.exe shell input keyevent KEYCODE_ENDCALL", androidPlatformToolsPath);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Telefonanruf an %s... \n"ANSI_RESET, phoneNumber);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(phoneCallCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Anrufen von %s!\n" ANSI_RESET, phoneNumber);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Anruf an %s wird durchgefuehrt...  " ANSI_RESET, phoneNumber);

    while (1) {
        printf(ANSI_LIGHT_STEEL_BLUE "\n\n  => Anruf beenden? [y/n]:\n");
        printf("  => " ANSI_RESET);
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            printf(ANSI_LIGHT_STEEL_BLUE "\n  => Beende Anruf... " ANSI_RESET);
            printf(ANSI_RED "");
            FILE* adbOutputCancle;
            char outputLineCancle[MAX_LINE_LENGTH];
            adbOutputCancle = popen(cancleCallCommand, "r");
            if (!adbOutputCancle) {
                printf(ANSI_RED "\n\n  => Fehler beim Beenden des Anrufs!\n" ANSI_RESET);
            }
            while (fgets(outputLineCancle, MAX_LINE_LENGTH, adbOutputCancle)) {
                printf("%s", outputLineCancle);
            }
            pclose(adbOutputCancle);
            printf(ANSI_RESET"");
            break;
        } else {
            printf(ANSI_LIGHT_STEEL_BLUE "\n=> Anruf wird weitergefuehrt..." ANSI_RESET);
        }
    }
    printf(ANSI_FOREST_GREEN "\n  => Anruf an %s beendet.\n" ANSI_RESET, phoneNumber);
}

void handleAndroidMonkeyForApps() {
    printf("--------------------------------------------");

    char monkeySaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];
    char monkeyPackageName[MAX_LINE_LENGTH];
    char monkeyActions[MAX_LINE_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    while (1){

        printf(ANSI_LIGHT_STEEL_BLUE "\n\n  Package-Name eingeben\n");
        printf("  oder\n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "  [1]" ANSI_RESET " Packages anzeigen\n");
        printf("\n----------------------------------------------------\n");
        printf("\n  Eingabe:\n");
        printf("  => ");
        scanf("%s", monkeyPackageName);

        if (monkeyPackageName[0] != '1') {
            printf("\n  => Anzahl der Aktionen eingeben:\n");
            printf("  => ");
            scanf("%s", monkeyActions);
            int i;
            bool isAllDigit = true;
            for (i = 0; i < strlen(monkeyActions); i++) {
                if (!isdigit(monkeyActions[i])) {
                    printf(ANSI_RED "\n  => '%s' ist keine Zahl!\n" ANSI_RESET, monkeyActions);
                    isAllDigit = false;
                    continue;
                }
            }
            if (isAllDigit) {
                break;
            } else {
                continue;
            }
        } else {
            catPackages();
            continue;
        }
    }

    sprintf(monkeySaveCommand, "%s/adb.exe shell monkey -p %s -v %s > SRLinker_Monkey_App/monkey_%s.txt", androidPlatformToolsPath, monkeyPackageName, monkeyActions, timestamp);

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Monkey_App...  " ANSI_RESET);
    int status = system("mkdir SRLinker_Monkey_App");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Monkey... \n" ANSI_RESET);
    printf(ANSI_DARK_ORANGE "");
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];
    adbOutput = popen(monkeySaveCommand, "r");
    if (!adbOutput) {
        printf(ANSI_RED "\n\n  => Fehler beim Starten des Monkeys!\n" ANSI_RESET);
    }
    while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
        printf("%s", outputLine);
    }
    pclose(adbOutput);
    printf(ANSI_RESET"");

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Monkey-Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Monkey_App/monkey_%s.txt'\n" ANSI_RESET, timestamp);
}

void handleAndroidMonkeyForSystem() {
    printf("--------------------------------------------");

    char monkeySaveCommand[MAX_LINE_LENGTH];
    char timestamp[MAX_TIMESTAMP_LENGTH];
    char monkeyActions[MAX_LINE_LENGTH];

    getTime(timestamp, sizeof(timestamp));

    printf("\n  => Anzahl der Aktionen eingeben:\n");
    printf("  => ");
    scanf("%s", monkeyActions);
    int i;
    bool isAllDigit = true;
    for (i = 0; i < strlen(monkeyActions); i++) {
        if (!isdigit(monkeyActions[i])) {
            printf(ANSI_RED "\n=> '%s' ist keine Zahl!\n" ANSI_RESET, monkeyActions);
            isAllDigit = false;
            continue;
        }
    }
    if (isAllDigit) {
        sprintf(monkeySaveCommand, "%s/adb.exe shell monkey -v %s > SRLinker_Monkey_System/monkey_%s.txt", androidPlatformToolsPath, monkeyActions, timestamp);

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_Monkey_System...  " ANSI_RESET);
        int status = system("mkdir SRLinker_Monkey_System");

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Starte Monkey... \n" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "");
        FILE* adbOutput;
        char outputLine[MAX_LINE_LENGTH];
        adbOutput = popen(monkeySaveCommand, "r");
        if (!adbOutput) {
            printf(ANSI_RED "\n\n  => Fehler beim Starten des Monkeys!\n" ANSI_RESET);
        }
        while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
            printf("%s", outputLine);
        }
        pclose(adbOutput);
        printf(ANSI_RESET"");

        printf(ANSI_LIGHT_STEEL_BLUE "\n  => Die Monkey-Results wurden unter folgendem Namen angelegt: " ANSI_RESET ANSI_DARK_ORANGE "'SRLinker_Monkey_System/monkey_%s.txt'\n" ANSI_RESET, timestamp);

    } else {
        handleAndroidMonkeyForSystem();
    }
}


// ------------------------------------------ Coordination ------------------------------------------


void handleLogFiles() {
    clearScreen();
    showLogo();
    printf(ANSI_BOLD "\n  Aktionen mit Logs:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");

    printf(ANSI_CORNFLOWER "   [1]" ANSI_RESET " Alle Logs sichern\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " Logcat anzeigen\n");
    printf(ANSI_DARK_ORANGE "   [3]" ANSI_RESET " Logcat sichern\n");
    printf(ANSI_DARK_ORANGE "   [4]" ANSI_RESET " Bug-Report erstellen\n");
    printf(ANSI_DARK_ORANGE "   [5]" ANSI_RESET " Dumpsys anzeigen\n");
    printf(ANSI_DARK_ORANGE "   [6]" ANSI_RESET " Dumpsys sichern\n");
    printf(ANSI_DARK_ORANGE "   [7]" ANSI_RESET " Kernel-Logs anzeigen (root)\n");
    printf(ANSI_DARK_ORANGE "   [8]" ANSI_RESET " Kernel-Logs sichern (root)\n");
    printf(ANSI_DARK_ORANGE "   [9]" ANSI_RESET " Packages anzeigen\n");
    printf(ANSI_DARK_ORANGE "   [a]" ANSI_RESET " Packages sichern\n");
    printf(ANSI_DARK_ORANGE "   [b]" ANSI_RESET " Sicherung von Logs aus /data/log/ (root)\n");
    printf(ANSI_DARK_ORANGE "   [c]" ANSI_RESET " Sicherung aller .log-Dateien (beta, root)\n");
    printf(ANSI_DEEP_PINK "   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED "   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", actionLogFiles);

    if (actionLogFiles[0] == 'q') {
        handleExit();

    } else if (actionLogFiles[0] == 'r') {
        showOptions();

    } else if (actionLogFiles[0] == '1') {
        refreshServer();
        saveLogcat();
        printf("\n");
        saveBugReport();
        printf("\n");
        saveDumpsys();
        printf("\n");
        saveKernelLogs();
        printf("\n");
        savePackages();
        printf("\n");
        saveAllFromDataLog();
        printf("\n");
        saveAllLogDatas();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '2') {
        refreshServer();
        catLogcat();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '3') {
        refreshServer();
        saveLogcat();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '4') {
        refreshServer();
        saveBugReport();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '5') {
        refreshServer();
        catDumpsys();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '6') {
        refreshServer();
        saveDumpsys();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '7') {
        refreshServer();
        catKernelLogs();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '8') {
        refreshServer();
        saveKernelLogs();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == '9') {
        refreshServer();
        catPackages();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == 'a') {
        refreshServer();
        savePackages();
        requestHandleLogFiles();

    } 
    else if (actionLogFiles[0] == 'b') {
        refreshServer();
        saveAllFromDataLog();
        requestHandleLogFiles();

    } else if (actionLogFiles[0] == 'c') {
        refreshServer();
        saveAllLogDatas();
        requestHandleLogFiles();
    }
    else {
        printf("\nNa na na, '%s' ist nicht vorgesehen.\n", actionLogFiles);
        printf("Nochmal? [y/n]:\n");
        printf("=> ");
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            handleLogFiles();
        } else {
            showOptions();
        }
    }
}

void handleNetwork() {
    clearScreen();
    showLogo();

    printf(ANSI_BOLD "\n  Aktionen mit Netzwerk:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");

    printf(ANSI_CORNFLOWER "   [1]" ANSI_RESET " Alles sichern\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " netstat -tulpen\n");
    printf(ANSI_DARK_ORANGE "   [3]" ANSI_RESET " netstat -r (Routing-Tabelle)\n");
    printf(ANSI_DARK_ORANGE "   [4]" ANSI_RESET " ifconfig\n");
    printf(ANSI_DARK_ORANGE "   [5]" ANSI_RESET " ip addr show\n");
    printf(ANSI_DARK_ORANGE "   [6]" ANSI_RESET " iptables -L (Firewall-Konfigurationen IPv4, root)\n");
    printf(ANSI_DARK_ORANGE "   [7]" ANSI_RESET " ip6tables -L (Firewall-Konfigurationen IPv6, root)\n");
    printf(ANSI_DEEP_PINK "   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED "   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", actionLogFiles);

    defaultP = true;

    if (actionLogFiles[0] == 'q') {
        handleExit();

    } else if (actionLogFiles[0] == 'r') {
        showOptions();

    } else if (actionLogFiles[0] == '1') {
        defaultP = false;
        refreshServer();
        handleNetstatTulpen();
        printf("\n");
        handleNetstatShowRoutingTable();
        printf("\n");
        handleIfconfig();
        printf("\n");
        handleIpAddrShow();
        printf("\n");
        handleIpTables();
        printf("\n");
        handleIpv6Tables();
        requestHandleNetwork();

    } else if (actionLogFiles[0] == '2') {
        refreshServer();
        handleNetstatTulpen();
        requestHandleNetwork();

    } else if (actionLogFiles[0] == '3') {
        refreshServer();
        handleNetstatShowRoutingTable();
        requestHandleNetwork();        

    } else if (actionLogFiles[0] == '4') {
        refreshServer();
        handleIfconfig();
        requestHandleNetwork();

    } else if (actionLogFiles[0] == '5') {
        refreshServer();
        handleIpAddrShow();
        requestHandleNetwork();

    } else if (actionLogFiles[0] == '6') {
        refreshServer();
        handleIpTables();
        requestHandleNetwork();        

    } else if (actionLogFiles[0] == '7') {
        refreshServer();
        handleIpv6Tables();
        requestHandleNetwork();      

    } else {
        printf("\nNa na na, '%s' ist nicht vorgesehen.\n", actionLogFiles);
        printf("Nochmal? [y/n]:\n");
        printf("=> ");
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            handleNetwork();
        } else {
            showOptions();
        }
    }
}

void handleProcesses() {
    clearScreen();
    showLogo();
    
    printf(ANSI_BOLD "\n  Aktionen mit Prozesse:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");

    printf(ANSI_CORNFLOWER "   [1]" ANSI_RESET " Alles sichern\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " pstree (falls verfuegbar)\n");
    printf(ANSI_DARK_ORANGE "   [3]" ANSI_RESET " ps\n");
    printf(ANSI_DARK_ORANGE "   [4]" ANSI_RESET " ps -ef\n");
    printf(ANSI_DARK_ORANGE "   [5]" ANSI_RESET " top (mit count)\n");
    printf(ANSI_DEEP_PINK "   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED "   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", actionLogFiles);

    defaultP = true;

    if (actionLogFiles[0] == 'q') {
        handleExit();

    } else if (actionLogFiles[0] == 'r') {
        showOptions();

    } else if (actionLogFiles[0] == '1') {
        defaultP = false;
        refreshServer();
        handlePsTree();
        printf("\n");
        handlePs();
        printf("\n");
        handlePsEF();
        printf("\n");
        handleTop();
        requestHandleProcesses();
        
    } else if (actionLogFiles[0] == '2') {
        refreshServer();
        handlePsTree();
        requestHandleProcesses();

    } else if (actionLogFiles[0] == '3') {
        refreshServer();
        handlePs();
        requestHandleProcesses();        

    } else if (actionLogFiles[0] == '4') {
        refreshServer();
        handlePsEF();
        requestHandleProcesses();        

    } else if (actionLogFiles[0] == '5') {
        refreshServer();
        handleTop();
        requestHandleProcesses();        

    } else {
        printf("\nNa na na, '%s' ist nicht vorgesehen.\n", actionLogFiles);
        printf("Nochmal? [y/n]:\n");
        printf("=> ");
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            handleProcesses();
        } else {
            showOptions();
        }
    }

}

void handleAPKs() {
    clearScreen();
    showLogo();
    
    printf(ANSI_BOLD "\n  Aktionen mit APKs:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");

    printf(ANSI_DARK_ORANGE "   [1]" ANSI_RESET " Installation\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " Deinstallation\n");
    printf(ANSI_DARK_ORANGE "   [3]" ANSI_RESET " Update\n");
    printf(ANSI_DARK_ORANGE "   [4]" ANSI_RESET " App-Sicherung (root)\n");
    printf(ANSI_DEEP_PINK "   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED "   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", actionLogFiles);

    defaultP = true;

    if (actionLogFiles[0] == 'q') {
        handleExit();

    } else if (actionLogFiles[0] == 'r') {
        showOptions();

    } else if (actionLogFiles[0] == '1') {
        refreshServer();
        installAPKs();
        requestHandleAPKs();

    } else if (actionLogFiles[0] == '2') {
        refreshServer();
        uninstallAPKs();
        requestHandleAPKs();

    } else if (actionLogFiles[0] == '3') {
        refreshServer();
        updateAPKs();
        requestHandleAPKs();

    } else if (actionLogFiles[0] == '4') {
        refreshServer();
        backupAPKs();
        requestHandleAPKs();

    } else {
        printf("\nNa na na, '%s' ist nicht vorgesehen.\n", actionLogFiles);
        printf("Nochmal? [y/n]:\n");
        printf("=> ");
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            handleAPKs();
        } else {
            showOptions();
        }
    }
}

void handleInteractions() {
    clearScreen();
    showLogo();
    
    printf(ANSI_BOLD "\n  Interaktionen mit dem Device:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");

    printf(ANSI_DARK_ORANGE "   [1]" ANSI_RESET " Geraeteneustart\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " Shell\n");
    printf(ANSI_DARK_ORANGE "   [3]" ANSI_RESET " Screenshot\n");
    printf(ANSI_DARK_ORANGE "   [4]" ANSI_RESET " Screenrecord\n");
    printf(ANSI_DARK_ORANGE "   [5]" ANSI_RESET " Telefonanruf starten\n");
    printf(ANSI_DARK_ORANGE "   [6]" ANSI_RESET " Android Monkey (Apps)\n");
    printf(ANSI_DARK_ORANGE "   [7]" ANSI_RESET " Android Monkey (System)\n");
    printf(ANSI_DEEP_PINK "   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED "   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", actionLogFiles);

    defaultP = true;

    if (actionLogFiles[0] == 'q') {
        handleExit();

    } else if (actionLogFiles[0] == 'r') {
        showOptions();

    } else if (actionLogFiles[0] == '1') {
        refreshServer();
        restartDevice();
        requestHandleInteractions();

    } else if (actionLogFiles[0] == '2') {
        refreshServer();
        printf("--------------------------------------------");
        printf(ANSI_DARK_ORANGE "\n\n  * Die Shell wird nicht im Root-Modus gestartet.\n");
        printf("  * Es wird eine Shell auf das Android-Device erstellt. Falls Root-Rechte vorliegen, kann mit dem Command 'su' zu Root gewechselt werden.\n");
        printf("  * Die Eingabe findet invisible statt, lediglich die Ausgabe wird angezeigt. Sobalt 'Bitte Command eingeben:' erscheint, kann mit dem Device interagiert werden.\n");
        printf("  * Fuer eine bessere Nutzung der Shell wird empfohlen, das Geraet direkt mit Hilfe von '.\\adb.exe shell' zu verbinden.\n");
        printf("  * Mit 'exit' wird die laufende Verbindung beendet.\n" ANSI_RESET);
        printf(ANSI_LIGHT_STEEL_BLUE "  * Beispiel: 'su'\n");
        printf("  * Beispiel: 'ls -la'\n" ANSI_RESET);
        startShell();
        requestHandleInteractions();       

    } else if (actionLogFiles[0] == '3') {
        refreshServer();
        handleScreenshot();
        requestHandleInteractions();        

    } else if (actionLogFiles[0] == '4') {
        refreshServer();
        handleScreenrecord();
        requestHandleInteractions();        

    } else if (actionLogFiles[0] == '5') {
        refreshServer();
        handlePhoneCall();
        requestHandleInteractions();        

    } else if (actionLogFiles[0] == '6') {
        refreshServer();
        handleAndroidMonkeyForApps();
        requestHandleInteractions();        

    } else if (actionLogFiles[0] == '7') {
        refreshServer();
        handleAndroidMonkeyForSystem();
        requestHandleInteractions();        

    } else {
        printf("\nNa na na, '%s' ist nicht vorgesehen.\n", actionLogFiles);
        printf("Nochmal? [y/n]:\n");
        printf("=> ");
        scanf("%s", actionLogFiles);
        if (actionLogFiles[0] == 'y') {
            handleInteractions();
        } else {
            showOptions();
        }
    }
}


// ------------------------------------------ Base ------------------------------------------


void showOptions() {
    clearScreen();
    showLogo();

    printf(ANSI_BOLD "\n  Optiere eine Kategorie oder Aktion:" ANSI_RESET_BOLD);
    printf("\n----------------------------------------------------\n\n");
    printf(ANSI_CORNFLOWER "   [a]" ANSI_RESET " Rundum-sorglos-Paket \n");
    printf(ANSI_DARK_ORANGE "   [1]" ANSI_RESET " ADB-Server startet\n");
    printf(ANSI_DARK_ORANGE "   [2]" ANSI_RESET " ADB-Server beenden\n");
    printf(ANSI_DARK_ORANGE"   [3]" ANSI_RESET " Geraeteinfos\n");
    printf(ANSI_DARK_ORANGE"   [4]" ANSI_RESET " Logdateien\n");
    printf(ANSI_DARK_ORANGE"   [5]" ANSI_RESET " Netzwerk\n");
    printf(ANSI_DARK_ORANGE"   [6]" ANSI_RESET " Prozesse\n");
    printf(ANSI_DARK_ORANGE"   [7]" ANSI_RESET " APKs\n");
    printf(ANSI_DARK_ORANGE"   [8]" ANSI_RESET " Interaktionen\n");
    printf(ANSI_DARK_ORANGE"   [9]" ANSI_RESET " Backup erstellen\n");
    printf(ANSI_DARK_ORANGE"   [0]" ANSI_RESET " Backup wiederherstellen\n");
    printf(ANSI_DEEP_PINK"   [r]" ANSI_RESET " Return\n");
    printf(ANSI_TOMATO_RED"   [q]" ANSI_RESET " Exit\n");
    printf("\n----------------------------------------------------\n");
    printf("\n  Eingabe:\n");
    printf("  => ");
    scanf("%s", inputRootOptions);

    defaultP = true;

    if (inputRootOptions[0] == 'q') {
        handleExit();

    } else if (inputRootOptions[0] == 'r') {
        printf("Eingabe: %s (Return)\n\n", inputRootOptions);
        main();

    } else if (inputRootOptions[0] == 'a') {
        defaultP = false;
        refreshServer();

        // Device Infos
        showDeviceInfos();
        printf("\n");

        // Log Files
        saveLogcat();
        printf("\n");
        saveBugReport();
        printf("\n");
        saveDumpsys();
        printf("\n");
        saveKernelLogs();
        printf("\n");
        savePackages();
        printf("\n");
        saveAllFromDataLog();
        printf("\n");
        saveAllLogDatas();
        printf("\n");

        // Network
        handleNetstatTulpen();
        printf("\n");
        handleNetstatShowRoutingTable();
        printf("\n");
        handleIfconfig();
        printf("\n");
        handleIpAddrShow();
        printf("\n");
        handleIpTables();
        printf("\n");
        handleIpv6Tables();
        printf("\n");

        // Processes
        handlePsTree();
        printf("\n");
        handlePs();
        printf("\n");
        handlePsEF();
        printf("\n");
        handleTop();
        printf("\n");

        printf(ANSI_MEDIUM_SEA_GREEN "\n\n  => Rundum-sorglos-Paket beendet.\n" ANSI_RESET);

        printf("\n\n\n----------------------------------------------------\n");

        printf(ANSI_MEDIUM_SEA_GREEN "\n  * Es wurden die folgenden Aktionen durchgefuehrt: \n" ANSI_RESET);
        
        printf(ANSI_DARK_ORANGE "\n\n  ** Kategorie: Geraeteinformationen" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "\n     --> Geraeteinformationen\n" ANSI_RESET);

        printf(ANSI_DARK_ORANGE "\n\n  ** Kategorie: Logdateien" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "\n     --> Logcat");
        printf("\n     --> Bug-Report");
        printf("\n     --> Dumpsys");
        printf("\n     --> Kernel-Logs (root)");
        printf("\n     --> Packages");
        printf("\n     --> Alle Logs aus /data/log/ (root)");
        printf("\n     --> Sicherung aller .log-Dateien (beta, root)" ANSI_RESET);

        printf(ANSI_DARK_ORANGE "\n\n  ** Kategorie: Netzwerk" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "\n     --> netstat -tulpen");
        printf("\n     --> netstat -r");
        printf("\n     --> ifconfig");
        printf("\n     --> ip addr show");
        printf("\n     --> iptables -L (root)");
        printf("\n     --> ip6tables -L (root)" ANSI_RESET);

        printf(ANSI_DARK_ORANGE "\n\n  ** Kategorie: Prozesse" ANSI_RESET);
        printf(ANSI_DARK_ORANGE "\n     --> pstree (falls verfuegbar)");
        printf("\n     --> ps");
        printf("\n     --> ps -ef");
        printf("\n     --> top" ANSI_RESET);

        printf(ANSI_MEDIUM_SEA_GREEN "\n\n  ** Alle Resultate wurden in den jeweiligen Unterordnern im Pfad '.../SRLinker/...' angelegt.\n" ANSI_RESET);

        printf("\n----------------------------------------------------\n");
        printf("\n\n  [y] Weitere Aktionen");
        printf("\n  [q] Programm beenden\n");
        printf("  => ");
        scanf("%s", inputRootOptions);
        if (inputRootOptions[0] == 'y') {
            showOptions();
        } else {
            handleExit();
            exit(0);
        }
    } else if (inputRootOptions[0] == '1') {
        handleServerStart();

    } else if (inputRootOptions[0] == '2') {
        handleServerKill();        

    } else if (inputRootOptions[0] == '3') {
        refreshServer();
        showDeviceInfos();        

    } else if (inputRootOptions[0] == '4') {
        handleLogFiles();
        
    } else if (inputRootOptions[0] == '5') {
        handleNetwork();        
        
    } else if (inputRootOptions[0] == '6') {
        handleProcesses();       
        
    } else if (inputRootOptions[0] == '7') {
        handleAPKs();        
        
    } else if (inputRootOptions[0] == '8') {
        handleInteractions();        
        
    } else if (inputRootOptions[0] == '9') {
        refreshServer();
        createBackup();  
        
    } else if (inputRootOptions[0] == '0') {
        refreshServer();
        restoreBackup();        
        
    } else {
        printf("\n----------------------------------------------------\n");
        printf("\n  Na na na, '%s' ist nicht vorgesehen.\n", inputRootOptions);
        printf("  Nochmal? [y/n]:\n");
        printf("  => ");
        scanf("%s", inputRootOptions);
        if (inputRootOptions[0] == 'y') {
            showOptions();
        } else {
            main();
        }
    }
}
