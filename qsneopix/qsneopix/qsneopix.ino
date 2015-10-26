#include <Timer.h>
#include <FastLED.h>
#include "fader.h"

//#include <Adafruit_NeoPixel.h>

#define DATARATE 57600 //115200

#define PIN 6
#define NUMBERIDS 8
#define NUMBERPIXELSPERID 15
#define NUMBERPIXELS ((NUMBERIDS*NUMBERPIXELSPERID)+1)

#define PACKETLEN 6
byte serin[PACKETLEN];

int roomA[4] = {0, 1, 2, 3};
int roomB[4] = {4, 5, 6, 7};

CRGB leds[NUMBERPIXELS];
CRGB target[NUMBERPIXELS];

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBERPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte segid, rval, gval, bval;
bool bRefresh;

#include "segment.h"
#include "trance.h"
#include "colors.h"

Fader fader;

///////////////////////////////////////////
void setup() {
  Serial.begin(DATARATE);

  //strip.begin();
  //strip.show();

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMBERPIXELS);
  fader.bind(leds, NUMBERPIXELS, FastLED);

  pattern_test();
  pxstatus_ready();

  delay(5000);
  
  // do a fade
  for(int i = 0; i < NUMBERPIXELS; i++) {
    target[i] = 0x202000;
  }
  
  fader.frame(target);
  fader.push(5000);
}

void loop() {
  //serialPump();

  fader.update();
/*
  if(bRefresh) {

    // is segment referring to the whole of Room A
    if(segid == 8) {
      for(int j = 0; j <= 3; j++) {
        segmentrgb(roomA[j], rval, gval, bval);
      }
    // is segment referring to the whole of Room B
    } else if (segid == 9) {
      for(int j = 0; j <= 3; j++) {
        segmentrgb(roomB[j], rval, gval, bval);
      }
    } else {
      segmentrgb(segid, rval, gval, bval);
    }
    
    bRefresh = false;
  }
  */
}

void serialPump() {
  while(Serial.available() > 0) {
    Serial.readBytes(serin, PACKETLEN);
    
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
