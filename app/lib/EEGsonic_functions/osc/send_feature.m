function [success] = send_feature(osc_string_list,osc)
%SEND_DATA_OSC Summary of this function goes here
%   Detailed explanation goes here

    %% Variable Setup
    success = 1;
    number_osc_receivers = length(osc.path);
    
    %% Sending OSC
    % Send osc data one osc receiver at a time
    for osc_index = 1:number_osc_receivers
        u = udp(osc.ip{osc_index},osc.port{osc_index});  
        fopen(u);
        for string_index = 1:length(osc_string_list)
            % TODO find the right way to send the data (see SLACK)
            % This is how to get to the right thing to send: osc_string_list(string_index);
            %oscsend(u,'/test','ifsINBTF', 1, 3.14, 'hello',[],[],false,[],[]);
        end
        fclose(u);
    end
end


