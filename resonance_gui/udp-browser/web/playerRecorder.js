// records audio from final gainNode of audio graph
// https://github.com/higuma/web-audio-recorder-js
// https://blog.addpipe.com/using-webaudiorecorder-js-to-record-audio-on-your-website/

var recorder;

function toggleRecording() {
	recordButton = document.getElementById('toggleRecording');
	if (recorder == null) {
		initializeRecorder();
		console.log('recorder initialized');
	}
	if (recorder.isRecording()) {
		recordButton.innerText = 'Start Recording';
		stopRecording();
	} else {
		recordButton.innerText = 'Stop Recording';
		startRecording();
	}

}

function initializeRecorder() {
	recorder = new WebAudioRecorder(sound.masterGain, {
		workerDir: 'web-audio-recorder-js-master/lib/',
		encoding: 'wav',
		encodeAfterRecord: true
	});
	// recorder.setEncoding('mp3');
	recorder.setOptions({timeLimit: 600}) // maximum recording duration - set to 10 minutes (600 seconds)
	recorder.onComplete = function(recorder, blob) {
            console.log("Encoding complete");
            createDownloadLink(blob, recorder.encoding);
        }
}

function startRecording() {
	console.log('starting recording');
	recorder.startRecording();
}

function stopRecording() {
	console.log('stopping recording');
	recorder.finishRecording();
}

function createDownloadLink(blob, encoding) {
    var url = URL.createObjectURL(blob);
    var link = document.createElement('a');
    var li = document.createElement('li');
    link.href = url;
    link.download = new Date().toISOString() + '.' + encoding;
    link.innerHTML = link.download;
    //add the new audio and a elements to the li element 
    list = document.getElementById('downloadLinks');
    li.appendChild(link); //add the li element to the ordered list 
    list.appendChild(li);
}
