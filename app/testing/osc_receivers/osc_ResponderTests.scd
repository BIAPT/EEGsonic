(
~masterControlWindow = Window("EEG Real Time Data and Features", Rect(128, 64, 1000, 1000)).front;
~path = Document.current.dir;

~posFromFile = TabFileReader.read(~path++"/EGI_electrodes.txt",skipEmptyLines:true);
~posFromFile.do({|item, i| item.do({|jtem,j|  if(j!=1, {~posFromFile[i][j] = ~posFromFile[i][j].interpret}) })  });
~posFromFile[0] = ~posFromFile[0].add(0);

~distanceXY = {|x, y|
    ~posFromFile.do({|item,i|
        ~posFromFile[i][16] = [(~posFromFile[i][14] - x).pow(2) , (~posFromFile[i][15] - y).pow(2)].sum.sqrt });
          };

~project3D2D = {|points, warp|
           var returnpoints;
           returnpoints = points.deepCopy;
           returnpoints.do({|item,i| returnpoints[i] = returnpoints[i].asSpherical;
           returnpoints[i].phi = returnpoints[i].phi.linlin(pi * -0.5, pi * 0.5, warp * pi * -0.5, pi * 0.5 );
           returnpoints[i] = returnpoints[i].asCartesian;
           returnpoints[i].z = returnpoints[i].z * warp;
            });
           returnpoints
           };

~electrodeColors = {|display, array | display.pointColors_( array.collect({|item,i| Color.red(item, item)  }), true ); };
~pv1Warp = 1;
~electrodeSize = {|display, array | display.pointSizeScales_( array.collect({ |item,i| item.linlin(0.0, 1.0, 1.0, 0.0).pow(~pv1Warp) }), true ); };

//~electrodeColors.(~pv1, {1.0.rand}!(~posFromFile.size));

// ~pv1.connectionStrokeWidth_(20);
// ~pv1.connectionColor_({Color.red(1.0.rand, 1.0.rand)}!(~posFromFile.size), true );
// ~pv1.pointColors_( {Color(1.0.rand, 1.0.rand)}!(~posFromFile.size), true );
// ~pv1.pointSizeScales_( {1.0.rand}!(~posFromFile.size), true );

~cartPos  = ~posFromFile.collect({|item, i| Cartesian(item[8], item[9], item[10]) });
~cartPlotPos = ~project3D2D.(~cartPos, 1.0);


~pv1 = PointView(~masterControlWindow, Rect(50, 90, 400, 800)).points_(~cartPlotPos).front;
~pv1.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);

~pv2 = PointView(~masterControlWindow, Rect(500, 90, 400, 800)).points_(~cartPlotPos).front;
~pv2.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);


~projectSL1 = EZSlider( ~masterControlWindow, Rect(20,20, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv1.points_(~cartPlotPos); } );
~pointSizeSL1 = EZSlider( ~masterControlWindow, Rect(20,40, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1.pointSize = ez.value; 0} );
~pointWarpSL1 = EZSlider( ~masterControlWindow, Rect(20,60, 300, 20), "map",
              ControlSpec(0.0, 2.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1Warp = ez.value; 0} );

~projectSL2 = EZSlider( ~masterControlWindow, Rect(600,20, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv2.points_(~cartPlotPos); } );

~pointSizeSL2 = EZSlider( ~masterControlWindow, Rect(600,50, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv2.pointSize = ez.value; 0} );



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
	{~electrodeColors.(~pv1, msg.drop(1)); ~electrodeSize.(~pv1, msg.drop(1))}.defer;
}, '/spectral_power_ratio_all_beta_over_alpha', nil);

OSCdef.newMatching(\alphaOverTheta, {|msg, time, addr, recvPort|
	msg.postln;
	{~electrodeColors.(~pv2, msg.drop(1))}.defer;
}, '/spectral_power_ratio_all_alpha_over_theta', nil);

// Topographic Distribution
OSCdef.newMatching(\topographicDistribution, {|msg, time, addr, recvPort|
	msg.postln;
}, '/topographic_distribution_front_over_back', nil);


NetAddr.langPort.postln;

thisProcess.openUDPPort(57120); // attempt to open 1121
thisProcess.openPorts; // list all open ports

m = NetAddr("127.0.0.1", 57121); // loopback


m.sendMsg("/fp_wpli_midline_and_lateral", "WPLI MID LATERAL");
m.sendMsg("/fp_wpli_midline_and_lateral", "DPLI MID LATERAL");
m.sendMsg("/hub_location", "HUB LOCATION");
m.sendMsg("/hub_location_graph", "HUB LOCATION GRAPH");
m.sendMsg("/permutation_entropy_frontal_and_parietal", "PERMUTATION ENTROPY FRONTAL PARIETAL");
m.sendMsg("/phase_amplitude_coupling_frontal_and_parietal", "PHASE AMPLITUDE COUPLING FRONTAL PARIETAL");
m.sendMsg("/spectral_power_ratio_all_beta_over_alpha", "BETA OVER ALPHA");
m.sendMsg("/spectral_power_ratio_all_alpha_over_theta", "ALPHA OVER THETA");
m.sendMsg("/topographic_distribution_front_over_back", "TOPOPGRAPHIC DISTRIBUTION FRONT OVER BACK");

OSCFunc.trace(true); // Turn posting on
OSCFunc.trace(false); // Turn posting on




)




[1,2,3].drop(1)

