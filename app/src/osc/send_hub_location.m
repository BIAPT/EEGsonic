function send_hub_location(is_graph,channel_index,graph,osc)
%SEND_HUB_LOCATION send to the osc receivers the data in string format
%   Input:
%       output_type: type of coordinate to output
%       channel_index: the index of the channel we want to send
%       channels_location: location data of the channels
%       osc: osc data structure

    osc_base_hd = '/hl_relative_position';
    osc_type_hd = get_osc_message_type(channel_index);
    
    if(is_graph)
       connectivity_vector = make_connectivity_vector(channel_index,graph)
       disp(length(connectivity_vector))
       osc_base_graph = '/hub_location_graph';
       osc_type_graph = get_osc_message_type(connectivity_vector);
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
        
        % Send hub location
        oscsend(u,osc_base_hd,osc_type_hd,channel_index);   
        if(is_graph)
           oscsend(u,osc_base_graph,osc_type_graph,connectivity_vector); 
        end
        
        fclose(u);
    end    
end

% Helper function to construct a vector of the following type:
% hd_index, electrode_x, weight_hd_x, hd_index, electrode_y, weight_hd_y
% where the weight are given by a thresholded graph
function [connectivity_vector] = make_connectivity_vector(channel_index,graph)
    connectivity_vector = [];
    for i = 1:length(graph)
        weight = graph(channel_index,i);
        if(i ~= channel_index && weight > 0)
           connectivity_vector = [connectivity_vector, channel_index, i, weight]; 
        end
    end
end
