#include <FastLED.h>
#include "fader.h"

#define DATARATE 57600

#define PIN 6
#define NUMBER_SEGMENTS 8
#define PIXELS_PER_SEGMENT 15
#define NUMBERPIXELS ((NUMBER_SEGMENTS*PIXELS_PER_SEGMENT)+1)

#define PACKETLEN 7
byte serin[PACKETLEN];

int roomA[4] = {0, 1, 2, 3};
int roomB[4] = {4, 5, 6, 7};

CRGB testclr[5] = {CRGB(0x202000), CRGB(0x202010), CRGB(0x200020), CRGB(0x002020), CRGB(0x100020)};

CRGB leds[NUMBERPIXELS];
CRGB target[NUMBERPIXELS];

byte segid, rval, gval, bval;
long durval;
bool bRefresh;

#include "segment.h"
#include "colors.h"

SegmentFader sfader[NUMBER_SEGMENTS];

///////////////////////////////////////////
void setup() {
  Serial.begin(DATARATE);

  randomSeed(analogRead(0));

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMBERPIXELS);
  
  // init segment faders
  int n, m;
  for(int i = 0; i < NUMBER_SEGMENTS; i++) {
    n = (i * PIXELS_PER_SEGMENT)+1;
    m = (n + PIXELS_PER_SEGMENT);

    sfader[i].bind(leds, NUMBERPIXELS, n, m);
  }

  pattern_test();
  pxstatus_ready();
}

void loop() {
  serialPump();

  for(int i = 0; i < NUMBER_SEGMENTS; i++) {
    sfader[i].update();
  }

  loopLight();
}

void loopLight() {
  if(bRefresh) {
    //CRGB triad = CRGB(rval, gval, bval);
    // is segment referring to the whole of Room A
    if(segid == 8) {
      for(int j = 0; j <= 3; j++) {
          int segment = roomA[j];
          sfader[segment].fadeto(CRGB(rval, gval, bval)).push(durval);
        //segmentrgb(roomA[j], rval, gval, bval);
      }
    // is segment referring to the whole of Room B
    } else if (segid == 9) {
      for(int j = 0; j <= 3; j++) {
        //segmentrgb(roomB[j], rval, gval, bval);
          int segment = roomB[j];
          sfader[segment].fadeto(CRGB(rval, gval, bval)).push(durval);
      }
    } else if (segid == 10) {
        sfader[0].fadeto(CRGB(rval, gval, bval)).push(durval);
        sfader[1].fadeto(CRGB(rval, gval, bval)).push(durval);
    } else if (segid == 11) {
        sfader[2].fadeto(CRGB(rval, gval, bval)).push(durval);
        sfader[3].fadeto(CRGB(rval, gval, bval)).push(durval);
    } else if (segid == 12) {
        sfader[4].fadeto(CRGB(rval, gval, bval)).push(durval);
        sfader[5].fadeto(CRGB(rval, gval, bval)).push(durval);
    } else if (segid == 13) {
        sfader[6].fadeto(CRGB(rval, gval, bval)).push(durval);
        sfader[7].fadeto(CRGB(rval, gval, bval)).push(durval);
    } else if ( (segid >= 20) && (segid < 28) ) {
        segmentrgb((segid - 20), rval, gval, bval);
    } else if ( segid == 30 ) {
        segmentrgb(0, rval, gval, bval);
        segmentrgb(1, rval, gval, bval);
    } else if ( segid == 31 ) {
        segmentrgb(2, rval, gval, bval);
        segmentrgb(3, rval, gval, bval);
    } else if ( segid == 32 ) {
        segmentrgb(4, rval, gval, bval);
        segmentrgb(5, rval, gval, bval);
    } else if ( segid == 33 ) {
        segmentrgb(6, rval, gval, bval);
        segmentrgb(7, rval, gval, bval);
    } else {
      //segmentrgb(segid, rval, gval, bval);
      sfader[segid].fadeto(CRGB(rval, gval, bval)).push(durval);
    }
    
    bRefresh = false;
  }
}

void serialPump() {
  while(Serial.available() > 0) {
    Serial.readBytes(serin, PACKETLEN);
    
    if ((serin[0] == 254) && (serin[PACKETLEN-1] == 255)) // is marker for beginning/end of message?
    {
      segid    = serin[1];
      rval     = serin[2];
      gval     = serin[3];
      bval     = serin[4];
      durval   = 100 * serin[5];
      bRefresh = true;
    }

    // flush remainder
    if (Serial.available() < PACKETLEN) {
      while(Serial.read() != -1) ;
    }
  } // while

}
