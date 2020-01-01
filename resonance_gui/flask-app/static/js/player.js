import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';

const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS

const fileDirectory = 'static/samples/';

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
		inputs: [{ 	channel:'/pe_parietal', 
					type:'volume', 
					min: 0, 
					peak: 1, 
					max: 1, 
					reversed: true, 
					pinToData: false }
				]
	}
]

// GLOBAL VARIABLES
const sound = {
	context : null,
	masterGain : null,
	tracks : [],
	signals: {}
}


// CLASSES

// Signal are the collection of messags on a channel, each also has an associated DOM element
// A channel is the message address - /spr_beta_alpha or /pe_frontal, etc.
class Signal {
	constructor (channel) {
		this.channel = channel;
		this.min = null;
		this.max = null;
		this.curr = null;
		this.mute = false;
		this.last10 = [];

		// signalListContainer is a flex-box div in index.html
		let signalListGUI = document.getElementById('signalContainer');

		this.signalGUI = document.createElement('div');
		this.signalGUI.innerHTML = `<div>${this.channel}</div>`
		let signalTableGUI = document.createElement('table');
		signalTableGUI.innerHTML = `<tr><td>min</td><td>curr</td><td>max</td><td>avg3</td><td>avg5</td><td>avg10</td>`
		this.signalTableRow = document.createElement('tr');
		
		this.minGUI = this.createGUI();
		this.maxGUI = this.createGUI();
		this.currGUI = this.createGUI();
		this.currGUI.classList.add('currentValue');
		this.avg3GUI = this.createGUI();
		this.avg5GUI = this.createGUI();
		this.avg10GUI = this.createGUI();

		signalTableGUI.appendChild(this.signalTableRow);
		let signalBox = document.createElement('div');
		signalBox.classList.add('signalBox')

		signalBox.appendChild(this.signalGUI);
		signalBox.appendChild(signalTableGUI);

		signalListGUI.appendChild(signalBox);
	}

	createGUI () {
		let gui = document.createElement('td');
		gui.innerText = '';
		this.signalTableRow.appendChild(gui);
		return gui;
	}

	update (message) {
		// update last 10 messages
		if (this.last10.length == 10) { this.last10.shift(); }
		this.last10.push(message.args[0]);

		if (this.max === null || message.args[0] > this.max) {this.max = message.args[0]}

		if (this.min === null || message.args[0] < this.min) {this.min = message.args[0]}

		this.curr = message.args[0];

		if (this.last10.length >= 3) {this.avg3 = Math.eval(this.last10.slice(-3).join('+'))/3;}
		else {this.avg3 = Math.eval(this.last10.join('+'))/this.last10.length}

		if (this.last10.length >= 5) { this.avg5 = Math.eval(this.last10.slice(-5).join('+'))/5;}
		else {this.avg5 = Math.eval(this.last10.join('+'))/this.last10.length}

		if (this.last10.length >= 10) {this.avg10 = Math.eval(this.last10.slice(-10).join('+'))/10} 
		else {this.avg10 = Math.eval(this.last10.join('+'))/this.last10.length}

		this.display();
	}

	display () {
		this.maxGUI.innerText = this.max.toFixed(3);
		this.minGUI.innerText = this.min.toFixed(3);
		this.currGUI.innerText = this.curr.toFixed(3);
		this.avg3GUI.innerText = this.avg3.toFixed(3);
		this.avg5GUI.innerText = this.avg5.toFixed(3);
		this.avg10GUI.innerText = this.avg10.toFixed(3);
	}

}

