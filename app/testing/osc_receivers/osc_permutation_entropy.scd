




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
OSCdef.newMatching(("permutation_entropy/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/permutation_entropy/avg_pe_frontal").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)

(
~numElectrodes = 128;

// setting up the responders
{|i|
OSCdef.newMatching(("permutation_entropy/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/permutation_entropy/avg_pe_parietal").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)