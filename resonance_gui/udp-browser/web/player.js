console.log('player online');

const AudioContext = window.AudioContext || window.webkitAudioContext;

// this is the default preset loaded when none is selected
const defaultPreset = [
		{fileName: 'res1_bass.mp3', trackName: 'Bass', input: '/fp_dpli_left_midline', reversed: false, gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_bells.mp3', trackName: 'Bells', input: '/fp_wpli_left_midline', reversed: true,  gain: null, min: -1, max: 1, pinToData: true},	
		{fileName: 'res1_guitar.mp3', trackName: 'Guitar', input: '/hl_relative_position', reversed: false,  gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_clarinet.mp3', trackName: 'Clarinet', input: '/pe_frontal', reversed: true,  gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_cellos.mp3', trackName: 'Cello', input: '/pe_parietal',  reversed: false,  gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_drone.mp3', trackName: 'Drone', input: '/spr_beta_alpha', reversed: false,  gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_flutes.mp3', trackName: 'Flute', input: '/spr_alpha_theta', reversed: true,  gain: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_violins.mp3', trackName: 'Violin', input: '/spr_alpha_theta', reversed: false,  gain: null, min: -1, max: 1, pinToData: true}
		]

// Web Audio requires user input to start audio. 
function startAudio(preset) {

	// Handle GUI
	document.getElementById('contextStarted').removeAttribute('style');
	document.getElementById('savePreset').removeAttribute('disabled');

	button = document.getElementById('startContext')
	if (button) {button.parentNode.removeChild(button);}
	
	// initialize sound graph
	sound = {
		context : new AudioContext(),
		masterGain : null,
		trackInfo : [],  	// information about soundFiles, presets populate this field
		buffers : [],      	// Buffer for loading files
		bufferSources : [],	// Actual Web Audio Node connected to rest of graph
		userGains: [],		// user-inputted gain for each track
		dataGains: [],		// per-track gain from biosignals
		data: [],			// keeps track of range of input singals
		selectedTrack: null
	}
	sound.context.suspend();

	data = {
		'/fp_dpli_left_midline': {min: null, max: null},
		'/fp_dpli_left_lateral': {min: null, max: null}, 
		'/fp_dpli_right_midline': {min: null, max: null}, 
		'/fp_dpli_left_lateral': {min: null, max: null}, 
		'/fp_wpli_left_midline': {min: null, max: null}, 
		'/fp_wpli_left_lateral': {min: null, max: null}, 
		'/fp_wpli_right_midline': {min: null, max: null}, 
		'/fp_wpli_right_lateral': {min: null, max: null}, 
		'/hl_relative_position': {min: null, max: null}, 
		'/pe_frontal': {min: null, max: null}, 
		'/pe_parietal': {min: null, max: null}, 
		'/pac_rpt_frontal': {min: null, max: null}, 
		'/pac_rpt_parietal': {min: null, max: null}, 
		'/spr_beta_alpha': {min: null, max: null}, 
		'/spr_alpha_theta': {min: null, max: null}, 
		'/td_front_back': {min: null, max: null}
	}
	
	sound.trackInfo = preset;

	// handle master gain slider, play and stop buttons
	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);

	// default value of master gain is coded in player.html. Gain is converted to decibels
	masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	}, false);

	playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{sound.context.resume()})

	stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})


	initializeInputs();

	loadMixer();

	for (let i=0; i < sound.trackInfo.length; i++) {
		setUpTrack(i); // ASYNC function! Adds gain nodes and then loads soundfile
	}

}

function initializeInputs() {
	// assigns inputs each track with none specified. Does not touch the GUI
	let j = 0;
	for (let i=0; i < sound.trackInfo.length; i++) {
		if (sound.trackInfo[i].input == null) {
			sound.data[j] = {min: null, max: null}
	    	sound.trackInfo[i].input = j;
	    	if (sound.trackInfo[i].reversed === false) { j++; }
	    } else {
	    	sound.data[sound.trackInfo[i].input] = {min: null, max: null}
	    }
	}
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
	sound.dataGains[i].connect(sound.masterGain);
	loadSoundfile(i);
}

// this is separate from setUpTrack because you can load a soundfile after
async function loadSoundfile(i) { 
	fileDirectory = './samples/';

	fileName = fileDirectory + sound.trackInfo[i].fileName;

	fetch(fileName, {mode: "cors"})
		.then(function(resp) {return resp.arrayBuffer()})
		.then((buffer) => {
			console.log(buffer);
			sound.context.decodeAudioData(buffer, (abuffer) => {
				sound.bufferSources[i] = sound.context.createBufferSource();
				sound.bufferSources[i].buffer = abuffer;
				sound.bufferSources[i].connect(sound.userGains[i]);
				sound.bufferSources[i].loop = true;
				sound.bufferSources[i].start();
				loadMixerTrack(i);   // loads the GUI element for this track
			});
		});
	return true;
}

