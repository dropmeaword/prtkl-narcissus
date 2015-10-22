inlets = 1;
outlets = 6;
autowatch = 1;

j1 = jsarguments[1]; // 1st arguments in the js object
j2 = jsarguments[2]; // 2nd arguments in the js object


RR=0; // red
GG=0; // green
BB=0; // blue
AA=0; // alpha
LUX=0; // number of light element

///////////////////////////////////////////////////////////
function NERO(maxlitez){
    
var i;

    for (i=0; i<maxlitez; i++){
	
	 	outlet(0,i);// channel
        outlet(1,0);// R
        outlet(2,0);// G
        outlet(3,0);// B

	    myDelay(50);

   }

}


///////////////////////////////////////////////////////////
function LITE(litenum,red,green,blue,alf){
    
var n,m,i;

	 	outlet(0,litenum);// channel
        outlet(1,red);// R
        outlet(2,green);// G
        outlet(3,blue);// B

		myDelay(50);


}

///////////////////////////////////////////////////////////
function LIZE(litenum,red,green,blue,alf){
    
var n,m,i;

    n = (litenum-1) * 6;
	m = n + 6;

    for (i=n; i<m; i++){
	
	 	outlet(0,i);// channel
        outlet(1,red);// R
        outlet(2,green);// G
        outlet(3,blue);// B

	    myDelay(50);

   }

}

///////////////////////////////////////////////////////////
function RANLIZE(totlites){
    
var n,m,i;

    for (i=1; i<=totlites; i++){
	
		n = Math.floor((Math.random() * 3) + 1);
		// outlet(5,n);	
 
	if(n==1){
		rr=200;	gg=0; bb=0;
		}
	else if (n==2){
		rr=0;	gg=200; bb=0;
		}
	else if (n==3){
		rr=0;	gg=0; bb=200;
		}
		
		LITE(i,rr,gg,bb,253);

   }

}

///////////////////////////////////////////////////////////


function myDelay(mz){
	
	// mz = milliseconds
	// setTimeout(function() { doSomething(); }, mz);
	//setInterval(function(){alert("Hello")},mz);
	
		var ranNums = [];
	
	for (var n=1; n<= 10000; ++n){
 	ranNums = shuffle(100);
	
	}
	
	
	function doSomething(){
	
	// nada
	}

//////////////////////////////////////////////////////////
function shuffle(array) {
    var i = array.length,
        j = 0,
        temp;

    while (i--) {

        j = Math.floor(Math.random() * (i+1));

        // swap randomly chosen element with current element
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;

    }

    return array;
}



//////////////////////////////////////////////////////////

function rar(maxnum){
	
	var ranNums = [];
	
	for (var i=0; i<maxnum; i++) {ranNums[i]=i+1;}
		
	outlet(5,shuffle(ranNums));	

}
/////////////////////////////////////////

}