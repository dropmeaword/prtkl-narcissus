#include <Timer.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMBERIDS 8
#define NUMBERPIXELSPERID 15
#define NUMBERPIXELS NUMBERIDS*NUMBERPIXELSPERID

float normArray[NUMBERIDS];
float timeArray[NUMBERIDS];

int idArray[NUMBERIDS]; //={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBERPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// serial comm variables
byte inBytes[8] = {0,0,0,0,0,0,0,0};

// Timers declarations
Timer PingTimer;
Timer onTimer;
Timer offTimer;

int id_off, id_offT;
int id_on, id_onT;
int pulser = 50; // 26
int pre_pulser = pulser;
int temp_pulser = pulser;
int heat = 0;
int red = 200, green = 200, blue = 200;
float incflik = 8;

int flickLevel=100;
int flickRange=20; 

int STATE;
int LITE = 0;
int myTime=0;

int rTrance = 0;
int gTrance = 0;
int bTrance = 0;
///////////////////////////////////////////
void setup() {
  Serial.begin(115200);
//randomSeed(analogRead(0));
//pinMode(2, INPUT_PULLUP);

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

  onTimer.update();
  offTimer.update();
  
  serialPool();
  
}

///////////////VOID///////////////////
void Setup_Void(){

  STATE = 1;
  pulser = 1000;
  myTime=0;

  Black();

  shuffleArray(idArray,NUMBERIDS);
    // START MAIN TIMER
  id_on  = onTimer.every(pulser, NeoVoid);
  
}

void NeoVoid(){

  int counter = 0;
  int mydelay = 0;

  shuffleArray(idArray, NUMBERIDS);
  randomizeTimeArray(normArray, NUMBERIDS, 1000, 240000); //third parameter is number of iterations and fourth is total time to distribute

  if (LITE < NUMBERIDS)
  {
    setGroupPixel (idArray[LITE], 0, 0, 253, 253);
    LITE++;
    Serial.println("LITE:" + LITE);
  }else{
    Serial.println("LAST LITE:" + LITE);
    LITE = 0;
    Serial.print("myTime: ");
    Serial.println(myTime/1000);

    onTimer.stop(id_on);

  }

  id_on  = onTimer.every(timeArray[LITE], NeoVoid);

}

///////////////TRANCE//////////////////
void Setup_Trance(){

  STATE = 2;
  pulser = 26;
  myTime=0;

  // START MAIN TIMER
  id_onT  = onTimer.every(pulser, NeoTrance);


}

void NeoTrance(){

  incflik += 0.01;
  pulser += 0.12 + incflik;

  // for(int i=0;i<NUMBERPIXELS;i++){   
  // strip.setPixelColor(i,0,0,incflik+random(incflik)); 
  // }  


  for(int i=0;i<NUMBERPIXELS;i++){   
  strip.setPixelColor(i,
    (incflik+random(incflik)) * (rTrance/253),
    (incflik+random(incflik)) * (gTrance/253),
    (incflik+random(incflik)) * (bTrance/253)
    ); 
  }  


  if(random(10)==1){ 
    int r=random(NUMBERIDS);
    setGroupPixel (r,0,0,0,incflik);
  }

  strip.show();

  // check if flicker rate has changed
  pulser = temp_pulser;
  
  if(pre_pulser != pulser){
    onTimer.stop(id_on);
    id_onT = onTimer.every(pulser, NeoTrance);
    pre_pulser = pulser;
    temp_pulser = pulser;
  }

  // ACTIVATE TIMER FOR LIGHTS OFF
  offTimer.after(pulser*0.5, offNeoTrance);

}


void offNeoTrance() {

  for(int i=0;i<NUMBERPIXELS;i++){   
   strip.setPixelColor(i,0,0,1); 
  }  
  
  strip.show(); 
}



////////////CHAOS1///////////////////
void Setup_Chaos1(){

  STATE = 3;
  pulser = 50;

  LITE = 1 + random(24);

  setGroupPixel(
    LITE,
    inBytes[3],
    inBytes[4],
    inBytes[5],
    inBytes[6]
  );

  // ACTIVATE TIMER FOR LIGHTS OFF
  id_off = offTimer.after(pulser, offChaos1);
}

void offChaos1(){
  setGroupPixel(LITE,0,0,0,253);
  offTimer.stop(id_off);
}

//////////////CHAOS2///////////////////////
void Setup_Chaos2(){
  // nada
}


//////////////////////////////////////////
void StopAllTimers() {
  onTimer.stop(id_on);
  offTimer.stop(id_off);
  onTimer.stop(id_onT);
  Black();
}

//////////////////////////////////////////
void serialPool () {

  while(Serial.available() > 0) {

    Serial.readBytes(inBytes, 8);

    if (inBytes[0] == 254 && inBytes[7] == 255)  
    {

      if (inBytes[1] == 1){
        // start MOOD #1 - VOID
        Serial.print("VOID");
        StopAllTimers();
        Setup_Void();

      } else if(inBytes[1] == 2){
      // TRANCE
       StopAllTimers();
       rTrance = inBytes[2];
       gTrance = inBytes[3];
       bTrance = inBytes[4];
       Setup_Trance();

     } else if(inBytes[1] == 3){
      // start MOOD #3 - CHAOS 1
      StopAllTimers();
      Setup_Chaos1();

    } else if(inBytes[1] == 4){
      // start MOOD #4 - CHAOS 2
      StopAllTimers();
      Setup_Chaos1();

    } else if(inBytes[1] == 5){
      //RESET/Black
      StopAllTimers();
      Black();

    }



  }
  if (Serial.available()< 8){
      while(Serial.read() != -1); //Flush any rest of buffer;
    }

  }
}


void setGroupPixel (uint8_t pixelID, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness){
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
