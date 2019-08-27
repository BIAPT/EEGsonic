function send_topographic_distribution(ratio_front_back,osc)
%SEND_TOPOGRAPHIC_DISTRIBUTION send to the osc receivers the data in string
%format
%   Input:
%       ratio_front_back: singular value representing ratio_front_back
%       osc: osc data structure
    osc_base = '/td_front_back';
    osc_type = get_osc_message_type(ratio_front_back);
    
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
        
        %% Sending ratio front back
        oscsend(u,osc_base,osc_type,ratio_front_back);
        
        fclose(u);
    end
end