// A single track manages playback of a single soundfile.
class Track {
	constructor (track) {

		this.fileName = track.fileName;
		this.inputs = [];

		// Add the GUI element to the mixer
		let mixerGUI = document.getElementById('resonanceMixer');
		this.mixerTrack = document.createElement('div');
		this.mixerTrack.classList.add('mixerTrack');
		mixerGUI.appendChild(this.mixerTrack);

		// load the file and create Tone.js player
		let buffer = new Tone.Buffer(fileDirectory + this.fileName, ()=>{
			this.length = buffer.duration;
		})
		this.player = new Tone.Player(buffer);
		this.player.autostart = true;
		this.player.loop = true;

		// create and connect audio nodes
		this.userGain = sound.context.createGain();
		this.dataGain = sound.context.createGain();
		this.decayGain = sound.context.createGain();
		this.player.connect(this.userGain);
		this.userGain.connect(this.dataGain);
		this.dataGain.connect(this.decayGain);
		this.decayGain.connect(sound.masterGain);

		// create & activate the mixer GUI elements
		this.userGainSlider = Track.createSlider(track.gain);
		this.userGain.gain.value = Math.pow(10, this.userGainSlider.value/20);
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

		// set up track inputs
		track.inputs.map(input => this.createInput(input));

		// display the GUI
		let infoGUI = document.createElement('div');
		infoGUI.innerText = this.fileName;
		infoGUI.setAttribute('class','mixerTrackInfo');
		this.mixerTrack.appendChild(infoGUI);

		let slidersGUI = document.createElement('div');
		slidersGUI.setAttribute('class','mixerTrackSliders');
		slidersGUI.appendChild(this.userGainSlider);
		slidersGUI.appendChild(this.dataGainSlider);
		slidersGUI.appendChild(this.decayGainSlider);
		this.mixerTrack.appendChild(slidersGUI);

		let inputsGUI = document.createElement('div');
		this.inputsCount = document.createElement('div');
		this.inputsCount.innerText = this.inputs.length;
		inputsGUI.innerHTML = `<div>IN</div>`
		inputsGUI.appendChild(this.inputsCount);
		inputsGUI.setAttribute('class','mixerTrackInputs')
		this.mixerTrack.appendChild(inputsGUI);
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

	createInput(input) {
		this.inputs.push(new Input(input.channel, input.type, input.min, input.peak, input.max, input.reversed, input.pinToData))
		console.log(this.inputs);
	}

	update (message) {
		console.log(message)
		for (let channel in this.inputs.map(input => input.channel)) {
			if (channel == message.address){
				if (input.type == 'volume') {
					// adjust track volume
					console.log('update ')
				}

				if (input.type == 'loopPoint') {
					// adjust looping behaviour
				}
			}
		}
	}

	display () {


	}

	getJSON() {
		let preset = { 'fileName': this.fileName, 'gain' : this.userGainSlider.value}
		preset.inputs = this.inputs.map((input)=>{ 
			return {'channel':input.channel, 'type': input.type, 'min': input.min, 'peak': input.peak, 'max': input.max, 'reversed': input.reversed, 'pinToData': input.pinToData }
		})
		return preset;
	}
}



// Interfaces between channels and tracks. A track can have several inputs.
class Input {
	constructor (channel, type='volume', min=0, peak=1, max=1, reversed=false, pinToData=false) {
		this.channel = channel;
		this.type = type;
		this.min = min;
		this.peak = peak;
		this.max = max;
		this.reversed = reversed;
		this.pinToData = pinToData;
	}
}

class Volume extends Input {

}

class LoopPoint extends Input {

}

class Message {

}


// INITIALIZE ENVIRONEMENT BEFORE LOADING AUDIO

// assign proper functions to GUI buttons
window.onload = function () {
	document.getElementById('startContextButton').addEventListener("click", () => { startAudio(defaultPreset) });
	document.getElementById('loadPresetButton').addEventListener('click', () => { loadPreset() })
	document.getElementById('savePresetButton').addEventListener('click', () => { savePreset() })

	// initalize channels
	channelList.forEach(channel => {
		sound.signals[channel] = new Signal(channel);
	})
}

// websocket for receiving messages
const socket = io('http://127.0.0.1:5000');

socket.on('connect', function() {
	socket.emit('my event', {data: "New connection!"})
})

socket.on('event', function(message){
	// oscRecorder.receiveMessage(data);
	sound.signals[message.address].update(message);
});

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
	console.log('saving app state as preset');
	// this is a hack for saving a file from the front-end
    var a = document.createElement("a");
    let tracksJSON = sound.tracks.map(track => track.getJSON());
    console.log(tracksJSON);
    var file = new Blob([JSON.stringify(tracksJSON)], {type: 'text/plain'});
    a.href = URL.createObjectURL(file);
    a.download = 'preset.txt';
    a.innerHTML = a.download;
    document.getElementById('resonancePlayer').appendChild(a);
    a.click();
    document.getElementById('resonancePlayer').removeChild(a);
    URL.revokeObjectURL(a.href);
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
	sound.tracks.push(new Track(track));
}