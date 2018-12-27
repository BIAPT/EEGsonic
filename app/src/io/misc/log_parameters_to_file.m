function log_parameters_to_file(path,name,parameters)
%LOG_TO_FILE will save the parameters into a files to know the inputs of
%this session
%   Input:
%       path: path where to save the parameters and the logfile
%       name: name of the logfile
%       parameters: data we wish to save

    %% Setting up variables
    file_name = strcat(path,filesep,name);
    file_id = fopen(file_name,'w');
    
    %% Writing to the opened logfile
    % Header
    fprintf(file_id,"Information EEG session - " + (date) + "\n");
    fprintf(file_id,"\n");

    % General
    fprintf(file_id,"General: \n");
    write_general(file_id,parameters.general);
    fprintf(file_id,"\n");

    % OSC
    fprintf(file_id,"Open Sound Control: \n");
    write_osc(file_id,parameters.osc);
    fprintf(file_id,"\n");

    % Spectral Power Ratio
    fprintf(file_id,"Spectral Power Ratio: \n");
    write_spr(file_id,parameters.spr);
    fprintf(file_id,"\n");

    % Topographic Distribution
    fprintf(file_id,"Topgraphic Distribution: \n");
    write_td(file_id,parameters.td,parameters.general);
    fprintf(file_id,"\n");

    % Phase Amplitude Coupling
    fprintf(file_id,"Phase Amplitude Coupling: \n");
    write_pac(file_id,parameters.pac,parameters.general);
    fprintf(file_id,"\n");

    % Fronto-Parietal wPLi
    fprintf(file_id,"Fronto-Parietal wPLI: \n");
    write_fp_wpli(file_id,parameters.fp_wpli,parameters.general);
    fprintf(file_id,"\n");

    % Fronto-Parietal dPLI
    fprintf(file_id,"Fronto-Parietal dPLI: \n");
    write_fp_dpli(file_id,parameters.fp_dpli,parameters.general);
    fprintf(file_id,"\n");

    % Hub Location
    fprintf(file_id,"Hub Location: \n");
    write_hl(file_id,parameters.hl);
    fprintf(file_id,"\n");

    % Permutation Entropy
    fprintf(file_id,"Permutation Entropy: \n");
    write_pe(file_id,parameters.pe,parameters.general);
    fprintf(file_id,"\n");
    
    % Closing the file
    fclose(file_id);
end

    %% Writer functions
    % All function work the same way
    % given a data structure they will read it and print it to the file
    % (pointed to by the file_id) in a readable format
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

function write_pac(file_id,pac,general)
    if(pac.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(pac.required_size) + " sec \n");
        if(general.egi129.is_selected)
            frontal_channels = make_channels_string(pac.frontal_channels.egi129);
            parietal_channels = make_channels_string(pac.parietal_channels.egi129);
        elseif(general.dsi24.is_selected)
            frontal_channels = make_channels_string(pac.frontal_channels.dsi24);
            parietal_channels = make_channels_string(pac.parietal_channels.dsi24);
        end        
        fprintf(file_id,"Frontal channels: " + frontal_channels + " \n");   
        fprintf(file_id,"Parietal channels: " + parietal_channels + " \n"); 
        fprintf(file_id,"Extra-low frequency bandwidth: " + mat2str(pac.extra_low_frequency.bandwith) + " \n");
        fprintf(file_id,"High frequency bandwidth: " + mat2str(pac.high_frequency.bandwith) + " \n");        
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_fp_wpli(file_id,fp_wpli,general)
    if(fp_wpli.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(fp_wpli.required_size) + " sec \n");
        if(general.egi129.is_selected)
            midline_channels = make_channels_string(fp_wpli.midline_channels.egi129);
            lateral_channels = make_channels_string(fp_wpli.lateral_channels.egi129);
        elseif(general.dsi24.is_selected)
            midline_channels = make_channels_string(fp_wpli.midline_channels.dsi24);
            lateral_channels = make_channels_string(fp_wpli.lateral_channels.dsi24);
        end     
        fprintf(file_id,"Midline channels: " + midline_channels + " \n");   
        fprintf(file_id,"Lateral channels: " + lateral_channels + " \n");  
        fprintf(file_id,"Number of surrogates: " + num2str(fp_wpli.number_surrogates) + " \n");
        fprintf(file_id,"p value: " + num2str(fp_wpli.p_value) + " \n");        
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_fp_dpli(file_id,fp_dpli,general)
    if(fp_dpli.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(fp_dpli.required_size) + " sec \n");
        if(general.egi129.is_selected)
            midline_channels = make_channels_string(fp_dpli.midline_channels.egi129);
            lateral_channels = make_channels_string(fp_dpli.lateral_channels.egi129);
        elseif(general.dsi24.is_selected)
            midline_channels = make_channels_string(fp_dpli.midline_channels.dsi24);
            lateral_channels = make_channels_string(fp_dpli.lateral_channels.dsi24);
        end     
        fprintf(file_id,"Midline channels: " + midline_channels + " \n");   
        fprintf(file_id,"Lateral channels: " + lateral_channels + " \n");  
        fprintf(file_id,"Number of surrogates: " + num2str(fp_dpli.number_surrogates) + " \n");
        fprintf(file_id,"p value: " + num2str(fp_dpli.p_value) + " \n");               
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_hl(file_id,hl)
    if(hl.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(hl.required_size) + " \n");
        fprintf(file_id,"Number of surrogates: " + num2str(hl.number_surrogates) + " \n");        
        fprintf(file_id,"p value: " + num2str(hl.p_value) + " \n");
        fprintf(file_id,"Top connection threshold: " + num2str(hl.top_connection_threshold) + " \n");        
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

function write_pe(file_id,pe,general)
    if(pe.is_selected)
        fprintf(file_id,"Is selected? YES\n");
        fprintf(file_id,"Window size: " + num2str(pe.required_size) + " sec \n");
        if(general.egi129.is_selected)
            frontal_channels = make_channels_string(pe.frontal_channels.egi129);
            posterior_channels = make_channels_string(pe.posterior_channels.egi129);
        elseif(general.dsi24.is_selected)
            frontal_channels = make_channels_string(pe.frontal_channels.dsi24);
            posterior_channels = make_channels_string(pe.posterior_channels.dsi24);
        end
        fprintf(file_id,"Frontal channels: " + frontal_channels + " \n");   
        fprintf(file_id,"Posterior channels: " + posterior_channels + " \n");   
        fprintf(file_id,"Embedding dimension: " + num2str(pe.embedding_dimension) + " \n");
        fprintf(file_id,"Time delay: " + num2str(pe.time_delay) + " \n");        
    else
        fprintf(file_id,"Is selected? NO\n");
    end
end

    %% Helper function
    % function to turn a channel array into a string
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