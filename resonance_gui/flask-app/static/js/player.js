//import { processMessage, adjustModulators, updateData, updateTracks } from './playerMessages.js';
//import { OSCPlayer, OSCRecorder } from './oscRecorder'
import io from '../node_modules/socket.io-client';
import Tone from '../node_modules/tone';

console.log('player online');

const AudioContext = window.AudioContext || window.webkitAudioContext;

// this is the default preset loaded when none is selected
const defaultPreset = [
	{fileName: 'res6-lowC.ogg', trackName: 'Low C', input:'/pe_frontal', tone: true, reversed: false, gain: -35, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'res6-LLwave.ogg', trackName: 'Left Lateral', input:'/fp_wpli_left_lateral', tone: true, reversed: false, gain: -35, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'res6-LMwave.ogg', trackName: 'Left Midline', input:'/fp_wpli_left_midline', tone: true, reversed: false, gain: -35, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'res6-RMwave.ogg', trackName: 'Right Midline', input:'/fp_wpli_right_midline', tone: true, reversed: false, gain: -35, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'res6-RLwave.ogg', trackName: 'Right Lateral', input:'/fp_wpli_right_lateral', tone: true, reversed: false, gain: -35, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'slow_gloc_melody.ogg', trackName: 'SPR alpha/theta', input:'/spr_alpha_theta', tone: true, reversed: false, gain: null, min: 0, max:1, peak: 1, pinToData: true, length: null},
	{fileName: 'flutefib.ogg', trackName: 'LL dPLI', input:'/fp_dpli_left_lateral', tone: true, reversed: false, gain: null, min: 0, max:1, peak: 1, pinToData: true, length: null}
]
// const defaultPreset = [
// 		{fileName: 'res1_bass.mp3', trackName: 'Bass', input: '/fp_dpli_left_midline', tone: false, reversed: false, gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_bells.mp3', trackName: 'Bells', input: '/fp_wpli_left_midline', tone: false, reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},	
// 		{fileName: 'res1_guitar.mp3', trackName: 'Guitar', input: '/hl_relative_position', tone: false, reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_clarinet.mp3', trackName: 'Clarinet', input: '/pe_frontal', tone: false, reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_cellos.mp3', trackName: 'Cello', input: '/pe_parietal', tone: false,  reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_drone.mp3', trackName: 'Drone', input: '/spr_beta_alpha', tone: false, reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_flutes.mp3', trackName: 'Flute', input: '/spr_alpha_theta', tone: false, reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
// 		{fileName: 'res1_violins.mp3', trackName: 'Violin', input: '/spr_alpha_theta', tone: true, reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true}
// 		]

// initialize sound graph
const sound = {
	context : null,
	masterGain : null,
	trackInfo : [],  	// information about soundFiles, presets populate this field
	players: [],
	pitchShifts: [],
	buffers : [],      	// Buffer for loading files
	bufferSources : [],	// Actual Web Audio Node connected to rest of graph
	userGains: [],		// user-inputted gain for each track
	dataGains: [],		// per-track gain from biosignals
	data: [],			// keeps track of range of input singals
	selectedTrack: null,
	wpliGain: [],
	PE_parietal: null,
	filterNode: null,
	preFilterGain: null,
	sprSpeedup: false
}

var data = {
	'/fp_dpli_left_midline': {min: null, max: null, curr: null, mute: false},
	'/fp_dpli_left_lateral': {min: null, max: null, curr: null, mute: false}, 
	'/fp_dpli_right_midline': {min: null, max: null, curr: null, mute: false}, 
	'/fp_dpli_right_lateral': {min: null, max: null, curr: null, mute: false}, 
	'/fp_wpli_left_midline': {min: null, max: null, curr: null, mute: false}, 
	'/fp_wpli_left_lateral': {min: null, max: null, curr: null, mute: false}, 
	'/fp_wpli_right_midline': {min: null, max: null, curr: null, mute: false}, 
	'/fp_wpli_right_lateral': {min: null, max: null, curr: null, mute: false}, 
	'/hl_relative_position': {min: null, max: null, curr: null, mute: false}, 
	'/pe_frontal': {min: null, max: null, curr: null, mute: false}, 
	'/pe_parietal': {min: null, max: null, curr: null, mute: false}, 
	'/pac_rpt_frontal': {min: null, max: null, curr: null, mute: false}, 
	'/pac_rpt_parietal': {min: null, max: null, curr: null, mute: false}, 
	'/spr_beta_alpha': {min: null, max: null, curr: null, mute: false}, 
	'/spr_alpha_theta': {min: null, max: null, curr: null, mute: false}, 
	'/td_front_back': {min: null, max: null, curr: null, mute: false}
}



