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
write_td(file_id,parameters.td);
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

end

function write_td(file_id,td)

end

function write_pac(file_id,pac)

end

function write_fp_wpli(file_id,fp_wpli)

end

function write_fp_dpli(file_id,fp_dpli)

end

function write_hl(file_id,hl)

end

function write_pe(file_id,pe)

end