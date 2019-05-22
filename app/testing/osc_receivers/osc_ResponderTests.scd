(
~masterControlWindow = Window("EEG Real Time Data and Features", Rect(128, 64, 1500, 1000)).front;
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

~interpolatePastValues = {|old, new, rate, current, now|
	var blendFactor, interPolatedArray;
	blendFactor = (now - current) / rate;
	interPolatedArray = [old,new].flop.collect({|item,i| item.blendAt(blendFactor)   });
	interPolatedArray
};

~interpolateAndThresholdConnectivity = {|old, new, rate = 1 , current = 0, now = 1, retain = 10|
	var blendFactor, interPolatedGraph, graphPlusWeights;
	blendFactor = (now - current) / rate;
	interPolatedGraph = [old,new].flop.collect({|item,i| item.blendAt(blendFactor)   });
	graphPlusWeights = [~fullyConnectedGraph, ~oldGraphWeights].flop.collect({|item,i| item.flatten  });
    graphPlusWeights.sort({|a,b| a[2] > b[2] }).copyRange(0, retain-1)
};


~ele = 129;
~fullyConnectedGraph = ~ele.collect({|i| ((i+1)..~ele).collect({|j| [i,j]})   }).flatten ;
~oldGraphWeights = {1.0.rand}!~fullyConnectedGraph.size;
~newGraphWeights = {1.0.rand}!~fullyConnectedGraph.size;
~graphCurrent = Main.elapsedTime;
~graphLast = Main.elapsedTime;
~graphRate = 1;
~reducedGraph = [[0,1, 0.5],[1,2, 0.9],[2,0, 0.9]];


// Arrays holding values updated by the OSCResponders

~pwrBetaOverAlphaOld = {10.0.rand}!129;
~pwrBetaOverAlphaNew = {10.0.rand}!129;
~pwrBetaOverAlphaLast = Main.elapsedTime;
~pwrBetaOverAlphaCurrent = Main.elapsedTime;
~pwrBetaOverAlphaRate = 1;

//
~pwrAlphaOverThetaOld = {10.0.rand}!129;
~pwrAlphaOverThetaNew = {10.0.rand}!129;
~pwrAlphaOverThetaLast = Main.elapsedTime;
~pwrAlphaOverThetaCurrent = Main.elapsedTime;
~pwrAlphaOverThetaRate = 1;

~pv1Map = 1;
~pv2Map = 1;


SkipJack.stopAll;
~displayJack = SkipJack({
	     ~skipJackNow = Main.elapsedTime;
	     ~electrodeColors.(~pv1, ~interpolatePastValues.(~pwrBetaOverAlphaOld, ~pwrBetaOverAlphaNew, ~pwrBetaOverAlphaRate, ~pwrBetaOverAlphaCurrent, ~skipJackNow) );
		 ~electrodeSize.(~pv1, ~interpolatePastValues.(~pwrBetaOverAlphaOld, ~pwrBetaOverAlphaNew, ~pwrBetaOverAlphaRate, ~pwrBetaOverAlphaCurrent, ~skipJackNow), ~pv1Map  );

		 ~electrodeColors.(~pv2, ~interpolatePastValues.(~pwrAlphaOverThetaOld, ~pwrAlphaOverThetaNew, ~pwrAlphaOverThetaRate, ~pwrAlphaOverThetaCurrent, ~skipJackNow) );
		 ~electrodeSize.(~pv2, ~interpolatePastValues.(~pwrAlphaOverThetaOld, ~pwrAlphaOverThetaNew, ~pwrAlphaOverThetaRate, ~pwrAlphaOverThetaCurrent, ~skipJackNow), ~pv2Map  );

	     ~reducedGraph = ~interpolateAndThresholdConnectivity.(~oldGraphWeights, ~newGraphWeights, ~graphRate, 0, 1, 100);

	     ~plotreducedGraph.(~pv2, ~reducedGraph);
            },
           0.05, { ~masterControlWindow.isClosed }, "windowUpdateJack", autostart:true);


~electrodeColors = {|display, array | display.pointColors_( array.collect({|item,i| Color.red(item, item)  }), true ); };
~pv1Warp = 1;
~electrodeSize = {|display, array, map | display.pointSizeScales_( array.collect({ |item,i| item.linlin(0.0, 1.0, 0.0, 1.0).pow(map) }), true ); };

~plotreducedGraph = {|display, array| display.connections_( array.collect({ |item,i| [item[0], item[1]] }), true );
	                                  display.connectionStrokeWidth_( array.collect({ |item,i| item[2] * 10  }) );
};

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

~pv3 = PointView(~masterControlWindow, Rect(900, 90, 400, 800)).points_(~cartPlotPos).front;
~pv3.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);


~projectSL1 = EZSlider( ~masterControlWindow, Rect(20,20, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv1.points_(~cartPlotPos); } );
~pointSizeSL1 = EZSlider( ~masterControlWindow, Rect(20,40, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1.pointSize = ez.value; 0} );
~pointWarpSL1 = EZSlider( ~masterControlWindow, Rect(20,60, 300, 20), "map",
              ControlSpec(0.0, 2.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1Map = ez.value; 0} );