window.onload = function () {
	document.getElementById('startContext').addEventListener("click", () => { startAudio(defaultPreset) });
	document.getElementById('loadPreset').addEventListener("click", () => { loadPreset() });
	document.getElementById('savePreset').addEventListener("click", () => { savePreset() });
	document.getElementById('loadOSC').addEventListener("click", () => { loadOSC() });
	document.getElementById('toggleOSC').addEventListener("click", () => { toggleOSC() });
	document.getElementById('resetOSC').addEventListener("click", () => { resetOSC() });
	document.getElementById('sendOSC').addEventListener("click", () => { sendOSC() });
	document.getElementById('loadRanges').addEventListener("click", () => { loadRanges() });
	document.getElementById('saveRanges').addEventListener("click", () => { saveRanges() });
	document.getElementById('toggleSPRSpeedup').addEventListener("click", () => { toggleSPRSpeedup() });
	document.getElementById('addNewTrack').addEventListener("click", () => { addNewTrack() });
}

// Web Audio requires user input to start audio. 
function startAudio(preset) {

	// Handle GUI
	document.getElementById('contextStarted').removeAttribute('style');
	document.getElementById('savePreset').removeAttribute('disabled');

	const button = document.getElementById('startContext')
	if (button) {button.parentNode.removeChild(button);}
	

	sound.context = new AudioContext();
	sound.context.suspend();
	Tone.context = sound.context;



	sound.trackInfo = preset;

	loadOSCTable(); 
	
	sound.preFilterGain = sound.context.createGain();
	sound.masterGain = sound.context.createGain();
	let filter = false;
	if (filter) {
		sound.filterNode = sound.context.createBiquadFilter();
		sound.filterNode.connect(sound.masterGain);
		sound.filterNode.frequency.setValueAtTime(4000, sound.context.currentTime);
		// handle master gain slider, play and stop buttons
		sound.preFilterGain.connect(sound.filterNode);
	} else {
		sound.preFilterGain.connect(sound.masterGain);
	}
	sound.masterGain.connect(sound.context.destination);

	// set up modulator for wPLI signals
	for (let i=0; i<4; i++) {
		sound.wpliGain[i] = sound.context.createGain();
		sound.wpliGain[i].connect(sound.preFilterGain);
		sound.wpliGain[i].gain.value = 0;
	}

	// default value of master gain is coded in player.html. Gain is converted to decibels
	const masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	}, false);

	const playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{sound.context.resume()})

	const stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const recordButton = document.getElementById('toggleRecording')
	recordButton.addEventListener('click', ()=>{toggleRecording()});

	const recordOSC = document.getElementById('recordOSC')
	recordOSC.addEventListener('click', ()=>{toggleOSCRecording()})

	loadMixer();

	for (let i=0; i < sound.trackInfo.length; i++) {
		setUpTrack(i); // ASYNC function! Adds gain nodes and then loads soundfile
	}

	console.log(sound.trackInfo);
	// //create a synth and connect it to the master output (your speakers)
	// var synth = new Tone.Synth().toMaster();

	// //play a middle 'C' for the duration of an 8th note
	// synth.triggerAttackRelease("C4", "8n");

}


// clears and sets up empty divs for each track in the mixer.
// this makes sure they are in the right order on the screen
function loadMixer() {
	const mixer = document.getElementById('mixerBox');
	mixer.innerHTML= '';

	for (let i=0; i < sound.trackInfo.length; i++) {
		mixer.insertAdjacentHTML('beforeend', `
			<td id='Track${i}' class='mixerTrack'>Track ${i}</td>
			`)
	}
}

