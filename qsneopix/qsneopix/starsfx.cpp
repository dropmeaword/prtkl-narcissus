#include "starsfx.h"


StarsFX::StarsFX() {
  lum = 255;
  bRefresh = false;
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

  if(bRefresh) {
    for(int i = 0; i < howmany; i++) {
      int chance = random(0, 99);
      if(chance > 97) {
        live[i].r =  lum;
        live[i].g =  lum;
        live[i].b =  lum;
      } else {
        live[i].r =  0;
        live[i].g =  0;
        live[i].b =  0;
      }
    } // for
  } else {
    if( (millis() % rfreq) == 0) {
      // mark to refresh in next update
      bRefresh = true;
    }
  }

  return *this;
} // update


StarsFX& StarsFX::show() {
  FastLED.show();
  return *this;
}

