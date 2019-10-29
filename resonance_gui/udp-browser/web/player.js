console.log('player online');

const AudioContext = window.AudioContext || window.webkitAudioContext;

// Web Audio requires user input to start audio. This function is triggered
// by the button in player.html
function startAudio() {
	sound = {
		context : new AudioContext(),
		masterGain : null,
		bufferFiles : [],  	// URL of soundFiles
		buffers : [],      	// Buffer for loading files
		bufferSources : [],	// Actual Web Audio Node connected to rest of graph
		userGains: [],		// user-inputted gain for each track
		dataGains: [],
		data: [],		// per-track gain from biosignals
		selectedTrack: null
	}

	sound.context.suspend();

	fileDirectory = './samples/';

	// // Version 1 - pretty music w bells, guitar and clarinet melody
	// sound.bufferFiles = [
	// 	'./samples/res1_bass.mp3',
	// 	'./samples/res1_bells.mp3',
	// 	'./samples/res1_cellos.mp3',
	// 	'./samples/res1_clarinet.mp3',
	// 	'./samples/res1_drone.mp3',
	// 	'./samples/res1_flutes.mp3',
	// 	'./samples/res1_guitar.mp3',
	// 	'./samples/res1_violins.mp3']
	// trackNames = ['bass', 'bells', 'cellos', 'clarinet', 'drone', 'flutes', 'guitar', 'violins']

	// // Version 2 - C major chord w strings and woodwinds
	// sound.bufferFiles = [
	// 	'./samples/res2_bass.mp3',
	// 	'./samples/res2_cello.mp3',
	// 	'./samples/res2_viola.mp3',
	// 	'./samples/res2_violin.mp3',
	// 	'./samples/res2_bassoon.mp3',
	// 	'./samples/res2_clarinet.mp3',
	// 	'./samples/res2_oboe.mp3',
	// 	'./samples/res2_flute.mp3'
	// 	]
	// trackNames = ['bass', 'cello', 'viola', 'violin', 'bassoon', 'clarinet', 'oboe', 'flute']

	// Version 3 - Version 1 but with sounds paired onto single input streams
	sound.bufferFiles = [
		{fileName: 'res1_bass.mp3', trackName: 'Bass', reversed: false, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_bells.mp3', trackName: 'Bells', reversed: true, input: null, min: -1, max: 1, pinToData: true},	
		{fileName: 'res1_guitar.mp3', trackName: 'Guitar', reversed: false, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_clarinet.mp3', trackName: 'Clarinet', reversed: true, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_cellos.mp3', trackName: 'Cello', reversed: false, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_drone.mp3', trackName: 'Drone', reversed: false, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_flutes.mp3', trackName: 'Flute', reversed: true, input: null, min: -1, max: 1, pinToData: true},
		{fileName: 'res1_violins.mp3', trackName: 'Violin', reversed: false, input: null, min: -1, max: 1, pinToData: true}]

	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);

	masterGainSlider = document.getElementById('masterGain');
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
		console.log(sound.masterGain.gain);
		console.log(masterGainSlider.value);
	}, false);
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);

	playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{sound.context.resume()})
	stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const mixer = document.getElementById('mixerBox');
	for (let i=0; i < sound.bufferFiles.length; i++) {
		mixer.insertAdjacentHTML('beforeend', `
			<td id='Track${i}' class='mixerTrack'>Track ${i}<br>
			${sound.bufferFiles[i].trackName}
			<div id='info${i}'></div></td>
			`)
		// fetch(sound.bufferFiles[i], {mode: "cors"})  // for versions 1 and 2
		setUpTrack(i);
		
	}
	button = document.getElementById('startContext')
	button.parentNode.removeChild(button);

	initializeInputs();
}

function setUpTrack(i) {
	sound.userGains[i] = sound.context.createGain();
	sound.dataGains[i] = sound.context.createGain();
	sound.userGains[i].connect(sound.dataGains[i]);
	sound.dataGains[i].connect(sound.masterGain);
	loadSoundfile(i);
}

async function loadSoundfile(i) {
	fileName = fileDirectory + sound.bufferFiles[i].fileName;
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
				updateMixerTrack(i);   // loads the GUI element for this track
			});
		});
	return true;
}

