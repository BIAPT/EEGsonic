function [selected_channels] = get_selected_channels(information,parameters)
%GET_SELECTED_CHANNELS will create all the boolean mask and will return
%them as an array of 1 and 0
%   Input: 
%       information: static data in the app
%       parameters: variables data as inputed by the user
%   Output:
%       selected_channels: structure containing the boolean masks
    
    %% Seting up Variables
    all_channels = get_channels(information.headset,parameters.general);
    selected_channels = struct(); 
    
    %% Creating the Masks
    
    % TD
    % Frontal and Posterior
    td = parameters.td;
    frontal_channels = get_ticked_channels(td.frontal_channels,parameters.general);
    posterior_channels = get_ticked_channels(td.posterior_channels,parameters.general);
    selected_channels.td.frontal_channels = find_selected_channels(all_channels,frontal_channels);
    selected_channels.td.posterior_channels = find_selected_channels(all_channels,posterior_channels);

    % PAC
    % Frontal and Parietal
    pac = parameters.pac;
    frontal_channels = get_ticked_channels(pac.frontal_channels,parameters.general);
    parietal_channels = get_ticked_channels(pac.parietal_channels,parameters.general);
    selected_channels.pac.frontal_channels = find_selected_channels(all_channels,frontal_channels);
    selected_channels.pac.parietal_channels = find_selected_channels(all_channels,parietal_channels);
       
    % FP WPLI
    % Midline and Lateral
    fp_wpli = parameters.fp_wpli;
    midline_channels = get_ticked_channels(fp_wpli.midline_channels,parameters.general);
    lateral_channels = get_ticked_channels(fp_wpli.lateral_channels,parameters.general);
    selected_channels.fp_wpli.midline_channels = find_selected_channels(all_channels,midline_channels);
    selected_channels.fp_wpli.lateral_channels = find_selected_channels(all_channels,lateral_channels);
    
    % FP DPLI
    % Midline and Lateral
    fp_dpli = parameters.fp_dpli;
    midline_channels = get_ticked_channels(fp_dpli.midline_channels,parameters.general);
    lateral_channels = get_ticked_channels(fp_dpli.lateral_channels,parameters.general);
    selected_channels.fp_dpli.midline_channels = find_selected_channels(all_channels,midline_channels);
    selected_channels.fp_dpli.lateral_channels = find_selected_channels(all_channels,lateral_channels);
    
    % PE
    % Frontal and Posterior
    pe = parameters.pe;
    frontal_channels = get_ticked_channels(pe.frontal_channels,parameters.general);
    posterior_channels = get_ticked_channels(pe.posterior_channels,parameters.general);
    selected_channels.pe.frontal_channels = find_selected_channels(all_channels,frontal_channels);
    selected_channels.pe.posterior_channels = find_selected_channels(all_channels,posterior_channels);
    
end

% Return the channels depending on the headset selected
function [channels] = get_channels(headset,general)
    if(general.egi129.is_selected)
       channels = {headset.egi129.channels_location.labels};
    elseif(general.dsi24.is_selected)
        channels = {headset.egi129.channels_location.labels};
    end
end

% return the channels that were selected for a specific analysis technique
function [channels] = get_ticked_channels(ticked_channels,general)
    if(general.egi129.is_selected)
       channels = ticked_channels.egi129; 
    elseif(general.dsi24.is_selected)
        channels = ticked_channels.dsi24;
    end

end

% create the boolean mask, by checking which channels are ticked.
% this create an array of 1s and 0s
function [boolean_mask] = find_selected_channels(all_channels,ticked_channels)
    % Setting up variables
    number_all_channels = length(all_channels);
    number_ticked_channels = length(ticked_channels);
    boolean_mask = zeros(1,number_all_channels);
    
    % Iterate over all channels and set boolean_mask{i} to 1 if ticked
    for i = 1:number_all_channels
        current_boolean_channel = all_channels{i};
        for j = 1:number_ticked_channels
            current_ticked_channel = ticked_channels{j};
            if(strcmp(current_boolean_channel,current_ticked_channel))
                boolean_mask(i) = 1;
                break; 
            end
        end
    end
end
