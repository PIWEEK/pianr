#include <ABCNoteParser.h>
#include <FileIO.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel pixels_11 = Adafruit_NeoPixel(11, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_12 = Adafruit_NeoPixel(10, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_13 = Adafruit_NeoPixel(11, 13, NEO_GRB + NEO_KHZ800);

File *file;
ABCNoteParser* abcParser;
int notePitch;
int noteDur;

int keys[38][2] = {
    {},       // pos0
    {},       // pos1
    {},       // pos2
    {},       // pos3
    {},       // pos4
    {},       // pos5
    {11, 5},  // pos6
    {11, 4},  // pos7
    {11, 6},  // pos8
    {11, 3},  // pos9
    {11, 7},  // pos10
    {11, 2},  // pos11
    {11, 8},  // pos12
    {11, 9},  // pos13
    {11, 1},  // pos14
    {11, 10}, // pos15
    {11, 0},  // pos16
    {12, 9},  // pos17
    {12, 8},  // pos18
    {12, 0},  // pos19
    {12, 7},  // pos20
    {12, 1},  // pos21
    {12, 6},  // pos22
    {12, 2},  // pos23
    {12, 5},  // pos24
    {12, 4},  // pos25
    {12, 3},  // pos26
    {13, 10}, // pos27
    {13, 0},  // pos28
    {13, 9},  // pos29
    {13, 8},  // pos30
    {13, 1},  // pos31
    {13, 7},  // pos32
    {13, 2},  // pos33
    {13, 6},  // pos34
    {13, 3},  // pos35
    {13, 5},  // pos36
    {13, 4},  // pos37
};





void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  FileSystem.begin();

  pixels_11.begin();
  //pixels_11.clear();
  pixels_12.begin();
  //pixels_12.clear();
  pixels_13.begin();
  //pixels_13.clear();

  play("/mnt/sd/SuperMarioTheme.abc");

}

void loop() {
}


void play(String path){
  Serial.print(path);
  Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  char song[50];
  path.toCharArray(song, 50);
  notePitch = 0;
  noteDur = 0;
  abcParser->reset();
  File tmpFile = FileSystem.open(song);
  file = &tmpFile;
  while(file->available()){
    abcParser->getNextNote(file, &notePitch, &noteDur);

    Serial.print("notePitch: ");
    Serial.print(notePitch);
    Serial.print(" noteDur: ");
    Serial.println(noteDur);

    pixels_11.clear();
    pixels_12.clear();
    pixels_13.clear();

    if(notePitch > 5 && notePitch < 17){
      pixels_11.setPixelColor(keys[notePitch][1], pixels_11.Color(0,150,0));
      pixels_11.show();
      delay(noteDur);
      pixels_11.clear();

    } else if (notePitch > 16 && notePitch < 27) {
      pixels_12.setPixelColor(keys[notePitch][1], pixels_12.Color(0,150,0));
      pixels_12.show();
      delay(noteDur);
      pixels_12.clear();

    } else if (notePitch > 26 && notePitch < 38) {
      pixels_13.setPixelColor(keys[notePitch][1], pixels_13.Color(0,150,0));
      pixels_13.show();
      delay(noteDur);
      pixels_13.clear();

    }
    delay(1000);
  }
  Serial.println("---------------------------------------------------------------------------------");
  file->close();
}





