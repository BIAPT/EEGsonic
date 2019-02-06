(
// Make a master controll window
~masterControlWindow = Window("EEG Real Time Data and Features", Rect(128, 64, 1000, 1000));
~masterControlWindow.front;

~eegData = {0.0}!130;

~swPlotter = SWPlotterMonitor.new( {
    //data to plot
    [~eegData]},
    400, //nr of points to plot
    130, // channels
    10, // plot dtime
    1 // write every n data points
    ).stop;

~swPlotter.plotter.name_("Electrode Data");
~swPlotter.plotter.bounds_( Rect(100, 100, 900, 900));
~swPlotter.plotter.parent.close;

/*
~monitorButton = Button(~masterControlWindow, Rect(20,20, 75, 24));
~monitorButton.states = [["Open", Color.blue, Color.grey] , ["Close", Color.red, Color.grey]];
~monitorButton.action_({|butt|
    if(butt.value == 1,{~swPlotter.plotter.makeWindow;},
                       {~swPlotter.plotter.parent.close;} )  });
*/

~masterGain = 0.0;
~gainSL = EZSlider( ~masterControlWindow, Rect(20,20, 300, 20), "Master",
              ControlSpec(0.001, 10.0, \exponential, 0.00001, 0.0),     // controlSpec
              { |ez| ~masterGain = ez.value;
                     ~decoder.set(\gain, ~masterGain );
                     ~masterGain.postln; } );

~gain = 20;
~gainSL = EZSlider( ~masterControlWindow, Rect(20,50, 300, 20), "gain",
              ControlSpec(0.0, 30, \lin, 0.01, 1, "gain"),     // controlSpec
              { |ez| ~gain = ez.value } );

~offset = 15;
~offsetSL = EZSlider( ~masterControlWindow, Rect(20,80, 300, 20), "offset",
              ControlSpec(0.0, 30, \lin, 0.01, 1, "gain"),     // controlSpec
              { |ez| ~offset = ez.value } );


~offsetSL = EZSlider( ~masterControlWindow, Rect(600,20, 300, 20), "warp",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "warp"),     // controlSpec
              { |ez| // ez.value.postln;
               ~cartPlotPos = ~project.(~cartPos, ez.value);
               ~pv.points_(~cartPlotPos);
               } );

~pointSizeSL = EZSlider( ~masterControlWindow, Rect(600,50, 300, 20), "size",
              ControlSpec(0.0, 1.0, \lin, 0.01, 1, "size"),     // controlSpec
              { |ez| // ez.value.postln;
                ~pv.pointSizeScales = {ez.value}!~pv.numPoints;
               } );



OSCdef.newMatching('electrode', {|msg, time, addr, recvPort|
    ~eegData = msg.drop(1);    ~eegData = ~eegData * ~gain;
    ~eegData.do({|item, i| ~eegData[i] = 50 + (~eegData[i] + (~offset * i))});
}, '/electrodes', nil);


OSCdef.newMatching('electrodeFeature', {|msg, time, addr, recvPort|
    ~eegFeatures = msg.drop(1);
    {~pv.pointColors_(~eegFeatures.collect{|item, i| Color(~eegFeatures[i], 0, 0, 1) })}.defer;
}, '/electrodeFeatures', nil);

OSCdef.newMatching('connectivity', {|msg, time, addr, recvPort|
    ~connectivity = msg.drop(1);
    ~connectiv = ~connectivity.clump(3).flop.drop(-1).flop.deepCopy;
    ~wheights = ~connectivity.clump(3).flop[2];
    {~pv.connections_(~connectiv, close: false);

    ~pv.connectionStrokeWidth_(~wheights * 10);
        ~pv.connectionColor_(~wheights.collect({|item,i| Color.red(item, item)  }));

    }.defer;
}, '/connectivity', nil);


~path = Document.current.dir;

~posFromFile = TabFileReader.read(~path++"/EGI_electrodes.txt",skipEmptyLines:true);
~posFromFile.do({|item, i| item.do({|jtem,j|  if(j!=1, {~posFromFile[i][j] = ~posFromFile[i][j].interpret}) })  });

~posFromFile[0] = ~posFromFile[0].add(0);

~distanceXY = {|x, y|
    ~posFromFile.do({|item,i|
        ~posFromFile[i][16] = [(~posFromFile[i][14] - x).pow(2) , (~posFromFile[i][15] - y).pow(2)].sum.sqrt });
          };

// ~distanceXY.(0,0);

~posFromFile = ~posFromFile.select({|item,i| item[2] < 7 });

~posFromFile.size;

~back  = ~posFromFile.flop[15].minItem;
~front = ~posFromFile.flop[15].maxItem;

~left  = ~posFromFile.flop[14].minItem;
~rigth = ~posFromFile.flop[14].maxItem;


// 14 15

m = NetAddr.localAddr;

~intro = "m.sendBundle(0.0,";
~outro = ");";


