# Resonance Flask Player

Resonance Flask App for use with EEGSonic for sonification of consciousness-related biosignals.


### Prerequisites

For the Flask backend

```
Flask
python-osc
Flask-SocketIO
```

For the JavaScript front-end

```
NPM
Webpack
```

### Installing

To configure the JavaScript modules navigate to flask-app/static and run

```
npm run build (for one-time use)
npm run watch (if you are changing files)
```

### When editing code

If you are editing the javascript or HTML/CSS files and the changes are not reflected in the site, you need to navigate to flask-app/static and run

```
npm run watch
```

### Running the Flask Server

To run the flask app, open a terminal window and navigate to flask-app/server. Run

```
python3 app.py
```

The server runs in two threads, one listening for UDP messages from EEGSonic and the second hosting the actual flask server. The rounting is handled by flask-app/app.py.

In the browser (tested in Firefox and Chrome), navigate to 

```
127.0.0.1:5000
```

and click "Load Default". You should see a list of tracks to the left and a list of signals to the right.


## Interacting with MATLAB EEGSonic

The Resonance app can work in two modes - it can either receive messages directly from the MATLAB EEGSonic app, or it can replay a .txt file of saved EEGSonic messages.

In the first case, to connect with the MATLAB EEGSonic app, close and re-open a new instance of MATLAB and make sure that only the EEGSonic folders and the default MATLAB files are included in the path. There are analysis functions in other folders that have the same names as the ones EEGSonic uses and these have caused conflicts in the past. When EEGSonic is run on MATLAB that has been open for a while sometimes different features will stop sending their messages after a few minutes, but this has not been a problem when MATLAB was cleanly closed and re-opened.


### Converting raw EEG data to EEGSonic's format in MATLAB

The BIAPT Lab uses the Philips .mff format. EEGSonic is designed run on raw, unfiltered EEG data. Starting with a .mff file:

1. In MATLAB's Command Window, type "eeglab" and press enter. This will open EEGLAB.
2. Select File -> Import Data -> Using EEGLAB functions and plugins -> Import Philips .mff file.
3. Select the .mff file you want to convert.
4. Make sure that the Sampling rate is 1000. With too low of a sampling rate some features will not work and the timing will be off.
5. Select File -> Save current dataset(s). Choose a location to save. This will give you two files, a .fdt and a .set
6. You can now close EEGLab.
7. In Matlab's Current Folder window, navigate to EEGsonic/app and double-click EEGsonic_app.mlapp.
8. In EEG Sonic, select File -> Convert EEG Data. A new window will open.
9. Click "Select input file" and choose the .set you just converted. The .set and .fdt must be in the same folder.
10. Click "Select output folder" and choose the folder where you want the converted files to be saved.
11. Under "Output folder name", give an appropriate name. This creates a new folder inside the selected output folder.
12. Click "Convert" and wait for it to display "Finished Converting" before closing the window.
13. You should now see a new folder with subfolders "data", "features", and "parameters", as well as an information.txt file.


### Replaying a converted folder

For troubleshooting, refer to "Working with MATLAB EEGSonic" above. Open EEGSonic_app.mlapp in MATLAB and click "Replay". Select the converted folder, which will have the Output Folder Name given in step 11 above.

The app should automatically have all the correct features set, but to be sure, clicking "OSC Receivers" should give a list that includes "external,120.0.0.1,7400". This is the port that the Python Flask app runs on, if in doubt, this address will be displayed to the screen when starting the Flask app.

If it is not already running, start the flask server in a terminal window and navigate to 127.0.0.1:5000 in the browser. 

Click the "Launch" button in the bottom right corner of EEGSonic to open the replay window. To start the data, press "Pause". You should see messages posted to the terminal window, and in the browser the signal data should begin to change. If this happens, you're all set!


### Streaming live EEG data

In Net Station Aquisition, before measuring impedences, set the Filter to Highpass: 0.1 Hz, Lowpass 30 Hz. Set the Sampling rate to 1000 s/s.

Open the EEGSonic_app.mlapp file in MATLAB. Click "Select Saving Directory" and select an output folder, and next to Folder Name, input a name of the new folder to be created. Select the "EGI-129" tab. Make sure the configuration is the same as listed above under "Replaying a converted folder". 



Start the Flask app and open the browser page in the same way as when replaying a folder. Make sure that EEGSonic is not in Debug mode, then press the Launch button to start recording data and broadcasting messages. 


*** Add instructions on disconnecting the amplifier afterwards



## Working with the Resonance Player - Playback

