
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

port.on("message", function (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));
    //console.log("message", oscMessage);
    console.log(oscMessage.args);
    for (let i=0; i < sound.bufferFiles.length; i++){
    	let slider = document.getElementById(`dataGain${i}`);
    	if (sound.bufferFiles[i].reversed) {
    		slider.value = (-oscMessage.args[sound.bufferFiles[i].input] * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    	} else {
			slider.value = (oscMessage.args[sound.bufferFiles[i].input] * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    	}
    }
});

port.open();

var sayHello = function () {
    port.send({
        address: "/hello",
        args: ["world"]
    });
};