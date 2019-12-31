import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';

const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS

defaultPreset = [
	{	fileName: 'res6-lowC.ogg', 
		gain: -35,
		inputs: [ 	channel:'/pe_frontal', 
					type:'volume', 
					min: 0, 
					peak: 1, 
					max: 1, 
					reversed: false, 
					pinToData: false ]
	}
]

channelList = [
	'/fp_dpli_left_midline',
	'/fp_dpli_left_lateral', 
	'/fp_dpli_right_midline', 
	'/fp_dpli_right_lateral', 
	'/fp_wpli_left_midline', 
	'/fp_wpli_left_lateral', 
	'/fp_wpli_right_midline', 
	'/fp_wpli_right_lateral', 
	'/hl_relative_position', 
	'/pe_frontal', 
	'/pe_parietal', 
	'/pac_rpt_frontal', 
	'/pac_rpt_parietal', 
	'/spr_beta_alpha', 
	'/spr_alpha_theta', 
	'/td_front_back'
]




// GLOBAL VARIABLES
const sound = {
	context : null,
	masterGain : null,
	tracks : []
}


// CLASSES
// A single track manages playback of a single soundfile. It has a number of behaviours.
class Track {
	constructor (filename) {
		this.filename = filename;
		this.inputs = [];

		this.player = null;
		this.userGain = sound.context.createGain();
		this.dataGain = sound.context.createGain();
		this.decayGain = sound.context.createGain();

	}

	update (message) {
		console.log(message)
	}

}

// Channels are the message addresses - /spr_beta_alpha or /pe_frontal, etc.
class Channel {
	constructor () {
		this.min = null;
		this.max = null;
		this.curr = null;
		this.mute = false;
		this.last5 = []
	}
}

// Interfaces between channels and tracks. A track can have several inputs.
class Input {
	constructor () {
		this.channel = '';
		this.type = '';
		this.min = null;
		this.peak = null;
		this.max = null;
		this.reversed = false
	}
}

class Volume extends Input {

}

class LoopPoint extends Input {

}

class Message {

}

// assign proper functions to GUI buttons
window.onload = function () {
	document.getElementById('startContextButton').addEventListener("click", () => { startAudio(defaultPreset) });
}


// handling presets
function loadPreset() {
	let fileName = document.getElementById('presetFileInput').value.split('\\');
	fileName = fileName[fileName.length - 1];

	if (fileName !== '') { // check if input field is blank
		fetch('static/playerPresets/' + fileName)
			.then(response => response.text())
			.then(preset => {
				startAudio(JSON.parse(preset));
			})
	} else {
		console.log('please select a preset file from the playerPresets folder');
	}
}

function savePreset() {

}


// initializing page
function startAudio(preset) {
	console.log('audio started!');

	// remove the start context button
	const button = document.getElementById('startContextButton')
	if (button) {button.parentNode.removeChild(button);}


	sound.context = new AudioContext();
	sound.context.suspend();
	Tone.context = sound.context;
}

function loadTrack() {

}