function initializeInputs() {
	// display information about input
	let j = 0;
	for (let i=0; i < sound.bufferFiles.length; i++) {
		sound.data[j] = {min: null, max: null}
		let info = document.getElementById(`info${i}`);
    	if (sound.bufferFiles[i].reversed) {
    		sound.bufferFiles[i].input = j;
    		info.innerText = `Reversed ${j}`;
    	} else {
    		sound.bufferFiles[i].input = j;
    		info.innerText = `Input ${j}`;
    		j++;
    	}
	}
}

function insertInputInfo(i) {
	let info = document.getElementById(`info${i}`);
		if (sound.bufferFiles[i].reversed) {
			info.innerText = `Reversed ${sound.bufferFiles[i].input}`;
		} else {
			info.innerText = `Input ${sound.bufferFiles[i].input}`
		}
}

function updateMixerTrack(i) {
	let trackId = `Track${i}`;
	console.log(trackId);

	document.getElementById(trackId).innerHTML = `
		<td id='Track${i}' class='mixerTrack'>Track ${i}<br>
			${sound.bufferFiles[i].trackName}<br>
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
	sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
	userGain.addEventListener('input', ()=>{
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

function showEdit(i) {
	gui = document.getElementById('mixerGui');
	console.log(i);
	gui.innerHTML = `
		<table>
			<tr>Track ${i}</tr>
			<tr>
				<td style='width: 100px'>Name:</td><td> ${sound.bufferFiles[i].trackName}</td>
			</tr>
			<tr>
				<td>File:</td><td> ${sound.bufferFiles[i].fileName} <input id='fileSelect${i}' type='file'></input><button id='fileSelectConfirm${i}'>Change</button></td>
			</tr>
			<tr>
				<td>Input:</td><td> <select id='selectedInput${i}'></select> <input id='reverseCheckbox${i}' type='checkbox' ${sound.bufferFiles[i].reversed ? 'checked' : ''}> reversed</td>
			</tr>
			<tr>
				<td>Range:</td><td> ${sound.bufferFiles[i].pinToData? 'pinned to min and max of input' : sound.bufferFiles[i].min + ' to ' + sound.bufferFiles[i].max}</td>
			</tr>
			<tr>
				<td>Range so far:</td><td id='range${i}'> ${sound.data[sound.bufferFiles[i].input].min ? sound.data[sound.bufferFiles[i].input].min + ' to ' + sound.data[sound.bufferFiles[i].input].max : 'no input'}</td>
			</tr>
		</table>
	`
	inputs = document.getElementById(`selectedInput${i}`);
	for (j=0; j<sound.data.length; j++) {
		var option = document.createElement('option');
		option.text = j;
		option.value = j;
		inputs.appendChild(option);
	}
	inputs.value = sound.bufferFiles[i].input;
	inputs.addEventListener('change', (event)=>{
		sound.bufferFiles[i].input = event.target.value;
		insertInputInfo(i);
	});

	reverseCheckbox = document.getElementById(`reverseCheckbox${i}`);
	reverseCheckbox.addEventListener('change', ()=>{
		sound.bufferFiles[i].reversed = event.target.checked;

		let info = document.getElementById(`info${i}`);
		if (sound.bufferFiles[i].reversed) {
			info.innerText = `Reversed ${sound.bufferFiles[i].input}`;
		} else {
			info.innerText = `Input ${sound.bufferFiles[i].input}`
		}
	});

	fileSelectButton = document.getElementById(`fileSelectConfirm${i}`);
	fileSelectButton.addEventListener('click', ()=>{
		fileSelection = document.getElementById(`fileSelect${i}`);
		console.log(fileSelection.value);
		if (fileSelection.value !== '') {
			sound.bufferSources[i].disconnect();
			src = fileSelection.value.split('\\')
			sound.bufferFiles[i].fileName = src[src.length - 1]; // warning - might only work on windows
			sound.bufferFiles[i].trackName = sound.bufferFiles[i].fileName.split('.')[0];
			console.log(sound.bufferFiles[i].fileName);
			loadSoundfile(i);
		}
	})
}



