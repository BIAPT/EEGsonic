

(
// Setting Up an OSC Responder
~numElectrodes = 128;

{|i|
OSCdef.newMatching(("electrode"++i).asSymbol, {|msg, time, addr, recvPort|
	 msg.postln;
	}, ("/electrode/"++i++"/alpha").asSymbol, nil);
	}!~numElectrodes;

)




(
// Sending Messages
m = NetAddr.localAddr;
m.sendMsg("/electrode/0/alpha", 10.rand)
)





(
~path = Document.current.dir;

~posFromFile = TabFileReader.read(~path++"/EGI_electrodes.txt",skipEmptyLines:true);
~posFromFile.do({|item, i| item.do({|jtem,j|  if(j!=1, {~posFromFile[i][j] = ~posFromFile[i][j].interpret}) })  });

~distance = {|index|
	~posFromFile.do({|item,i|
		~posFromFile[i] = ~posFromFile[i].add((~posFromFile[i].copyRange(8,10) - ~posFromFile[index].copyRange(8,10)).pow(2).sum.sqrt) });
	};

~distance.(50);

)


(
w = Window.new("Electrode Positions Numbering", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[0],Color.black, Color.hsv(item[0].linlin(0, 129, 0,0.9), 1.0, 1.0,  )]])
    };
w.refresh;
)


(
w = Window.new("Electrode labels", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[1],Color.black, Color.gray(1.0)]])
    };
w.refresh;
)


(
w = Window.new("Electrode EGI Rings", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[2],Color.black,  Color.hsv(item[2].linlin(0, 9, 0,0.999), 1.0, 1.0,  )]])
    };
w.refresh;
)

(
w = Window.new("Electrode EGI Index on Ring Clockwise", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[3],Color.black, Color.hsv(item[3].linlin(0, 21, 0,0.999), 1.0, 1.0,  )]])
    };
w.refresh;
)

(
w = Window.new("Electrode EGI Spiral Count Clockwise", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[4],Color.black, Color.hsv(item[4].linlin(0, 129, 0,0.999), 1.0, 1.0,  )]])
    };
w.refresh;
)

(
w = Window.new("Electrode EGI Hemisphers", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[1],Color.black, Color.gray((item[5]).linlin(-1.0,1.0, 0.5, 1.0) )]])
    };
w.refresh;
)


(
w = Window.new("Electrode EGI FrontBack", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[6],Color.black, Color.gray((item[6]).linlin(-1.0,1.0, 0.4, 1.0) )]])
    };
w.refresh;
)

(
w = Window.new("Electrode EGI Regions", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[7],Color.black, Color.hsv(item[7].linlin(0, 10, 0,0.9999), 1.0, 1.0,  )]])
    };
w.refresh;
)

(
w = Window.new("Electrode EGI Regions", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.select({|item,i| item[2] == 9 }).do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[2],Color.black, Color.hsv(item[2].linlin(0, 10, 0,0.9999), 1.0, 1.0,  )]])
    };
w.refresh;
)


(
w = Window.new("Electrode EGI Regions", Rect(800,800, 820, 820)).front;
w.view.background_(Color.white);
    ~posFromFile.select({|item,i| item[5] == 0 }).do{|item,i|
	Button(w,Rect((item[14] * 120) + 390,(item[15] * -120) + 400, 35, 35) )
	.states_([[item[5],Color.black, Color.hsv(item[5].linlin(-1, 1, 0,0.9999), 1.0, 1.0,  )]])
    };
w.refresh;
)