function loadMixerTrack(i) {

	document.getElementById(`Track${i}`).innerHTML = `
		<td id='Track${i}' class='mixerTrack'>Track ${i}<br>
			${sound.trackInfo[i].trackName}<br>
			<div id='info${i}'></div></td>
		<div>
			<input id='userGain${i}' type='range' min='-60' max='0' step='1' value='-10' class='v-slider userGainSlider' orient="vertical">
			<input id='dataGain${i}' type='range' min='-40' max='0' step='1' value='-20' class='v-slider dataGainSlider' orient='vertical' disabled>
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
			sound.bufferSources[i].playbackRate.value = 0.0000001;
			console.log(sound.bufferSources[i].playbackRate)
			muteButton.innerText = 'Unmute'
		} else {
			sound.bufferSources[i].playbackRate.value = 1;
			console.log(sound.bufferSources[i].playbackRate)
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
		if (sound.trackInfo[i].reversed) {
			info.innerText = `Reversed ${sound.trackInfo[i].input}`;
		} else {
			info.innerText = `Input ${sound.trackInfo[i].input}`
		}
}

// displays the edit menu in the upper right corner
function showEdit(i) {
	gui = document.getElementById('mixerGui');
	gui.innerHTML = `
		<table>
			<tr><td><b>Track ${i}</b></td><td><button style='flex-grow: 0' onClick='removeTrack(${i})'>Remove Track</button></td>
			<tr><td style='width: 100px'>Name:</td><td> ${sound.trackInfo[i].trackName}</td></tr>
			<tr><td>File:</td><td> ${sound.trackInfo[i].fileName} <br>
				<input id='fileSelect${i}' type='file'></input><button id='fileSelectConfirm${i}'>Change</button></td></tr>
			<tr><td>Input:</td><td> <select id='selectedInput${i}'></select> <input id='reverseCheckbox${i}' type='checkbox' ${sound.trackInfo[i].reversed ? 'checked' : ''}> reversed</td></tr>
			<tr><td>Range:</td><td> ${sound.trackInfo[i].pinToData? 'pinned to min and max of input' : sound.trackInfo[i].min + ' to ' + sound.trackInfo[i].max}</td></tr>
			<tr><td>Range so far:</td><td id='range${i}'> ${sound.data[sound.trackInfo[i].input] && sound.data[sound.trackInfo[i].input].min ? sound.data[sound.trackInfo[i].input].min + ' to ' + sound.data[sound.trackInfo[i].input].max : 'no input'}</td></tr>
		</table>
	`
	inputs = document.getElementById(`selectedInput${i}`);
	for (j=0; j<sound.data.length; j++) {
		var option = document.createElement('option');
		option.text = j;
		option.value = j;
		inputs.appendChild(option);
	}
	inputs.value = sound.trackInfo[i].input;
	inputs.addEventListener('change', (event)=>{
		sound.trackInfo[i].input = parseInt(event.target.value);
		insertInputInfo(i);
	});

	reverseCheckbox = document.getElementById(`reverseCheckbox${i}`);
	reverseCheckbox.addEventListener('change', ()=>{
		sound.trackInfo[i].reversed = event.target.checked;

		let info = document.getElementById(`info${i}`);
		if (sound.trackInfo[i].reversed) {
			info.innerText = `Reversed ${sound.trackInfo[i].input}`;
		} else {
			info.innerText = `Input ${sound.trackInfo[i].input}`
		}
	});

	fileSelectButton = document.getElementById(`fileSelectConfirm${i}`);
	fileSelectButton.addEventListener('click', ()=>{
		fileSelection = document.getElementById(`fileSelect${i}`);
		console.log(fileSelection.value);
		if (fileSelection.value !== '') {
			sound.bufferSources[i].disconnect();
			src = fileSelection.value.split('\\')
			sound.trackInfo[i].fileName = src[src.length - 1]; // warning - might only work on windows
			sound.trackInfo[i].trackName = sound.trackInfo[i].fileName.split('.')[0];
			console.log(sound.trackInfo[i].fileName);
			loadSoundfile(i);
			showEdit(i);
		}
	})
}


// *** ADD AND REMOVE TRACKS ***
function addNewTrack() {
	let filename = document.getElementById('newTrack').value.split('\\');
	filename = filename[filename.length - 1];
	sound.trackInfo.push({fileName: filename, trackName: filename.split('.')[0], input: sound.data.length, reversed: false, gain: null, min: -1, max: 1, pinToData: true},)
	sound.data.push({min: null, max: null})

	const mixer = document.getElementById('mixerBox');
	mixer.insertAdjacentHTML('beforeend', `
			<td id='Track${sound.trackInfo.length - 1}' class='mixerTrack'>Track ${sound.trackInfo.length - 1}</td>
			`)


	setUpTrack(sound.trackInfo.length - 1);


}

function removeTrack(i) {
	contextState = sound.context.state
	console.log(contextState);
	if (window.confirm('Are you sure you want to remove this track?')) { // this interrupts the audio!!
		console.log('removing');
		console.log(sound.bufferSources);
		sound.bufferSources[i].disconnect();
		sound.bufferSources.splice(i, 1);
		sound.trackInfo.splice(i, 1);
		sound.buffers.splice(i, 1);
		sound.userGains.splice(i, 1);
		sound.dataGains.splice(i, 1);
		if (contextState == 'suspended') {
			sound.context.suspend();
		}
		loadMixer();
	}
}


// *** HANDLING PRESETS ***
function loadPreset() {
	fileName = document.getElementById('presetSelector').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];

	if (fileName !== '') { // do nothing if the input field is blank
		// clear out any pre-existing bufferSources
		if (typeof sound !== 'undefined') {
			for (i=0; i<sound.bufferSources.length; i++) {
				sound.bufferSources[i].disconnect();
			}
		}

		fetch('./playerPresets/' + fileName)
			.then(response => response.text())
			.then(preset => {
				startAudio(JSON.parse(preset));
			})
	}
}

function savePreset() {
	console.log('saving app state as preset');
	// function download(content, fileName, contentType) {
    var a = document.createElement("a");
    var file = new Blob([JSON.stringify(sound.trackInfo)], {type: 'text/plain'});
    a.href = URL.createObjectURL(file);
    a.download = 'preset.txt';
    a.innerHTML = a.download;
    presets = document.getElementById('presetsButtons');
    presets.appendChild(a);
    a.click();
    presets.removeChild(a);
    URL.revokeObjectURL(a.href);
}








