from flask import Flask, render_template, send_from_directory
from werkzeug.utils import secure_filename

import argparse
from pythonosc import osc_server
from pythonosc.dispatcher import Dispatcher

from flask_socketio import SocketIO, emit, send

import threading
import socket

UPLOAD_FOLDER = '/static/'

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
socketio = SocketIO(app)

@app.route('/')
def render_index():
    return render_template("index.html")

# @app.route('/samples/<path:filename>')
# def send_sample(filename):
# 	return send_from_directory(app.config['UPLOAD_FOLDER'], '/static/samples/' + filename, as_attachment=True)

@socketio.on("connect")
def connect():
    print("Client connected")

def relayOSC(address, message):
	print(address)
	print(message)
	socketio.emit('event', message) # this is sending the OSC message to the the front end

def launchUDPServer():
	# this is handling the messages received from EEGSonic
	parser = argparse.ArgumentParser()
	parser.add_argument('--ip', default='127.0.0.1',
		help='The ip of the OSC server')
	parser.add_argument('--port', type=int, default=7400,
		help='the port the OSC server is listening on')
	args = parser.parse_args()

	dispatcher = Dispatcher()
	dispatcher.map(f'/fp_dpli_left_midline', relayOSC) # this is receiving the messages from EEGsonic and forwarding to the front end

	server = osc_server.ThreadingOSCUDPServer(
		(args.ip, args.port), dispatcher)
	print(f'Serving on {server.server_address}')
	server.serve_forever()


if __name__ == '__main__':
	# this starts the OSC server that receives from EEGSonic in a separate thread
	t = threading.Thread(target=launchUDPServer)
	t.daemon = True
	t.start()

	# this starts the Flask app with web sockets
	socketio.run(app, host='0.0.0.0', port=5000, debug=True, use_reloader=False)