function setUpTrack(i) {
	sound.userGains[i] = sound.context.createGain();
	sound.dataGains[i] = sound.context.createGain();
	sound.userGains[i].connect(sound.dataGains[i]);
	if (sound.trackInfo[i].input == '/fp_dpli_left_lateral') {
		sound.dataGains[i].connect(sound.wpliGain[0]);
	} else if (sound.trackInfo[i].input == '/fp_dpli_left_midline') {
		sound.dataGains[i].connect(sound.wpliGain[1]);
	} else if (sound.trackInfo[i].input == '/fp_dpli_right_midline') {
		sound.dataGains[i].connect(sound.wpliGain[2]);
	} else if (sound.trackInfo[i].input == '/fp_dpli_right_lateral') {
		sound.dataGains[i].connect(sound.wpliGain[3]);
	} else{
		sound.dataGains[i].connect(sound.preFilterGain);
	}
	loadSoundfile(i);
}

// this is separate from setUpTrack because you can load a soundfile after
async function loadSoundfile(i) { 
	let fileDirectory = 'static/samples/';
	let fileName = fileDirectory + sound.trackInfo[i].fileName;
	let buffer = new Tone.Buffer(fileName, ()=>{
		console.log(buffer.duration);
		sound.trackInfo[i].length = buffer.duration;
	})

	sound.players[i] = new Tone.Player(buffer);
	

	if (sound.trackInfo[i].input == '/spr_alpha_theta') {
		sound.pitchShifts[i] = new Tone.PitchShift(0);
		sound.pitchShifts[i].windowSize = 0.05;
		sound.players[i].connect(sound.pitchShifts[i]);
		Tone.connect(sound.pitchShifts[i], sound.userGains[i]);
	}
	else {
		Tone.connect(sound.players[i], sound.userGains[i]);
		sound.pitchShifts[i] = null;
	}
	sound.players[i].loop = true;
	sound.players[i].autostart = true;
	loadMixerTrack(i);
	return true;
}

function loadMixerTrack(i) {

	document.getElementById(`Track${i}`).innerHTML = `
		<td id='Track${i}' class='mixerTrack'><span>Track ${i}</span><br>
			<span>${sound.trackInfo[i].trackName}</span><br>
			<div id='info${i}' class='trackInfo'></div></td>
		<div>
			<input id='userGain${i}' type='range' min='-60' max='0' step='1' value='-10' class='v-slider userGainSlider' orient="vertical">
			<input id='dataGain${i}' type='range' min='-20' max='0' step='1' value='-10' class='v-slider dataGainSlider' orient='vertical' disabled>
		</div>
		<button id='mute${i}'>Mute</button>
		<button id='edit${i}'>Edit</button>
		`;

	insertInputInfo(i);

	let userGain = document.getElementById(`userGain${i}`)
	if (sound.trackInfo[i].gain !== null) {userGain.value = sound.trackInfo[i].gain};

	sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
	userGain.addEventListener('input', ()=>{
		sound.trackInfo[i].gain = userGain.value;
		sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
	})

	let muteButton = document.getElementById(`mute${i}`)
	muteButton.addEventListener('click', ()=>{
		if (muteButton.innerText === 'Mute') {
			console.log(`mute track ${i}`);
			sound.players[i].mute = true;
			muteButton.innerText = 'Unmute'
		} else {
			sound.players[i].mute = false;
			muteButton.innerText = 'Mute'
		}
	})

	let editButton = document.getElementById(`edit${i}`)
	editButton.addEventListener('click', () => {
		sound.selectedTrack = i;
		showEdit(i)
	});
}

// displays which input stream is used in the mixer
function insertInputInfo(i) {
	let info = document.getElementById(`info${i}`);
	if (sound.trackInfo[i].input == null) {
		info.innerHTML = `<div>No input</div><div>normal</div>`
	} else if (sound.trackInfo[i].reversed) {
		info.innerHTML = `<div>${sound.trackInfo[i].input.substring(0, 17)}</div><div>reversed</div>`;
	} else {
		info.innerHTML = `<div>${sound.trackInfo[i].input.substring(0, 17)}</div><div>normal</div>`
	}
}

