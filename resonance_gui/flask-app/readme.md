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

Open the EEGSonic_app.mlapp file in MATLAB. Click "Select Saving Directory" and select an output folder, and next to Folder Name, input a name of the new folder to be created. The default output folder is the desktop. Select the "EGI-129" tab. Make sure the configuration is the same as listed above under "Replaying a converted folder". 

Start the Flask app and open the browser page in the same way as when replaying a folder. Make sure that EEGSonic is not in Debug mode, then press the Launch button to start recording data and broadcasting messages. 


*** Add instructions on disconnecting the amplifier afterwards


## Working with the Resonance Player - Playback

This section is about the JavaScript program that is hosted at 127.0.0.1:5000 in the browser. The most important file here is flask-app/static/js/player.js. This app is compiled using Webpack - this is why any changes made will not take effect until you run "npm run watch" or "npm run build" in the static folder.

The app uses the Web Audio API and Tone.js for coordinating and playing back the music.

### Replaying saved OSC messages

In order to use Resonance independently from MATLAB EEGSonic, simply press "load Default", the select an OSC file from the playerEvents folder (it must be in this folder!), and click "load OSC". Next click "play OSC." If it plays a couple messages then stops, this just means that the soundfiles had not fully loaded. Wait a moment and press "play OSC" again.


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

These soundfiles can either be shorter loops like the HL drones, or longer melodies like the wPLI woodwinds or the HL strings. Including longer soundfiles that loop at different intervals (like in Brian Eno's Music for Airports) helps to give some stability to the overall musical form, I found that when using only loopPoint the music was too choppy and incoherent.

The current level of a Track is shown by the middle of the three horizontal sliders.


##### loopPoint Inputs

The tracks with loopPoints are sampled using a greatly simplified version of Berio's technique described above. There is one soundfile for each instrument heard. These are composed so that there is an obvious, gradual change from beginning to end, usually with the pitch moving from low to high. For examples, listen to harp.ogg, rhodes.ogg, softersynth.ogg, or any of the dPLI sounds. Moving the playhead from left to right on the soundfiles gives an obvious gradual change. 

The loopPoint input repeatedly plays through a short segment of the soundfile; you can specify the length with the loopLength field in the Track object. When receiving a message, the loopPoint input calculates a 0-1 value in exactly the same way as a volume input, but uses this to decide where within the soundfile to begin the next loop segment. So, a value of 0.5 would begin the segment at halfway through the file, and so on. The segments are slighly overlapped so that one is fading out while the next one is fading in.

So, the loopPoint is chaining together short segments of a soundfile, in order to give a sort of melody that rises and falls with the control signal. It also works to shorten the loopLength to less than a second and use the loopPoint as a sort of concatinative/granular synthesizer.


##### playbackRate Inputs

The playbackRate changes the rate at which the samples are played through, resulting in an increase/decrease of both speed and pitch. There are two variables: playbackMin and playbackSpeedup. playbackMin gives the slowest rate, and playbackSpeedup is the factor by which the calculated 0-1 value of the input is multiplied by.

The calculation is
```
newPlaybackRate = playbackMin + calculatedValue * playbackSpeedup.
```

If you want a track to vary between half-speed (0.5) and double-speed (2.0), this would mean a playbackMin of 0.5 and a playbackSpeedup of 1.5 (because 0.5 + 1.5 comes to 2).


#### The Decay Feature

An important thing to realize is that Resonance is designed to highlight *changes* in the signals, as well as reflecting the values of the signals themselves. Tracks associated with a signal that has stayed very constant will gradually fade out, and only be heard again once the control signal moves into a new range.

This works by an interaction of four variables defined in the input: decayRate, decayRange, decayBoost and decayThreshold. These work with the *calculated value* of the input, as described above with min, peak and max variables. The Decay also stores an internal value called decayValue that is the result of the calculation. The decayValue of a Track is the *average* of the decayValues of each of its Inputs, so that novelty in any of the Inputs reflects as novelty in the Track.

To begin, the first message an input receives is stored as a new target value, and the decayValue is set equal to the decayBoost. 

With each subsequent message, first we check whether the absolute difference between the new value and the target value is less than the decayRange - in other words, if the decayRange is 0.2, we check whether the new value is within 0.2 above or below the value we have stored. Again, this is not referring to the actual value of the Signal, but to the result of the calculations done by the Input, which will always be in a range of 0 to 1.

If the new value is within this range, we consider the signal not to have changed, so we *multiply* the decayValue by the decayRate. If the decayRate is high, like 0.9, the decayValue will decrease slowly. If it is low, it will decrease more quickly and the Track will soon fade out. (this should really be adjusted because the name implies the opposite of what it does... todo)

If instead the new value is outside of this range, we consider the signal to have changed, and we *add* the decayBoost to the existing decayValue. After this boost, if the new decayValue is above the decayThreshold, then we re-assign a new target value of the decay as the new reference point for deciding whether the signal has changed or not.

The result of this is that when a Signal changes significantly, a Track will slowly increase in volume so long as the incoming values are outside of the current decayRange, until it reaches the decayThreshold, at which point the target value will change. If the Signal then stays steady, the decay will slowly decrease because the new values are being compared with the updated target value.

To make a sound more present, you can lower its decayRange so that a smaller change causes an increase in volume, you can increase its decayBoost so that each message that falls outside the range causes a larger increase, you can increase the decayRate so that the track fades out more slowly, or you can increase the decayThreshold so that more change is noticeable when the signal is outside of the decayRange. You can also change how often the entire track is present by decreasing its decayCutoff.

The current decay value of a track is shown on the third horzontal slider of each track in the tracks panel.


### Making new combined features

Sometimes we need to do a calculation that takes into account more than one signal, for example the '/pe_combined' signal is not sent by EEGSonic but instead calculated within the processMessage function of the Signal object in player.js. 

In order to add a new channel, you must do two things:
1) add its name to the signals list and assign it a range 
2) create a new if statement in Signal.processMessage that creates a new message and sends it.

