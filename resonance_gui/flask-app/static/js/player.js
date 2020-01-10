import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';
import '../node_modules/web-audio-recorder-js-webpack/lib/WebAudioRecorder.js';
// import './web-audio-recorder-js-master/lib/WebAudioRecorderMp3.js';


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
	{	fileName: 'harpascending2.ogg', 
		gain: -10,
		loopLength: 5,
		decayRate: 1, // decay rate is 0 to 1 value, 1 tends to stay on longer, 0 to fade quickly
		inputs: [{ 	channel:'/spr_beta_alpha',
					type:'loopPoint',
					value:'curr',
					min: 0.28, 
					peak: 0.35, 
					max: 0.35, 
					pinToData: false },
				{ 	channel:'/spr_beta_alpha', 
					type:'volume',
					value:'curr',
					min: 0.28, 
					peak: 0.34, 
					max: 0.45, 
					pinToData: false }

				]
	},
	{ 	fileName: 'softersynth2.ogg',
		gain: -15,
		loopLength: 6,
		decayRate: 1,
		inputs: [{	channel:'/spr_beta_alpha',
					type:'loopPoint',
					value: 'avg3',
					min: 0.26,
					peak: 0.32,
					max: 0.32,
					pinToData: false },
				{	channel:'/spr_beta_alpha',
					type:'volume',
					value: 'avg',
					min: 0.25,
					peak: 0.30,
					max: 0.35,
					pinToData: false }
		]
	},
	{	fileName: 'pianoascending.ogg', 
		gain: -1,
		loopLength: 5,
		decayRate: 1, // decay rate is 0 to 1 value, 1 tends to stay on longer, 0 to fade quickly
		inputs: [{ 	channel:'/spr_alpha_theta',
					type:'loopPoint',
					value:'curr',
					min: 0.25, 
					peak: 0.35, 
					max: 0.35, 
					pinToData: false },
				{ 	channel:'/spr_alpha_theta', 
					type:'volume',
					value:'curr',
					min: 0.25, 
					peak: 0.34, 
					max: 0.45, 
					pinToData: false }

				]
	},
	{	fileName: 'dpliLLxylophone.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_left_lateral', 
					type:'loopPoint',
					value: 'curr',
					min: 0.35, 
					peak: 0.35, 
					max: 0.48,   
					pinToData: false },
				{ 	channel:'/fp_dpli_left_lateral', 
					type:'volume', 
					value: 'curr',
					min: 0.30, 
					peak: 0.30, 
					max: 0.48, 
					pinToData: false },
				{ 	channel:'/fp_wpli_left_lateral', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},
	{	fileName: 'dpliLMmarimba.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_left_midline', 
					type:'loopPoint',
					value: 'curr',
					min: 0.35, 
					peak: 0.35, 
					max: 0.48,   
					pinToData: false },
				{ 	channel:'/fp_dpli_left_midline', 
					type:'volume', 
					value: 'curr',
					min: 0.30, 
					peak: 0.30, 
					max: 0.48, 
					pinToData: false },
				{ 	channel:'/fp_wpli_left_midline', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},
	{	fileName: 'dpliRMcelesta.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_right_midline', 
					type:'loopPoint',
					value: 'curr',
					min: 0.35, 
					peak: 0.35, 
					max: 0.48,   
					pinToData: false },
				{ 	channel:'/fp_dpli_right_midline', 
					type:'volume', 
					value: 'curr',
					min: 0.30, 
					peak: 0.30, 
					max: 0.48, 
					pinToData: false },
					{ 	channel:'/fp_wpli_right_midline', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},
	{	fileName: 'dpliRLvibraphone.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_right_lateral', 
					type:'loopPoint',
					value: 'curr',
					min: 0.35, 
					peak: 0.35, 
					max: 0.48,  
					pinToData: false },
				{ 	channel:'/fp_dpli_right_lateral', 
					type:'volume', 
					value: 'curr',
					min: 0.30, 
					peak: 0.30, 
					max: 0.48, 
					pinToData: false },
				{ 	channel:'/fp_wpli_right_lateral', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},

	// positive values of dPLI
	{	fileName: 'dpliLLxylophone.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_left_lateral', 
					type:'loopPoint',
					value: 'curr',
					min: 0.52, 
					peak: 0.65, 
					max: 0.65, 
					pinToData: false },
				{ 	channel:'/fp_dpli_left_lateral', 
					type:'volume', 
					value: 'curr',
					min: 0.52, 
					peak: 0.70, 
					max: 0.70, 
					pinToData: false },
				{ 	channel:'/fp_wpli_left_lateral', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},
	{	fileName: 'dpliLMmarimba.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_left_midline', 
					type:'loopPoint',
					value: 'curr',
					min: 0.52, 
					peak: 0.65, 
					max: 0.65, 
					pinToData: false },
				{ 	channel:'/fp_dpli_left_midline', 
					type:'volume', 
					value: 'curr',
					min: 0.52, 
					peak: 0.70, 
					max: 0.70, 
					pinToData: false },
				{ 	channel:'/fp_wpli_left_midline', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false }
				]
	},
	{	fileName: 'dpliRMcelesta.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_right_midline', 
					type:'loopPoint',
					value: 'curr',
					min: 0.52, 
					peak: 0.65, 
					max: 0.65,   
					pinToData: false },
				{ 	channel:'/fp_dpli_right_midline', 
					type:'volume', 
					value: 'curr',
					min: 0.52, 
					peak: 0.70, 
					max: 0.70, 
					pinToData: false },
				{ 	channel:'/fp_wpli_right_midline', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false },
				]
	},
	{	fileName: 'dpliRLvibraphone.ogg', 
		gain: -1,
		loopLength: 1.5,
		decayRate: 1,
		inputs: [{ 	channel:'/fp_dpli_right_lateral', 
					type:'loopPoint',
					value: 'curr',
					min: 0.52, 
					peak: 0.65, 
					max: 0.65,  
					pinToData: false },
				{ 	channel:'/fp_dpli_right_lateral', 
					type:'volume', 
					value: 'curr',
					min: 0.52, 
					peak: 0.70, 
					max: 0.70, 
					pinToData: false },
				{ 	channel:'/fp_wpli_right_lateral', 
					type:'volume',
					value: 'curr',
					min: 0.01, 
					peak: 0.1, 
					max: 0.1, 
					pinToData: false },
				]
	},
	
	// { 	fileName: 'woodblock1.ogg',
	// 	gain: -10,
	// 	loopLength: 5,
	// 	decayRate: 1,
	// 	inputs: [{	channel:'/spr_alpha_theta',
	// 				type:'loopPoint',
	// 				value: 'avg5',
	// 				min: 0.24,
	// 				peak: 0.25,
	// 				max: 0.25,
	// 				pinToData: false },
	// 			{	channel:'/spr_alpha_theta',
	// 				type:'volume',
	// 				value: 'avg5',
	// 				min: 0.24,
	// 				peak: 0.25,
	// 				max: 0.255,
	// 				pinToData: false }
	// 	]
	// },
	// { 	fileName: 'woodblock2.ogg',
	// 	gain: -10,
	// 	loopLength: 5,
	// 	decayRate: 1,
	// 	inputs: [{	channel:'/spr_alpha_theta',
	// 				type:'loopPoint',
	// 				value: 'avg5',
	// 				min: 0.25,
	// 				peak: 0.26,
	// 				max: 0.26,
	// 				pinToData: false },
	// 			{	channel:'/spr_alpha_theta',
	// 				type:'volume',
	// 				value: 'avg5',
	// 				min: 0.25,
	// 				peak: 0.26,
	// 				max: 0.265,
	// 				pinToData: false }
	// 	]
	// },
	// { 	fileName: 'woodblock3.ogg',
	// 	gain: -10,
	// 	loopLength: 5,
	// 	decayRate: 1,
	// 	inputs: [{	channel:'/spr_alpha_theta',
	// 				type:'loopPoint',
	// 				value: 'avg5',
	// 				min: 0.26,
	// 				peak: 0.27,
	// 				max: 0.27,
	// 				pinToData: false },
	// 			{	channel:'/spr_alpha_theta',
	// 				type:'volume',
	// 				value: 'avg5',
	// 				min: 0.26,
	// 				peak: 0.27,
	// 				max: 0.275,
	// 				pinToData: false }
	// 	]
	// },
	// { 	fileName: 'woodblock4.ogg',
	// 	gain: -10,
	// 	loopLength: 5,
	// 	decayRate: 1,
	// 	inputs: [{	channel:'/spr_alpha_theta',
	// 				type:'loopPoint',
	// 				value: 'avg5',
	// 				min: 0.27,
	// 				peak: 0.28,
	// 				max: 0.28,
	// 				pinToData: false },
	// 			{	channel:'/spr_alpha_theta',
	// 				type:'volume',
	// 				value: 'avg5',
	// 				min: 0.27,
	// 				peak: 0.28,
	// 				max: 0.285,
	// 				pinToData: false }
	// 	]
	// },
	// { 	fileName: 'woodblock5.ogg',
	// 	gain: -10,
	// 	loopLength: 8,
	// 	decayRate: 0.6,
	// 	inputs: [{	channel:'/spr_alpha_theta',
	// 				type:'loopPoint',
	// 				value: 'avg5',
	// 				min: 0.28,
	// 				peak: 0.29,
	// 				max: 0.29,
	// 				pinToData: false },
	// 			{	channel:'/spr_alpha_theta',
	// 				type:'volume',
	// 				value: 'avg5',
	// 				min: 0.28,
	// 				peak: 0.29,
	// 				max: 0.295,
	// 				pinToData: false }
	// 	]
	// },
	{	fileName: 'microtwinkle.ogg',
		gain: -1,
		loopLength: 4,
		decayRate: 1,
		inputs: [{	channel:'/pe_frontal',
					type: 'volume',
					value: 'curr',
					min: 0.79,
					peak: 0.85,
					max: 0.85,
					pinToData: false 
				},
				{	channel:'/pe_frontal',
					type: 'loopPoint',
					value: 'avg3',
					min: 0.6,
					peak: 0.8,
					max: 1,
					pinToData: false

				}
			]

	}]



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
		this.prev = null;
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

		this.prev = this.curr;
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
		this.loopLength = track.loopLength; // loop duration in seconds - actually the time between successive starts, signal plays for 1 1/2 times the loop length
		this.decayRate = track.decayRate;

		// Add the GUI element to the mixer
		let mixerGUI = document.getElementById('resonanceMixer');
		this.mixerTrack = document.createElement('div');
		this.mixerTrack.classList.add('mixerTrack');
		mixerGUI.appendChild(this.mixerTrack);

		// load the file and create Tone.js player
		let buffer = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{
			this.length = buffer.duration;
		})
		let buffer2 = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{})
		this.player = new Tone.Player(buffer);
		this.player.autostart = true;
		this.player.loop = true;
		this.player.fadeIn = this.loopLength / 2.;
		this.player.fadeOut = this.loopLength / 2.;
		// set up for looping
		this.player2 = new Tone.Player(buffer2); // used in loopPoint messages
		this.player2.autostart = false;
		this.player2.loop = false;
		this.player2.fadeIn = this.loopLength / 2.;
		this.player2.fadeOut = this.loopLength / 2.;
		this.looping = false;
		this.nextLoopPlayer = this.player;
		// for now just always 50% overlap, linear fade up and down, listen to it

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
			track.update(message);
		})
	}

	createInput(input) {
		this.inputs.push(new Input(input.channel, input.type, input.value, input.min, input.peak, input.max, input.pinToData))
	}

	calculateValue(input) {
		// got a message and matched it with an input to this track.
		let value = sound.signals[input.channel][input.value];

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

		let newValue = 0;

		// if range min and max are the same, signal is always on
		if (rangeMax == rangeMin) {
			newValue = 1;
		}
		// case where the peak equals the max means it stays on above the max
		else if (rangeMax == rangePeak) {
			newValue = (value - rangeMin)/(rangeMax-rangeMin);
		}
		// case where the peak equals min, it stays on below min
		else if (rangeMin == rangePeak) {
			newValue = 1 - ((value - rangeMin)/(rangeMax-rangeMin));
		}
		// otherwise signal value depends on whether it is above or below peak
		else if (value > rangeMin && value < rangePeak) {
			newValue = (value - rangeMin)/(rangePeak-rangeMin);
		}
		else if (value >= rangePeak && value < rangeMax) {
			newValue = 1 - ((value - rangePeak)/(rangeMax-rangePeak));
		}

		// clean up out-of-range values
		if (newValue < 0) {newValue = 0}
		if (newValue > 1) {newValue = 1}

		return newValue; // returns a number from 0 to 1 for this input		
	}

	update (message) {
		let gainChanged = false; // allows for several volume inputs to same track, they are multiplied
		let changedGain = 0;
		let newGain;
		this.inputs.forEach((input) => {
			if (input.channel == message.address){
				if (input.type == 'volume' && !gainChanged) { // calculates results of all volume inputs when it sees the first one
					this.inputs.forEach((input) => {
						if (input.type == 'volume') {
							console.log(input);
							newGain = this.calculateValue(input);

							if (gainChanged) { // keeps track if there are several volume inputs on a single track
								//newGain = (newGain + changedGain)/2;
								newGain = newGain * changedGain;
								changedGain = newGain;
							} else {
								gainChanged = true;
								changedGain = newGain;
							}
						}
					})

					this.dataGainSlider.value = (newGain * 20) - 20;
					let targetGain = Math.pow(10, this.dataGainSlider.value/20);
					if (newGain == 0) {targetGain = 0;}
					// ramps to new gain in 3 seconds
					this.dataGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);
							
					// // values for calculating decay
					// let oldGainForDecay = Math.pow(10, this.dataGainSlider.value/20);
					// // calculate decay gain
					// let newGainForDecay = Math.pow(10, this.dataGainSlider.value/20);

					// let oldDecay = this.decayGain.gain.value;
					// let newDecay = this.decayRate*oldDecay + (Math.abs(newGainForDecay - oldGainForDecay)); // Looks at absolute difference between last two volumes
					// console.log("oldDecay: " + oldDecay + " newDecay: " + newDecay + " oldGainForDecay: " + oldGainForDecay + " newGainForDecay: " + newGainForDecay);
					// this.decayGainSlider.value = (newDecay * 20 ) - 20;
					// let targetDecay = Math.pow(10, this.decayGainSlider.value/20);
					// if (newDecay == 0) {targetDecay = 0;}
					// this.decayGain.gain.setTargetAtTime(targetDecay, sound.context.currentTime, 2);

				}

				if (input.type == 'loopPoint') {
					// adjust looping behaviour
					// calculate at what point of the file to start
					let value  = this.calculateValue(input)
					let startPoint = value*(this.length-this.loopLength);

					// calculate "momentum" bsed on current signal vs average
					//let momentum = (sound.signals[input.channel].curr - sound.signals[input.channel].avg3)*this.length*0.15; // not safe for all channels!
					let momentum = 0.01*this.length;

					if (!this.looping) {
						this.player.stop(sound.context.currentTime + (this.loopLength / 2));
						this.player2.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
						this.looping = true;
					}
					clearTimeout(this.nextLoop);
					this.triggerNextGrain(startPoint, momentum);
				}
			}
		})

	}

	triggerNextGrain(startPoint, momentum) {
		// catch the cases where momentum takes us outside of bounds
		if (startPoint > (this.length - 1.5*(this.loopLength) )) { startPoint = this.length - 1.5*(this.loopLength) };
		if (startPoint < 0)  {startPoint = 0};

		this.nextLoopPlayer.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
		this.nextLoopPlayer == this.player ? this.nextLoopPlayer = this.player2 : this.nextLoopPlayer = this.player;

		if (sound.context.state == 'running') {
			this.nextLoop = setTimeout(()=>{this.triggerNextGrain(startPoint + momentum, momentum)}, this.loopLength*1000);
		}
		return true;
	}

	display () {


	}

	getJSON() {
		let preset = { 'fileName': this.fileName, 'gain' : this.userGainSlider.value}
		preset.inputs = this.inputs.map((input)=>{ 
			return {'channel':input.channel, 'type': input.type, 'value': input.value, 'min': input.min, 'peak': input.peak, 'max': input.max, 'pinToData': input.pinToData }
		})
		return preset;
	}
}



