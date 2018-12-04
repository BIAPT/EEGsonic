function send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc)
%SEND_SPECTRAL_POWER_RATIO send to the osc receivers the data in string
%format
%   Input:
%       ratio_beta_alpha: vector for the ratio for each channels
%       ratio_alpha_theta: vector for the ratio for each channels
%       osc: osc data structure

    %% Variable Setup
    osc_base_ba = "/spectral_power_ratio_ba";
    osc_base_at = "/spectral_power_ration_at";
    osc_message_type_ba = char(get_osc_message_type(ratio_beta_alpha));
    osc_message_type_at = char(get_osc_message_type(ratio_alpha_theta));
       
    %% Sending OSC
    % Send osc data one osc receiver at a time
    number_osc_receivers = length(osc.path);
    for osc_index = 1:number_osc_receivers
        % Create a connection to the OSC receivers
        u = udp(osc.ip{osc_index},str2num(osc.port{osc_index}));
        %increase the buffer size (input and output)
        u.InputBufferSize = 3200;
        u.OutputBufferSize = 3200;
        
        % Sending the messages to the OSC receiver
        fopen(u);
        %% Sending Ratio Beta Alpha
        oscsend(u,osc_base_ba,osc_message_type_ba,double(ratio_beta_alpha));
        %% Sending Ratio Alpha Theta
        oscsend(u,osc_base_at,osc_message_type_at,double(ratio_alpha_theta));
        % Close communication with OSC receivers
        fclose(u);
        %% TODO TURN THE RATIO ALPHA THETA INTO A STRING ARRAY
    end
end

