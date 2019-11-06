// records OSC messages in real time and allows them to be played back.
// version 0.1


class OSCRecorder {
	constructor() {
		this._recording = false;
		this.timeStarted = null;
		let events = [];
		console.log('created OSC recorder');

		this.startRecording = function() {
			this.recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = function () {
			console.log('OSC stopped recording');
			this.recording = false;
			console.log(events);
		}

		this.receiveMessage = function(message) {
			console.log(message);
			if (this._recording) {
				events.push({'time': Date.now() - this.timeStarted, 'message': message});
				console.log('recorded message at ' + (Date.now()-this.timeStarted));
			} else { console.log('not currently recording') }
		}
	}

	set recording (value) {
		console.log('recording: ' + value);
		this._recording = value;
	}

	get recording () {
		return this._recording;
	}
}