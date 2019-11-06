// records OSC messages in real time and allows them to be played back.
// version 0.1


class OSCRecorder {
	constructor() {
		this.recording = false;
		this.timeStarted = null;
		console.log('created OSC recorder');

		this.startRecording = function() {
			this.recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = function () {
			console.log('OSC stopped recording');
			this.recording = false;
		}

		this.receiveMessage = function(message) {
			console.log(message);
			if (this.recording) {
				console.log('recorded message at ' + (Date.now()-this.timeStarted));
			} else { console.log('not currently recording') }
		}
	}
}