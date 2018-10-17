




(
OSCdef.newMatching(("matrix").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	}, ("/topographic_distribution/ratio_front_back").asSymbol, nil);
)


(
OSCdef.newMatching(("string").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	}, ("/string").asSymbol, nil);
)



(
~numElectrodes = 128;

// setting up the responders
{|i|
	OSCdef.newMatching(("hub_location/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/hub_location/coordinate").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)