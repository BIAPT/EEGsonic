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

	sound.masterGain = sound.context.createGain();
	sound.masterGain.connect(sound.context.destination);

	sound.bufferFiles = [
		'./samples/res1_bass.mp3',
		'./samples/res1_bells.mp3',
		'./samples/res1_cellos.mp3',
		'./samples/res1_clarinet.mp3',
		'./samples/res1_drone.mp3',
		'./samples/res1_flutes.mp3',
		'./samples/res1_guitar.mp3',
		'./samples/res1_violins.mp3']


	for (i=0; i < sound.bufferFiles.length; i++) {
		fetch(sound.bufferFiles[i], {mode: "cors"})
			.then(function(resp) {return resp.arrayBuffer()})
			.then((buffer) => {
				console.log(buffer);
				sound.context.decodeAudioData(buffer, (abuffer) => {
					sound.bufferSources[i] = sound.context.createBufferSource();
					sound.bufferSources[i].buffer = abuffer;
					sound.bufferSources[i].connect(sound.context.destination);
					sound.bufferSources[i].loop = true;
					sound.bufferSources[i].start();
					addMixerTrack(i);
				});
			});
	}
}

function addMixerTrack(i) {

	const mixer = document.getElementById('resonanceMixer');
	mixer.insertAdjacentHTML('beforeend', `<h1>ELEMENT</h1>`)
}