// displays the edit menu in the upper right corner
function showEdit(i) {
	let gui = document.getElementById('mixerGui');
	gui.innerHTML = `
		<table>
			<tr><td><b>Track ${i}</b></td><td><button style='flex-grow: 0' id='removeTrack${i}'>Remove Track</button></td>
			<tr><td style='width: 100px'>Name:</td><td> ${sound.trackInfo[i].trackName}</td></tr>
			<tr><td>File:</td><td> ${sound.trackInfo[i].fileName} <br>
				<input id='fileSelect${i}' type='file'></input><button id='fileSelectConfirm${i}'>Change</button></td></tr>
			<tr><td>Input:</td><td> <select id='selectedInput${i}'></select> <input id='reverseCheckbox${i}' type='checkbox' ${sound.trackInfo[i].reversed ? 'checked' : ''}> reversed</td></tr>
			<tr><td>Range:</td>
				<td class='flex-row'>
						<input id='rangeMin${i}' class='number-input' type='number' step='0.01' value='${sound.trackInfo[i].min}' > to 
						<input id='rangeMax${i}' type='number' class='number-input' step='0.01' value='${sound.trackInfo[i].max}' > 
						<input id='rangeCheckbox${i}' type='checkbox' ${sound.trackInfo[i].pinToData ? 'checked': ''}> Pin range to input
				</td>
			</tr>
			<tr><td>Range so far:</td><td id='range${i}' > ${data[sound.trackInfo[i].input] && data[sound.trackInfo[i].input].min ? data[sound.trackInfo[i].input].min.toFixed(5) + ' to ' + data[sound.trackInfo[i].input].max.toFixed(5) : 'No input'}</td></tr>
			<tr><td>Current value:</td><td id='currentValue${i}'> ${data[sound.trackInfo[i].input] && data[sound.trackInfo[i].input].curr ? data[sound.trackInfo[i].input].curr.toFixed(5) : 'No input'}
		</table>
	`
	document.getElementById(`removeTrack${i}`).addEventListener('click', () => {
		removeTrack(i);
	})


	let inputs = document.getElementById(`selectedInput${i}`);

	var option = document.createElement('option');
	option.text = 'None';
	option.value = null;
	for (let j=0; j<Object.keys(data).length; j++) {
		var option = document.createElement('option');
		option.text = Object.keys(data)[j];
		option.value = Object.keys(data)[j];
		inputs.appendChild(option);
	}

	inputs.value = sound.trackInfo[i].input;
	inputs.addEventListener('change', (event)=>{
		sound.trackInfo[i].input = event.target.value;
		sound.dataGains[i].disconnect();
		if (sound.trackInfo[i].input == '/fp_dpli_left_lateral') {
			sound.dataGains[i].connect(sound.wpliGain[0]);
		} else if (sound.trackInfo[i].input == '/fp_dpli_left_midline') {
			sound.dataGains[i].connect(sound.wpliGain[1]);
		} else if (sound.trackInfo[i].input == '/fp_dpli_right_midline') {
			sound.dataGains[i].connect(sound.wpliGain[2]);
		} else if (sound.trackInfo[i].input == '/fp_dpli_right_lateral') {
			sound.dataGains[i].connect(sound.wpliGain[3]);
		} else {
			sound.dataGains[i].connect(sound.preFilterGain);
		}
		insertInputInfo(i);
		showEdit(i);
	});

	let reverseCheckbox = document.getElementById(`reverseCheckbox${i}`);
	reverseCheckbox.addEventListener('change', ()=>{
		sound.trackInfo[i].reversed = event.target.checked;
		insertInputInfo(i);
	});

	let rangeCheckbox = document.getElementById(`rangeCheckbox${i}`);
	rangeCheckbox.addEventListener('change', ()=>{
		sound.trackInfo[i].pinToData = event.target.checked;
		insertInputInfo(i);
	})

	let rangeMin = document.getElementById(`rangeMin${i}`)
	rangeMin.addEventListener('change', ()=>{
		sound.trackInfo[i].min = parseFloat(event.target.value);
	})

	let rangeMax = document.getElementById(`rangeMax${i}`)
	rangeMax.addEventListener('change', ()=>{
		sound.trackInfo[i].max = parseFloat(event.target.value);
	})

	let fileSelectButton = document.getElementById(`fileSelectConfirm${i}`);
	fileSelectButton.addEventListener('click', ()=>{
		let fileSelection = document.getElementById(`fileSelect${i}`);
		if (fileSelection.value !== '') {
			sound.bufferSources[i].disconnect();
			let src = fileSelection.value.split('\\')
			sound.trackInfo[i].fileName = src[src.length - 1]; // warning - might only work on windows
			sound.trackInfo[i].trackName = sound.trackInfo[i].fileName.split('.')[0];
			loadSoundfile(i);
			showEdit(i);
		}
	})
}