You can look at how the '/pe_combined' is made by detecting a '/pe_parietal' message.


## The GUI

### Main Controls Panel

The panel in the upper left corner lets you control the audio and interact with the saved presets and OSC (Open Sound Control) messages, and allows you to add a new Track. It is important to note that Resonance looks in specific folders for these files - by default these are the playerPresets, playerEvents and playerSamples folders respectively. This can be changed in the code at the top of player.js.

### The Tracks Panel

Below the main controls is a list of all the tracks, each with three blue sliders. Of these you are only able to control the top one, the other two are for visual feedback only. The top slider is the user-controlled gain on the track. Use this to turn up or down the level on a single track. The middle slider shows the current calculated volume of the track, this is the average of all the volume inputs on the track and it updates with each message the input receives. The final slider is the decay value, which reduces the volume of the track if it has been playing for a while without changing much. 


## Sound Design

### About the Process that Generates the Music

The primary inspiration for the algorithmic process that Resonance uses comes from Luciano Berio's Sequenza IXa for solo clarinet. Berio was a pre-eminent Italian composer of the mid-20th century, and his works include a series of pieces exploring the possibilities of different solo instruments. For his clarinet sequenza, Berio first wrote a technically challenging melody that explores the range of sounds the clarinet can make, and he then used this as source material to compose the Sequenza. He made the Sequenza by sampling, looping and manipulating short fragments of his melody, repeating them, playing them forwards and backwards, similar to tape-editing techniques popular at the time. He explores the space that the melody traces out by using a "sliding window" that draws out features and contrasts.

https://www.youtube.com/watch?v=vGogPD1H6YI

I've always appreciated this technique because it allows for a systemic, rule-bound and structural way of manipulating an expressive musical idea. It is difficult to reconcile the place of intuition and the composer's free spirit with a technological and algorithmic, data-driven working process. Berio's technique in this Sequenza allows the composer complete creative control over the sound material, and offers a process that can be used to draw out and amplify contrasts while still giving the piece a coherent and self-contained structure, giving it an identity and a clear form.

This idea of using algorithms to amplify the characteristics, the latent potential of a freely expressed "seed crystal melody" is central to how I approach music in general. This was also a concern of Claude Vivier, a notable Quebecois composer, who similarly used algorithmic processes to draw out the latent qualities of his freely composed melodies.


### Sound Design of the Default Preset

The 'parti pris' or organizing principle that I arrived at in composing the music for Resonance is of a 'deconstructed lullaby'. When considering the sounds to be used, a lot of my thought was that 1) this was going to be used with children, 2) family members visiting a loved one are likely to be in a certain emotional state, 3) it needs to be appropriate for a hospital setting, 4) it needs to be something you could listen to for a long while without it becoming tedious. I also to some extent wanted to create a sense of magic.

A lot of my own early musical experiences came from the looping music of video games, in which 4) is a big factor of the design - it's maybe a bit of a kitschy example, but the music of the original Pokemon Red/Blue games needed to convey a lot of character with a extreme economy of means, just because of the storage space on a GameBoy cartrige. If you listen to the music of Vermillion City (it's on YouTube), the entire loop is about 40 seconds long, but you could listen to it for a very long time and anyone who grew up playing those games would recognize it in a heartbeat.

