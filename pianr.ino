#include <TuneManager.h>
#include <ABCNoteParser.h>
#include <FileIO.h>

TuneManager* songManager;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);

  songManager = new TuneManager();
  songManager->playTune("/mnt/sd/SuperMarioTheme.abc");
}

void loop() {


  /*
    leer boton
    si el botón 1 está pulsado { play(canción1) }
    si el botón 2 está pulsado { play(canción2) }
    si el botón 3 está pulsado { play(canción3) }
  */

}


/*
void play(String path) {

  char song[50];
  path.toCharArray(song, 50);

  FileSystem.begin();
  Serial.println(path);
  File myFile = FileSystem.open(song);
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
}

*/