// *** ADD AND REMOVE TRACKS ***
function addNewTrack() {
	let filename = document.getElementById('newTrack').value.split('\\');
	filename = filename[filename.length - 1];
	sound.trackInfo.push({fileName: filename, trackName: filename.split('.')[0], input: null, reversed: false, gain: null, min: 0, max: 1, pinToData: true},)
	

	const mixer = document.getElementById('mixerBox');
	mixer.insertAdjacentHTML('beforeend', `
			<td id='Track${sound.trackInfo.length - 1}' class='mixerTrack'>Track ${sound.trackInfo.length - 1}</td>
			`)

	setUpTrack(sound.trackInfo.length - 1);
}



function removeTrack(i) {
	let contextState = sound.context.state
	console.log(contextState);

	sound.players[i].disconnect();
	sound.players.splice(i,1);
	sound.pitchShifts.splice(i,1);
	sound.trackInfo.splice(i, 1);
	sound.buffers.splice(i, 1);
	sound.userGains.splice(i, 1);
	sound.dataGains.splice(i, 1);
	if (contextState == 'suspended') {
		sound.context.suspend();
	}

	let mixerGui = document.getElementById('mixerGui');
	mixerGui.innerHTML='';
	sound.selectedTrack = null;
	loadMixer();
	for (let i=0; i < sound.trackInfo.length; i++) {
		loadMixerTrack(i); // ASYNC function! Adds gain nodes and then loads soundfile
	}
}


// *** HANDLING PRESETS ***
function loadPreset() {
	let fileName = document.getElementById('presetSelector').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];

	if (fileName !== '') { // do nothing if the input field is blank
		// clear out any pre-existing bufferSources
		if (typeof sound !== 'undefined') {
			for (let i=0; i<sound.bufferSources.length; i++) {
				sound.bufferSources[i].disconnect();
			}
		}

		fetch('static/playerPresets/' + fileName)
			.then(response => response.text())
			.then(preset => {
				startAudio(JSON.parse(preset));
			})
	}
}

function savePreset() {
	console.log('saving app state as preset');
	// this is a hack for saving a file from the front-end
    var a = document.createElement("a");
    var file = new Blob([JSON.stringify(sound.trackInfo)], {type: 'text/plain'});
    a.href = URL.createObjectURL(file);
    a.download = 'preset.txt';
    a.innerHTML = a.download;
    let presets = document.getElementById('presetsButtons');
    presets.appendChild(a);
    a.click();
    presets.removeChild(a);
    URL.revokeObjectURL(a.href);
}


// OSC FUNCTIONS //
function toggleOSCRecording() {
	oscRecorder.toggleRecording()
	if (oscRecorder.recording) {
		document.getElementById('recordOSC').innerText='Stop Recording OSC'
	} else document.getElementById('recordOSC').innerText='Start Recording OSC'
}

function loadOSC() {
	let fileName = document.getElementById('OSCEventFile').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];
	console.log(fileName);

	if (fileName !== '') {
		fetch('static/playerEvents/' + fileName)
				.then(response => response.text())
				.then(events => {
					oscPlayer.loadOSCEvents(JSON.parse(events));
					document.getElementById('toggleOSC').removeAttribute('disabled');
					document.getElementById('resetOSC').removeAttribute('disabled');
				})
	}
}

function toggleOSC() {
	let button = document.getElementById('toggleOSC');
	console.log(oscPlayer.playing);
	if (oscPlayer.playing) {
		oscPlayer.cancelNextEvent();
		button.innerText = 'Play OSC';
	} else {
		playOSC();
		button.innerText = 'Pause OSC';
	}
}

function playOSC() {
	console.log('playing OSC');
	oscPlayer.playOSCEvents();
}

function resetOSC() {
	if (oscPlayer.playing) {
		toggleOSC();
	}
	oscPlayer.setOSCStep(0);
}