This section is about the JavaScript program that is hosted at 127.0.0.1:5000 in the browser. The most important file here is flask-app/static/js/player.js. This app is compiled using Webpack - this is why any changes made will not take effect until you run "npm run watch" or "npm run build" in the static folder.

The app uses the Web Audio API and Tone.js for coordinating and playing back the music.

### Replaying saved OSC messages

In order to use Resonance independently from MATLAB EEGSonic, simply press "load Default", the select an OSC file from the playerEvents folder (it must be in this folder!), and click "load OSC". Next click "play OSC." If it plays a couple messages then stops, this just means that the soundfiles had not fully loaded. Wait a moment and press "play OSC" again.


### About the Process that Generates the Music

The inspiration for the algorithmic process that Resonance uses comes from Luciano Berio's Sequenza IXa for solo clarinet. Berio was a pre-eminent Italian composer of the mid-20th century, and his works include a series of pieces exploring the possibilities of different solo instruments. For his clarinet sequenza, Berio first wrote a technically challenging melody that explores the range of sounds the clarinet can make, and he then used this as source material to compose the Sequenza. He made the Sequenza by sampling, looping and manipulating short fragments of his melody, repeating them, playing them forwards and backwards, similar to popular tape-editing techniques. He explores the space that the melody traces out by using a "sliding window" that draws out features and contrasts.

https://www.youtube.com/watch?v=vGogPD1H6YI

I've always appreciated this technique because it allows for a systemic, rule-bound and structural way of manipulating an expressive and intuitively composed musical core. Of course, this manipulation itself can also be expressive and intuitive. It is difficult to reconcile the place of intuition and the composer's free spirit with a technological and algorithmic, data-driven working process. Berio's technique in this Sequenza allows the composer complete creative control over the sound material, and offers a process that can be used to draw out and amplify contrasts while still giving the piece a coherent and self-contained structure, giving it an identity and a clear form.

This idea of using algorithms to amplify the characteristics, the latent potential of a freely expressed "seed crystal melody" is central to how I approach music in general. This was also a concern of Claude Vivier, a notable Quebecois composer, who similarly used algorithmic processes to draw out the latent qualities of his freely composed melodies.


### Recording Audio Output

In previous versions of the app it was possible to directly record and save the streaming audio. However, I have found it more practical to use a third-party software for this, it also allows us to record a single sound-file for the entire experimental session, not having to restart it if we refresh the page or change the Resonance Player's settings.

For this, use Audacity to record the Windows WASAPI if you are on PC, or a combination of SoundFlower and QuickTime on a Mac.


## Presets

A preset is structured as follows:
```
const preset = {
	signals: [ array of signal objects ],
	tracks: [ array of track objects ]
}
```


### Signals, Ranges, Tracks and Inputs

The four main "moving parts" in Resonance are the Signal, Range, Track, and Input objects.

Briefly, Signals store channel-specific information about the messages received from EEGSonic, and Ranges represent specific named sub-ranges of each Signal. For instance, a Signal could have channel '/spr_beta_alpha' and the Range could be 'spr_beta_alpha_low' with a min of 0.1 and a max of 0.3.

A Track is a single soundfile that is controlled by one or several Inputs, it also keeps a decay value that silences the Track if its Inputs have not changed in a while. Inputs have different effects depending on their type, and are defined relative to a Range. 

This way, there can be several different Tracks that all have Inputs that are relative to a single Range, and to optimize Resonance for a specific brain we only have to adjust the values of the Ranges and all the related Tracks and Inputs will behave accordingly. 



#### Signals

```
	signals: [
		{ 	channel: '/pe_frontal',
			ranges: [
				{
					name: 'pe_frontal_rel',
					relative: true,				
				},
				{	name: 'pe_frontal_abs',
					min: 0.4,
					max: 1
				},
				{	name: 'pe_frontal_diff',
					min: -0.5,
					max: 0.5
				}
			]
		}
	]
```

A signal keeps track of information from a single input channel, there is one for each different kind of message that can be received from EEGSonic. When Resonance loads it creates a Signal object for each element in the preset's signals array.

With each incoming message, the corresponding Signal stores the current value, previous, minimum seen so far, max so far, as well as the average of the last 3, 5 and 10 messages. It also tracks the difference of the most recent value with the average of the last 3, 5 and 10 as diff3, diff5, and diff10 respectively, and stores the difference between the avg3 and avg10 as diff3_10. These are useful for indicating when a signal is changing - positive values indicate the signal increasing and negative values, decreasing.

#### Ranges

