// playerMessages.js
// this script handles OSC messages coming from EEG Sonic by way of the Flask backend.
import io from '../node_modules/socket.io-client';

console.log('playerMessages reporting in');

const socket = io();


socket.on('event', function(data){
	console.log('received message');
	console.log(data);

	oscRecorder.receiveMessage(oscMessage);

	processMessage(oscMessage);
});



function processMessage (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));

     if (data[oscMessage.address].mute ) {
    	console.log(`${oscMessage.address} is muted`);
    	return false;
    }

    console.log(oscMessage.address);
    console.log(oscMessage.args[0]);

    updateData(oscMessage);
    updateTracks(oscMessage);
    adjustModulators(oscMessage);

}



function adjustModulators (oscMessage) {

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

    if (oscMessage.address === '/pac_rpt_parietal') {
    	console.log(oscMessage.address);
    	console.log(oscMessage.args[0]);
    	console.log(Math.pow(oscMessage.args[0],6));
    	sound.filterNode.frequency.setValueAtTime(Math.pow(oscMessage.args[0],15)*7000, sound.context.currentTime, 4);
    	console.log(sound.filterNode.frequency.value);
    }	
}

function updateData (oscMessage) {
	let address = oscMessage.address;
    // update ranges
    if (data[address].max === null || oscMessage.args[0] > data[address].max) {
		data[address].max = oscMessage.args[0]
		console.log(data[address].max);
		document.getElementById(`max${address}`).innerText = data[address].max.toFixed(3);
	}
	if (data[address].min === null || oscMessage.args[0] < data[address].min) {
		data[address].min = oscMessage.args[0]
		document.getElementById(`min${address}`).innerText = data[address].min.toFixed(3);
	}
	data[address].curr = oscMessage.args[0];
	document.getElementById(`curr${address}`).innerHTML = `${data[address].curr.toFixed(3)}`;
}

function updateTracks (oscMessage) {
	for (let i=0; i < sound.trackInfo.length; i++){
    	// calculate the new value
    	let value;
    	if (sound.trackInfo[i].input === oscMessage.address) {
    		
    		if (oscMessage.address == '/spr_beta_alpha') {
				if (sound.sprSpeedup) {
    				sound.bufferSources[i].playbackRate.value = Math.pow((1 + oscMessage.args[0]), 2);
    			} else {
    				sound.bufferSources[i].playbackRate.value = 1;
    			}
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
	    	sound.dataGains[i].gain.setTargetAtTime(newGain, sound.context.currentTime, 2);

	    	// update track edit GUI
	    	if (i == sound.selectedTrack) {
	    		rangeMinMax = document.getElementById(`range${i}`)
	    		rangeMinMax.innerText = data[sound.trackInfo[i].input].min.toFixed(5) + ' to ' + data[sound.trackInfo[i].input].max.toFixed(5);
	    		currentValue = document.getElementById(`currentValue${i}`)
	    		currentValue.innerText = data[sound.trackInfo[i].input].curr.toFixed(5);
	    	}
    	}
    }
}