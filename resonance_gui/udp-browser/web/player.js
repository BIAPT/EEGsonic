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
	'./samples/res1_bass.mp3',
	'./samples/res1_bells.mp3',
	'./samples/res1_cellos.mp3',
	'./samples/res1_clarinet.mp3',
	'./samples/res1_drone.mp3',
	'./samples/res1_flutes.mp3',
	'./samples/res1_guitar.mp3',
	'./samples/res1_violins.mp3']


fetch(sound.bufferFiles[0], {mode: "cors"})
	.then(function(resp) {return resp.arrayBuffer()})
	.then((buffer) => {
		console.log(buffer);
		sound.context.decodeAudioData(buffer, (abuffer) => {
			sound.bufferSources[0] = sound.context.createBufferSource();
			sound.bufferSources[0].buffer = buffer;
			sound.bufferSources[0].connect(sound.context.destination);
			sound.bufferSources[0].loop = true;
			sound.bufferSources[0].start();
		});
	});




