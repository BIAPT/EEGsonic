function [coordinate] = get_coordinate(type,channel_index,information,parameters)
%GET_COORDINATE Summary of this function goes here
%   Detailed explanation goes here
    
    %% Select the right channel location struct
    channels_location = struct();
    if(parameters.general.egi129.is_selected)
        channels_location = information.headset.egi129.channels_location;
    elseif(parameters.general.dsi24.is_selected)
        channels_location = information.headset.dsi24.channels_location;
    end
    
    %% Get the coordinate in the right format
    if(strcmp(type,"cartesian"))
        coordinate = get_cartesian(channel_index,channels_location);
    end
    %% TODO add spherical if needed
    
end

function [coordinate] = get_cartesian(channel_index,channels_location)
    channel_location = channels_location(channel_index);
    coordinate = [channel_location.X,channel_location.Y,channel_location.Z];
end