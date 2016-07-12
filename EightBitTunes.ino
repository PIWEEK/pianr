#include "ABCNoteParser.h"
#include "TuneManager.h"


TuneManager* songManager;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  songManager = new TuneManager();
}

void loop() {
  manageTunes();
}

void manageTunes() {
  songManager->turnOnLeds();
}
