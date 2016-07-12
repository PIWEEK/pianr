#ifndef TUNEMANAGER_H
#define TUNEMANAGER_H

#include "Arduino.h"



// Buffer Constants
static const int MIN_NOTE_BUFFER = 15;
static const int MAX_NOTE_BUFFER = 100;

class TuneManager {
  public:
    TuneManager();
    void turnOnLeds();
  private:
    void addNotesToTune(Stream* str, int numOfNotesToAdd);
};

#endif
