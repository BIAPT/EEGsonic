// Example web interface for Resonance
// Copyright (c) 2019 BiaptLab
// written by Mathieu Bouchard

/*
  OSC MESSAGE

  Spectral Power Ratio
    spr_beta_alpha
    spr_alpha_theta

  Topographic Distribution
    td_front_back

  Phase Amplitude Coupling
    pac_rpt_frontal
    pac_rpt_parietal

  Weighted Phase Lag Index
    fp_wpli_left_midline
    fp_wpli_left_lateral
    fp_wpli_right_midline
    fp_wpli_right_lateral

  Directed Phase Lag Index
    fp_dpli_left_midline
    fp_dpli_left_lateral
    fp_dpli_right_midline
    fp_dpli_right_lateral

  Hub Location
    hl_relative_position

  Permutation Entropy
    pe_frontal
    pe_parietal
*/

// Features used in the first fully conscious workshop
resonanceInputs = [
    {name:"spr_beta_alpha", min:0.15, max:1.7},
    {name:"spr_alpha_theta", min:0.05, max:1.5},
    {name:"hl_relative_position", min:0, max:1},
    {name:"pe_frontal", min:0.85, max:1},
    {name:"pe_parietal", min:0.8, max:1},
    {name:"fp_wpli_left_midline", min:0, max:0.2},
    {name:"fp_dpli_left_midline", min:0.45, max:0.55},
]

preset = {
  anamnesis_1 : [
        {name:"s0", select:"", min:-10, max:10},
        {name:"s1", select:"", min:-10, max:10},
        {name:"s2", select:"", min:-10, max:10},
        {name:"s3", select:"fp_wpli_left_midline", min:-10, max:10},
        {name:"s4", select:"fp_dpli_left_midline", min:-10, max:10},
        {name:"s5", select:"spr_beta_alpha", min:-10, max:10},
        {name:"s6", select:"spr_alpha_theta", min:-10, max:10},
        {name:"s7", select:"hl_relative_position", min:-10, max:10},
        {name:"s8", select:"pe_frontal", min:-10, max:10},
        {name:"s9", select:"pe_parietal", min:-10, max:10},
    ],
  anamnesis_2 : [
        {name:"s0", select:"", min:-10, max:10},
        {name:"s1", select:"", min:-10, max:10},
        {name:"s2", select:"", min:-10, max:10},
        {name:"s3", select:"fp_wpli_left_midline", min:-10, max:10},
        {name:"s4", select:"fp_dpli_left_midline", min:-10, max:10},
        {name:"s5", select:"spr_beta_alpha", min:-10, max:10},
        {name:"s6", select:"pe_frontal", min:-10, max:10},
        {name:"s7", select:"hl_relative_position", min:-10, max:10},
        {name:"s8", select:"spr_alpha_theta", min:-10, max:10},
        {name:"s9", select:"pe_parietal", min:-10, max:10},
    ],
  japanese_garden : [
        {name:"s0", select:"hl_relative_position", min:-10, max:10},
        {name:"s1", select:"", min:-10, max:10},
        {name:"s2", select:"", min:-10, max:10},
        {name:"s3", select:"", min:-10, max:10},
        {name:"s4", select:"spr_alpha_theta", min:-10, max:10},
        {name:"s5", select:"spr_beta_alpha", min:-10, max:10},
        {name:"s6", select:"fp_wpli_left_midline", min:-10, max:10},
        {name:"s7", select:"fp_dpli_left_midline", min:-10, max:10},
        {name:"s8", select:"pe_frontal", min:-10, max:10},
        {name:"s9", select:"pe_parietal", min:-10, max:10},
    ],
  tibetan_choir_1 : [
        {name:"s0", select:"", min:-10, max:10},
        {name:"s1", select:"", min:-10, max:10},
        {name:"s2", select:"fp_wpli_left_midline", min:-10, max:10},
        {name:"s3", select:"fp_dpli_left_midline", min:-10, max:10},
        {name:"s4", select:"spr_alpha_theta", min:-10, max:10},
        {name:"s5", select:"spr_beta_alpha", min:-10, max:10},
        {name:"s6", select:"hl_relative_position", min:-10, max:10},
        {name:"s7", select:"pe_parietal", min:-10, max:10},
        {name:"s8", select:"pe_frontal", min:-10, max:10},
        {name:"s9", select:"", min:-10, max:10},
    ],
  tibetan_choir_2 : [
        {name:"s0", select:"", min:-10, max:10},
        {name:"s1", select:"", min:-10, max:10},
        {name:"s2", select:"fp_wpli_left_midline", min:-10, max:10},
        {name:"s3", select:"fp_dpli_left_midline", min:-10, max:10},
        {name:"s4", select:"spr_alpha_theta", min:-10, max:10},
        {name:"s5", select:"pe_parietal", min:-10, max:10},
        {name:"s6", select:"hl_relative_position", min:-10, max:10},
        {name:"s7", select:"pe_frontal", min:-10, max:10},
        {name:"s8", select:"spr_beta_alpha", min:-10, max:10},
        {name:"s9", select:"", min:-10, max:10},
    ],
}

