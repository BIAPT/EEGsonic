function log_parameters_to_file(path,name,parameters)
%LOG_TO_FILE Summary of this function goes here
%   Detailed explanation goes here

%% TODO WRITE THIS FUNCTION TO SAVE  PARAMETERS INTO FILE!
file_name = path + "\"+name;
file_id = fopen(file_name,'w');
fprintf(file_id,"Information EEG session - " + (date) + "\n");
fprintf(file_id,"\n");

fprintf(file_id,"General: \n");
write_general(file_id,parameters.general);
fprintf(file_id,"\n");

fprintf(file_id,"Open Sound Control: \n");
write_osc(file_id,parameters.osc);
fprintf(file_id,"\n");

fprintf(file_id,"Spectral Power Ratio: \n");
write_spr(file_id,parameters.spr);
fprintf(file_id,"\n");

fprintf(file_id,"Topgraphic Distribution: \n");
write_td(file_id,parameters.td,parameters.general);
fprintf(file_id,"\n");

fprintf(file_id,"Phase Amplitude Coupling: \n");
write_pac(file_id,parameters.pac);
fprintf(file_id,"\n");

fprintf(file_id,"Fronto-Parietal wPLI: \n");
write_fp_wpli(file_id,parameters.fp_wpli);
fprintf(file_id,"\n");

fprintf(file_id,"Fronto-Parietal dPLI: \n");
write_fp_dpli(file_id,parameters.fp_dpli);
fprintf(file_id,"\n");

fprintf(file_id,"Hub Location: \n");
write_hl(file_id,parameters.hl);
fprintf(file_id,"\n");

fprintf(file_id,"Permutation Entropy: \n");
write_pe(file_id,parameters.pe);
fprintf(file_id,"\n");
fclose(file_id);
end

%% Writer functions
function write_general(file_id,general)
    headset = "none";
    data_acquisition_size = "not specified";
    if(general.egi129.is_selected)
        headset = "EGI 129";
        data_acquisition_size = num2str(general.egi129.data_acquisition_size)+" sec";
    elseif(general.dsi24.is_selected)
        headset = "DSI 24";
    end
    fprintf(file_id,"Headset: " + headset + "\n");
    fprintf(file_id,"Data acquisition size: " + data_acquisition_size + "\n");
    
end

function write_osc(file_id,osc)
    for i = 1:length(osc.path)
       osc_receiver =  "Path: " + osc.path{i} + ", Ip: " + osc.ip{i} + ", Port: " + osc.port{i} + "\n";
       fprintf(file_id,"Osc receiver("+num2str(i)+"): " + osc_receiver);
    end

end

function write_spr(file_id,spr)

    if(spr.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(spr.window_size) + " sec \n");
        fprintf(file_id,"Step size: " + num2str(spr.step_size) + " sec \n");
        fprintf(file_id,"Time bandwidth product: " + num2str(spr.time_bandwith_product) + " \n");
        fprintf(file_id,"Number of tapers: " + num2str(spr.number_tapers) + " \n");
        fprintf(file_id,"Theta bandwidth("+num2str(spr.theta.is_selected)+"): " + mat2str(spr.theta.bandwith) + " \n");
        fprintf(file_id,"Alpha bandwidth("+num2str(spr.alpha.is_selected)+"): " + mat2str(spr.alpha.bandwith) + " \n");
        fprintf(file_id,"Beta bandwidth("+num2str(spr.beta.is_selected)+"): " + mat2str(spr.beta.bandwith) + " \n");
        fprintf(file_id,"Required size for computation: " + num2str(spr.required_size) + " sec \n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end

end

function write_td(file_id,td,general)
    if(td.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(td.required_size) + " sec \n");
        fprintf(file_id,"Frequency: " + num2str(td.frequency) + " Hz \n");
        frontal_channels = "";
        posterior_channels = "";
        if(general.egi129.is_selected)
            frontal_channels = make_channels_string(td.frontal_channels.egi129);
            posterior_channels = make_channels_string(td.posterior_channels.egi129);
        elseif(general.dsi24.is_selected)
            frontal_channels = make_channels_string(td.frontal_channels.dsi24);
            posterior_channels = make_channels_string(td.posterior_channels.dsi24);
        end
        fprintf(file_id,"Frontal channels: " + frontal_channels + " \n");   
        fprintf(file_id,"Posterior channels: " + posterior_channels + " \n");           
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_pac(file_id,pac)
    if(pac.is_selected)
        fprintf(file_id,"Is selected? YES\n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_fp_wpli(file_id,fp_wpli)
    if(fp_wpli.is_selected)
        fprintf(file_id,"Is selected? YES\n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_fp_dpli(file_id,fp_dpli)
    if(fp_dpli.is_selected)
        fprintf(file_id,"Is selected? YES\n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_hl(file_id,hl)
    if(hl.is_selected)
        fprintf(file_id,"Is selected? YES\n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_pe(file_id,pe)
    if(pe.is_selected)
        fprintf(file_id,"Is selected? YES\n");
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

%% Helper function
function [channels_string] = make_channels_string(channels)
    channels_string = "";
    for i = 1:length(channels)
        if(i == 1)
            separator = "";
        else
            separator = ",";
        end
        channels_string = channels_string + separator + channels{i};
    end
end