import io from '../node_modules/socket.io-client';

const socket = io();

socket.on('event', function(data){
	console.log('received message');
	console.log(data);
});