A Signal can have several Ranges, a Range is a sub-section of the Signal that has its own name- for instance the range of 0.1 to 0.3 of one of the Spectral Power Ratio signals could be called "spr_low". 

If a range is marked "relative: true", its minimum and maximum will update to match the min and max of the corresponding signal. If no default min and max are given, then it will match the signal's min and max exactly, however if you provide a min and max for the range and also specify "relatve: true", these will only change when the signal exceeds these bounds, in which case the min or max will update to the new value.


#### Tracks

```
	tracks: [
		{	fileName: 'harp_main.ogg',
			gain: -2,
			loopLength: 5,
			decayCutoff: 0.1,
			inputs: [{ 	range:'spr_alpha_theta_fullrange',
						type:'loopPoint',
						value:'avg5',
						min: 0.2,
						peak: 0.45,
						max: 0.45,
						decayBoost: 0.3,
						decayRate: 0.4,
						decayRange: 0.15,
						decayThreshold: 0.6
					},
					{ 	range:'spr_alpha_theta_fullrange',
						type:'volume',
						value:'avg3',
						min: 0.2,
						peak: 0.4,
						max: 0.6,
						decayRate: 0.4,
						decayRange: 0.15
					}
				]
		}
	]
```

Each soundfile is a single Track, and the way these are played back depends on the inputs. As well as an array of inputs, the track has a fileName (required), a gain (between -20 and 0), a loopLength in seconds, only needed when there is an input of type "loopPoint" (default is 6 seconds), and a decayCutoff, which is a value between 0 and 1. When the *average* decay values of the track's inputs is below the decayCutoff, the track will be muted.

There are two ways sound files are played back in Resonance - those with a loopPoint input and those without. Those with no loopPoint are only controlled in volume, they are heard when a signal is in certain range, and they simply play through and loop the contents of the sound file.


#### Inputs

Inputs control how the Track responds to incoming messages. Each input specifies a range, type and value, as well as min, peak and max values and information about the decay behaviour. The range specifies which Signal and which Range the Input responds to, and the value says which statistic of that signal is being referenced. The type can either be 'volume', 'loopPoint', or 'playbackRate', explained below.

Starting from the min, peak and max, the input calculates a value between 0 and 1. The value increases linearly between min and peak, then reduces back to 0 at max, so that the value is 0 any time the signal is outside of the relevant values. The *exception* to this is when the peak is equal to either the min or the max, in these cases, the input *stays at 1* above or below the relevant range. This is so that you can have an input that ramps up and then stays on when above or below a given amount. This is ideal for loopPoint inputs.

Min, peak and max are *relative to the range*, so that you can place several tracks with Inputs referencing the same Range. If an input is referencing a Range that has a min of 0.5 and a max of 1, and the input also has a min of 0.5 and a max of 1, then the input responds when the signal is between 0.75 and 1. 

The calculation is
```
inputMin = ((rangeMax - rangeMin) * inputMin) + rangeMin
inputPeak = ((rangeMax - rangeMin) * inputPeak) + rangeMin
inputMax = ((rangeMax - rangeMin) * inputMax) + rangeMin
```
This way, if you want 5 Tracks spaced evenly across the Range, you can use
```
input1: min = 0, peak = 0.1, max: 0.2,
input2: min = 0.2, peak = 0.3, max: 0.4,
input3: min = 0.4, peak = 0.5, max: 0.6,
input4: min = 0.6, peak = 0.7, max: 0.8, 
input5: min = 0.8, peak = 0.9, max: 1.0.
```
It is set up this way, so if you adjust the range for a specific brain, you only need to adjust the Range and all 5 of these Tracks will adjust accordingly. In this case, when steadily increasing the Signal across the Range, you would hear Track1 ramp up and down, then silence at 0.2, then Track2, silence at 0.4 and so on. To overlap the sounds you would slightly overlap the input min and max of the different Tracks.


##### volume Inputs

Receiving a message, the volume input calculates a 0-1 value and reassigns the track's level accordingly. 

There can be more than one volume input on a given track, and the level is the *product* of all the volume inputs - this way a signal can be heard only if the dPLI is in a given range AND the wPLI is in some range, if either value comes to 0 the overall loudness will be 0. The potential issue with this choice is that when several inputs all have small but relevant values the product will be smaller still, I worked around this by adjusting my input ranges accordingly.

