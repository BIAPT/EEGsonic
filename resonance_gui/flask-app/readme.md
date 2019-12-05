# Project Title

Resonance Flask App for use with EEGSonic

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

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
nmp run watch (if you are changing files)
```

### Running the Server

To run the flask app, navigate to flask-app/server and run

```
python app.py
```

The server runs in two threads, one listening for UDP messages from EEGSonic and the second hosting the actual flask server.
