#include <Timer.h>
#include <FastLED.h>
#include "fader.h"

//#include <Adafruit_NeoPixel.h>

#define DATARATE 57600 //115200

#define PIN 6
#define NUMBER_SEGMENTS 8
#define PIXELS_PER_SEGMENT 10
#define NUMBERPIXELS ((NUMBER_SEGMENTS*PIXELS_PER_SEGMENT)+1)

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

//Fader fader;

//SegmentFader sfader[NUMBERIDS];
SegmentFader sf;
SegmentFader sf2;
SegmentFader sf3;

///////////////////////////////////////////
void setup() {
  Serial.begin(DATARATE);

  //strip.begin();
  //strip.show();

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMBERPIXELS);
  //fader.bind(leds, NUMBERPIXELS);

  sf.bind(leds, NUMBERPIXELS, 1, 20);
  sf2.bind(leds, NUMBERPIXELS, 21, 40);
  sf3.bind(leds, NUMBERPIXELS, 41, 60);
  
  // init segment faders
//  for(int i = 0; i < NUMBER_SEGMENTS; i++) {
//    int n, m;
//    n = (i * PIXELS_PER_SEGMENT)+1;
//    m = (n + PIXELS_PER_SEGMENT);
//    sfader[i].bind(FastLED, leds, NUMBERPIXELS, n, m);
//  }

  pattern_test();
  pxstatus_ready();

//  // do a fade
//  for(int i = 0; i < NUMBERPIXELS; i++) {
//    target[i] = 0x101000;
//  }
  
//  fader.frame(target);
//  fader.push(1000);

  // fade segment
//  sfader[2].fadeto(CRGB(0x200000)).push(5000);
//  sfader[3].fadeto(CRGB(0x002000)).push(5000);
//  sfader[4].fadeto(CRGB(0x000020)).push(5000);
  sf.fadeto(CRGB(0x000020)).push(5000);
  sf2.fadeto(CRGB(0x001000)).push(5000);
  sf3.fadeto(CRGB(0x001010)).push(5000);
}

void loop() {
  //serialPump();

//  segmentrgb(0, 10, 0, 0);
//  segmentrgb(1, 0, 10, 0);
//  segmentrgb(2, 0, 0, 10);
//  segmentrgb(3, 10, 0, 10);
//  segmentrgb(4, 0, 10, 10);
//  segmentrgb(5, 10, 10, 10);

  sf.update();
  sf2.update();
  sf3.update();
  
//  fader.update();
//  for(int i = 0; i < NUMBERIDS; i++) {
//    sfader[i].update();
//  }
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
