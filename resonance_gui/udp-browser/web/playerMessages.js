
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

port.on("message", function (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));
    //console.log(oscMessage.args);

    let address = oscMessage.address;

    // update ranges
    if (data[address].max === null || oscMessage.args[0] > data[address].max) {
		data[address].max = oscMessage.args[0]
	}
	if (data[address].min === null || oscMessage.args[0] < data[address].min) {
		data[address].min = oscMessage.args[0]
	}
	data[address].curr = oscMessage.args[0];



  //   for (let h=0; h < oscMessage.args.length; h++) {
  //   	if (h >= sound.data.length) {
		// 	sound.data.push({min: oscMessage.args[h], max: oscMessage.args[h]});
		// } else {
  //   		if (sound.data[h].max === null || oscMessage.args[h] > sound.data[h].max) {
  //   			sound.data[h].max = oscMessage.args[h]
  //   		} else if (sound.data[h].min === null || oscMessage.args[h] < sound.data[h].min) {
  //   			sound.data[h].min = oscMessage.args[h]
  //   		}
  //   	}
  //   }

    for (let i=0; i < sound.trackInfo.length; i++){
    	// calculate the new value
    	let value;
    	if (sound.trackInfo[i].input === oscMessage.address) {
    		console.log(sound.trackInfo[i].input);
	    	if (sound.trackInfo[i].pinToData) { // if it's relative to limits of data stream
	    		let range = data[sound.trackInfo[i].input].max - data[sound.trackInfo[i].input].min;
	    		value = (oscMessage.args[0] - data[sound.trackInfo[i].input].min)/range;
	    		value = (value*2)-1;
	    	} else { // if it's got its own set range
	    		let range = sound.trackInfo[i].max - sound.trackInfo[i].min;
	    		value = (oscMessage.args[0] - sound.trackInfo[i].min)/range;
	    		value = (value*2)-1;
	    	}

	    	let slider = document.getElementById(`dataGain${i}`);
	    	// set the value to the slider and gain
	    	if (sound.trackInfo[i].reversed) {
	    		slider.value = (-value * 20)-20;
	    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
	    	} else {
				slider.value = (value * 20)-20;
	    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
	    	}
	    	if (i == sound.selectedTrack) {
	    		rangeMinMax = document.getElementById(`range${i}`)
	    		rangeMinMax.innerText = data[sound.trackInfo[i].input].min.toFixed(5) + ' to ' + data[sound.trackInfo[i].input].max.toFixed(5);
	    		currentValue = document.getElementById(`currentValue${i}`)
	    		currentValue.innerText = data[sound.trackInfo[i].input].curr.toFixed(5);
	    	}
    	}
    }
});

port.open();

// this is still here in case we need it at some point!
var sayHello = function () {
    port.send({
        address: "/hello",
        args: ["world"]
    });
};