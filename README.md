![grafik](https://github.com/Doe-eod/SRLinker_Windows/assets/73845354/1b46f5e2-7b23-4d77-bc60-331acc20c8b0)

# SRLinker
```
SRLinker
  von: Sven Herz
```
* Author: Sven Herz
* Getestet: Windows 11


## Beschreibung

Das Ziel von **SRLinker** ist es, eine vereinfachte und zum Teil automatisierte Möglichkeit zu bieten, mit einem Android-Gerät durch die ADB (Android Debug Bridge) zu interagieren. Unter Windows kann die Anwendung mit Powershell ausgeführt werden. Spezielle Aktionen sind teilweise nur (oder eingeschränkt) möglich, wenn auf dem Android-Gerät Root-Rechte vorliegen.

Die folgende Auflistung soll einen guten Überblick über vorhandene Aktionsmöglichkeiten geben:




```
* Rundum-sorglos-Paket
		-> Sicherung aller verfügbarer Bereicher der nachfolgenden Kategorien

* ADB-Server startet
		-> Startet Verbindung zu Device	

* ADB-Server beenden
		-> Beendet Verbindung zum Device

* Geräteinfos
		-> Auflistung von Geräteeigenschaften

* Logdateien
		-> Alle Logs sichern
		-> Logcat anzeigen
		-> Logcat sichern
		-> Bug-Report erstellen
		-> Dumpsys anzeigen
		-> Dumpsys sichern
		-> Kernel-Logs anzeigen (root)
		-> Kernel-Logs sichern (root)
		-> Packages anzeigen
		-> Packages sichern
		-> Sicherung von Logs aus /data/log/ (root)
		-> Sicherung aller .log-Dateien (beta, root)

* Netzwerk
		-> Alles sichern
		-> netstat -tulpen
		-> netstat -r (Routing-Tabelle)
		-> ifconfig
		-> ip addr show
		-> iptables -L (Firewall-Konfigurationen IPv4, root)
		-> ip6tables -L (Firewall-Konfigurationen IPv6, root)

* Prozesse
		-> Alles sichern
		-> pstree (falls verfuegbar)
		-> ps
		-> ps -ef
		-> top (mit count)

* APKs
		-> Installation
		-> Deinstallation
		-> Update
		-> App-Sicherung (root)

* Interaktionen
		-> Geraeteneustart
		-> Shell
		-> Screenshot
		-> Telefonanruf starten
		-> Android Monkey (Apps)
		-> Android Monkey (System)

* Backup erstellen

* Backup wiederherstellen
```





## Voraussetzung

Um das Programm nutzen zu können wird die **adb.exe** benötigt. Das Tool ADB kann bei [Android Developers]( https://developer.android.com/tools/releases/platform-tools?hl=de) für Windows heruntergeladen werden und ist Teil der Platform-Tools. 

Außerdem kann das Tool im Moment nur verwendet werden, wenn **ein einzelnes Gerät** per USB-Kabel angeschlossen ist. Bei mehreren angeschlossenen Devices kann momentan noch nicht ausgewählt werden, mit welchem interagiert werden soll. 





## Start mit hinterlegter EXE

Um lediglich die fertige SRLinker.exe-Datei mit Powershell unter Windows zu verwenden, müssen die folgenden Schritte durchgeführt werden:

```
1)	Starte eine Powershell
		* Keine Adminrechte nötig
	
2)	Navigiere in den entsprechenden Ordner
		* Beispielsweise: cd C:\Users\USERNAME\Desktop\SRLinker

3)	Starte das Programm
		* .\SRLinker

4)	Setze den Pfad zur adb.exe
		* Beispielsweise: C:/Users/USERNAME/AppData/Local/Android/Sdk/platform-tools/
		
5)	Anschließend kann das Programm verwendet werden.
```



## Projekt kompilieren

Wenn das Projekt zuerst kompiliert und eine neue EXE erstellt werden möchte, kann unter Windows beispielsweise mit MinGW durchgeführt werden:

```
1)	Installation und Einrichtung von MinGW
2)	Kompiliere das Projekt mit gcc:

		gcc -o C:\Users\USERNAME\Desktop\SRLinker\SRLinker.exe 
			C:\Users\USERNAME\Desktop\SRLinker\main.c 
			C:\Users\USERNAME\Desktop\SRLinker\Root.c 
			C:\Users\USERNAME\Desktop\SRLinker\Actions\Backup.c 
			C:\Users\USERNAME\Desktop\SRLinker\Actions\DeviceInfos.c 
			C:\Users\USERNAME\Desktop\SRLinker\Actions\AuxiliaryFunctions.c 
			C:\Users\USERNAME\Desktop\SRLinker\Logo\Logo.c

3)	Anschließend kann das Programm, wie oben beschrieben, gestartet und verwendet werden.
```











