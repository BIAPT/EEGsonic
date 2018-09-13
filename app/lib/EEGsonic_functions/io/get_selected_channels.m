function [selected_channels] = get_selected_channels(information,parameters)
%GET_SELECTED_CHANNELS Summary of this function goes here
%   Detailed explanation goes here
    
    %% Seting up Variables
    channels = get_channels(information.headset,parameters.general);
    selected_channels = struct();
    

    %% TODO:
    % create a boolean mask for each analysis technique that has channels
    % selection and then populate this structure with each of these boolean
    % mask.
    
    
    %% Creating the Masks
    
    % TD
    % Frontal and Posterior
    
    % PAC
    % Frontal and Parietal
    
    % FP WPLI
    % Midline and Lateral
    
    % FP DPLI
    % Midline and Lateral
    
    % PE
    % Frontal and Posterior
    
    
    
    
end

function [channels] = get_channels(headset,general)
    if(general.egi129.is_selected)
       channels = {headset.egi129.channels_location.labels};
    elseif(general.dsi24.is_selected)
        channels = {headset.egi129.channels_location.labels};
    end
end

function [boolean_mask] = find_selected_channels(all_channels,selected_channels)
    boolean_mask = zeros(1,length(all_channels));
    
    %% TODO Iterate over all the channels and find them in the selected channels
end
