#ifndef ABCNOTEPARSER_H
#define ABCNOTEPARSER_H

#include "Arduino.h"

class ABCNoteParser {
  public:
    ABCNoteParser();
    void reset();
    void getNextNote(Stream* str, int* pitch, int* dur);
  private:
    void skipCharacters(Stream* stream, char* input, char* skipChars);
    void skipCharactersUntil(Stream* stream, char* input, char* skipUntil);
    int getIntegerFromStream(Stream* str, char* previewedChar);
    double delayTimeInMilliseconds(double noteLength, float bpm);
    int getPitch(Stream* stream, char* input);
    int getDuration(Stream* stream, char* input);
};

#endif