function sendOSC() {
	console.log(Object.keys(data));
	for (var key of Object.keys(data)){
		let input = document.getElementById(`osc${key}`)
		if (input.value) {
			let oscMessage = {'address': key, 'args':[parseFloat(input.value)]};

    		updateData(oscMessage);
    		updateTracks(oscMessage);
    		adjustModulators(oscMessage);
		}
	}
}

function loadOSCTable() {
	let oscTable = document.getElementById('oscTable');
	oscTable.innerHTML = `<tr>
                            <td style='width:150px'>Name</td>
                            <td>Min</td>
                            <td>Current</td>
                            <td>Max</td>
                            <td>Muted</td>
                            <td>New</td>
                            <td>Reset</td>
                        </tr>`
	for (const [key, value] of Object.entries(data)) {
  		oscTable.insertAdjacentHTML('beforeend', 
  			`<tr>
  				<td>${key}</td>
  				<td id='min${key}'>${data[key].min ? data[key].min.toFixed(3) : 'none'}</td>
  				<td ><b id='curr${key}'>${data[key].curr ? data[key].curr.toFixed(3) : 'none'}</b></td>
  				<td id='max${key}'>${data[key].max ? data[key].max.toFixed(3) : 'none'}</td>
  				<td><input id='mute${key}' type='checkbox' ${data[key].mute ? 'checked' : ''}></td>
  				<td><input id='osc${key}' type='number' class='number-input' step='0.01'></input></td>
  				<td><button id='reset${key}'>Reset</button></td>
  			</tr>`)

  		document.getElementById(`mute${key}`).addEventListener('click', ()=>{
  			data[key].mute = event.target.checked;
  		})

  		document.getElementById(`reset${key}`).addEventListener('click', ()=>{
  			data[key] = {min: null, max: null, curr: null, mute: true};
  			document.getElementById(`max${key}`).innerText = 'none';
  			document.getElementById(`min${key}`).innerText = 'none';
  			document.getElementById(`curr${key}`).innerText = 'none';
  			if (!document.getElementById(`mute${key}`).checked) {
  				console.log(document.getElementById(`mute${key}`).checked);
  				document.getElementById(`mute${key}`).click();
  			}
  			for (let i=0; i<sound.trackInfo.length; i++) {
  				if (sound.trackInfo[i].input == key) {
  					//sound.trackInfo[i].gain = userGain.value;
					//sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
					console.log('resetting gain');
  					document.getElementById(`dataGain${i}`).value = -10;
  					console.log(document.getElementById(`dataGain${i}`).value);
  					sound.dataGains[i].gain.setTargetAtTime(Math.pow(10, (-10/20)), sound.context.currentTime, 2);
  				}
  			}
  		})
  	}
}



// handling presets for input ranges
function loadRanges() {
	let fileName = document.getElementById('oscRanges').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];
	console.log(fileName);

	if (fileName !== '') {
		fetch('static/ranges/' + fileName)
				.then(response => response.json())
				.then(events => {
					console.log(data);
					console.log(events);

					data = events;
					loadOSCTable();
					//oscPlayer.loadOSCEvents(JSON.parse(events));
					//document.getElementById('playOSCFile').removeAttribute('disabled');
					//document.getElementById('resetOSCFile').removeAttribute('disabled');
				})
	}
}

function saveRanges() {
	console.log('saving data ranges as preset');
	// function download(content, fileName, contentType) {
    var a = document.createElement("a");
    var file = new Blob([JSON.stringify(data)], {type: 'text/plain'});
    a.href = URL.createObjectURL(file);
    a.download = 'ranges.txt';
    a.innerHTML = a.download;
    let presets = document.getElementById('presetsButtons');
    presets.appendChild(a);
    a.click();
    presets.removeChild(a);
    URL.revokeObjectURL(a.href);
}

function toggleSPRSpeedup () {
	sound.sprSpeedup = !sound.sprSpeedup;
	console.log('SPRSpeedup ' + sound.sprSpeedup);
}





// Websocket set-up and processing incoming messages
const socket = io();

socket.on('event', function(data){
	oscRecorder.receiveMessage(data);
	processMessage(data);
});



