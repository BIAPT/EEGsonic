function send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc)
%SEND_SPECTRAL_POWER_RATIO send to the osc receivers the data in string
%format
%   Input:
%       ratio_beta_alpha: vector for the ratio for each channels
%       ratio_alpha_theta: vector for the ratio for each channels
%       osc: osc data structure

    %% Variable Setup
    ratio_beta_alpha_osc = strings(1,128);
    ratio_alpha_theta_osc = strings(1,128);
    osc_base_string = strings(1,128);
    number_channels = length(ratio_beta_alpha);
    
    %% Create Base string
    for i = 1:number_channels
        osc_base_string(i) = "/sensor_"+num2str(i)+"/spectral_power_ratio/";
    end
    %% Beta/Alpha to OSC
    for i = 1:number_channels
        ratio_beta_alpha_osc(i) = osc_base_string(i) + "ratio_beta_alpha " + num2str(ratio_beta_alpha(i));
    end
    
    %% Alpha/Theta to OSC
    for i = 1:number_channels
        ratio_alpha_theta_osc(i) = osc_base_string(i) + "ratio_alpha_theta " + num2str(ratio_alpha_theta(i));
    end
    
    %% Sending OSC
    % Send osc data one osc receiver at a time
    number_osc_receivers = length(osc.path);
    for osc_index = 1:number_osc_receivers
        % Create a connection to the OSC receivers
        u = udp(osc.ip{osc_index},str2num(osc.port{osc_index}));
        %increase the buffer size (input and output)
        u.InputBufferSize = 3200;
        u.OutputBufferSize = 3200;
        
        % Sending the messages to the OSC receivers
        fopen(u);
        
        %% Sending Ratio Beta Alpha
        for string_index = 1:length(ratio_beta_alpha_osc)
            current_osc_message = strsplit(ratio_beta_alpha_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        %% Sending Ratio Alpha Theta
        for string_index = 1:length(ratio_alpha_theta_osc)
            current_osc_message = strsplit(ratio_alpha_theta_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        fclose(u);
    end
end

