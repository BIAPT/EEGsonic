
(
// WPLI DPLI
OSCdef.newMatching(\wpliMidline, {|msg, time, addr, recvPort|
	msg.postln;
}, '/fp_wpli_midline_and_lateral', nil);
OSCdef.newMatching(\dpliMidline, {|msg, time, addr, recvPort|
	msg.postln;
}, '/fp_dpli_midline_and_lateral', nil);

// HUB Location
OSCdef.newMatching(\hub_location, {|msg, time, addr, recvPort|
	msg.postln;
}, '/hub_location', nil);

OSCdef.newMatching(\hub_location_graph, {|msg, time, addr, recvPort|
	msg.postln;
}, '/hub_location_graph', nil);

// PermutationEntropy
OSCdef.newMatching(\permutation_entropy_frontal_and_parietal, {|msg, time, addr, recvPort|
	msg.postln;
}, '/permutation_entropy_frontal_and_parietal', nil);

// PhaseAmplitudeCoupling
OSCdef.newMatching(\phase_amplitude_coupling_frontal_and_parietal, {|msg, time, addr, recvPort|
	msg.postln;
}, '/phase_amplitude_coupling_frontal_and_parietal', nil);

// spectral power Ratio
OSCdef.newMatching(\betaOverAlpha, {|msg, time, addr, recvPort|
	msg.postln;
}, '/spectral_power_ratio_all_beta_over_alpha', nil);

OSCdef.newMatching(\alphaOverBeta, {|msg, time, addr, recvPort|
	msg.postln;
}, '/spectral_power_ratio_all_alpha_over_theta', nil);

// Topographic Distribution
OSCdef.newMatching(\topographicDistribution, {|msg, time, addr, recvPort|
	msg.postln;
}, '/topographic_distribution_front_over_back', nil);


)





OSCFunc.trace(true); // Turn posting on

OSCdef(\test, {|msg, time, addr, recvPort| \unmatching.postln}, '/spectral_power_ratio_all_beta_over_alpha', nil); // def style


m = NetAddr("127.0.0.1", 57120); // loopback

m.sendMsg("/spectral_power_ratio_all_beta_over_alpha", "Hello App 1")

m.sendMsg("/spectral_power_ratio_all_alpha_over_theta", "Hello App 1")


OSCdef

NetAddr.langPort

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
	OSCdef.newMatching(("fp_dpli/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/fp_dpli/avg_dpli_midline").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)

(
~numElectrodes = 128;

// setting up the responders
{|i|
	OSCdef.newMatching(("fp_dpli/").asSymbol, {|msg, time, addr, recvPort|
	msg.postln;
	},
	("/fp_dpli/avg_dpli_lateral").asSymbol, // change the receiver string here
	nil);
	}!~numElectrodes;

)