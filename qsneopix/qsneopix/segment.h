void segment(uint8_t segID, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness){
  int n, m;
  n = (segID-1) * 6;
  m = n + 6;

  for (int i = n; i < m; i++){
   strip.setPixelColor(i, (brightness*r/255) , (brightness*g/255), (brightness*b/255));
 }
 
 strip.show();
}


