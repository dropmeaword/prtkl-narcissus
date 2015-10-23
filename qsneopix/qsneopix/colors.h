
void pattern_bounce() {
  int lum = 255;
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, lum, lum);
    strip.show();
    delay(4);
  }

/*  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, 0, 0, 0);
  }*/
  strip.show();
}

void pattern_bright(int lum) {
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, lum, lum);
  }
  strip.show();
}

void pattern_red(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, 0, 0); 
  }
  strip.show();
}

void pattern_green(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i,0,lum,0);
  }
  strip.show();
}

void pattern_blue(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i,0,0,lum);
  }
  strip.show();
}


void pattern_test() {
  int lum = 10;

  delay(100);
  pattern_red(lum);
  delay(1000);
  pattern_green(lum);
  delay(1000);
  pattern_blue(lum);
  delay(500);
  pattern_bounce();

/*
  for(int i = 0; i < NUMBERIDS; i++) {
    segmentl(i, 64);
    segmentl(i-1, 0);
    delay(1000);
  }
  segmentl(NUMBERIDS-1, 0);*/
}



