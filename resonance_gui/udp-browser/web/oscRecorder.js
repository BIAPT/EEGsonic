// records OSC messages in real time and allows them to be played back.
// version 0.1


class OSCRecorder {
	constructor() {
		this._recording = false;
		this.timeStarted = null;
		let events = [];
		console.log('created OSC recorder');

		this.startRecording = () => {
			this._recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = () => {
			this._recording = false;
			console.log('OSC stopped recording');
			console.log(events);
			this.timeStarted = null;
			this.saveEvents();
		}

		this.receiveMessage = (message) => {
			if (this._recording) {
				events.push({'time': Date.now() - this.timeStarted, 'message': message});
				console.log('recorded message at ' + (Date.now()-this.timeStarted));
			} 
		}

		this.saveEvents = () => {
			console.log('saving events to file');
			// this is a hacky way of saving a text file that I got off stack overflow
		    var a = document.createElement("a");
		    var file = new Blob([JSON.stringify(events)], {type: 'text/plain'});
		    a.href = URL.createObjectURL(file);
		    a.download = 'oscEvents.txt';
		    a.innerHTML = a.download;
		    let dummy = document.getElementById('messageArea');
		    dummy.appendChild(a);
		    a.click();
		    dummy.removeChild(a);
		    URL.revokeObjectURL(a.href);
		}

		this.play = () => {
			playOSCEvents(events);
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

function playOSCEvents (events) {
	console.log('play them');
}

function sequenceNextEvent() {
	console.log('next event');
}