~projectSL2 = EZSlider( ~masterControlWindow, Rect(600,20, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv2.points_(~cartPlotPos); } );
~pointSizeSL2 = EZSlider( ~masterControlWindow, Rect(600,40, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv2.pointSize = ez.value; 0} );
~pointWarpSL1 = EZSlider( ~masterControlWindow, Rect(600,60, 300, 20), "map",
              ControlSpec(0.0, 2.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv2Map = ez.value; 0} );

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
	if(msg.size > 2, {
		~oldGraphWeights = ~newGraphWeights;
		~newGraphWeights = msg.drop(1);
	    ~graphLast = ~graphCurrent;
        ~graphCurrent = Main.elapsedTime;
        ~graphRate = ~graphCurrent - ~graphLast;
	    },{msg.postln;});
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
	if(msg.size > 2, {
		~pwrBetaOverAlphaOld = ~pwrBetaOverAlphaNew;
		~pwrBetaOverAlphaNew = msg.drop(1);
	    ~pwrBetaOverAlphaLast = ~pwrBetaOverAlphaCurrent;
        ~pwrBetaOverAlphaCurrent = Main.elapsedTime;
        ~pwrBetaOverAlphaRate = ~pwrBetaOverAlphaCurrent - ~pwrBetaOverAlphaLast;
	    },{msg.postln;});
}, '/spectral_power_ratio_all_beta_over_alpha', nil);

OSCdef.newMatching(\alphaOverTheta, {|msg, time, addr, recvPort|
	if(msg.size > 2, {
		~pwrAlphaOverThetaOld = ~pwrAlphaOverThetaNew;
		~pwrAlphaOverThetaNew = msg.drop(1);
	    ~pwrAlphaOverThetaLast = ~pwrAlphaOverThetaCurrent;
        ~pwrAlphaOverThetaCurrent = Main.elapsedTime;
        ~pwrAlphaOverThetaRate = ~pwrAlphaOverThetaCurrent - ~pwrAlphaOverThetaLast;
	    },{msg.postln;});
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





(
~waitTime = 0.50;
t = Task({
    inf.do({ ~oscTestBetaOverAlpha = {1.0.rand}!130; ~oscTestBetaOverAlpha.addFirst("/spectral_power_ratio_all_beta_over_alpha"); m.sendBundle(0.0, ~oscTestBetaOverAlpha  );
		~oscTestAlphaOverTheta = {1.0.rand}!130; ~oscTestAlphaOverTheta.addFirst("/spectral_power_ratio_all_alpha_over_theta"); m.sendBundle(0.0, ~oscTestAlphaOverTheta);
			 ~graphWeights = {1.0.rand}!~fullyConnectedGraph.size; ~graphWeights.addFirst("/hub_location_graph"); m.sendBundle(0.0, ~graphWeights);
             ~waitTime.wait;
    });
}).start;
)

t.stop;

~waitTime = 3.5;






~interpolateAndThresholdConnectivity = {|old, new, rate = 1 , current = 0, now = 1, retain = 10|
	var blendFactor, interPolatedGraph, graphPlusWeights;
	blendFactor = (now - current) / rate;
	interPolatedGraph = [old,new].flop.collect({|item,i| item.blendAt(blendFactor)   });
	graphPlusWeights = [~fullyConnectedGraph, ~oldGraphWeights].flop.collect({|item,i| item.flatten  });
    graphPlusWeights.sort({|a,b| a[2] > b[2] }).copyRange(0, retain)
};

~ele = 130;
~fullyConnectedGraph = ~ele.collect({|i| ((i+1)..~ele).collect({|j| [i,j]})   }).flatten ;
~oldGraphWeights = {1.0.rand}!~fullyConnectedGraph.size;
~newGraphWeights = {1.0.rand}!~fullyConnectedGraph.size;

~interpolateAndThresholdConnectivity.(~oldGraphWeights, ~newGraphWeights, 1, 0, 1, 1)







~all.size;


~pv2.connections_(~all, close:false, update: true)

~pv2.connections_([[0,1], [3,4]], close:false, update: true)

~pv2.connectionColor_({Color.rand}!~ele)

~pv2.connectionStrokeWidth_({10.0.rand}!~ele)



~graphPlusWeights = [~fullyConnectedGraph, ~oldGraphWeights].flop.collect({|item,i| item.flatten  })

~graphPlusWeights.sort({|a,b| a[2] > b[2] }).copyRange(0, 5)






(
    i = Image.new(20@20);
    i.pixels_(
        Int32Array.fill(i.width * i.height, {
            Integer.fromRGBA(255.rand,127.rand,255.rand,255)
        })
    );
    //i.interpolation_(\none); // uncomment to see the difference
    w = i.plot(freeOnClose:true);
    i.pixels.postln;
)

(
    i = Image.color(50@50, Color.white);
    i.setPixels(
        Int32Array.fill(20*20,{Integer.fromRGBA(255.rand, 127.rand, 255.rand, 255)}),
        Rect(10,10,20,20)
    );
    i.interpolation_(\none); // uncomment to see the difference
    w = i.plot(freeOnClose:true);
    i.pixels.postln;
)

HeatMap