~prepareElectrodeFeatures =
{|spread1,spread2|
    var feats;
    // (~dists1 + ~dists2).normailze;
    // ~posFromFile = ~posFromFile.flop.deepCopy;
    // ~posFromFile[16] = (~posFromFile[16].normalize).linexp( 0.0 ,1.0 ,1.0 , spread1 ).deepCopy;
    // ~posFromFile = ~posFromFile.flop.deepCopy;
    ~features = (~dists1 + ~dists2).normalize;
    feats = ~features.deepCopy;
    ~theFeatures = feats.addFirst(('/electrodeFeatures').asString).asCompileString;
     (~intro++~theFeatures++~outro).interpret;
};


~dists1 = {0}!~posFromFile.flop[16].size;
~features = {0}!~posFromFile.flop[16].size;

~spread1 = 0.001;
~spread1SL = EZSlider( ~masterControlWindow, Rect(20, 540, 200, 20), "spread",
              ControlSpec(0.001, 0.5, \exponential, 0.0001, 1, "warp"),     // controlSpec
              { |ez| ~spread1 = ez.value; } );

~dists2 = {0}!~posFromFile.flop[16].size;
~spread2 = 0.001;
~spread2SL = EZSlider( ~masterControlWindow, Rect(240, 540, 200, 20), "spread",
              ControlSpec(0.001, 0.5, \exponential, 0.0001, 1, "warp"),     // controlSpec
              { |ez| ~spread2 = ez.value; } );


~t1 = Slider2D(~masterControlWindow, Rect(20, 580, 200, 200))
        .x_(0.5) // initial location of x
        .y_(1)   // initial location of y
        .action_({|sl|
    ~distanceXY.(sl.x.linlin(0.0, 1.0, ~left, ~rigth),sl.y.linlin(0.0, 1.0, ~back, ~front));
    ~dists1 = (~posFromFile.flop[16].normalize).linexp( 0.0 ,1.0 ,1.0 , ~spread1 ).deepCopy;
    ~prepareElectrodeFeatures.(~spread1,~spread2);


    ~features.do({|item, i|
                            ~encoder.set( (\bw++i.asString).asSymbol, item.linexp(0.0, 1.0, 1.5, 0.001) );
                            ~encoder.set( (\gain++i.asString).asSymbol,  item.linexp(0.0, 1.0, 0.001, 100.0) );
     });
        });

~t2 = Slider2D(~masterControlWindow, Rect(240, 580, 200, 200))
        .x_(0.5) // initial location of x
        .y_(1)   // initial location of y
        .action_({|sl|
    ~distanceXY.(sl.x.linlin(0.0, 1.0, ~left, ~rigth),sl.y.linlin(0.0, 1.0, ~back, ~front));
    ~dists2 = (~posFromFile.flop[16].normalize).linexp( 0.0 ,1.0 ,1.0 , ~spread2 ).deepCopy;
    ~prepareElectrodeFeatures.(~spread1,~spread2);

        ~features.do({|item, i|
                            ~encoder.set( (\bw++i.asString).asSymbol, item.linexp(0.0, 1.0, 1.5, 0.001) );
                            ~encoder.set( (\gain++i.asString).asSymbol,  item.linexp(0.0, 1.0, 0.001, 100.0) );
     });
        });


~electrodes = {}!~posFromFile.size;

    ~posFromFile.do{|item,i|
    ~electrodes[i] =
    Button(~masterControlWindow,Rect((item[14] * 70) + 250,(item[15] * -70) + 320, 20, 20) )
    .states_([[item[1],Color.black, Color.gray((item[5]).linlin(-1.0,1.0, 0.5, 1.0) )],
              [item[1],Color.black, Color.green((item[5]).linlin(-1.0,1.0, 0.5, 1.0) )],
              [item[1],Color.black, Color.blue((item[5]).linlin(-1.0,1.0, 0.2, 1.0) )]
    ])
    .font_(Font("Helvetica", 7));
    };

~cartPos  = ~posFromFile.collect({|item, i| Cartesian(item[8], item[9], item[10]) });

~project = {|points, warp|
           var returnpoints;
           returnpoints = points.deepCopy;
           returnpoints.do({|item,i| returnpoints[i] = returnpoints[i].asSpherical;
           returnpoints[i].phi = returnpoints[i].phi.linlin(pi * -0.5, pi * 0.5, warp * pi * -0.5, pi * 0.5 );
           returnpoints[i] = returnpoints[i].asCartesian;
           returnpoints[i].z = returnpoints[i].z * warp;
             });
           returnpoints
           };


~cartPlotPos = ~project.(~cartPos, 1.0);


~pv = PointView(~masterControlWindow, Rect(500, 90, 400, 800)).points_(~cartPlotPos).front;

~pv.rotate_(-90.degrad);
~pv.tumble_(90.degrad);
~pv.showIndices_(false);
~pv.showAxes_(false);
~pv.connectionColor_(Color.black);



ServerOptions.devices;
s = Server.local;
// s = Server.internal;
//Server.supernova;
 Server.scsynth;
Server.local = Server.default;
o = Server.local.options; // Get the local server's options
//o.outDevice = "HDSPe MADI (23453676)"; // MetaLab HDSPe MADI (23453676)

