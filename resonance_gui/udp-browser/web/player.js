console.log('player online');

const AudioContext = window.AudioContext || window.webkitAudioContext;


// Web Audio requires user input to start audio. This function is triggered
// by the button in player.html
function startAudio() {
	sound = {
		context : new AudioContext(),
		masterGain : null,
		bufferFiles : [],
		buffers : [],
		bufferSources : []
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
	sound.masterGain.gain.value = 0.8;

	masterGainSlider = document.getElementById('masterGain');
	masterGainSlider.addEventListener('change', ()=> {
		sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	}, false);

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
					sound.bufferSources[i].connect(sound.masterGain);
					sound.bufferSources[i].loop = true;
					sound.bufferSources[i].start();
					addMixerTrack(i);
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
		
		<input type='range' min='-60' max='0' step='1' class='v-slider' orient="vertical">
		<button id='Mute${1}'>Mute</button>
		`);
}



