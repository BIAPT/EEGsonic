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

### Running the Server

To run the flask app, navigate to flask-app/server and run

```
python3 app.py
```

The server runs in two threads, one listening for UDP messages from EEGSonic and the second hosting the actual flask server. The rounting is handled by flask-app/app.py.

In the browser (tested on Firefox and Chrome), navigate to 

```
127.0.0.1:5000
```

and click "Load Default". You should see a list of tracks to the left and a list of signals to the right.

### Working with MATLAB EEGSonic

The Resonance app can work in two modes - it can either receive messages directly from the MATLAB EEGSonic app, or it can replay a .txt file of saved EEGSonic messages.

In the first case, to connect with the MATLAB EEGSonic app, close and re-open a new instance of MATLAB and make sure that only the EEGSonic folders and the default MATLAB files are included in the path. There are analysis functions in other folders that have the same names as the ones EEGSonic uses and these have caused conflicts in the past. When EEGSonic is run on MATLAB that has been open for a while sometimes different features will stop sending their messages after a few minutes, but this has not been a problem when MATLAB was recently opened.

### Converting raw EEG data to EEGSonic's format

The BIAPT Lab uses the Philips .mff format. EEGSonic is designed run on raw, unfiltered EEG data. Starting with a .mff file:

1. In MATLAB's Command Window, put "eeglab" and press enter. This will open EEGLAB.
2. Select File -> Import Data -> Using EEGLAB functions and plugins -> Import Philips .mff file.
3. Select the .mff file you want to convert.
4. Make sure that the Sampling rate is 1000. With too low of a sampling rate some features will not work, and the signals will not be sent as frequently.
5. Still in EEGLab, select File -> Save current dataset(s). Choose a location to save. This will give you two files, a .fdt and a .set
6. You can now close EEGLab.
7. In Matlab's Current Folder window, navigate to EEGsonic/app and double-click EEGsonic_app.mlapp. In a moment the app will open.
8. In EEG Sonic, select File -> Convert EEG Data. A new window will open.
9. Click "Select input file" and choose the .set you just converted. The .set and .fdt must be in the same folder for this to work.
10. Click "Select output folder" and choose where you want the converted files to be saved.
11. Under "Output folder name", insert an appropriate name. A new folder of this name will be created inside the selected output folder.
12. Click "Convert" and wait for it to display "Finished Converting" before closing the window.
13. You should now see a new folder with subfolders "data", "features", and "parameters", as well as an information.txt file.

Once the replay function is 

