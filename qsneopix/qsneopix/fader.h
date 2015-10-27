#ifndef FADER_H
#define FADER_H

#include <math.h>
#include <FastLED.h>
#include "easing.h"

typedef float (*EasingFx)(float t, float b, float c, float d);

/*
 * The CandyFader can fade any pixel with any value to any other pixel with any other value using
 * Penner's easing equations for interpolation. The CandyFader refreshes the WHOLE LED strip
 * on every step of the fade.
 */
class CandyFader {
  protected:
    int      ledCount;
    bool     bAnimating;

    CRGB     *live;
    CRGB     *cache;
    CRGB     *target;

    //CFastLED FLref;

    EasingFx easingfx;

    unsigned long duration;  // duration
    unsigned long timein;    // time in

  public:
    CandyFader();
    CandyFader& bind(CRGB *leds, int cnt);

    void setEasingFunc( EasingFx func );

    CandyFader& blank();
    CandyFader& frame(CRGB *fbuffer);
    CandyFader& push(int d);
    CandyFader &update();
};

/*
 * The SegmentFader can fade any block of LEDs on a given strip from one color to another color. Each block
 * has a single color. Only those LEDs in the block affected will be refreshed on every frame. 
 * 
 * @NOTE For some reason inheriting from the other more general fader makes the Arduino choke, so I copied and pasted
 * a lot of code that should really be inherited.
 */
class SegmentFader { //: public Fader {
  private:
    int      begins;
    int      ends;

    CRGB     targetc;
    CRGB     cachec;

    int      ledCount;
    bool     bAnimating;

    CRGB     *live;
    CRGB     *cache;
    CRGB     *target;

    //CFastLED FLref;

    EasingFx easingfx;

    unsigned long duration;  // duration
    unsigned long timein;    // time in
  public:
    SegmentFader();

    void setEasingFunc( EasingFx func );

    SegmentFader& bind(CRGB *leds, int cnt, int b, int e);
    SegmentFader& push(int d);
    SegmentFader& set(CRGB val);
    SegmentFader& fadeto(CRGB val);
    SegmentFader &update();
};

#endif
