function send_hub_location(output_type,channel_index,channels_location,osc)
%SEND_HUB_LOCATION send to the osc receivers the data in string format
%   Input:
%       output_type: type of coordinate to output
%       channel_index: the index of the channel we want to send
%       channels_location: location data of the channels
%       osc: osc data structure
    coordinate = get_coordinate(output_type,channel_index,channels_location);
    
end

