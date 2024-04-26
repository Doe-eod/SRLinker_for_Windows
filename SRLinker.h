// SRLinker.h

#ifndef RASP_DROID_H
#define RASP_DROID_H

#include <stdbool.h>

extern char androidPlatformToolsPath[256];
extern char androidRechte[256];
extern char continueDeviceInfos[256];
extern bool defaultP;


// MinGW_Command Home:
// gcc -o C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\SRLinker.exe C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\main.c C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\Root.c C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\Actions\Backup.c C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\Actions\DeviceInfos.c C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\Actions\AuxiliaryFunctions.c C:\Users\maste\Desktop\A_Studien\SRLinker_Windows\Logo\Logo.c


// Home: Path to the Android Platform Tools
// C:\Users\maste\AppData\Local\Android\Sdk\platform-tools




// MinGW_Command Laptop:
// gcc -o C:\Users\svenh\Desktop\A_Studien\SRLinker\SRLinker.exe C:\Users\svenh\Desktop\A_Studien\SRLinker\main.c C:\Users\svenh\Desktop\A_Studien\SRLinker\Root.c C:\Users\svenh\Desktop\A_Studien\SRLinker\Actions\Backup.c


// Laptop: Path to the Android Platform Tools
// C:\Users\svenh\AppData\Local\Android\Sdk\platform-tools




// -------------------------------------- DEFINE BOLD --------------------------------------

#define ANSI_BOLD "\033[1m"
#define ANSI_RESET_BOLD "\033[0m"




// -------------------------------------- DEFINE Colors --------------------------------------

// Farbcodes für ANSI-Escape-Sequenzen
#define ANSI_RESET          "\033[0m"
#define ANSI_BLACK          "\033[0;30m"
#define ANSI_RED            "\033[0;31m"
#define ANSI_GREEN          "\033[0;32m"
#define ANSI_YELLOW         "\033[0;33m"
#define ANSI_BLUE           "\033[0;34m"
#define ANSI_MAGENTA        "\033[0;35m"
#define ANSI_CYAN           "\033[0;36m"
#define ANSI_WHITE          "\033[0;37m"

#define ANSI_ORANGE         "\033[0;38;2;255;165;0m"
#define ANSI_DARK_ORANGE    "\033[0;38;2;255;140;0m"
#define ANSI_LIGHT_ORANGE   "\033[0;38;2;255;190;0m"
#define ANSI_GOLD           "\033[0;38;2;255;215;0m"
#define ANSI_TOMATO_RED     "\033[0;38;2;255;69;0m"
#define ANSI_CORAL_RED      "\033[0;38;2;255;99;71m"
#define ANSI_DEEP_PINK      "\033[0;38;2;255;105;180m"
#define ANSI_LIGHT_PINK     "\033[0;38;2;255;182;193m"
#define ANSI_VIOLET         "\033[0;38;2;238;130;238m"
#define ANSI_ORCHID         "\033[0;38;2;218;112;214m"

#define ANSI_LIME           "\033[0;38;2;0;255;0m"
#define ANSI_FOREST_GREEN   "\033[0;38;2;34;139;34m"
#define ANSI_TEAL           "\033[0;38;2;0;128;128m"
#define ANSI_AQUA           "\033[0;38;2;0;255;255m"
#define ANSI_NAVY           "\033[0;38;2;0;0;128m"
#define ANSI_PURPLE         "\033[0;38;2;128;0;128m"
#define ANSI_INDIGO         "\033[0;38;2;75;0;130m"
#define ANSI_MAROON         "\033[0;38;2;128;0;0m"
#define ANSI_SALMON         "\033[0;38;2;250;128;114m"
#define ANSI_SIENNA         "\033[0;38;2;160;82;45m"
#define ANSI_CORNFLOWER     "\033[0;38;2;100;149;237m"
#define ANSI_SKY_BLUE       "\033[0;38;2;135;206;235m"
#define ANSI_MEDIUM_BLUE    "\033[0;38;2;0;0;205m"
#define ANSI_DARK_TURQUOISE "\033[0;38;2;0;206;209m"
#define ANSI_SLATE_BLUE     "\033[0;38;2;106;90;205m"
#define ANSI_ROYAL_BLUE     "\033[0;38;2;65;105;225m"
#define ANSI_MEDIUM_PURPLE  "\033[0;38;2;147;112;219m"
#define ANSI_DARK_OLIVE     "\033[0;38;2;85;107;47m"
#define ANSI_LIGHT_SKY_BLUE "\033[0;38;2;135;206;250m"
#define ANSI_MIDNIGHT_BLUE  "\033[0;38;2;25;25;112m"
#define ANSI_DARK_MAGENTA   "\033[0;38;2;139;0;139m"
#define ANSI_CHOCOLATE      "\033[0;38;2;210;105;30m"
#define ANSI_MEDIUM_SEA_GREEN "\033[0;38;2;60;179;113m"
#define ANSI_SLATE_GRAY     "\033[0;38;2;112;128;144m"
#define ANSI_DIM_GRAY       "\033[0;38;2;105;105;105m"
#define ANSI_LIGHT_SLATE_GRAY "\033[0;38;2;119;136;153m"
#define ANSI_LIGHT_STEEL_BLUE "\033[0;38;2;176;196;222m"
#define ANSI_LIGHT_GRAY     "\033[0;38;2;211;211;211m"
#define ANSI_GAINSBORO      "\033[0;38;2;220;220;220m"






// -------------------------------------- main.c --------------------------------------

int main();
void clearScreen();
void showOptions();




// -------------------------------------- Root.c --------------------------------------

// Logs
void handleLogFiles();
void catLogcat();
void saveLogcat();
void saveBugReport();
void catDumpsys();
void saveDumpsys();
void catKernelLogs();
void saveKernelLogs();
void catPackages();
void savePackages();
void saveAllFromDataLog();
void saveAllLogDatas();

// Network
void handleNetwork();
void handleNetstatTulpen();
void handleNetstatShowRoutingTable();
void handleIfconfig();
void handleIpAddrShow();
void handleIpTables();
void handleIpv6Tables();

// Processes
void handleProcesses();
void handlePsTree();
void handlePs();
void handlePsEF();
void handleTop();

// APKs
void handleAPKs();
void installAPKs();
void uninstallAPKs();
void updateAPKs();

// Interactions
void handleInteractions();
void restartDevice();
void startShell();
void handleScreenshot();
void handleScreenrecord();
void handleAndroidMonkeyForApps();
void handleAndroidMonkeyForSystem();





// -------------------------------------- Actions/Backup.c --------------------------------------

// Backup
void createBackup();
void restoreBackup();





// -------------------------------------- Actions/AuxiliaryFunctions.c --------------------------------------

void getTime();
void handleServerStart();
void handleServerKill();
void refreshServer();
void refreshServerLong();
void requestHandleLogFiles();
void requestHandleNetwork();
void requestHandleProcesses();
void requestHandleAPKs();
void requestHandleInteractions();
void printIncreasingDots(int count);
void handleExit();





// -------------------------------------- Actions/DeviceInfos.c --------------------------------------

void showDeviceInfos();





// -------------------------------------- Actions/Logo.c --------------------------------------

int showLogo();


#endif

