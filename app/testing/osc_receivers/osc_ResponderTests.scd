
(
~masterControlWindow = Window("EEG Real Time Data and Features", Rect(128, 64, 1500, 1300)).front;
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

~topographicDistributionNew = 1;

~phaseAmplitudeCouplingFrontalNew  = 1;
~phaseAmplitudeCouplingParietalNew = 1;

~wPliMidlineNew = 1;
~wPliLateralNew = 1;

~dPliMidlineNew = 1;
~dPliLateralNew = 1;

~permEntropyFrontNew = 1;
~permEntropyBackNew = 1;

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


~pv1 = PointView(~masterControlWindow, Rect(50, 280, 400, 800)).points_(~cartPlotPos).front;
~pv1.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);

~pv2 = PointView(~masterControlWindow, Rect(50, 680, 400, 800)).points_(~cartPlotPos).front;
~pv2.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);

~pv3 = PointView(~masterControlWindow, Rect(900, 280, 400, 800)).points_(~cartPlotPos).front;
~pv3.rotate_(-90.degrad).tumble_(90.degrad).showIndices_(false).showAxes_(false).connectionColor_(Color.black);


~projectSL1 = EZSlider( ~masterControlWindow, Rect(20, 220, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv1.points_(~cartPlotPos); } );
~pointSizeSL1 = EZSlider( ~masterControlWindow, Rect(20, 240, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1.pointSize = ez.value; 0} );
~pointMapSL1 = EZSlider( ~masterControlWindow, Rect(20, 260, 300, 20), "map",
              ControlSpec(0.0, 2.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv1Map = ez.value; 0} );

{~pointMapSL1.value_(0); ~projectSL1.value_(0); ~pointSizeSL1.value(20.0)}.defer;

~projectSL2 = EZSlider( ~masterControlWindow, Rect(600, 220, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| ~cartPlotPos = ~project3D2D.(~cartPos, ez.value); ~pv2.points_(~cartPlotPos); } );
~pointSizeSL2 = EZSlider( ~masterControlWindow, Rect(600, 240, 300, 20), "size",
              ControlSpec(0.0, 100.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv2.pointSize = ez.value; 0} );
~pointMapSL2 = EZSlider( ~masterControlWindow, Rect(600, 260, 300, 20), "map",
              ControlSpec(0.0, 2.0, \lin, 0.01, 10, "size"),     // controlSpec
              { |ez| ~pv2Map = ez.value; 0} );



