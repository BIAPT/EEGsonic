// records OSC messages in real time and allows them to be played back.
// version 0.1


class OSCRecorder {
	constructor() {
		this.recording = false;
		this.timeStarted = null;
		this.events = [];
		console.log('created OSC recorder');

		this.startRecording = function() {
			this.recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = function () {
			console.log('OSC stopped recording');
			this.recording = false;
			console.log(this.events);
		}

		this.receiveMessage = function(message) {
			console.log(message);
			if (this.recording) {
				this.events.push({'time': Date.now() - this.timeStarted, 'message': message})
				console.log('recorded message at ' + (Date.now()-this.timeStarted));
			} else { console.log('not currently recording') }
		}
	}
}