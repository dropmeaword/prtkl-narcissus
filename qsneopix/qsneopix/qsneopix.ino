#include <Timer.h>
#include <Adafruit_NeoPixel.h>

#include "Trance.h"

#define PIN 6
#define NUMBERIDS 8
#define NUMBERPIXELSPERID 15
#define NUMBERPIXELS NUMBERIDS*NUMBERPIXELSPERID

int idArray[NUMBERIDS];

Timer metro;

Trance trance;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBERPIXELS, PIN, NEO_GRB + NEO_KHZ800);

///////////////////////////////////////////
void setup() {
  Serial.begin(115200);

  // initialize the ID per segment
  for(int i = 0; i < NUMBERIDS; i++) {
    idArray[i] = i+1;
  }

  strip.begin();
  strip.show();
  
  pattern_test();
}

void pattern_test() {
  int lum = 10;
  
  delay(100);
  Red(lum);
  delay(1000);
  Green(lum);
  delay(1000);
  Blue(lum);
}

void loop() {
  metro.update();
}

//////////////////////////////////////////
void StopAllTimers() {
  metro.stop(id_on);
  metro.stop(id_onT);
  Black();
}

void setGroupPixel(uint8_t pixelID, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness){
  int n, m;
  n = (pixelID-1) * 6;
  m = n + 6;

  for (int i = n; i < m; i++){
   strip.setPixelColor(i, (brightness*r/255) , (brightness*g/255), (brightness*b/255));
 }
 strip.show();
}

//////////////////////////////////////////
void shuffleArray(int *array, size_t n){

  if (n > 1){
    size_t i;
    for (i = 0; i < n - 1; i++){

      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

///////////////////////////////////////////
void randomizeTimeArray (float *array , int elements, int iterations, int time){
  int index = 0;
  int index2 = 0;

  for (int i = 0; i < NUMBERIDS; ++i)
  {
    array[i]=1/(float)NUMBERIDS;
  }

  for (int i = 0; i < iterations; ++i)
  {

    index = random(NUMBERIDS);
    index2 = random(NUMBERIDS);
    
    if (array[index] >= 0.001 && array[index2] >= 0.001)
    {
      array[index] = array[index] - 0.001;
      array[index2] = array[index2] + 0.001;
    }

  }

  for (int i = 0; i < NUMBERIDS; ++i)
  {
    timeArray[i] = array[i] * time;
  }
}

///////////Primary colors////////////
void Black(){
  for(int i=0;i<NUMBERPIXELS;i++){   
    strip.setPixelColor(i,0,0,0); 
  }  
  strip.show(); 
}

void Red(int lum){
  for(int i=0;i<NUMBERPIXELS;i++){   
    strip.setPixelColor(i, lum,0,0); 
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

void serialEvent () {
  while(Serial.available()) {
    char inc = (char)Serial.read();
    if(inc == '1') {
      // TRANCE
      StopAllTimers();
      rTrance = inBytes[2];
      gTrance = inBytes[3];
      bTrance = inBytes[4];
      Setup_Trance();
    }
  }
}

