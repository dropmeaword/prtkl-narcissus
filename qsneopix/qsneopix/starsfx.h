#ifndef __STARFX_H__
#define __STARFX_H__

#include <math.h>
#include <FastLED.h>

class StarsFX {
  protected:
    CRGB     *live;
    CRGB     *cache;
    CRGB     *target;

    unsigned long duration;  // duration
    unsigned long timein;    // time in

    int howmany;
    int pinData;
    int pinClock;

  public:
    StarsFX();
    StarsFX& bind(CRGB *leds, int cnt);

    StarsFX& enter();
    StarsFX& leave();
    
    StarsFX& blank();
    StarsFX& update();
    StarsFX& show();
};

#endif // __STARFX_H__
