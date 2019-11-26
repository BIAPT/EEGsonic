console.log('player online');

const AudioContext = window.AudioContext || window.webkitAudioContext;

// this is the default preset loaded when none is selected
const defaultPreset = [
		{fileName: 'res1_bass.mp3', trackName: 'Bass', input: '/fp_dpli_left_midline', reversed: false, gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_bells.mp3', trackName: 'Bells', input: '/fp_wpli_left_midline', reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},	
		{fileName: 'res1_guitar.mp3', trackName: 'Guitar', input: '/hl_relative_position', reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_clarinet.mp3', trackName: 'Clarinet', input: '/pe_frontal', reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_cellos.mp3', trackName: 'Cello', input: '/pe_parietal',  reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_drone.mp3', trackName: 'Drone', input: '/spr_beta_alpha', reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_flutes.mp3', trackName: 'Flute', input: '/spr_alpha_theta', reversed: true,  gain: null, min: 0, max: 1, peak: 1, pinToData: true},
		{fileName: 'res1_violins.mp3', trackName: 'Violin', input: '/spr_alpha_theta', reversed: false,  gain: null, min: 0, max: 1, peak: 1, pinToData: true}
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
		selectedTrack: null,
		wpliGain: [],
		PE_parietal: null,
		filterNode: null,
		preFilterGain: null,
	}
	sound.context.suspend();


	sound.trackInfo = preset;

	data = {
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

	loadOSCTable();
	
	sound.preFilterGain = sound.context.createGain();
	sound.masterGain = sound.context.createGain();

	let filter = true;

	if (filter) {

		sound.filterNode = sound.context.createBiquadFilter();
		sound.filterNode.connect(sound.masterGain);
		sound.filterNode.frequency.setValueAtTime(4000, sound.context.currentTime);

		// handle master gain slider, play and stop buttons
		sound.preFilterGain.connect(sound.filterNode);
	} else {
		sound.preFilterGain.conect(sound.masterGain);
	}

	sound.masterGain.connect(sound.context.destination);

	// set up modulator for wPLI signals
	for (i=0; i<4; i++) {
		sound.wpliGain[i] = sound.context.createGain();
		sound.wpliGain[i].connect(sound.preFilterGain);
		sound.wpliGain[i].gain.value = 0;
	}

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
		//if (sound.trackInfo[i].input == null) {
			//sound.data[j] = {min: null, max: null, curr: null}
	    	//sound.trackInfo[i].input = j;
	    	//if (sound.trackInfo[i].reversed === false) { j++; }
	    //} else {
	    	sound.data[sound.trackInfo[i].input] = {min: null, max: null, curr: null, mute:false}
	    //}
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
	console.log(sound.trackInfo[i].input);
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
	gui = document.getElementById('mixerGui');
	gui.innerHTML = `
		<table>
			<tr><td><b>Track ${i}</b></td><td><button style='flex-grow: 0' onClick='removeTrack(${i})'>Remove Track</button></td>
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
	inputs = document.getElementById(`selectedInput${i}`);

	var option = document.createElement('option');
	option.text = 'None';
	option.value = null;
	for (j=0; j<Object.keys(data).length; j++) {
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

	reverseCheckbox = document.getElementById(`reverseCheckbox${i}`);
	reverseCheckbox.addEventListener('change', ()=>{
		sound.trackInfo[i].reversed = event.target.checked;
		insertInputInfo(i);
	});

	rangeCheckbox = document.getElementById(`rangeCheckbox${i}`);
	rangeCheckbox.addEventListener('change', ()=>{
		sound.trackInfo[i].pinToData = event.target.checked;
		insertInputInfo(i);
	})

	rangeMin = document.getElementById(`rangeMin${i}`)
	rangeMin.addEventListener('change', ()=>{
		console.log(parseFloat(event.target.value));
		sound.trackInfo[i].min = parseFloat(event.target.value);
	})


	rangeMax = document.getElementById(`rangeMax${i}`)
	rangeMax.addEventListener('change', ()=>{

		console.log(parseFloat(event.target.value));
		sound.trackInfo[i].max = parseFloat(event.target.value);
	})

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
	sound.trackInfo.push({fileName: filename, trackName: filename.split('.')[0], input: null, reversed: false, gain: null, min: 0, max: 1, pinToData: true},)
	

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
		gui = document.getElementById('mixerGui');
		mixerGui.innerHTML='';
		sound.selectedTrack = null;
		loadMixer();
		for (let i=0; i < sound.trackInfo.length; i++) {
			loadMixerTrack(i); // ASYNC function! Adds gain nodes and then loads soundfile
		}	
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


// OSC FUNCTIONS //
function toggleOSCRecording() {
	oscRecorder.toggleRecording()
	if (oscRecorder.recording) {
		document.getElementById('OSCToggleButton').innerText='Stop Recording OSC'
	} else document.getElementById('OSCToggleButton').innerText='Start Recording OSC'
}

function loadOSC() {
	fileName = document.getElementById('OSCEventFile').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];
	console.log(fileName);

	if (fileName !== '') {
		fetch('./playerEvents/' + fileName)
				.then(response => response.text())
				.then(events => {
					oscPlayer.loadOSCEvents(JSON.parse(events));
					document.getElementById('playOSCFile').removeAttribute('disabled');
					document.getElementById('resetOSCFile').removeAttribute('disabled');
				})
	}
}

function toggleOSC() {
	button = document.getElementById('playOSCFile');
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
		console.log(key);
		input = document.getElementById(`osc${key}`)
		if (input.value) {
			oscMessage = {'address': key, 'args':[parseFloat(input.value)]};

    		updateData(oscMessage);
    		updateTracks(oscMessage);
    		adjustModulators(oscMessage);
		}
	}
}

function loadOSCTable() {
	oscTable = document.getElementById('oscTable');
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
  		console.log(key, value);
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
	fileName = document.getElementById('oscRanges').value.split('\\'); // MAC COMPATIBILITY WARNING
	fileName = fileName[fileName.length - 1];
	console.log(fileName);

	if (fileName !== '') {
		fetch('./ranges/' + fileName)
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
    presets = document.getElementById('presetsButtons');
    presets.appendChild(a);
    a.click();
    presets.removeChild(a);
    URL.revokeObjectURL(a.href);
}

