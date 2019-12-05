// playerMessages.js
// this script handles OSC messages coming from EEG Sonic by way of the Flask backend.
import io from '../node_modules/socket.io-client';

console.log('playerMessages reporting in');

const socket = io();

socket.on('event', function(data){
	console.log('received message');
	console.log(data);
});