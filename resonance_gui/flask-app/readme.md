# RESONANCE FLASK PLAYER

Resonance Flask App for use with EEGSonic

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
Tone.js
```

### Installing

To configure the JavaScript modules navigate to flask-app/static and run

```
npm run build (for one-time use)
npm run watch (if you are changing files)
```

### When editing files

If you are editing the javascript or HTML/CSS files and the changes are not reflected in the site, you need to navigate to flask-app/static and run

```
npm run watch
```

## HOW IT WORKS

### Working with MATLAB EEGSonic

The Resonance app can work in two modes - it can either receive messages directly from the MATLAB EEGSonic app, or it can replay a .txt file of saved EEGSonic messages.

In the first case, to connect with the MATLAB EEGSonic app, close and re-open a new instance of MATLAB and make sure that only the EEGSonic folders and the default MATLAB files are included in the path. There are analysis functions in other folders that have the same names as the ones EEGSonic uses and these have caused conflicts in the past. When EEGSonic is run on MATLAB that has been open for a while sometimes different features will stop sending their messages after a few minutes, but this has not been a problem when MATLAB was recently opened.

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


### Converting raw EEG data to EEGSonic's format in MATLAB

The BIAPT Lab uses the Philips .mff format. EEGSonic is designed run on raw, unfiltered EEG data. Starting with a .mff file:

1. In MATLAB's Command Window, type "eeglab" and press enter. This will open EEGLAB.
2. Select File -> Import Data -> Using EEGLAB functions and plugins -> Import Philips .mff file.
3. Select the .mff file you want to convert.
4. Make sure that the Sampling rate is 1000. With too low of a sampling rate some features will not work.
5. Select File -> Save current dataset(s). Choose a location to save. This will give you two files, a .fdt and a .set
6. You can now close EEGLab.
7. In Matlab's Current Folder window, navigate to EEGsonic/app and double-click EEGsonic_app.mlapp.
8. In EEG Sonic, select File -> Convert EEG Data. A new window will open.
9. Click "Select input file" and choose the .set you just converted. The .set and .fdt must be in the same folder.
10. Click "Select output folder" and choose where you want the converted files to be saved.
11. Under "Output folder name", give an appropriate name. This creates a new folder inside the selected output folder.
12. Click "Convert" and wait for it to display "Finished Converting" before closing the window.
13. You should now see a new folder with subfolders "data", "features", and "parameters", as well as an information.txt file.


### Replaying a converted folder

For troubleshooting, refer to "Working with MATLAB EEGSonic" above. Open EEGSonic_app.mlapp in MATLAB and click "Replay". Select the converted folder, which will have the Output Folder Name given in step 11 above.

The app should automatically have all the correct features set, but to be sure, clicking "OSC Receivers" should give a list that includes "external,120.0.0.1,7400". This is the port that the Python Flask app runs on, if in doubt, this address will be displayed to the screen when starting the Flask app.

If it is not already running, start the flask server in a terminal window, and navigate to 127.0.0.1:5000 in a browser window. 

Click the button in the bottom right corner of EEGSonic to open the replay window. To start the data, press "Play". You should begin to see messages posted to the terminal window, and in the browser the signal data should begin to change. If this happens, you're all set!


### Streaming live EEG data

Open the EEGSonic_app.mlapp file in MATLAB. Click "Select Saving Directory" and select an output folder, and next to Folder Name, input a name of the new folder to be created. Select the "EGI-129" tab. Make sure the configuration is the same as listed above under "Replaying a converted folder". Start the app and open the browser page in the same way as when replaying a folder. Press the Play button to start recording data and broadcasting messages. 