// Interfaces between channels and tracks. A track can have several inputs.
class Input {
	constructor (channel, type, value, min, peak, max, pinToData) {
		this.channel = channel;
		this.type = type;
		this.value = value;
		this.min = min;
		this.peak = peak;
		this.max = max;
		this.pinToData = pinToData;
	}
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
	//sound.signals[message.address].update(message);
	Signal.processMessage(message);
});

// instantiate objects

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

	// activate main GUI buttons
	const playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{
		sound.context.resume();
	})

	const stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.setTargetAtTime(Math.pow(10, masterGainSlider.value/20),sound.context.currentTime, 0.1);
	}, false);


	// initialize the audio recorder

	// const saveRecording = (blob, encoding) => {
	// 	console.log('save recording');
	// 	console.log(blob);
	// 	console.log(encoding);
 //    	var link = document.createElement('a');
 //    	link.href = URL.createObjectURL(blob);
 //    	link.download = new Date().toISOString() + '.' + encoding;
 //    	link.innerHTML = link.download;
 //    	//add the new audio and a elements to the li element
 //    	list = document.getElementById('audioDownloadLinks');
 //    	list.appendChild(link);
 //    	link.click();
	// }

	// let audioRecorder = new WebAudioRecorder(sound.masterGain, {
	// 		workerDir: 'static/node_modules/web-audio-recorder-js-webpack/lib/',
	// 		encoding: 'mp3',
	// 		encodeAfterRecord: true
	// 	});

	// audioRecorder.setOptions({timeLimit: 3600}); // maximum recording is 1 hour;

	// audioRecorder.onComplete = function (recorder, blob) {
	// 	console.log("encoding complete");
	// 	saveRecording(blob, recorder.encoding);
	// }

	// const toggleRecordingAudio = document.getElementById('toggleRecordingAudio');
	// toggleRecordingAudio.addEventListener('click', ()=>{
	// 	if (audioRecorder.isRecording()) {
	// 		audioRecorder.finishRecording();
	// 		document.getElementById('toggleRecordingAudio').innerText = "Start Recording Audio";
	// 	} else {
	// 		audioRecorder.startRecording();
	// 		document.getElementById('toggleRecordingAudio').innerText = "Stop Recording Audio";
	// 	}
	// });


	//load the selected preset
	preset.map(track => loadTrack(track));

	//sound.context.resume();
}

function loadTrack(track) {
	sound.tracks.push(new Track(track));
}