Another reference to loops is in Ambient music, especially in works like "Music for Airports" by Brian Eno. This music is made up of loops of different durations that overlap differently with each repetition, so the musicality is in the play of between their internal stasis and the changing contrasts they have with other loops.


### Mobile Form

A popular trend in mid-20th Century music was of "mobile form" - named after a hanging mobile like you might see in an infant's bedroom - the idea was to create music where the parts are able to re-arrange their order. This falls under the umbrella of Aleatoric Music. The idea is that the piece is not a pre-determined, ordered progression of sounds that goes in a straight line from beginning to end; the sound of the piece can vary from performance to performance and the identity of the piece is in the form of the interactions. Later, the composer Agostino Di Scipio described this new role of the composer not as creating specific instructions to be dutifully carried out by the performers, but as "composing desirable interactions". These sorts of ideas are ideal for making the flexible sort of music that Resonance requires.


### Suspended Time, Moment Form, Flexible Meter & Elastic Rhythm

An immediately noticeable aspect of the music of Resonance is that it does not adhere to a meter and that different parts may be going along at entirely different tempos. The inspiration here is from another mid-century concept of "suspended time", music where the rhythms are much more "floaty" and the interest is in the contrast between moments. This give a variation of the sort of interactions from Music for Airports - the harp part and drums will have contrasts between their tempos, in a way that sometimes they cohere and other times they are disjunct. All of these interactions add to the interest of the music, although admittedly it does sometimes result in musical "glitches" and takes a certain amount of skill to make it work without being too jarring. 


## Concepts for Composing New Pieces

### Making a Soundscape where each Signal has its own Role and Identity

An advantage of music is that it is more "transparent" - there can be sevearal sounds playing at once and we hear all of them, unlike a visual representation where one signal can cover up or interfere more with another. Despite this, if the signals do not have their own identity it will be much harder to tell them apart. A big part of the compositional process was to find a 'niche', a unique place in the ecosystem for each sound so that they can all be harmonious, and all be slowly changing so you can hear all the changes without making the overall result too crowded and messy.

In the default preset, the PE is represented by drums which speed up and slow down, and also by a noisy texture. The SPR are melodic instruments that form the foreground of the music. The dPLI and wPLI are spatialized, with left-lobe signals playing in the left speaker and right-lobe in the right. The dPLI and wPLI share this spatialization, but the sounds associated with them are very different. Furthermore, the dPLI sounds are made using a microtonal process - they are not in 12-tone equal temperament, do not adhere to any scale and this helps distinguish them from the other pitched material. The HL fills out the background of the piece, especially in the lower registers, and helps to create contrast between stasis and movement when the HL is towards the front and back, respecively. The TD plays a similar supporting role to the HL, but in a higher frequency range, it adds "energy" or "excitement" to the sound. This way, for each signal if you know where to listen for it, you can find that information easily.


### Composing in Detail to Fill Gaps Between Messages

With EEGSonic, the Spectral Power Ratio signals are sent every 5 seconds and the others every 10 seconds (this can be adjusted). This can either be a challenge or an advantage depending on how you approach it. If we wanted to map a signal directly to a simple, low-level feature of the music - for instance the Hub Location being the pitch of some instrument, then the messages are too infrequent and come at too regular of intervals to be of much musical interest. Therefore, I have opted to use soundfiles that have a lot more internal detail, where the content of the music changes gradually so that every 5 seconds there's a noticeable change in more than one dimension of the music. My thinking is that for each incoming message, we have about 5 or 10 seconds to communicate the value of that message, and that value can be conveyed simultaneously in several aspects of the soundfile. This leaves the aesthetic, the expressive form of the music much more up to the composer, so long as there are noticeable contrasts and direction in the composition.


### Making Contrast on Different Orders of Magnitude

One of the most difficult things to figure out for Resonance was how to have recognizable, audible changes in response to both small- and large-range variations of a signal. One thing that music is very good for is to be able to make contrasts at different time-scales and to have both micro- and macro-variations - the music has a fractal form where you can hear different sorts of contrasts every 30 seconds, every 10, every 5, etc.

