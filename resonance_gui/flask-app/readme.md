# Project Title

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

### Running the Server

To run the flask app, navigate to flask-app/server and run

```
python3 app.py
```

The server runs in two threads, one listening for UDP messages from EEGSonic and the second hosting the actual flask server.

### When editing files

If you are editing the javascript or HTML/CSS files and the changes are not reflected in the site, you need to navigate to flask-app/static and run

```
npm run watch
```

