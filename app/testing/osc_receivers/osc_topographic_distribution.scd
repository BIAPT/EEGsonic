




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
	OSCdef.newMatching(("topographic_distribution/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/topographic_distribution/ratio_front_back").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)