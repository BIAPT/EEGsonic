function send_topographic_distribution(ratio_front_back,osc)
%SEND_TOPOGRAPHIC_DISTRIBUTION send to the osc receivers the data in string
%format
%   Input:
%       ratio_front_back: singular value representing ratio_front_back
%       osc: osc data structure

    
    osc_base_string = "/topographic_distribution";
    ratio_front_back_osc = osc_base_string + num2str(ratio_front_back);
    
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
        for string_index = 1:length(ratio_front_back_osc)
            current_osc_message = strsplit(ratio_front_back_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        fclose(u);
    end
end

