// records audio from final gainNode of audio graph
// https://github.com/higuma/web-audio-recorder-js

var recorder;

function toggleRecording() {
	recordButton = document.getElementById('toggleRecording');
	if (recorder == null) {
		initlaizeRecorder();
		console.log('recorder initialized');
	}
	if (recorder.isRecording) {
		recordButton.innerText = 'Start Recording';
		stopRecording();
	} else {
		recordButton.innerText = 'Stop Recording';
		startRecording();
	}

}

function initializeRecorder() {
	recorder =  WebAudioRecorder(sourceNode, {
  		workerDir: "javascripts/"     // must end with slash
	});
	recorder.setEncoding('mp3');
	recorder.setOptions({timeLimit: 600}) // maximum recording duration - set to 10 minutes (600 seconds)
}

function startRecording() {
	console.log('starting recording');
	recorder.startRecording();
}

function stopRecording() {
	console.log('stopping recording');
	recorder.finishRecording();
}