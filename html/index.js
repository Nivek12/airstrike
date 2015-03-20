//Javascript for index

function Target(x, y, width, height, color)
{
	this.x = x;
	this.y = y;
	this.width = width;
	this. height = height;
	this.color = color;
}

//============METHODS==========

function initCanvas()
{
	mCanvas = $("#myCanvas");
	mCtx = mCanvas[0].getContext("2d");
}

function startPolling()
{
	mPoller = new com.TI.tokenPoller({
			"paramPage": "param_airstrike.html", 
			"refreshRate": 25,
			"valueMap": [{
			"paramId": "Test_Text",
				"outputSuccess": function(output) {
					parseTargets(output);
					console.log(output);
					//DEBUG_generateTargets();
					update();
				},
				"outputDefault": function() {
					//TODO something
				}
			}]
		});
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

function DEBUG_generateTargets()
{
	mTargets.length = 0;
	
	//Calculate coordinates
	var x = getRandomInt(0, mCanvas.width());
	var y = getRandomInt(0, mCanvas.height());
	var target = new Target(x,y,100,100,'red');
	mTargets.push(target);
}

function parseTargets(output)
{
	mTargets.length = 0;
	if(output != "none")
	{
		var info = output.split("|");
		var centerX = parseInt(info[0]);
		var centerY = parseInt(info[1]);
		var height = parseInt(info[2]);
		var width = parseInt(info[3]);
		var x = centerX - (width/2);
		var y = centerY - (height/2);
		var target = new Target(x,y,width,height, "red");
		mTargets.push(target);
	}
	
	
}

//Redraw canvas object
function update()
{
    mCtx.clearRect ( 0 , 0 , mCanvas.width(), mCanvas.height() );

	var i;
	for(i=0; i<mTargets.length; i++)
	{
		var target = mTargets[i];
		mCtx.fillStyle = target.color;
		mCtx.fillRect(target.x, target.y, target.width, target.height);
	}
}
	
var mPoller;
var mCanvas;
var mCtx;
var mTargets = [];

$(document).ready(function()
{
	initCanvas();
	startPolling();

});