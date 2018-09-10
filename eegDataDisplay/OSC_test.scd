




(
OSCdef.newMatching(("matrix").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	}, ("/matrix").asSymbol, nil);
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
OSCdef.newMatching(("electrode"++i).asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/electrode/"++i++"/alpha").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)