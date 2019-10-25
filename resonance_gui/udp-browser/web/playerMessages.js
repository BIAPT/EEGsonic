
var port = new osc.WebSocketPort({
    url: "ws://localhost:8081"
});

port.on("message", function (oscMessage) {
    $("#message").text(JSON.stringify(oscMessage, undefined, 2));
    console.log("message", oscMessage);
});

port.open();

var sayHello = function () {
    port.send({
        address: "/hello",
        args: ["world"]
    });
};