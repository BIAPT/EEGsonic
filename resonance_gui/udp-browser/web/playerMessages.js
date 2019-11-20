
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

oscRecorder = new OSCRecorder();
oscPlayer = new OSCPlayer();
//oscRecorder.startRecording();


// SPR SPEEDUP
sprSpeedup = true;

port.on("message", function (oscMessage) {
    //console.log(oscMessage.args);

    oscRecorder.receiveMessage(oscMessage);

    processMessage(oscMessage);
    
});

function processMessage (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));

    console.log(oscMessage.address);
    console.log(oscMessage.args[0]);

    updateData(oscMessage);
    updateTracks(oscMessage);



    if (oscMessage.address === '/fp_wpli_left_lateral') {
    	sound.wpliGain[0].gain.setTargetAtTime(oscMessage.args[0] * 10, sound.context.currentTime, 0.5);

    }

    if (oscMessage.address === '/fp_wpli_left_midline') {
    	sound.wpliGain[1].gain.setTargetAtTime(oscMessage.args[0] * 10, sound.context.currentTime, 0.5);

    }

    if (oscMessage.address === '/fp_wpli_right_midline') {
    	sound.wpliGain[2].gain.setTargetAtTime(oscMessage.args[0] * 10, sound.context.currentTime, 0.5);

    }

    if (oscMessage.address === '/fp_wpli_right_lateral') {
    	sound.wpliGain[3].gain.setTargetAtTime(oscMessage.args[0] * 10, sound.context.currentTime, 0.5);

    }

    // if (oscMessage.address === '/spr_beta_alpha') {
    // 	console.log(oscMessage.address);
    // 	console.log(oscMessage.args[0]);
    // 	console.log(Math.pow(2,oscMessage.args[0]));
    // 	sound.filterNode.frequency.setValueAtTime((Math.pow(2,oscMessage.args[0])-1)*40000, sound.context.currentTime, 4);
    // 	console.log(sound.filterNode.frequency.value);
    // }
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
    		if (sprSpeedup && oscMessage.address == '/spr_beta_alpha') {
    			sound.bufferSources[i].playbackRate.value = 1 + oscMessage.args[0];
    		}

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
	    		value = -value;  // this is a crumby way of centering the range around -10
	    	}
			slider.value = (value * 10)-10;
	    	let newGain = Math.pow(10, slider.value/20);
	    	if (value == -1) {newGain = 0};

	    	// this actually sets the gain
	    	sound.dataGains[i].gain.setTargetAtTime(newGain, sound.context.currentTime, 1);


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