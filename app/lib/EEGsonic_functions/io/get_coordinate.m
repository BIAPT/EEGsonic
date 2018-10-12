function [coordinate] = get_coordinate(type,channel_index,channels_location)
%GET_COORDINATE Summary of this function goes here
%   Detailed explanation goes here
    
    %% Get the coordinate in the right format
    if(strcmp(type,'cartesian'))
        coordinate = get_cartesian(channel_index,channels_location);
    end
    %% TODO add spherical if needed
    
end

function [coordinate] = get_cartesian(channel_index,channels_location)
    channel_location = channels_location(channel_index);
    coordinate = [channel_location.X,channel_location.Y,channel_location.Z];
end