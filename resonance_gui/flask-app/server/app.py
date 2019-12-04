from flask import Flask, render_template

import argparse
from pythonosc import osc_server
from pythonosc.dispatcher import Dispatcher

from flask_socketio import SocketIO, emit

import threading
import socket

app = Flask(__name__, static_folder="../static/dist", template_folder="../static")
socketio = SocketIO(app)

@app.route('/index/')
def render_index():
    return render_template("index.html")

@app.route('/<string:page_name>/')
def render_static(page_name):
    return f"{page_name} world!"

@socketio.on("connect")
def connect():
    print("Client connected")

def relayOSC(address, message):
	print(message)
	socketio.emit('my response', message)

def launchUDPServer():
	parser = argparse.ArgumentParser()
	parser.add_argument('--ip', default='127.0.0.1',
		help='The ip of the OSC server')
	parser.add_argument('--port', type=int, default=7400,
		help='the port the OSC server is listening on')
	args = parser.parse_args()

	dispatcher = Dispatcher()
	dispatcher.map(f'/fp_dpli_left_midline', relayOSC)

	server = osc_server.ThreadingOSCUDPServer(
		(args.ip, args.port), dispatcher)
	print(f'Serving on {server.server_address}')
	server.serve_forever()


if __name__ == '__main__':
	# this starts the OSC server in a separate thread
	t = threading.Thread(target=launchUDPServer)
	t.daemon = True
	t.start()
	# t = threading.Thread(target=launchWebsocket)
	# t.daemon = True
	# t.start()

	# this starts the Flask app
	#app.run()
	socketio.run(app, host='0.0.0.0', port=5000, debug=True, use_reloader=False)


