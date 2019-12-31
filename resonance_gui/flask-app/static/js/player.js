import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';

const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS

const fileDirectory = 'static/samples/';

const defaultPreset = [
	{	fileName: 'res6-lowC.ogg', 
		gain: -35,
		inputs: [{ 	channel:'/pe_frontal', 
					type:'volume', 
					min: 0, 
					peak: 1, 
					max: 1, 
					reversed: false, 
					pinToData: false }
				]
	},
	{	fileName: 'res6-RLwave.ogg', 
		gain: -35,
		inputs: [{ 	channel:'/pe_frontal', 
					type:'volume', 
					min: 0, 
					peak: 1, 
					max: 1, 
					reversed: false, 
					pinToData: false }
				]
	}
]

const channelList = [
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

// A single track manages playback of a single soundfile.
class Track {
	constructor (filename, gain = null) {

		let mixerGUI = document.getElementById('resonanceMixer');
		this.mixerTrack = document.createElement('DIV');
		this.mixerTrack.classList.add('mixerTrack');
		mixerGUI.appendChild(this.mixerTrack);

		this.filename = filename;
		this.inputs = [];

		// load the file
		let buffer = new Tone.Buffer(fileDirectory + filename, ()=>{
			this.length = buffer.duration;
		})

		// create Tone.JS player
		this.player = new Tone.Player(buffer);
		this.player.autostart = true;
		this.player.loop = true;

		// create audio nodes
		this.userGain = sound.context.createGain();
		this.dataGain = sound.context.createGain();
		this.decayGain = sound.context.createGain();

		// connect audio nodes
		this.player.connect(this.userGain);
		this.userGain.connect(this.dataGain);
		this.dataGain.connect(this.decayGain);
		this.decayGain.connect(sound.masterGain);

		// create the mixer GUI elements
		this.userGainSlider = Track.createSlider(gain);
		this.userGainSlider.classList.add('userGainSlider');
		this.userGainSlider.addEventListener('input', ()=>{
			this.userGain.gain.value = Math.pow(10, this.userGainSlider.value/20);
		});

		this.dataGainSlider = Track.createSlider();
		this.dataGainSlider.classList.add('dataGainSlider');
		this.dataGainSlider.setAttribute('disabled', true);

		this.decayGainSlider = Track.createSlider();
		this.decayGainSlider.classList.add('decayGainSlider');
		this.decayGainSlider.setAttribute('disabled', true);


		// display GUI
		let info = document.createElement('div');
		info.innerText = this.filename;
		info.setAttribute('class','mixerTrackInfo');
		this.mixerTrack.appendChild(info);

		let container = document.createElement('div');
		container.setAttribute('class','mixerTrackSliders');
		container.appendChild(this.userGainSlider);
		container.appendChild(this.dataGainSlider);
		container.appendChild(this.decayGainSlider);
		this.mixerTrack.appendChild(container);

		let inputs = document.createElement('div');
		inputs.innerHTML = `<div>IN</div><div>${this.inputs.length}</div>`
		inputs.setAttribute('class','mixerTrackInputs')
		this.mixerTrack.appendChild(inputs);

	}

	static createSlider(gain) { // default gain value
		let slider = document.createElement('input');
		slider.setAttribute('class', 'h-slider');
		slider.setAttribute('type', 'range');
		slider.setAttribute('min', '-60');
		slider.setAttribute('max', '0');
		slider.setAttribute('step', '1');
		slider.setAttribute('value', gain ? gain : -10);
		slider.setAttribute('orient', 'horizonal');
		return slider;
	}	


	update (message) {
		console.log(message)
	}

	display () {

	}
}

// Signal are the message addresses - /spr_beta_alpha or /pe_frontal, etc.
class Signal {
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

	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);

	//load the selected preset
	preset.map(track => loadTrack(track));

	sound.context.resume();
}

function loadTrack(track) {
	sound.tracks.push(new Track(track.fileName));
}