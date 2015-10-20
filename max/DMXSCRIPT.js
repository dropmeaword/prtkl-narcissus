/////////////////////////////////////////////////////////////////
inlets = 4;
outlets = 1;
autowatch = 1;

// arguments in the js object
var litenum = jsarguments[1]; 
var red = jsarguments[2]; 
var green = jsarguments[3]; 
var blue = jsarguments[4]; 

// global array for all light fixtures
liteArr = [];
liteIn = []

initLite();

//
function initLite(){
	
	for (var n=0; n<255; ++n){
		liteArr[n] = 0;
		
	}
	
}


///

function Lite(litenum, red, green, blue){

mylite = (litenum-1) * 3;	
	
liteArr[mylite] = red;
liteArr[mylite + 1] = green;
liteArr[mylite + 2] = blue;
		
		outlet(0,liteArr);
	
}


post(liteArr);
////