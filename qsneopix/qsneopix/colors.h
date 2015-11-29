
void pattern_bounce(CRGB *mleds) {
  int lum = 255;
  for(int i=0;i<NUMBERPIXELS;i++){
    //strip.setPixelColor(i, lum, lum, lum);
    //strip.show();
    mleds[i].r = lum;
    mleds[i].g = lum;
    mleds[i].b = lum;
    FastLED.show();
    delay(4);
  }

//  for(int i=0;i<NUMBERPIXELS;i++){
//    mleds[i].r = 0;
//    mleds[i].g = 0;
//    mleds[i].b = 0;
//    FastLED.show();
//    delay(4);
//  }
  
  FastLED.show();
  //strip.show();
}

void pattern_bright(CRGB *mleds, int lum) {
  for(int i=0;i<NUMBERPIXELS;i++){
    //strip.setPixelColor(i, lum, lum, lum);
    mleds[i].r = lum;
    mleds[i].g = lum;
    mleds[i].b = lum;
  }
  FastLED.show();
  //strip.show();
}

void pattern_red(CRGB *mleds, int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    mleds[i].r = lum;
    mleds[i].g = 0;
    mleds[i].b = 0;
    //strip.setPixelColor(i, lum, 0, 0); 
  }
  //strip.show();
  FastLED.show();
}

void pattern_green(CRGB *mleds, int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    mleds[i].r = 0;
    mleds[i].g = lum;
    mleds[i].b = 0;
    //strip.setPixelColor(i,0,lum,0);
  }
  //strip.show();
  FastLED.show();
}

void pattern_blue(CRGB *mleds, int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    mleds[i].r = 0;
    mleds[i].g = 0;
    mleds[i].b = lum;
    //strip.setPixelColor(i,0,0,lum);
  }
  //strip.show();
  FastLED.show();
}


void pattern_test(CRGB *mleds) {
  int lum = 10;

  delay(100);
  pattern_red(mleds, lum);
  delay(1000);
  pattern_green(mleds, lum);
  delay(1000);
  pattern_blue(mleds, lum);
  delay(500);
  pattern_bounce(mleds);

/*
  for(int i = 0; i < NUMBERIDS; i++) {
    segmentl(i, 64);
    segmentl(i-1, 0);
    delay(1000);
  }
  segmentl(NUMBERIDS-1, 0);*/
}

void pxstatus_ready() {
  leds[0] = 0x000a00;
  FastLED.show();
  //strip.setPixelColor(0,0,10,0);
  //strip.show();
}