function processMessage (oscMessage) {

	document.getElementById('message').innerText = JSON.stringify(oscMessage, undefined, 2);

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

    // if (oscMessage.address === '/pac_rpt_parietal') {
    // 	console.log(oscMessage.address);
    // 	console.log(oscMessage.args[0]);
    // 	console.log(Math.pow(oscMessage.args[0],6));
    // 	sound.filterNode.frequency.setValueAtTime(Math.pow(oscMessage.args[0],15)*7000, sound.context.currentTime, 4);
    // 	console.log(sound.filterNode.frequency.value);
    // }	
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

    		if (oscMessage.address == '/spr_alpha_theta') {
    			sound.players[i].playbackRate = Math.pow((1 + oscMessage.args[0]), 2);
    			// console.log(sound.players[i].playbackRate);
    			// sound.pitchShifts[i].pitch = 12*Math.log2(1/(0.8 + oscMessage.args[0]))
    		}

    		if (oscMessage.address == '/fp_dpli_left_lateral') {
    			//sound.players[i].
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
			if (slider) {
				 slider.value = (value * 10)-10;
				 let newGain = Math.pow(10, slider.value/20);
				 if (value == -1) {newGain = 0};

	    	// this actually sets the gain
	    		sound.dataGains[i].gain.setTargetAtTime(newGain, sound.context.currentTime, 2);
			}


	    	// update track edit GUI
	    	if (i == sound.selectedTrack) {
	    		let rangeMinMax = document.getElementById(`range${i}`)
	    		rangeMinMax.innerText = data[sound.trackInfo[i].input].min.toFixed(5) + ' to ' + data[sound.trackInfo[i].input].max.toFixed(5);
	    		let currentValue = document.getElementById(`currentValue${i}`)
	    		currentValue.innerText = data[sound.trackInfo[i].input].curr.toFixed(5);
	    	}
    	}
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

class OSCPlayer {
	constructor() {
		this._playing = false;
		this._currentEvent = 0;
		this._nextEvent = null;
		this.timeout = null;
		this.events = []
		this.processMessage = processMessage

		this.loadOSCEvents = (events) => {
			this.events = events;
		}

		this.playOSCEvents = (i) => {
			console.log('playing OSC');
			this._playing = true;
			this.playEvent(this._currentEvent);
		}

		this.playEvent = (i) => {
			if (i < this.events.length) {
				this._currentEvent = i;
				processMessage(this.events[i].message);
				this.sequenceNextEvent(i);
			}
		}

		this.sequenceNextEvent = (i) => {
			if (i + 1 < this.events.length) {
				let delay = this.events[i+1].time - this.events[i].time;
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
	}

	get playing() {
		return this._playing;
	}
}



const oscPlayer = new OSCPlayer();
const oscRecorder = new OSCRecorder();



// for recording audio

var recorder;

function toggleRecording() {
	let recordButton = document.getElementById('toggleRecording');
	if (recorder == null) {
		initializeRecorder();
		console.log('recorder initialized');
	}
	if (recorder.isRecording()) {
		recordButton.innerText = 'Start Recording';
		stopRecording();
	} else {
		recordButton.innerText = 'Stop Recording';
		startRecording();
	}

}

function initializeRecorder() {
	recorder = new WebAudioRecorder(sound.masterGain, {
		workerDir: 'web-audio-recorder-js-master/lib/',
		encoding: 'mp3',
		encodeAfterRecord: true
	});
	// recorder.setEncoding('mp3');
	recorder.setOptions({timeLimit: 3000}) // maximum recording duration - set to 50 minutes (3000 seconds)
	recorder.onComplete = function(recorder, blob) {
            console.log("Encoding complete");
            createDownloadLink(blob, recorder.encoding);
        }
}

function startRecording() {
	console.log('starting recording');
	recorder.startRecording();
}

function stopRecording() {
	console.log('stopping recording');
	recorder.finishRecording();
}

function createDownloadLink(blob, encoding) {
	console.log('creating download link');
    var url = URL.createObjectURL(blob);
    var link = document.createElement('a');
    var li = document.createElement('li');
    link.href = url;
    link.download = new Date().toISOString() + '.' + encoding;
    console.log(link.download);
    link.innerHTML = link.download;
    //add the new audio and a elements to the li element 
    list = document.getElementById('downloadLinks');
    li.appendChild(link); //add the li element to the ordered list 
    list.appendChild(li);
}
