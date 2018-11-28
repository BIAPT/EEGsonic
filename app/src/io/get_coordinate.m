function [coordinate] = get_coordinate(type,channel_index,channels_location)
%GET_COORDINATE return a converted coordinate location for OSC
%   Input:
%       type: type of conversion from index
%       channel_index: index of the currently selected channel
%       channels_location: data structure containing all the info on
%       channels
%   Output:
%       coordinate: string format of the coordinate
    
    %% Get the coordinate in the right format
    if(strcmp(type,'cartesian'))
        coordinate = get_cartesian(channel_index,channels_location);
    end
    %% TODO add spherical if needed
    
end

% function to get cartesian coordinate out of channels_location
function [coordinate] = get_cartesian(channel_index,channels_location)
    channel_location = channels_location(channel_index);
    coordinate = [channel_location.X,channel_location.Y,channel_location.Z];
end