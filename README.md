# nodemcu-wdmx
Ein Projekt, dass DMX-Signale über WLAN überträgt. Der Empfänger besteht dabei aus einem NodeMCU-Mikrocontroller, der an einen Max485-Chip angeschlossen ist (zur Konvertierung der Signale).
Es gibt zwei mögliche Betriebsmodi:
- Es wird ein Interface oder ein Mischpult genutzt: die Signale des benutzten DMX-Ausgangs werden zuerst von einem Arduino Uno ausgelesen (`dmx_to_pi.ino`) und dann über I2C an einen Raspberry Pi weitergeleitet. Von hier aus werden die Empfänger über UDP-Broadcasts angesprochen (`sender.py`).
- Es wird ein Programm genutzt, dass ArtNet unterstützt und einen lokalen ArtNet-Server öffnen kann: In diesem Fall kann ein Skript auf dem selben Computer diese Signale aufnehmen, die ArtNet-Header entfernen und direkt an die Stationen weiterleiten.
