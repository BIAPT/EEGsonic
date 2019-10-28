
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

port.on("message", function (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));
    //console.log(oscMessage.args);
    for (let h=0; h < oscMessage.args.length; h++) {
    	if (h >= sound.data.length) {
			sound.data.push({min: oscMessage.args[h], max: oscMessage.args[h]});
		} else {
    		if (sound.data[h].max === null || oscMessage.args[h] > sound.data[h].max) {
    			sound.data[h].max = oscMessage.args[h]
    		} else if (sound.data[h].min === null || oscMessage.args[h] < sound.data[h].min) {
    			sound.data[h].min = oscMessage.args[h]
    		}
    	}
    }

    for (let i=0; i < sound.bufferFiles.length; i++){
    	// calculate the new value
    	let value;
    	if (sound.bufferFiles[i].pinToData) { // if it's relative to limits of data stream
    		let range = sound.data[sound.bufferFiles[i].input].max - sound.data[sound.bufferFiles[i].input].min;
    		value = (oscMessage.args[sound.bufferFiles[i].input] - sound.data[sound.bufferFiles[i].input].min)/range;
    		value = (value*2)-1;
    	} else { // if it's got its own set range
    		let range = sound.bufferFiles[i].max - sound.bufferFiles[i].min;
    		value = (oscMessage.args[sound.bufferFiles[i].input] - sound.bufferFiles[i].min)/range;
    		value = (value*2)-1;
    	}

    	let slider = document.getElementById(`dataGain${i}`);
    	// set the value to the slider and gain
    	if (sound.bufferFiles[i].reversed) {
    		slider.value = (-value * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    	} else {
			slider.value = (value * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    	}
    	if (i == sound.selectedTrack) {
    		rangeMinMax = document.getElementById(`range${i}`)
    		rangeMinMax.innerText = sound.data[sound.bufferFiles[i].input].min + ' to ' + sound.data[sound.bufferFiles[i].input].max
    	}
    }
});

port.open();

var sayHello = function () {
    port.send({
        address: "/hello",
        args: ["world"]
    });
};