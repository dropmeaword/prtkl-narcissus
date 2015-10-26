/////////////////////////////////////////////////////////////////
inlets = 1;
outlets = 1;
autowatch = 1;

///

outmess = [];

///

function strip(stripnum, red, green, blue){
	outmess = [254, stripnum, red, green, blue, 255];

	outlet(0, outmess);
	
//	setTimeout(delayz, 50);
	
//	post(outmess);
//	post ("\n");
}

///

function strips(low, high, r, g, b) {
	var i;
	
	for (i=low; i<=high; i++){
		
		outmess = [254,i, r, g, b, 255];
		
		outlet(0, outmess);
		
	//	setTimeout(delayz, 50);
		
	//	post(outmess);
	//	post ("\n");
	}
}
	

function roomA(r,g,b){
	strips(0, 3, r, g, b);
}

function roomB(r,g,b){
	strips(4, 7, r, g, b);
}
	

function allblack(){
	strips(0, 7, 0, 0, 0);
}


function allbright(){
	strips(0, 7, 255, 255, 255);
}
	
	
//

