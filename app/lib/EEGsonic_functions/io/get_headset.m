function [headset] = get_headset(information,parameters)
%GET_HEADSET Summary of this function goes here
%   Detailed explanation goes here
    if(parameters.general.egi129.is_selected)
        headset = information.headset.egi129;
    elseif(parameters.general.dsi24.is_selected)
        headset = information.headset.dsi24;
    end
end

