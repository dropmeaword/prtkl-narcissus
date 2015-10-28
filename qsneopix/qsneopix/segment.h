
void segmentrgbl(int segID, int r, int g, int b, int brightness) {
  
  if (segID < 0) return;
  
  int n, m;
  n = (segID * PIXELS_PER_SEGMENT)+1; // skip first pixels
  m = (n + PIXELS_PER_SEGMENT);

  for (int i = n; i < m; i++) {
    leds[i].r = (brightness*r/255.0);
    leds[i].g = (brightness*g/255.0);
    leds[i].b = (brightness*b/255.0);
   //strip.setPixelColor(i, (brightness*r/255.0) , (brightness*g/255.0), (brightness*b/255.0));
 }

 FastLED.show();
 //strip.show();
}

void segmentl(int segID, int lum) {
  segmentrgbl(segID, 255, 255, 255, lum);
}

void segmentrgb(int segID, int r, int g, int b){
  segmentrgbl(segID, r, g, b, 255);
}


