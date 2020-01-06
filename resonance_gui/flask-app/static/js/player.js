import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';

const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS

const sampleFilePath = 'static/samples/';
const eventsFilePath = 'static/playerEvents/';

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
		gain: -10,
		inputs: [{ 	channel:'/pe_frontal', 
					type:'volume', 
					min: 0, 
					peak: 1, 
					max: 1, 
					pinToData: true }
				]
	},
	{	fileName: 'res6-RLwave.ogg', 
		gain: -10,
		inputs: [{ 	channel:'/pe_parietal', 
					type:'volume', 
					min: 0, 
					peak: 0, 
					max: 1, 
					pinToData: true }
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

		let signalListGUI = document.getElementById('signalContainer');

		// create the right-side pannel of signals
		this.signalGUI = document.createElement('div');
		this.signalGUI.innerHTML = `<div>${this.channel}</div>`
		let signalTableGUI = document.createElement('table');
		signalTableGUI.innerHTML = `<tr><td>min</td><td>curr</td><td>max</td><td>avg3</td><td>avg5</td><td>avg10</td>`
		this.signalTableRow = document.createElement('tr');
		
		this.minGUI = this.createGUI();
		this.currGUI = this.createGUI();
		this.currGUI.classList.add('currentValue');
		this.maxGUI = this.createGUI();
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

	static processMessage(message) {
		sound.signals[message.address].update(message);
		Track.processMessage(message);
	}

	update (message) {
		// update last 10 messages
		if (this.last10.length == 10) { this.last10.shift(); }
		this.last10.push(message.args[0]);

		if (this.max === null || message.args[0] > this.max) {this.max = message.args[0]}
		if (this.min === null || message.args[0] < this.min) {this.min = message.args[0]}

		this.curr = message.args[0];

		this.avg3 = this.last10.slice(-3).reduce((a,c)=>{return a+c})/this.last10.slice(-3).length;
		this.avg5 = this.last10.slice(-5).reduce((a,c)=>{return a+c})/this.last10.slice(-5).length;
		this.avg10 = this.last10.slice(-10).reduce((a,c)=>{return a+c})/this.last10.slice(-10).length;

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
		let buffer = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{
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
			this.userGain.gain.setTargetAtTime(Math.pow(10, this.userGainSlider.value/20), sound.context.currentTime, 0.1);
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
		slider.setAttribute('min', '-20');
		slider.setAttribute('max', '0');
		slider.setAttribute('step', '1');
		slider.setAttribute('value', gain ? gain : -10);
		slider.setAttribute('orient', 'horizonal');
		return slider;
	}	

	static processMessage(message) {
		// searches the list of tracks and inputs for matching message channel
		sound.tracks.forEach((track)=>{
			track.inputs.forEach((input) => {
				if (input.channel == message.address) {
					track.update(message);
				}
			})
		})
	}

	createInput(input) {
		this.inputs.push(new Input(input.channel, input.type, input.min, input.peak, input.max, input.pinToData))
	}

	update (message) {
		let gainChanged = false; // allows for several volume inputs to same track, they are multiplied
		let changedGain = 0;
		this.inputs.forEach((input) => {
			if (input.channel == message.address){
				if (input.type == 'volume') {
					// adjust track volume

					// got a message and matched it with a volume input to this track.
					let value = message.args[0];

					// determine the range of the signal we are looking for
					let rangeMin = input.min;
					let rangeMax = input.max;
					let rangePeak = input.peak;

					// adjust range if it's relative to the data so far
					if (input.pinToData) {
						let signalRangeMin = sound.signals[input.channel].min;
						let signalRangeMax = sound.signals[input.channel].max;
						let signalRange = signalRangeMax - signalRangeMin;
						rangeMin = (rangeMin * signalRange) + signalRangeMin;
						rangeMax = (rangeMax * signalRange) + signalRangeMin;
						rangePeak = (rangePeak * signalRange) + signalRangeMin;
					} 

					let newGain;

					// if range min and max are the same, signal is always on
					if (rangeMax == rangeMin) {
						newGain = 1;
					}
					// case where the peak equals the max means it stays on above the max
					else if (rangeMax == rangePeak) {
						newGain = (value - rangeMin)/(rangeMax-rangeMin);
					}
					// case where the peak equals min, it stays on below min
					else if (rangeMin == rangePeak) {
						newGain = 1 - ((value - rangeMin)/(rangeMax-rangeMin));
					}
					// otherwise signal value depends on whether it is above or below peak
					else if (value > rangeMin && value < rangePeak) {
						newGain = (value - rangeMin)/(rangePeak-rangeMin);
					}
					else if (value >= rangePeak && value < rangeMax) {
						newGain = 1 - ((value - rangePeak)/(rangeMax-rangePeak));
					}

					// clean up out-of-range values
					if (newGain < 0) {newGain = 0}
					if (newGain > 1) {newGain = 1}

					if (gainChanged) { // keeps track if there are several volume inputs on a single track
						newGain = newGain * changedGain;
						changedGain = newGain;
					} else {
						gainChanged = true;
						changedGain = newGain;
					}

					// gain maps to slider value, then slider value converts to audioNode gain
					this.dataGainSlider.value = (newGain * 20) - 20;
					// ramps to new gain in 3 seconds
					this.dataGain.gain.setTargetAtTime(Math.pow(10, this.dataGainSlider.value/20), sound.context.currentTime, 3);
				}

				if (input.type == 'loopPoint') {
					// adjust looping behaviour
				}
			}
		})
	}

	display () {


	}

	getJSON() {
		let preset = { 'fileName': this.fileName, 'gain' : this.userGainSlider.value}
		preset.inputs = this.inputs.map((input)=>{ 
			return {'channel':input.channel, 'type': input.type, 'min': input.min, 'peak': input.peak, 'max': input.max, 'pinToData': input.pinToData }
		})
		return preset;
	}
}



// Interfaces between channels and tracks. A track can have several inputs.
class Input {
	constructor (channel, type, min, peak, max, pinToData) {
		this.channel = channel;
		this.type = type;
		this.min = min;
		this.peak = peak;
		this.max = max;
		this.pinToData = pinToData;
	}
}

class Volume extends Input {

}

class LoopPoint extends Input {

}

class Message {

}

/// HANDLING OSC RECORDINGS/PLAYBACK

class OSCPlayer {
	constructor() {
		this._playing = false;
		this._currentEvent = 0;
		this._nextEvent = null;
		this.timeout = null;
		this.events = [];

		this.loadOSCEvents = () => {
			let fileName = document.getElementById('OSCEventFile').value.split('\\'); 
			fileName = fileName[fileName.length - 1];

			if (fileName !== '') {
				fetch(eventsFilePath + fileName)
					.then(response => response.text())
					.then(events => {
						this.events = JSON.parse(events);
						document.getElementById('toggleOSC').removeAttribute('disabled');
						document.getElementById('resetOSC').removeAttribute('disabled');
						console.log(this.events.length + ' events loaded');
					})
			}
		}

		this.toggleOSC = () => {
			let button = document.getElementById('toggleOSC');
			if (this._playing) {
				this.cancelNextEvent();
				button.innerText = 'Play OSC';
			} else {
				this.playOSC();
				button.innerText = 'Pause OSC';
			}
		}

		this.playOSC = () => {
			console.log('playing OSC');
			this._playing = true;
			this.playEvent(this._currentEvent);
		}

		this.playEvent = (i) => {
			if (i < this.events.length) {
				this._currentEvent = i;
				// message processing goes here!
				Signal.processMessage(this.events[i].message);
				this.sequenceNextEvent(i);
			}
		}

		this.sequenceNextEvent = (i) => {
			if (i + 1 < this.events.length) {
				let delay = this.events[i+1].time - this.events[i].time;
				// SAMPLE RATE PATCH
				delay = delay/4;
				this.timeout = setTimeout(this.playEvent, delay, i+1);
			} else { console.log('reached end of OSC')};
		}

		this.cancelNextEvent = () => {
			clearTimeout(this.timeout);
			this._playing = false;
		}

		this.setOSCStep = (step) => {
			this._currentEvent = step;
		}

		this.resetOSC = () => {
			if (this.playing) {
				this.toggleOSC();
			}
			oscPlayer.setOSCStep(0);
		}
	}

	get playing() {
		return this._playing;
	}
}

class OSCRecorder {
	constructor() {
		this._recording = false;
		this.timeStarted = null;
		let events = [];
		console.log('created OSC recorder');

		this.startRecording = () => {
			this._recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = () => {
			this._recording = false;
			console.log('OSC stopped recording');
			console.log(events);
			this.saveEvents();
			this.timeStarted = null;
			events = [];
		}

		this.toggleRecording = () => {
			if (this._recording) {
				this.stopRecording();
			} else this.startRecording();
		}

		this.receiveMessage = (message) => {
			if (this._recording) {
				events.push({'time': Date.now() - this.timeStarted, 'message': message});
			}
		}

		this.saveEvents = () => {
			console.log('saving events to file');
			// this is a hacky way of saving a text file
		    var a = document.createElement("a");
		    var file = new Blob([JSON.stringify(events)], {type: 'text/plain'});
		    a.href = URL.createObjectURL(file);
		    a.download = 'oscEvents.txt';
		    a.innerHTML = a.download;
		    let dummy = document.getElementById('messageArea');
		    dummy.appendChild(a);
		    a.click();
		    dummy.removeChild(a);
		    URL.revokeObjectURL(a.href);
		}

		this.play = () => {
			playOSCEvents(events);
		}
	}

	set recording (value) {
		console.log('recording: ' + value);
		this._recording = value;
	}

	get recording () {
		return this._recording;
	}
}

// INITIALIZE ENVIRONEMENT BEFORE LOADING AUDIO

// assign proper functions to GUI buttons
window.onload = function () {
	document.getElementById('startContextButton').addEventListener("click", () => { startAudio(defaultPreset) });
	document.getElementById('loadPresetButton').addEventListener('click', () => { loadPreset() });
	document.getElementById('savePresetButton').addEventListener('click', () => { savePreset() });
	document.getElementById('loadOSC').addEventListener('click', () => { oscPlayer.loadOSCEvents() });
	document.getElementById('toggleOSC').addEventListener("click", () => { oscPlayer.toggleOSC() });
	document.getElementById('resetOSC').addEventListener("click", () => { oscPlayer.resetOSC() });
	
	// initalize list of channels
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

// OSC HANDLERS

const oscPlayer = new OSCPlayer();
const oscRecorder = new OSCRecorder();

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

	document.getElementById('mainControls').removeAttribute('style');

	sound.context = new AudioContext();
	sound.context.suspend();
	Tone.context = sound.context;

	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);

	// activate main audio GUI
	const playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{sound.context.resume()})

	const stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.setTargetAtTime(Math.pow(10, masterGainSlider.value/20),sound.context.currentTime, 0.1);
	}, false);


	//load the selected preset
	preset.map(track => loadTrack(track));

	sound.context.resume();
}

function loadTrack(track) {
	sound.tracks.push(new Track(track));
}





