#include <Timer.h>
#include <Adafruit_NeoPixel.h>

#define DATARATE 9600 //115200

#define PIN 6
#define NUMBERIDS 8
#define NUMBERPIXELSPERID 15
#define NUMBERPIXELS NUMBERIDS*NUMBERPIXELSPERID


int idArray[NUMBERIDS];

#define PACKETLEN 6
byte serin[PACKETLEN];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBERPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte segid, rval, gval, bval;
bool bRefresh;

#include "segment.h"
#include "trance.h"
#include "colors.h"

///////////////////////////////////////////
void setup() {
  Serial.begin(DATARATE);

  // initialize the ID per segment
  for(int i = 0; i < NUMBERIDS; i++) {
    idArray[i] = i+1;
  }

  strip.begin();
  strip.show();

  pattern_test();
}

void loop() {
  serialPump();

  if(bRefresh) {
    segmentrgb(segid, rval, gval, bval);
    bRefresh = false;
  }
}

void serialPump() {
  while(Serial.available() > 0) {
    Serial.readBytes(serin, PACKETLEN); // read 5 bytes
    
    if ((serin[0] == 254) && (serin[PACKETLEN-1] == 255)) // is marker for beginning/end of message?
    {
      segid = serin[1];
      rval  = serin[2];
      gval  = serin[3];
      bval  = serin[4];
      bRefresh = true;
    }

    // flush remainder
    if (Serial.available() < PACKETLEN) {
      while(Serial.read() != -1) ;
    }

  }
}
