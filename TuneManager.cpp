#include <FileIO.h>
#include "ABCNoteParser.h"
#include "TuneManager.h"

// File information
File tuneFile;

// Buffered note storage/parsing
ABCNoteParser* abcParser;
int readNoteIndex = 0;
int writeNoteIndex = 0;
int tunePitch[MAX_NOTE_BUFFER];
int tuneDur[MAX_NOTE_BUFFER];

// Timing
unsigned long previousMillis = 0;
unsigned long interval = 0;

TuneManager::TuneManager() {
  Serial.println(F("Initializing TuneManager"));
  previousMillis = millis();
  abcParser = new ABCNoteParser();

  FileSystem.begin();

  File tuneFile = FileSystem.open("/song");
}

void TuneManager::addNotesToTune(Stream* str, int numOfNotesToAdd) {
  for (int i=0; i<numOfNotesToAdd; i++) {
    // Immediately abort loading more notes if we have run out of space in the buffer
    if ((writeNoteIndex+1)%MAX_NOTE_BUFFER == readNoteIndex) return;

    // If the file is still available, get the next freq and duration
    if (str->available()) {
      // Get our next note from the file
      int nextNotePitch = 0;
      int nextNoteDur = 0;

      // get the next note using our parser
      abcParser->getNextNote(str, &nextNotePitch, &nextNoteDur);

      // Check to make sure that we have a note (in case it reached end of file)
      if (nextNoteDur != 0) {
        // Otherwise, add our decoded note to the ongoing tune
        tunePitch[writeNoteIndex] = nextNotePitch;
        tuneDur[writeNoteIndex] = nextNoteDur;

        // Increment the index of where we are writing our notes
        writeNoteIndex = (writeNoteIndex+1)%MAX_NOTE_BUFFER;

        // So long as we were able to get the next note, continue with the parsing process
        continue;
      }
    }
    // If we have reached the end of the song, return to avoid trying to load more notes
    return;
  }
}


void TuneManager::turnOnLeds() {
  this->addNotesToTune(&tuneFile, MAX_NOTE_BUFFER);

  // play the song by iterating over the notes at given intervals:
  unsigned long currentMillis = millis();
  if (readNoteIndex != writeNoteIndex && (currentMillis - previousMillis > interval) ) {
    previousMillis = currentMillis;

    // Before playing, if this and the next notes are the same frequency, we need to manually
    // add a small break between the notes so they don't blend together
    int tempDur = tuneDur[readNoteIndex];
    if (tunePitch[(readNoteIndex+1)%MAX_NOTE_BUFFER] == tunePitch[readNoteIndex]) {
      // Remove some milliseconds to the notes interval to create a short 'rest'
      tempDur -= 10;
    }

    // TODO!
    // Turn on the led
    // where tunePitch[readNoteIndex] is the pitch and tempDur is the duration;
    // digitalWrite(led-que-sea, HIGH); // correspondiente con el tunePitch[readNoteIndex]
    // delay(tempDur);
    // digitalWrite(13, LOW);

    // Set how long to wait until next note
    interval = tuneDur[readNoteIndex];

    // Remove the note we just played so it doesn't repeat
    readNoteIndex = (readNoteIndex+1)%MAX_NOTE_BUFFER;
  } else {
    // If we can't play a note yet, might as well buffer some of the upcoming notes
    //Serial.println("Not playing a note, so add to buffer");
    addNotesToTune(&tuneFile, MIN_NOTE_BUFFER);
  }
}
