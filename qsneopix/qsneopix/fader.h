#ifndef FADER_H
#define FADER_H

#include <math.h>
#include "easing.h"

typedef float (*EasingFx)(float t, float b, float c, float d);

class Fader {
  private:
    int      ledCount;
    bool     bAnimating;

    CRGB     *live;
    CRGB     *cache;
    CRGB     *target;

    CFastLED FLref;

    EasingFx easingfx;

    unsigned long duration;  // duration
    unsigned long timein;    // time in

  public:
    Fader() {
    }

    Fader& bind(CRGB *leds, int cnt, CFastLED& fastledref) {
      live = leds;
      ledCount = cnt;
      FLref = fastledref;
      cache = new CRGB[ledCount];
      this->clear();
      setEasingFunc(Easer_easeInOutCubic);
    }

    void setEasingFunc( EasingFx func ) {
      easingfx = func;
    }

    Fader& clear() {
      for (int i = 0; i < ledCount; i++) {
        live[i]   = CRGB(0,0,0);
      }
      return *this;
    }

    Fader& frame(CRGB *fbuffer) {
      target = fbuffer;
    }

    Fader& push(int d) {
      duration = d;
      
      // cache current live buffer
      for (int i = 0; i < ledCount; i++) {
        cache[i] = live[i];
      }
 
      timein = millis();
      bAnimating = true;
    }
    

    Fader &update() {
      if(bAnimating) {
        float elapsed = millis() - timein;
        for (int i = 0; i < ledCount; i++) {
          float cr = easingfx(elapsed, cache[i].r, (target[i].r-cache[i].r), duration);
          float cg = easingfx(elapsed, cache[i].g, (target[i].g-cache[i].g), duration);
          float cb = easingfx(elapsed, cache[i].b, (target[i].b-cache[i].b), duration);
          live[i] = CRGB(
            int(cr),
            int(cg),
            int(cb)
          );
        }

        FLref.show();

        // check if we have to stop animating
        if(elapsed > duration) {
          bAnimating = false;
        }
        
      } // bAnimating
    }

};

#endif
