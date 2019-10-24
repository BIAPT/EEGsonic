console.log('player');


const AudioContext = window.AudioContext || window.webkitAudioContext;

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
	'res1_bass.mp3',
	'res1_bells.mp3',
	'res1_cellos.mp3',
	'res1_clarinet.mp3',
	'res1_drone.mp3',
	'res1_flutes.mp3',
	'res1_guitar.mp3',
	'res1_violins.mp3']


fetch(sound.bufferFiles[0], {mode: "cors"})
	.then(function(resp) {return resp.arrayBuffer()})
	.then((buffer) => {
		console.log(buffer);
	});

sound.bufferSources[0] = sound.context.createBufferSource();
sound.bufferSources[0]

