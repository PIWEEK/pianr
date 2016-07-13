#include <TuneManager.h>
#include <ABCNoteParser.h>
#include <FileIO.h>

TuneManager* songManager;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  songManager = new TuneManager("/mnt/sd/SuperMarioTheme.abc");
  
}

void loop() {  
  songManager->playTune();
  delay(2000);
  /*
    leer boton
    si el botón 1 está pulsado { play(canción1) }
    si el botón 2 está pulsado { play(canción2) }
    si el botón 3 está pulsado { play(canción3) }
  */
}


/*
void play() {
  FileSystem.begin();
  File myFile = FileSystem.open("/mnt/sd/SuperMarioTheme.abc");
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
}
*/

