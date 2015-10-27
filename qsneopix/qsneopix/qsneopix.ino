#include <Timer.h>
#include <FastLED.h>
#include "fader.h"

#define DATARATE 57600

#define PIN 6
#define NUMBER_SEGMENTS 4
#define PIXELS_PER_SEGMENT 30
#define NUMBERPIXELS ((NUMBER_SEGMENTS*PIXELS_PER_SEGMENT)+1)

#define PACKETLEN 6
byte serin[PACKETLEN];

int roomA[4] = {0, 1, 2, 3};
int roomB[4] = {4, 5, 6, 7};

CRGB testclr[5] = {CRGB(0x202000), CRGB(0x202010), CRGB(0x200020), CRGB(0x002020), CRGB(0x100020)};

CRGB leds[NUMBERPIXELS];
CRGB target[NUMBERPIXELS];

byte segid, rval, gval, bval;
bool bRefresh;

#include "segment.h"
#include "trance.h"
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

  // do a fade
  for(int i = 0; i < NUMBERPIXELS; i++) {
    target[i] = 0x101000;
  }
  
  // fade segment
  for(int i = 0; i < NUMBER_SEGMENTS; i++) {
    int r = random(5);
    sfader[i].fadeto(testclr[r]).push(random(200, 5000));
  }
}

void loop() {
  serialPump();

  for(int i = 0; i < NUMBER_SEGMENTS; i++) {
    sfader[i].update();
  }

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
  } // while

}