resonanceDummyInput={name:"",min:0,max:1} // written as "(none)"
resonanceInputsByName = {}
for (var i=0; i<resonanceInputs.length; i++) resonanceInputsByName[resonanceInputs[i].name]=resonanceInputs[i];

// those have to be ordered with no gaps : [i]={name:"s"+i,...} as .name isn't being used.
resonanceMapping = preset.tibetan_choir_1;

function resonanceSelectChange(id) {
    var select=document.getElementById(id);
    var i=id.substring(1,2);
    var sid="s"+i;
    //console.log("resonanceSelectChange %o",select);
    console.log("select.value=%s",select.value);
    resonanceMapping[i].select = select.value;
    var input=select.value===""?resonanceDummyInput:resonanceInputsByName[select.value];
    document.getElementById(sid+"-smin").textContent=input.min.toFixed(3);
    document.getElementById(sid+"-smax").textContent=input.max.toFixed(3);
    $("#"+sid+"-min").slider("option","min",input.min);
    $("#"+sid+"-min").slider("option","max",input.max);
    $("#"+sid+"-min").slider("value",input.min);
    $("#"+sid+"-max").slider("option","min",input.min);
    $("#"+sid+"-max").slider("option","max",input.max);
    $("#"+sid+"-max").slider("value",input.max);
    console.log("resonanceSelect=["+resonanceMapping[i].select+"]");
    //resonanceSliderChange(sid+"min");
    //resonanceSliderChange(sid+"max");
}

function resonanceSliderChange(id) {
    var i=id.substring(1,2), sid="s"+i;
    var v=$("#"+id).slider("value");
    //console.log(name+"="+v);
    if (id.endsWith("min")) {
        resonanceMapping[i].min=v;
        document.getElementById(sid+"-cmin").textContent=v.toFixed(3);
    }
    if (id.endsWith("max")) {
        resonanceMapping[i].max=v;
        document.getElementById(sid+"-cmax").textContent=v.toFixed(3);
    }
}

function resonanceTestSliderChange(id) {
    var name=id.substring(3);
    var input=resonanceInputsByName[name];
    input.value=$("#"+id).slider("value");
    document.getElementById(id+"-value").textContent=input.value.toFixed(3);
    //console.log("%s.value = %f",name,input.value);
    computeOutput(input);
}

function computeOutput(input) {
    for (var i=0; i<10; i++) {
        var m=resonanceMapping[i];
        if (m.select===input.name) {
            var diff=m.max-m.min;
            var x= diff==0 ? 0.5 : (input.value-m.min)/diff;
            if (x<0) x=0; else if (x>1) x=1;
            var sid="s"+i;
            $("#"+sid).slider("value",x);
            console.log("min=%f max=%f input=%f %s.value=%s",m.min,m.max,input.value,sid,x);
        }
    }
}

