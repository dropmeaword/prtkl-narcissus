#include <Timer.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMBERIDS 8
#define NUMBERPIXELSPERID 15
#define NUMBERPIXELS NUMBERIDS*NUMBERPIXELSPERID

int idArray[NUMBERIDS];

byte serin[5];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBERPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte segid, rval, gval, bval;
bool bRefresh;

#include "trance.h"
#include "colors.h"
#include "segment.h"

///////////////////////////////////////////
void setup() {
  Serial.begin(115200);

  // initialize the ID per segment
  for(int i = 0; i < NUMBERIDS; i++) {
    idArray[i] = i+1;
  }

  strip.begin();
  strip.show();

  pattern_test();
}

void pattern_test() {
  int lum = 10;

  delay(100);
  Red(lum);
  delay(1000);
  Green(lum);
  delay(1000);
  Blue(lum);
  delay(500);
  Bounce();
}

void loop() {
  if(bRefresh) {
    segmentrgb(segid, rval, gval, bval);
    bRefresh = false;
  }
}

void serialEvent() {
  if(Serial.available()) {
    
    Serial.readBytes(serin, 5); // read 5 bytes
    
    if (serin[0] == 0xEE) // is marker for beginning of message?
    {
      segid = serin[1];
      rval  = serin[2];
      gval  = serin[3];
      bval  = serin[4];
      bRefresh = true;
    }

    // flush remainder
    if (Serial.available() < 8) {
      while(Serial.read() != -1) ;
    }

  }
}
