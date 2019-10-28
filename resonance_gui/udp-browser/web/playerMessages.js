
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

port.on("message", function (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));
    //console.log("message", oscMessage);
    console.log(oscMessage.args);
    let j = 0;
    for (let i=0; i < sound.bufferFiles.length; i++){

    	let slider = document.getElementById(`dataGain${i}`);
    	console.log(slider);
    	if (sound.bufferFiles[i].linkNext) {
    		slider.value = (-oscMessage.args[j] * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    	} else {
			slider.value = (oscMessage.args[j] * 20)-20;
    		sound.dataGains[i].gain.linearRampToValueAtTime(Math.pow(10, slider.value/20), sound.context.currentTime + 1);
    		j++;
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