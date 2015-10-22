class Trance {
  int pulser;
  
  int tIn;
  int tOut;
  int myTime;
  
  Adafruit_NeoPixel &strip;

  Trance() {
  }  
  
  void setup(Adafruit_NeoPixel &strip) {
    STATE = 2;
    pulser = 26;
    myTime=0;
  
    tIn  = metro.every(pulser, NeoTrance);
  }
  
  void frame() {
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
      metro.stop(id_on);
      id_onT = metro.every(pulser, NeoTrance);
      pre_pulser = pulser;
      temp_pulser = pulser;
    }
  
    // ACTIVATE TIMER FOR LIGHTS OFF
    offTimer.after(pulser*0.5, offNeoTrance);
  }
  
  void enter() {
  }
  
  void exit() {
    for(int i=0;i<NUMBERPIXELS;i++){   
     strip.setPixelColor(i,0,0,1); 
    }  
    
    strip.show(); 
  }
  
};


