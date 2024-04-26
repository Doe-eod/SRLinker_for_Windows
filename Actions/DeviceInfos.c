// DeviceInfos.c

#include "../SRLinker.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_TIMESTAMP_LENGTH 20




void showDeviceInfos() {

    printf("--------------------------------------------");

    char timestamp[MAX_TIMESTAMP_LENGTH];
    getTime(timestamp, sizeof(timestamp));

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Erstelle Verzeichnis SRLinker_DeviceInfos/... " ANSI_RESET);

    int status = system("mkdir SRLinker_DeviceInfos");


    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Sicherung der Geraeteinfos wird erstellt... \n" ANSI_RESET);
    char deviceInfosCommand[MAX_LINE_LENGTH];
    sprintf(deviceInfosCommand, "%s/adb.exe shell getprop > SRLinker_DeviceInfos/%s_deviceInfos.txt", androidPlatformToolsPath, timestamp);
    FILE* adbOutputSave;
    char outputLineSave[MAX_LINE_LENGTH];

    const char* deviceInfos1[] = {
        "ro.product.model",
        "ro.product.manufacturer",
        "ro.product.brand",
        "ro.product.name",
        "ro.product.device",
        "ro.product.board",
        "ro.product.cpu.abi",
        "ro.product.locale",
        "ro.build.version.sdk",
        "ro.build.version.release",
        "ro.build.version.security_patch",
        "ro.build.version.codename",
        "ro.build.version.incremental",
        "ro.build.characteristics",
        "ro.sf.lcd_density",
        "ro.revision",
        "ro.serialno",
        "ro.build.display.id",
        "ro.bootimage.build.fingerprint",
        "ro.build.fingerprint",
        "ro.bootimage.build.date",
        "sys.locksecured",
        "ro.bootloader",
        "ro.boot.hardware",
    };

    for (int i = 0; i < sizeof(deviceInfos1) / sizeof(deviceInfos1[0]); i++) {
        sprintf(deviceInfosCommand, "%s/adb.exe shell getprop %s >> SRLinker_DeviceInfos/%s_deviceInfos.txt", androidPlatformToolsPath, deviceInfos1[i], timestamp);
        adbOutputSave = popen(deviceInfosCommand, "w");
        char command[MAX_LINE_LENGTH];

        while (fgets(outputLineSave, MAX_LINE_LENGTH, adbOutputSave)) {
            printf("%s", outputLineSave);
        }
        pclose(adbOutputSave);
    }


    char adbDevicesCommand[MAX_LINE_LENGTH];    
    FILE* adbOutput;
    char outputLine[MAX_LINE_LENGTH];

    const char* deviceInfos[] = {
        "ro.product.model",
        "ro.product.manufacturer",
        "ro.product.brand",
        "ro.product.name",
        "ro.product.device",
        "ro.product.board",
        "ro.product.cpu.abi",
        "ro.product.locale",
        "ro.build.version.sdk",
        "ro.build.version.release",
        "ro.build.version.security_patch",
        "ro.build.version.codename",
        "ro.build.version.incremental",
        "ro.build.characteristics",
        "ro.sf.lcd_density",
        "ro.revision",
        "ro.serialno",
        "ro.build.display.id",
        "ro.bootimage.build.fingerprint",
        "ro.build.fingerprint",
        "ro.bootimage.build.date",
        "sys.locksecured",
        "ro.bootloader",
        "ro.boot.hardware",
    };

    printf(ANSI_LIGHT_STEEL_BLUE "\n  => Ausgabe wird generiert..." ANSI_RESET);

    for (int i = 0; i < sizeof(deviceInfos) / sizeof(deviceInfos[0]); i++) {
        sprintf(adbDevicesCommand, "%s/adb.exe shell getprop %s", androidPlatformToolsPath, deviceInfos[i]);
        adbOutput = popen(adbDevicesCommand, "r");

        if (!adbOutput) {
            printf(ANSI_TOMATO_RED "\n  ==> Fehler bei der Ausgabe der Geraeteinfos!\n" ANSI_RESET);
        }
        printf(ANSI_DARK_ORANGE "");
        while (fgets(outputLine, MAX_LINE_LENGTH, adbOutput)) {
            if (deviceInfos[i] == "ro.product.model") {
                printf("\n\nModell: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.manufacturer") {
                printf("Hersteller: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.brand") {
                printf("Marke: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.name") {
                printf("Produktname: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.device") {
                printf("Geraet: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.board") {
                printf("Board: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.cpu.abi") {
                printf("CPU ABI: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.product.locale") {
                printf("Landescode: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.version.sdk") {
                printf("SDK-Version: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.version.release") {
                printf("Android-Version: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.version.security_patch") {
                printf("Sicherheitspatch: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.version.codename") {
                printf("Codename: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.version.incremental") {
                printf("Inkrementelle Version: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.characteristics") {
                printf("Geraetetyp: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.sf.lcd_density") {
                printf("LCD-Dichte: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.revision") {
                printf("Hardwarerevision: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.serialno") {
                printf("Seriennummer: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.display.id") {
                printf("Build-Nummer: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.bootimage.build.fingerprint") {
                printf("Bootimage-Fingerprint: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.build.fingerprint") {
                printf("Fingerprint: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.bootimage.build.date") {
                printf("Bootimage-Datum: %s", outputLine);
            }
            else if (deviceInfos[i] == "sys.locksecured") {
                printf("Gesperrt: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.bootloader") {
                printf("Bootloader: %s", outputLine);
            }
            else if (deviceInfos[i] == "ro.boot.hardware") {
                printf("Boot-Hardware: %s", outputLine);
            }            
        }

        pclose(adbOutput);
        printf(ANSI_RESET "");
    }

    if (defaultP) {
        printf("\n\n----------------------------------------------------\n");
        printf("\n  Weitere Aktionen? [y/n]:\n");
        printf("  => ");
        scanf("%s", continueDeviceInfos);

        if (continueDeviceInfos[0] == 'y') {
            showOptions();
        } else {
            main();
        }
    }
}