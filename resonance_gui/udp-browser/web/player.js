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
		dataGains: []		// per-track gain from biosignals
	}

	sound.context.suspend();

	sound.bufferFiles = [
		'./samples/res1_bass.mp3',
		'./samples/res1_bells.mp3',
		'./samples/res1_cellos.mp3',
		'./samples/res1_clarinet.mp3',
		'./samples/res1_drone.mp3',
		'./samples/res1_flutes.mp3',
		'./samples/res1_guitar.mp3',
		'./samples/res1_violins.mp3']

	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);
	

	masterGainSlider = document.getElementById('masterGain');
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	}, false);
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);

	playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{sound.context.resume()})
	stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

    
	const mixer = document.getElementById('mixerBox');
	for (let i=0; i < sound.bufferFiles.length; i++) {
		mixer.insertAdjacentHTML('beforeend', `<td id='Track${i}' class='mixerTrack'>Track ${i+1}</td>`)
		fetch(sound.bufferFiles[i], {mode: "cors"})
			.then(function(resp) {return resp.arrayBuffer()})
			.then((buffer) => {
				console.log(buffer);
				sound.context.decodeAudioData(buffer, (abuffer) => {
					sound.bufferSources[i] = sound.context.createBufferSource();
					sound.bufferSources[i].buffer = abuffer;
					sound.userGains[i] = sound.context.createGain();
					sound.dataGains[i] = sound.context.createGain();
					//sound.bufferSources[i].connect(sound.masterGain);
					sound.bufferSources[i].connect(sound.userGains[i]);
					sound.userGains[i].connect(sound.dataGains[i]);
					sound.dataGains[i].connect(sound.masterGain);
					sound.bufferSources[i].loop = true;
					sound.bufferSources[i].start();
					addMixerTrack(i);   // loads the GUI element for this track
				});
			});
	}
	button = document.getElementById('startContext')
	button.parentNode.removeChild(button);
}

function addMixerTrack(i) {
	let trackId = `Track${i}`;
	console.log(trackId);

	document.getElementById(trackId).insertAdjacentHTML('beforeend', `
		<div>
			<input id='userGain${i}' type='range' min='-30' max='0' step='1' value='-10' class='v-slider' orient="vertical">
			<input id='dataGain${i}' type='range' min='-30' max='0' step='1' value='-10' class='v-slider' orient='vertical' disabled>
		</div>
		<button id='mute${i}'>Mute</button>
		`);

	let userGain = document.getElementById(`userGain${i}`)
	sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
	userGain.addEventListener('input', ()=>{
		sound.userGains[i].gain.value = Math.pow(10, userGain.value/20);
	})

	let dataGain = document.getElementById(`userGain${i}`)
	sound.dataGains[i].gain.value = Math.pow(10, dataGain.value/20);
	dataGain.addEventListener('input', ()=>{
		sound.dataGains[i].gain.value = Math.pow(10, dataGain.value/20);
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
}



