void Bounce() {
  int lum = 255;
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, lum, lum);
    strip.show();
    delay(10);
  }
}

void Bright(int lum) {
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, lum, lum);
  }
  strip.show();
}

void Red(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i, lum, 0, 0); 
  }
  strip.show();
}

void Green(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i,0,lum,0);
  }
  strip.show();
}

void Blue(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){
    strip.setPixelColor(i,0,0,lum);
  }
  strip.show();
}