// SPECTRAL POWER RATIO
~spectralPowerRatioB_A = SensorData.new(24, 12).addValue( 0.0 );
~spectralViewB_A = CompositeView(~masterControlWindow, Rect( 50, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~spectralPlotterB_A = Plotter("plot", parent: ~spectralViewB_A).value_(~spectralPowerRatioB_A.data.asArray);

~spectralPowerRatioA_T = SensorData.new(24, 12).addValue( 0.0 );
~spectralViewA_T = CompositeView(~masterControlWindow, Rect(150, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~spectralPlotterA_T = Plotter("plot", parent: ~spectralViewA_T).value_(~spectralPowerRatioA_T.data.asArray);

~spectralPowerRatioSpecs = SensorData.new(24, 12).addValue( 0.0 );

// TOPOGRAPHIC DISTRIBUTION
~topographicDistribution = SensorData.new(24, 12).addValue( 0.0 );
~topographicDistributionView = CompositeView(~masterControlWindow, Rect(300, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~topographicDistributionPlotter = Plotter("plot", parent: ~topographicDistributionView).value_(~topographicDistribution.data.asArray);

// PHASE AMPLITUDE COUPLING
~phaseAmplitudeCouplingFrontal = SensorData.new(24, 12).addValue( 0.0 );
~phaseAmplitudeCouplingFrontalView = CompositeView(~masterControlWindow, Rect(450, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~phaseAmplitudeCouplingFrontalPlotter = Plotter("plot", parent: ~phaseAmplitudeCouplingFrontalView).value_(~phaseAmplitudeCouplingFrontal.data.asArray);

~phaseAmplitudeCouplingParietal = SensorData.new(24, 12).addValue( 0.0 );
~phaseAmplitudeCouplingParietalView = CompositeView(~masterControlWindow, Rect(550, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~phaseAmplitudeCouplingParietalPlotter = Plotter("plot", parent: ~phaseAmplitudeCouplingParietalView).value_(~phaseAmplitudeCouplingParietal.data.asArray);

~phaseAmplitudeCouplingSpecs = SensorData.new(24, 12).addValue( 0.0 );

// WEIGHTED PHASE LAG INDEX
~wPliMidline = SensorData.new(24, 12).addValue( 0.0 );
~wPliMidlineView = CompositeView(~masterControlWindow, Rect(750, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~wPliMidlinePlotter = Plotter("plot", parent: ~wPliMidlineView).value_(~wPliMidline.data.asArray);

~wPliLateral = SensorData.new(24, 12).addValue( 0.0 );
~wPliLateralView = CompositeView(~masterControlWindow, Rect(850, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~wPliLateralPlotter = Plotter("plot", parent: ~wPliLateralView).value_(~wPliLateral.data.asArray);

~wPliSpecs = SensorData.new(24, 12).addValue( 0.0 );

// DIRECTED PHASE LAG INDEX
~dPliMidline = SensorData.new(24, 12).addValue( 0.0 );
~dPliMidlineView = CompositeView(~masterControlWindow, Rect(1000, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~dPliMidlinePlotter = Plotter("plot", parent: ~dPliMidlineView).value_(~dPliMidline.data.asArray);

~dPliLateral = SensorData.new(24, 12).addValue( 0.0 );
~dPliLateralView = CompositeView(~masterControlWindow, Rect(1100, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~dPliLateralPlotter = Plotter("plot", parent: ~dPliLateralView).value_(~dPliLateral.data.asArray);

~dPliSpecs = SensorData.new(24, 12).addValue( 0.0 );

// PERMUTATION ENTROPY
~permEntropyFront = SensorData.new(24, 12).addValue( 0.0 );
~permEntropyFrontView = CompositeView(~masterControlWindow, Rect(1250, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~permEntropyFrontPlotter = Plotter("plot", parent: ~permEntropyFrontView).value_(~permEntropyFront.data.asArray);

~permEntropyBack = SensorData.new(24, 12).addValue( 0.0 );
~permEntropyBackView = CompositeView(~masterControlWindow, Rect(1350, 10, 100, 200)).background_(Color.rand(0.7)).resize_(5);
~permEntropyBackPlotter = Plotter("plot", parent: ~permEntropyBackView).value_(~permEntropyBack.data.asArray);

~permEntropySpecs = SensorData.new(24, 12).addValue( 0.0 );


// WPLI 0 to 1 neutral 0
// DPLI 0 to 1 neutral 0.5

// permEntropy  no bounds

// PA Coupling 0.8 1.2  0.7 1.3 neutral is 1

// ratio

//


// WPLI DPLI
OSCdef.newMatching(\wpliMidline, {|msg, time, addr, recvPort|
	    "WPLI".postln;
	    //  msg.postln;

	     ~wPliMidlineNew = msg[1];
         ~wPliLateralNew = msg[2];

	    ~wPliMidlineNew.postln;
	    ~wPliLateralNew.postln;

   	if(~wPliMidline.data.size < 2,
			{~wPliMidline.data[0] = ~wPliMidlineNew; ~wPliMidline.addValue(~wPliMidlineNew)},
			{~wPliMidline.addValue(~wPliMidlineNew)});
    if(~wPliLateral.data.size < 2,
			{~wPliLateral.data[0] = ~wPliLateralNew; ~wPliLateral.addValue(~wPliLateralNew)},
			{~wPliLateral.addValue(~wPliLateralNew)});
	if(~wPliSpecs.data.size < 2,
			{~wPliSpecs.data[0] = ~wPliMidlineNew; ~wPliSpecs.addValue(~wPliLateralNew)},
			{~wPliSpecs.addValue(~wPliMidlineNew); ~wPliSpecs.addValue(~wPliLateralNew)});
		{
		// ~wPliMidlinePlotter.specs = [~wPliSpecs.longMean - (2 * ~wPliSpecs.longStdDev), ~wPliSpecs.longMean + (2 * ~wPliSpecs.longStdDev), \lin, 0, 0, "wpli Mid"].asSpec;
		// ~wPliLateralPlotter.specs = [~wPliSpecs.longMean - (2 * ~wPliSpecs.longStdDev), ~wPliSpecs.longMean + (2 * ~wPliSpecs.longStdDev), \lin, 0, 0, "wpli Lateral"].asSpec;
		~wPliMidlinePlotter.specs = [0, 1, \lin, 0, 0, "wpli Mid"].asSpec;
		~wPliLateralPlotter.specs = [0, 1, \lin, 0, 0, "wpli Lateral"].asSpec;
		~wPliMidlineView.refresh;
		~wPliLateralView.refresh;
		}.defer;
}, '/fp_wpli_midline_and_lateral', nil);
OSCdef.newMatching(\dpliMidline, {|msg, time, addr, recvPort|
	    "DPLI".postln;
	    //  msg.postln;

	     ~dPliMidlineNew  = msg[1];
         ~dPliLateralNew = msg[2];

	    ~dPliMidlineNew.postln;
	    ~dPliLateralNew.postln;

   	if(~dPliMidline.data.size < 2,
			{~dPliMidline.data[0] = ~dPliMidlineNew; ~dPliMidline.addValue(~dPliMidlineNew)},
			{~dPliMidline.addValue(~dPliMidlineNew)});
    if(~dPliLateral.data.size < 2,
			{~dPliLateral.data[0] = ~dPliLateralNew; ~dPliLateral.addValue(~dPliLateralNew)},
			{~dPliLateral.addValue(~dPliLateralNew)});
	if(~dPliSpecs.data.size < 2,
			{~dPliSpecs.data[0] = ~dPliMidlineNew; ~dPliSpecs.addValue(~dPliLateralNew)},
			{~dPliSpecs.addValue(~dPliMidlineNew); ~dPliSpecs.addValue(~dPliLateralNew)});
		{
		// ~dPliMidlinePlotter.specs = [~dPliSpecs.longMean - (2 * ~dPliSpecs.longStdDev), ~dPliSpecs.longMean + (2 * ~dPliSpecs.longStdDev), \lin, 0, 0, "dpli Mid"].asSpec;
		// ~dPliLateralPlotter.specs = [~dPliSpecs.longMean - (2 * ~dPliSpecs.longStdDev), ~dPliSpecs.longMean + (2 * ~dPliSpecs.longStdDev), \lin, 0, 0, "dpli Lateral"].asSpec;
		~dPliMidlinePlotter.specs = [0, 1, \lin, 0, 0, "dpli Mid"].asSpec;
		~dPliLateralPlotter.specs = [0, 1, \lin, 0, 0, "dpli Lateral"].asSpec;
		~dPliMidlineView.refresh;
		~dPliLateralView.refresh;
		}.defer;
}, '/fp_dpli_midline_and_lateral', nil);

// HUB Location
OSCdef.newMatching(\hub_location, {|msg, time, addr, recvPort|
		 ~wPliMidlineNew  = msg[1];
         ~wPliLateralNew = msg[2];

	    ~wPliMidlineNew.postln;
	    ~wPliLateralNew.postln;

   	if(~wPliMidline.data.size < 2,
			{~wPliMidline.data[0] = ~wPliMidlineNew; ~wPliMidline.addValue(~wPliMidlineNew)},
			{~wPliMidline.addValue(~wPliMidlineNew)});
    if(~wPliLateral.data.size < 2,
			{~wPliLateral.data[0] = ~wPliLateralNew; ~wPliLateral.addValue(~wPliLateralNew)},
			{~wPliLateral.addValue(~wPliLateralNew)});
	if(~wPliSpecs.data.size < 2,
			{~wPliSpecs.data[0] = ~wPliMidlineNew; ~wPliSpecs.addValue(~wPliLateralNew)},
			{~wPliSpecs.addValue(~wPliMidlineNew); ~wPliSpecs.addValue(~wPliLateralNew)});
		{
			~wPliMidlinePlotter.specs = [~wPliSpecs.longMean - (2 * ~wPliSpecs.longStdDev), ~wPliSpecs.longMean + (2 * ~wPliSpecs.longStdDev), \lin, 0, 0, "wpli Mid"].asSpec;
		~wPliLateralPlotter.specs = [~wPliSpecs.longMean - (2 * ~wPliSpecs.longStdDev), ~wPliSpecs.longMean + (2 * ~wPliSpecs.longStdDev), \lin, 0, 0, "wpli Lateral"].asSpec;
			~wPliMidlineView.refresh;
		    ~wPliLateralView.refresh;
		}.defer;
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
	  ~permEntropyFrontNew  = msg[1];
      ~permEntropyBackNew = msg[2];

	    ~permEntropyFrontNew.postln;
	    ~permEntropyBackNew.postln;

   	if(~permEntropyFront.data.size < 2,
			{~permEntropyFront.data[0] = ~permEntropyFrontNew; ~permEntropyFront.addValue(~permEntropyFrontNew)},
			{~permEntropyFront.addValue(~permEntropyFrontNew)});
    if(~permEntropyBack.data.size < 2,
			{~permEntropyBack.data[0] = ~permEntropyBackNew; ~permEntropyBack.addValue(~permEntropyBackNew)},
			{~permEntropyBack.addValue(~permEntropyBackNew)});
	if(~permEntropySpecs.data.size < 2,
			{~permEntropySpecs.data[0] = ~permEntropyFrontNew; ~permEntropySpecs.addValue(~permEntropyBackNew)},
			{~permEntropySpecs.addValue(~permEntropyFrontNew); ~permEntropySpecs.addValue(~permEntropyBackNew)});
		{
		~permEntropyFrontPlotter.specs = [~permEntropySpecs.longMean - (2 * ~permEntropySpecs.longStdDev), ~permEntropySpecs.longMean + (2 * ~permEntropySpecs.longStdDev), \lin, 0, 0, "permEntropyFront"].asSpec;
		~permEntropyBackPlotter.specs = [~permEntropySpecs.longMean - (2 * ~permEntropySpecs.longStdDev), ~permEntropySpecs.longMean + (2 * ~permEntropySpecs.longStdDev), \lin, 0, 0, "permEntropyBack"].asSpec;
			~permEntropyFrontView.refresh;
		    ~permEntropyBackView.refresh;
		}.defer;
}, '/permutation_entropy_frontal_and_parietal', nil);

// PhaseAmplitudeCoupling
OSCdef.newMatching(\phase_amplitude_coupling_frontal_and_parietal, {|msg, time, addr, recvPort|
		 "PHASE AMPLITUDE".postln;
	    //  msg.postln;

	     ~phaseAmplitudeCouplingFrontalNew  = msg[1];
         ~phaseAmplitudeCouplingParietalNew = msg[2];

	     ~phaseAmplitudeCouplingFrontalNew.postln;
	     ~phaseAmplitudeCouplingParietalNew.postln;

   	if(~phaseAmplitudeCouplingFrontal.data.size < 2,
			{~phaseAmplitudeCouplingFrontal.data[0] = ~phaseAmplitudeCouplingFrontalNew; ~phaseAmplitudeCouplingFrontal.addValue(~phaseAmplitudeCouplingFrontalNew)},
			{~phaseAmplitudeCouplingFrontal.addValue(~phaseAmplitudeCouplingFrontalNew)});
    if(~phaseAmplitudeCouplingParietal.data.size < 2,
			{~phaseAmplitudeCouplingParietal.data[0] = ~phaseAmplitudeCouplingParietalNew; ~phaseAmplitudeCouplingParietal.addValue(~phaseAmplitudeCouplingParietalNew)},
			{~phaseAmplitudeCouplingParietal.addValue(~phaseAmplitudeCouplingParietalNew)});
	if(~phaseAmplitudeCouplingSpecs.data.size < 2,
			{~phaseAmplitudeCouplingSpecs.data[0] = ~phaseAmplitudeCouplingParietalNew; ~phaseAmplitudeCouplingSpecs.addValue(~phaseAmplitudeCouplingFrontalNew)},
			{~phaseAmplitudeCouplingSpecs.addValue(~phaseAmplitudeCouplingParietalNew); ~phaseAmplitudeCouplingSpecs.addValue(~phaseAmplitudeCouplingFrontalNew)});
		{
		//	~phaseAmplitudeCouplingFrontalPlotter.specs = [~phaseAmplitudeCouplingSpecs.longMean - (2 * ~phaseAmplitudeCouplingSpecs.longStdDev), ~phaseAmplitudeCouplingSpecs.longMean + (2 * ~phaseAmplitudeCouplingSpecs.longStdDev), \lin, 0, 0, "PA Cplng Front"].asSpec;
		// ~phaseAmplitudeCouplingParietalPlotter.specs = [~phaseAmplitudeCouplingSpecs.longMean - (2 * ~phaseAmplitudeCouplingSpecs.longStdDev), ~phaseAmplitudeCouplingSpecs.longMean + (2 * ~phaseAmplitudeCouplingSpecs.longStdDev), \lin, 0, 0, "PA Cplng Pariet"].asSpec;

		~phaseAmplitudeCouplingFrontalPlotter.specs = [0.7, 1.3, \lin, 0, 0, "PA Cplng Front"].asSpec;
		~phaseAmplitudeCouplingParietalPlotter.specs = [0.7, 1.3, \lin, 0, 0, "PA Cplng Pariet"].asSpec;
			~phaseAmplitudeCouplingFrontalView.refresh;
		    ~phaseAmplitudeCouplingParietalView.refresh;
		}.defer;

}, '/phase_amplitude_coupling_frontal_and_parietal', nil);

// spectral power Ratio
OSCdef.newMatching(\betaOverAlpha, {|msg, time, addr, recvPort|
	if(msg.size > 2, {
		~pwrBetaOverAlphaOld = ~pwrBetaOverAlphaNew;
		~pwrBetaOverAlphaNew = msg.drop(1);
	    ~pwrBetaOverAlphaLast = ~pwrBetaOverAlphaCurrent;
        ~pwrBetaOverAlphaCurrent = Main.elapsedTime;
        ~pwrBetaOverAlphaRate = ~pwrBetaOverAlphaCurrent - ~pwrBetaOverAlphaLast;
		~pwrBetaOverAlphaNew.postln;
		if(~spectralPowerRatioB_A.data.size < 2,
			{~spectralPowerRatioB_A.data[0] = ~pwrBetaOverAlphaNew.mean.log10; ~spectralPowerRatioB_A.addValue(~pwrBetaOverAlphaNew.mean.log10)},
			{~spectralPowerRatioB_A.addValue(~pwrBetaOverAlphaNew.mean)});
		if(~spectralPowerRatioSpecs.data.size < 2,
			{~spectralPowerRatioSpecs.data[0] = ~pwrBetaOverAlphaNew.mean.log10; ~spectralPowerRatioSpecs.addValue(~pwrBetaOverAlphaNew.mean.log10)},
			{~spectralPowerRatioSpecs.addValue(~pwrBetaOverAlphaNew.mean.log10)});
		{
			~spectralPlotterB_A.specs = [~spectralPowerRatioSpecs.longMean - (2 * ~spectralPowerRatioSpecs.longStdDev), ~spectralPowerRatioSpecs.longMean + (2 * ~spectralPowerRatioSpecs.longStdDev), \lin, 0, 0, "B/A average"].asSpec;
			~spectralViewB_A.refresh;
		}.defer;
	    },{msg.postln;});
}, '/spectral_power_ratio_all_beta_over_alpha', nil);

OSCdef.newMatching(\alphaOverTheta, {|msg, time, addr, recvPort|
	if(msg.size > 2, {
		~pwrAlphaOverThetaOld = ~pwrAlphaOverThetaNew;
		~pwrAlphaOverThetaNew = msg.drop(1);
	    ~pwrAlphaOverThetaLast = ~pwrAlphaOverThetaCurrent;
        ~pwrAlphaOverThetaCurrent = Main.elapsedTime;
        ~pwrAlphaOverThetaRate = ~pwrAlphaOverThetaCurrent - ~pwrAlphaOverThetaLast;
		~pwrAlphaOverThetaNew.postln;
		if(~spectralPowerRatioA_T.data.size < 2,
			{~spectralPowerRatioA_T.data[0] = ~pwrAlphaOverThetaNew.mean.log10; ~spectralPowerRatioA_T.addValue(~pwrAlphaOverThetaNew.mean.log10)},
			{~spectralPowerRatioA_T.addValue(~pwrAlphaOverThetaNew.mean.log10)});
		if(~spectralPowerRatioSpecs.data.size < 2,
			{~spectralPowerRatioSpecs.data[0] = ~pwrAlphaOverThetaNew.mean.log10; ~spectralPowerRatioSpecs.addValue(~pwrAlphaOverThetaNew.mean.log10)},
			{~spectralPowerRatioSpecs.addValue(~pwrAlphaOverThetaNew.mean.log10)});
		{
			~spectralPlotterA_T.specs = [~spectralPowerRatioSpecs.longMean - (2 * ~spectralPowerRatioSpecs.longStdDev), ~spectralPowerRatioSpecs.longMean + (2 * ~spectralPowerRatioSpecs.longStdDev), \lin, 0, 0, "A/T average"].asSpec;
			~spectralViewA_T.refresh;
		}.defer;
	    },{msg.postln;});
}, '/spectral_power_ratio_all_alpha_over_theta', nil);

// Topographic Distribution
OSCdef.newMatching(\topographicDistribution, {|msg, time, addr, recvPort|

		~topographicDistributionNew = msg.drop(1);

		if(~topographicDistribution.data.size < 2,
	        {~topographicDistribution.data[0] = ~topographicDistributionNew[0]; ~topographicDistribution.addValue(~topographicDistributionNew[0])},
			{~topographicDistribution.addValue(~topographicDistributionNew[0])});
		{
			~topographicDistributionPlotter.specs = [~topographicDistribution.longMean - (4 * ~topographicDistribution.longStdDev), ~topographicDistribution.longMean + (4 * ~topographicDistribution.longStdDev), \lin, 0, 0, "topo distri"].asSpec;
			~topographicDistributionView.refresh;
		}.defer;

}, '/topographic_distribution_front_over_back', nil);


NetAddr.langPort.postln;

thisProcess.openUDPPort(57120); // attempt to open 1121
thisProcess.openPorts; // list all open ports

m = NetAddr("127.0.0.1", 57120); // loopback

// m.sendMsg("/fp_wpli_midline_and_lateral", "WPLI MID LATERAL");
// m.sendMsg("/fp_dpli_midline_and_lateral", "DPLI MID LATERAL");
m.sendMsg("/hub_location", "HUB LOCATION");
m.sendMsg("/hub_location_graph", "HUB LOCATION GRAPH");
// m.sendMsg("/permutation_entropy_frontal_and_parietal", "PERMUTATION ENTROPY FRONTAL PARIETAL");
// m.sendMsg("/phase_amplitude_coupling_frontal_and_parietal", "PHASE AMPLITUDE COUPLING FRONTAL PARIETAL");
// m.sendMsg("/spectral_power_ratio_all_beta_over_alpha", "BETA OVER ALPHA");
// m.sendMsg("/spectral_power_ratio_all_alpha_over_theta", "ALPHA OVER THETA");
// m.sendMsg("/topographic_distribution_front_over_back", "TOPOPGRAPHIC DISTRIBUTION FRONT OVER BACK");

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



