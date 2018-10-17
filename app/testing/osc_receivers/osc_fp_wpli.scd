




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
	OSCdef.newMatching(("fp_wpli/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/fp_wpli/avg_pli_midline").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)

(
~numElectrodes = 128;

// setting up the responders
{|i|
	OSCdef.newMatching(("fp_wpli/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/fp_wpli/avg_pli_lateral").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)