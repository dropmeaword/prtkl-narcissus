#include "starsfx.h"


StarsFX::StarsFX() {
}

StarsFX& StarsFX::bind(CRGB *leds, int cnt) {
    
    live = leds;
    howmany = cnt;

//    pinClock = _pinClock;
//    pinData = _pinData;
//    
//    if(_pinClock != 0) {
//      FastLED.addLeds<APA102, pinData, pinClock>(leds, cnt);
//    } else {
//      FastLED.addLeds<NEOPIXEL, pinData>(leds, cnt);
//    }

    return *this;
}

StarsFX& StarsFX::enter() {
  timein = millis();

    return *this;
}

StarsFX& StarsFX::leave() {
    return *this;
}


StarsFX& StarsFX::blank() {
  for(int i = 0; i < howmany; i++) {
    live[i].r =  0;
    live[i].g =  0;
    live[i].b =  0;
  }
  return *this;
}

StarsFX& StarsFX::update() {
  for(int i = 0; i < howmany; i++) {
    int chance = random(0, 99);
    if(chance > 97) {
      live[i].r =  255;
      live[i].g =  255;
      live[i].b =  255;
    } else {
      live[i].r =  0;
      live[i].g =  0;
      live[i].b =  0;
    }
  } // for

  return *this;
} // update


StarsFX& StarsFX::show() {
  FastLED.show();
  return *this;
}

