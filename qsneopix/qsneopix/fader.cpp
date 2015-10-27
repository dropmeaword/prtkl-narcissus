#include "fader.h"

// copying colors:
//  memmove8( &leds[dest], &leds[src], 10 * sizeof( CRGB) );

//Fader::Fader() {
//}
//
//Fader& Fader::bind(CRGB *leds, int cnt) { //CFastLED& fastledref, CRGB *leds, int cnt) {
//  live = leds;
//  ledCount = cnt;
//  //FLref = fastledref;
//  cache = new CRGB[ledCount];
//  blank();
//  setEasingFunc(Easer_easeInOutCubic);
//}
//
//void Fader::setEasingFunc( EasingFx func ) {
//  easingfx = func;
//}
//
//Fader& Fader::blank() {
//  for (int i = 0; i < ledCount; i++) {
//    live[i]   = CRGB(0,0,0);
//  }
//  return *this;
//}
//
//Fader& Fader::frame(CRGB *fbuffer) {
//  target = fbuffer;
//  
//  return *this;
//}
//
//Fader& Fader::push(int d) {
//  duration = d;
//  
//  // cache current live buffer
//  for (int i = 0; i < ledCount; i++) {
//    cache[i] = live[i];
//  }
//
//  timein = millis();
//  bAnimating = true;
//
//  return *this;
//}
//
//
//Fader &Fader::update() {
//  if(bAnimating) {
//    float elapsed = millis() - timein;
//    for (int i = 0; i < ledCount; i++) {
//      float cr = easingfx(elapsed, cache[i].r, (target[i].r-cache[i].r), duration);
//      float cg = easingfx(elapsed, cache[i].g, (target[i].g-cache[i].g), duration);
//      float cb = easingfx(elapsed, cache[i].b, (target[i].b-cache[i].b), duration);
//      live[i] = CRGB(
//        int(cr),
//        int(cg),
//        int(cb)
//      );
//    }
//
//    FastLED.show();
//
//    // check if we have to stop animating
//    if(elapsed > duration) {
//      bAnimating = false;
//    }
//    
//  } // bAnimating
//}

SegmentFader::SegmentFader() {
}

void SegmentFader::setEasingFunc( EasingFx func ) {
  easingfx = func;
}

SegmentFader& SegmentFader::bind(CRGB *leds, int cnt, int b, int e) {
  //Fader::bind(leds, cnt);
  begins = b;
  ends = e;

  live = leds;
  setEasingFunc(Easer_easeInOutCubic);

  return *this;
}

SegmentFader& SegmentFader::push(int d) {
  //Fader::push(d);
  duration = d;
  
  timein = millis();
  bAnimating = true;

  cachec = live[begins];

  return *this;
}

SegmentFader& SegmentFader::set(CRGB val) {
  cachec = val;
  
  for (int i = begins; i < ends; i++) {
    live[i] = val;
  }
  
  return *this;
}

SegmentFader& SegmentFader::fadeto(CRGB val) {
  targetc = val;
  return *this;
}

SegmentFader &SegmentFader::update() {
  if(bAnimating) {
    float elapsed = millis() - timein;

    int cr = (int)easingfx(elapsed, cachec.r, (targetc.r-cachec.r), duration);
    int cg = (int)easingfx(elapsed, cachec.g, (targetc.g-cachec.g), duration);
    int cb = (int)easingfx(elapsed, cachec.b, (targetc.b-cachec.b), duration);

//    Serial.print(begins);
//    Serial.print(" ");
//    Serial.print(ends);
//    Serial.print(" // ");
//    
//    Serial.print("c = ");
//    Serial.print(cr);
//    Serial.print(" ");
//    Serial.print(cg);
//    Serial.print(" ");
//    Serial.print(cb);
//    Serial.print(" ");
//    Serial.println();
    
    for (int i = begins; i <= ends; i++) {
      live[i] = CRGB(cr, cg, cb);
    }

    FastLED.show();

    // check if we have to stop animating
    if(elapsed > duration) {
      bAnimating = false;
    }
    
  } // bAnimating
}

