
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

oscRecorder = new OSCRecorder();
oscPlayer = new OSCPlayer();
//oscRecorder.startRecording();

port.on("message", function (oscMessage) {
    //console.log(oscMessage.args);

    oscRecorder.receiveMessage(oscMessage);

    processMessage(oscMessage);
    
});

function processMessage (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));

    console.log(oscMessage.address);
    updateData(oscMessage);
    updateTracks(oscMessage);
}

function updateData (oscMessage) {
	let address = oscMessage.address;
    // update ranges
    if (data[address].max === null || oscMessage.args[0] > data[address].max) {
		data[address].max = oscMessage.args[0]
	}
	if (data[address].min === null || oscMessage.args[0] < data[address].min) {
		data[address].min = oscMessage.args[0]
	}
	data[address].curr = oscMessage.args[0];
}

function updateTracks (oscMessage) {
	for (let i=0; i < sound.trackInfo.length; i++){
    	// calculate the new value
    	let value;
    	if (sound.trackInfo[i].input === oscMessage.address) {
	    	if (sound.trackInfo[i].pinToData) { // if it's relative to limits of data stream
	    		let inputRange = data[sound.trackInfo[i].input].max - data[sound.trackInfo[i].input].min;
	    		let pinRange = sound.trackInfo[i].max - sound.trackInfo[i].min;
	    		let effectiveRange = inputRange * pinRange;
	    		let min = (sound.trackInfo[i].min * inputRange) + data[sound.trackInfo[i].input].min;
	    		value = (oscMessage.args[0] - min)/effectiveRange;
	    	} else { // if it's got its own set range
	    		let range = sound.trackInfo[i].max - sound.trackInfo[i].min;
	    		value = (oscMessage.args[0] - sound.trackInfo[i].min)/range;
	    	}

	    	if (value < 0) {value = 0} // filter sounds below input range
    		if (value > 1) {value = 1}
    		value = (value*2)-1; // this is a crumby way of centering the range around -10

	    	let slider = document.getElementById(`dataGain${i}`);
	    	// set the value to the slider and gain
	    	if (sound.trackInfo[i].reversed) {
	    		slider.value = (-value * 10)-10;  // this is a crumby way of centering the range around -10
	    	} else {
				slider.value = (value * 10)-10;
	    	}
	    	let newGain = Math.pow(10, slider.value/20);
	    	if (value == 0) {newGain = 0};
	    	sound.dataGains[i].gain.linearRampToValueAtTime(newGain, sound.context.currentTime + 4);
	    	if (i == sound.selectedTrack) {
	    		rangeMinMax = document.getElementById(`range${i}`)
	    		rangeMinMax.innerText = data[sound.trackInfo[i].input].min.toFixed(5) + ' to ' + data[sound.trackInfo[i].input].max.toFixed(5);
	    		currentValue = document.getElementById(`currentValue${i}`)
	    		currentValue.innerText = data[sound.trackInfo[i].input].curr.toFixed(5);
	    	}
    	}
    }
}

port.open();

// this is still here in case we need it at some point!
var sayHello = function () {
    port.send({
        address: "/hello",
        args: ["world"]
    });
};