These soundfiles can either be shorter loops like the HL drones, or longer melodies like the wPLI woodwinds or the HL strings. Including longer soundfiles that loop at different intervals (like in Brian Eno's Music for Airports) helps to give some stability to the overall musicalal form, I found that when using only loopPoint the music was too choppy and incoherent.

The current level of a Track is shown by the middle of the three horizontal sliders.


##### loopPoint Inputs

The tracks with loopPoints are sampled using a greatly simplified version of Berio's technique described above. There is one soundfile for each instrument heard. These are composed so that there is an obvious, gradual change from beginning to end, usually with the pitch moving from low to high. For examples, listen to harp.ogg, rhodes.ogg, softersynth.ogg, or any of the dPLI sounds. Moving the playhead from left to right on the soundfiles gives an obvious gradual change. 

The loopPoint input repeatedly plays through a short segment of the soundfile; you can specify the length with the loopLength field in the Track object. When receiving a message, the loopPoint input calculates a 0-1 value in exactly the same way as a volume input, but uses this to decide where within the soundfile to begin the next loop segment. So, a value of 0.5 would begin the segment at halfway through the file, and so on. The segments are slighly overlapped so that one is fading out while the next one is fading in.

So, the loopPoint is chaining together short segments of a soundfile, in order to give a sort of melody that rises and falls with the control signal. It also works to shorten the loopLength to less than a second and use the loopPoint as a sort of concatinative synthesizer.


##### playbackRate Inputs

The playbackRate changes the rate at which the samples are played through, resulting in an increase/decrease of both speed and pitch. There are two variables: playbackMin and playbackSpeedup. playbackMin gives the slowest rate, and playbackSpeedup is the factor by which the calculated 0-1 value of the input is multiplied by.

The calculation is
```
newPlaybackRate = playbackMin + calculatedValue * playbackSpeedup.
```

If you want a track to vary between half-speed (0.5) and double-speed (2.0), this would mean a playbackMin of 0.5 and a playbackSpeedup of 1.5 (because 0.5 + 1.5 comes to 2).


#### The Decay Feature

An important thing to realize is that Resonance is designed to highlight *changes* in the signals, as well as reflecting the values of the signals themselves. Tracks associated with a signal that has stayed very constant will gradually fade out, and only be heard again once the control signal moves into a new range.

This works by an interaction of four variables defined in the input: decayRate, decayRange, decayBoost and decayThreshold. These work with the *calculated value* of the input, as described above with min, peak and max variables. The Decay also stores an internal value called decayValue that is the result of the calculation. The decayValue of a track is the *average* of the decayValues of each of its inputs, so that novelty in any of the Inputs reflects as novelty in the Track.

To begin, the first message an input receives is stored as a new target value, and the decayValue is set equal to the decayBoost. 

With each subsequent message, first we check whether the absolute difference between the new value and the target value is less than the decayRange - in other words, if the decayRange is 0.2, we check whether the new value is within 0.2 of the value we have stored.

If the new value is within this range, we consider the signal not to have changed, so we *multiply* the decayValue by the decayRate. If the decayRate is high, like 0.9, the decayValue will decrease slowly. If it is low, it will decrease more quickly and the Track will soon fade out.

If instead the new value is outside of this range, we consider the signal to have changed, and we *add* the decayBoost to the existing decayValue. After this boost, if the new decayValue is above the decayThreshold, then we re-assign a new target value of the decay as the new reference point for deciding whether the signal has changed or not.

The result of this is that when a Signal changes significantly, a Track will slowly increase in volume so long as the incoming values are outside of the current decayRange, until it reaches the decayThreshold, at which point if the Signal stays steady, the decay will slowly decrease.

The current decay value of a track is shown on the third horzontal slider of each track in the tracks panel.


## The GUI

### The Tracks Panel

Below the main controls is a list of all the tracks, each with three blue sliders. Of these you are only able to control the top one, the other two are for visual feedback only. The top slider is the user-controlled gain on the track. Use this to turn up or down the level on a single track. The middle slider shows the current calculated volume of the track, this is the average of all the volume inputs on the track and it updates with each message the input receives. The final slider is the decay value, which reduces the volume of the track if it has been playing for a while without changing much. The decay function is explained further below.







## Sound Design and Composing New Pieces

### Making Contrast on Different Orders of Magnitude (Fractal Design)

One of the most difficult things to figure out for Resonance was how to have audible changes in response to both small- and large-range variations of a signal. One thing that music is very good for is to be able to make contrasts at different time-scales and to have both micro- and macro-variations. 





### Troubleshooting

```
"Error: buffer is either not set or not loaded"
```
This error comes up if you try to play a list of OSC messages before the soundfiles are fully loaded. Just give it a moment.