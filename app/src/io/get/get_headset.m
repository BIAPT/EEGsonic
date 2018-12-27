function [headset] = get_headset(information,parameters)
%GET_HEADSET return a headset information
%   Input:
%       information: contains static data in the app
%       parameters: contains variable data as inputted by the user
%   Output:
%       headset: the headset informations

    if(parameters.general.egi129.is_selected)
        headset = information.headset.egi129;
    elseif(parameters.general.dsi24.is_selected)
        headset = information.headset.dsi24;
    end
end