function initResonanceTest() {
    var div=document.getElementById("resonance-test");
    for (i in resonanceInputs) {
        var input=resonanceInputs[i];
        var sid="in-"+input.name;
        div.insertAdjacentHTML('beforeend','\
            <div class="resonance-slider" style="width:64px" align="center">'+input.name+'<br>\
                <span id="'+sid+'-value">?</span><br>'+input.max+'<br>\
                <div id="'+sid+'" style="margin-top:8px; margin-bottom:8px" role="slider" class="resonance-slider '+sid+' ui-slider ui-slider-vertical ui-widget ui-widget-content ui-corner-all">\
                  <div class="ui-slider-range ui-widget-header ui-corner-all ui-slider-range-min" style="height: 100%;"></div>\
                  <span class="ui-slider-handle ui-state-default ui-corner-all" tabindex="0" style="bottom: 100%;"></span>\
                </div><br>'+input.min+'\
            </div>');
        $("#"+sid).slider({
          orientation: "vertical",
          min: input.min,
          max: input.max,
          range: "min",
          value: (input.min+input.max)/2,
          step:0.00001,
          slide: function( event, ui ) {resonanceTestSliderChange(event.target.id)},
          change: function( event, ui ) {resonanceTestSliderChange(event.target.id)}
        });
        resonanceTestSliderChange(sid); //init
    }
}

function initResonance() {
    console.log("start initResonance");
    var div=document.getElementById("resonance-settings");
    //div.appendChild();
    var keys=['none','hello','world'];
    var options='<option value="">(none)</option>';
    for (var i in resonanceInputs) {
        var k=resonanceInputs[i].name;
        options+='<option value="'+k+'">'+k+'</option>';
    }
    for (var i=0; i<10; i++) {
        sid="s"+i;
        var m=resonanceMapping[i];
        div.insertAdjacentHTML('beforeend','\
              <div class="resonance-slider" align="center">\
    		  <select id="'+sid+'-select" style="width:72px" onchange="resonanceSelectChange(this.id)">'+options+'</select><br clear="left">\
    		  <span id="'+sid+'-cmax">cmax</span><br><span id="'+sid+'-cmin">cmin</span><br><span id="'+sid+'-smax">smax</span><br>\
    		  <div id="'+sid+'-min" role="slider" style="margin-top:8px;margin-bottom:8px" class="resonance-slider '+sid+' ui-slider ui-slider-vertical ui-widget ui-widget-content ui-corner-all">\
                <div class="ui-slider-range ui-widget-header ui-corner-all ui-slider-range-min" style="height: 100%;"></div>\
                <span class="ui-slider-handle ui-state-default ui-corner-all" tabindex="0" style="bottom: 100%;"></span>\
              </div>\
              <div class="resonance-slider" style="width:1px;height:1px;"></div>\
              <div id="'+sid+'-max" role="slider" style="margin-top:8px;margin-bottom:8px" class="resonance-slider '+sid+' ui-slider ui-slider-vertical ui-widget ui-widget-content ui-corner-all">\
                <div class="ui-slider-range ui-widget-header ui-corner-all ui-slider-range-min" style="height: 100%;"></div>\
                <span class="ui-slider-handle ui-state-default ui-corner-all" tabindex="0" style="bottom: 100%;"></span>\
              </div><br><span id="'+sid+'-smin">smin</span>\
            </div>');
        $("#"+sid+"-min, #"+sid+"-max").slider({
          orientation: "vertical",
          min: 0,
          max: 1,
          range: "min",
          value: 0.5,
          step:0.001,
          slide: function( event, ui ) {resonanceSliderChange(event.target.id)},
          change: function( event, ui ) {resonanceSliderChange(event.target.id)}
        });
        //initialising
        var min=m.min, max=m.max;
        $("#"+sid+"-select").val(m.select);
        resonanceSelectChange(sid+"-select");
        $("#"+sid+"-min").slider("value",min);
        $("#"+sid+"-max").slider("value",max);
        resonanceSliderChange(sid+"-min");
        resonanceSliderChange(sid+"-max");
    }
    initResonanceTest();
    var port = new osc.WebSocketPort({url: "ws://localhost:8081"});
    port.on("message", function (m) {
        k="in-"+m.address.substring(1);
        v=m.args[0];
        $("#"+k).slider("value",v);
        //resonanceTestSliderChange(k);
        //console.log("message",k,v);
    });
    port.open();
    console.log("end initResonance");
}
