// records OSC messages in real time and allows them to be played back.
// version 0.1


class OSCRecorder() {
	constructor() {
		this.recording = false;
		this.timeStarted = null;
	}

	function startRecording() {
		this.recording = true;
		this.timeStarted = Date.now();
		console.log('OSC started recording at ' + this.timeStarted);
	}

	function stopRecording() {
		console.log('OSC stopped recording');
		this.recording = false;
	}
}