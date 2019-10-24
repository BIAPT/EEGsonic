console.log('player');


const AudioContext = window.AudioContext || window.webkitAudioContext;

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
				});
			});
	}

}