I am using pitch a lot for large-scale structure - the harp, piano, synth, etc go from low to high. Then, I compose the details of the soundfile so that sections close to each-other are similar in terms of phrasing, repeating sections of melodies with more and more ornamentation, etc. This way, the overall 'character' of the soundfile changes gradually as the pitch goes steadily from low to high. By using a loopPoint input that samples 5-second long segments of the soundfile in a moving window, small changes in the signal will result in small but noticeable changes in detail of the sound, while larger changes will be much more noticeable and drastic changes.

I also like to pass between 'accompaniment-sounding' to 'melodic-sounding' in different points in the soundfile. I'll also gradually add more activity, but I also like to decrease the amount of activity when it gets into the higher register, because this allows to put two different soundfiles that overlap slightly in subsequently higher ranges on the same Signal. If both move from low to high pitch and pass from an accompaniment to a lead role, you can have the low part of the higher soundfile playing at the same time as the higher part of the lower one and do a sort of transfer of the focal point, so that you can hear the direction the change is going.


### Using loopLength to Distinguish Between Different Features

It seems like for most of the parts, in order to be able to hear out the variations, a loopLength of about 4 or 5 seconds is good. If each part has a slightly different loopLength, that gives the overall music a distinctive character, the regularity of the loops helps hold the music together in way that you might not notice at first - but the changes are always coming at the same intervals and this gives the music structural integrity. It also helps to have some Tracks without loopLength inputs so they loop through a longer, more static musical segment and make the music feel less choppy.

In the default preset, the TD signal is coded with a much shorter loopLength, of only 0.5 seconds. The correspoing sound file changes more quickly, and has contrasts in timbre as well as pitch. This is a different way that you can catch the listener's ear and is a characteristic that lets you recognize this signal as distinct from the others. 


### Using the diff values to show when a signal is increasing/decreasing

As stated above, Resonance is intended to amplify the changes in the signals, as much as the values of the signal themselves. One way this can be done effectively is to put two paired soundfiles on the same Signal, for instance harp_main.ogg and harp_melody.ogg. The harp_main is the structural part of the music and the harp_melody contains additional ornamentation. Both have the same loopPoint input, so for any given SPR value the playhead will be at the same point; the sounds will match. But, the harp_main's volume is based on the average of the last 3 values, it increases and decreases along with the SPR. The harp_melody's volume is based on the difference between the current value and the average of the last 5 - it will be heard when the current value is higher than the average, regardless of what that average is. As a result, harp_melody is heard whenever the signal is increasing. Because of how the decay function works, this has the result that when the SPR signal increases into a new range, the first sounds heard are both the harp_main and the harp_melody, this draws a lot of attention to this signal. Then, as the average starts to match this range, the melody fades out and we hear only the main part, which then fades out a bit more slowly. This principal could be applied to all the signals to really emphasize when there is a sudden change.


### How You Could Do Harmony

Another very noticeable way that you could vary the timbre or harmony would be to have matching soundfiles in different modes/keys/instruments, etc. You could take a Track, duplicate it with exactly the same inputs, assign a different, corresponding soundfile of the same duration with a contrasting harmony/timbre, then add another volume input to both, related to the new feature you want to code for. That way, the looping point and otherwise the volume will be the same for either track so the two will always be properly aligned, but you would also hear a cross-fade in timbre between the two Tracks, or if you use a smaller min-peak-max, a sudden change in mode/harmony when you cross some threshold.


### Making More Use of the Tone.JS Library

If you look up the documentation of Tone.JS, there are a bunch of filters and other effects that could be used to manipulate the sound in Resonance. I've only explored this a little bit, adding a low-pass filter when the TD moves towards the front of the brain (indicating sedation I think?), but adding more effects like this on individual tracks or on the whole thing just before the master gain would be another way of distinguising the different Signals.


## Troubleshooting

#### Trouble adding soundfiles for new tracks

The soundfiles need to be in the playerSamples folder. (similarly, presets and events need to be in their own labeled files as well.)

#### Trouble saving and loading presets

The browser saves a cached version of any file you open. So, if you're saving the preset by overwriting the previous one, it will load the cached version instead of updating and loading the new file. It's a bit of a nuissance but the work-around is to save each iteration of the preset as its own file (preset1.txt, preset2.txt, etc.)

#### Range that starts at 0 displays as 'null'

This is because in JavaScript 0 is false. You might have to put the range as '0.'

#### OSC messages stop after a couple seconds

The console will show:

```
"Error: buffer is either not set or not loaded"
```
This error comes up if you try to play a list of OSC messages before the soundfiles are fully loaded. Just give it a moment.


#### Signals for EEGSonic are Way Too Constant

Make sure that EEGSonic is not in Debug mode. In Debug mode for every signal it sends random noise between 0 and 1.