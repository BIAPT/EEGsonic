function send_hub_location(output_type,is_graph,channel_index,graph,channels_location,osc)
%SEND_HUB_LOCATION send to the osc receivers the data in string format
%   Input:
%       output_type: type of coordinate to output
%       channel_index: the index of the channel we want to send
%       channels_location: location data of the channels
%       osc: osc data structure
    %coordinate = get_coordinate(output_type,channel_index,channels_location);
    coordinate = "";
    %% TODO change below to be coordinate instead of the channel index
    osc_base_string = "/hub_location";
    osc_graph_base_string = "/hub_location_graph"
    
    if(is_graph)
       connectivity_vector = make_connectivity_vector(channel_index,graph);
    else
       connectivity_vector = coordinate; % The X Y and Z are now the connectivity vector or only the index
    end
    coordinate_osc = osc_base_string + num2str(channel_index); % This last part need to change!
    
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
        
        %% Sending coordinate
        for string_index = 1:length(coordinate_osc)
            current_osc_message = strsplit(coordinate_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message); % This also needs to change   
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