// o.device = "MADIface USB (23631679)"; // CIRMMT workshop  MADIface USB (23635751)
o.device = nil;
o.numInputBusChannels = 2; // Set Input to number of Mikes
o.numOutputBusChannels = 36;
o.numAudioBusChannels = 2048 * 8;
o.blockSize = 512 ;
o.numWireBufs = 1024 * 32;
o.memSize = 2.pow(20);
o.sampleRate = 48000;
o.maxSynthDefs = 1024 * 16;
//o.threads_(2);
s.makeWindow;
s.reboot;




)


(
~hoaOrder = 3;
~hoaNumChannels = (~hoaOrder + 1).pow(2);
~numSensors = 92;
s.scope(17);

Routine.run{

Buffer.freeAll(s);
HOABinaural.loadHeadphoneCorrections(s);
HOABinaural.loadbinauralIRs(s);
HOABinaural.headPhoneIRs.postln;
HOABinaural.binauralIRs.postln;

~source = NodeProxy.new(s, \audio, 1);
~source.source = { WhiteNoise.ar(0.01) };
~source.fadeTime = 0.1;

s.sync;

~encoder = NodeProxy.new(s, \audio, ~hoaNumChannels);
~numSensors.do({|i|
        ~encoder[i] = { HOALibEnc3D3.ar(
                                       Resonz.ar(
                                                DelayN.ar(\in.ar(1), 6.0,
                                                     (\delay++i.asString).asSymbol.kr(
                                                             ~posFromFile[i][15].linlin(~back, ~front, 6.0, 0.0)
                                                              ) ) ,
                                               (\freq++i.asString).asSymbol.kr( 440 ),
                                               (\bw++i.asString).asSymbol.kr( 0.1, 3.0 ),
                                               (\gain++i.asString).asSymbol.ar( 0.001, 1.0 )
                                             ),
                                     (\az++i.asString).asSymbol.kr( ~posFromFile[i][12] ),
                                    (\el++i.asString).asSymbol.kr( ~posFromFile[i][13] ),
        0 )};
 // s.sync;
});

s.sync;
~encoder.fadeTime = 1;

~decoder = NodeProxy.new(s, \audio, 17);
// ~decoder.source = {|gain| HOABinaural.ar(~hoaOrder, \in.ar(0!(~hoaNumChannels)), headphoneCorrection: 4 )  * gain };
~decoder.source = {|gain|
        var rotated, mirrored;
        rotated =  HOATransRotateAz.ar(~hoaOrder, \in.ar(0!(~hoaNumChannels)), 0.0 );
        mirrored = HOATransMirror.ar(~hoaOrder, rotated,1,1,0);
        HOADecCIRMMT17D3o.ar( ~hoaOrder, mirrored ) * gain };
~decoder.fadeTime = 0.1;
~decoder.play(0, 17);

s.sync;
~source <>> ~encoder;
s.sync;
~encoder <>> ~decoder;


s.sync;

};

)

(

~source.source = { Decay.ar(Impulse.ar(0.333), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };

~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][7].linlin(1,5,50, 90).midicps ); });

~numSensors.do({|i| var randN = 1.0.rand;
                            ~encoder.set( (\bw++i.asString).asSymbol, randN.linexp(0.0, 1.0, 1.5, 0.001) );
                            ~encoder.set( (\gain++i.asString).asSymbol,  randN.linexp(0.0, 1.0, 0.01, 10.0) );
});

)

// Different exciters

~source.source = { Decay.ar(Impulse.ar(1), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.0000001)  };
~source.source = { Decay.ar(Impulse.ar(0.5), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.0000001)  };
~source.source = { Decay.ar(Impulse.ar(0.3333), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.0000001)  };
~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.0000001)  };
~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };


~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, PinkNoise.ar(2) )   };

~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, WhiteNoise.ar(2) )   };

~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, ClipNoise.ar(2) )   };


~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.25), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.05)  };


~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.25), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };


~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, ClipNoise.ar(2) ) +  PinkNoise.ar(0.01)  };

~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.04, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };


~source.source = { Decay.ar(Impulse.ar(1), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };

~source.source = { Decay.ar(Impulse.ar(0.5), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.001)  };

~source.source = { Decay.ar(Impulse.ar(0.3333), 0.02, PinkNoise.ar(2) ) +  PinkNoise.ar(0.01)  };

~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.005, ClipNoise.ar(2) ) +  PinkNoise.ar(0.01)  };

~source.source = { Decay.ar(Impulse.ar(0.3333 * 0.5), 0.01, WhiteNoise.ar(2) ) +  PinkNoise.ar(0.01)  };




// different Tunings
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][7].linlin(1,5,50, 90).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][7].linlin(1,5,40, 90).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][7].linlin(1,5,40, 70).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][7].linlin(1,5,60, 95).midicps ); });


~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][2].linlin(0,6,90, 50).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][2].linlin(0,6,90, 60).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][2].linlin(0,6,90, 40).midicps ); });
~numSensors.do({|i|   ~encoder.set( (\freq++i.asString).asSymbol, ~posFromFile[i][2].linlin(0,6,90, 35).midicps ); });





~posFromFile.flop[2].plot
