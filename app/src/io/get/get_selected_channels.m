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
    channels_location = information.headset.egi129.channels_location;
    selected_channels = struct(); 
    
    %% Creating the Masks
    
    % TD
    % Frontal and Posterior
    td = parameters.td;
    channels = td.channels;
    anterior_channels = get_anterior(channels, channels_location);
    posterior_channels = get_posterior(channels, channels_location);
    
    selected_channels.td.frontal_channels = find_selected_channels(all_channels,anterior_channels);
    selected_channels.td.posterior_channels = find_selected_channels(all_channels,posterior_channels);

    % PAC
    % Frontal and Parietal
    pac = parameters.pac;
    channels = pac.channels;
    anterior_channels = get_anterior(channels, channels_location);
    posterior_channels = get_posterior(channels, channels_location);
    
    selected_channels.pac.frontal_channels = find_selected_channels(all_channels,anterior_channels);
    selected_channels.pac.parietal_channels = find_selected_channels(all_channels,posterior_channels);
       
    
    %TODO: GET THE MIDLINE AND LATERAL ELECTRODE FROM THE FP WPLI and FP
    %DPLI
    % FP WPLI
    % Midline and Lateral
    fp_wpli = parameters.fp_wpli;    
    channels = fp_wpli.channels;
    midline_channels = channels;
    lateral_channels = channels;
    selected_channels.fp_wpli.midline_channels = find_selected_channels(all_channels,midline_channels);
    selected_channels.fp_wpli.lateral_channels = find_selected_channels(all_channels,lateral_channels);
    
    % FP DPLI
    % Midline and Lateral
    fp_dpli = parameters.fp_dpli;
    channels = fp_dpli.channels;
    midline_channels = channels;
    lateral_channels = channels;
    selected_channels.fp_dpli.midline_channels = find_selected_channels(all_channels,midline_channels);
    selected_channels.fp_dpli.lateral_channels = find_selected_channels(all_channels,lateral_channels);
    
    % PE
    % Frontal and Posterior
    pe = parameters.pe;
    channels = pe.channels;
    anterior_channels = get_anterior(channels, channels_location);
    posterior_channels = get_posterior(channels, channels_location);
    
    selected_channels.pe.frontal_channels = find_selected_channels(all_channels,anterior_channels);
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

function [anterior_channels] = get_anterior(selected_channels, all_channels)
%   GET_ANTERIOR getter function to fetch only the part of the vector that are
%   in the anterior part of the brain
%   vector: motif frequency count vector of length number of channels
%   channels_location: chanlocs data structure with channel information
%
%   sifted_vector: is the motif frequency count vector minus the channels
%   location who didn't meet the threshold.
   
    anterior_channels = [];
    for i = 1:length(selected_channels)
        position = -1;
        for j = 1:length(all_channels)
            if(strcmp(selected_channels(i),all_channels(j).labels))
               position = j;
               break;
            end
        end
        
        % Every channels that are anterior to the center line of the
        % headset is defined as anterior
        if(position ~= -1 && all_channels(i).X > -0.001)
            anterior_channels = [anterior_channels, selected_channels(i)];
        end
    end
end

function [posterior_channels] = get_posterior(selected_channels,all_channels)
%   GET_POSTERIOR getter function to fetch only the part of the vector that are
%   in the posterior part of the brain
%   vector: motif frequency count vector of length number of channels
%   channels_location: chanlocs data structure with channel information
%
%   sifted_vector: is the motif frequency count vector minus the channels
%   location who didn't meet the threshold.

    posterior_channels = [];
    for i = 1:length(selected_channels)
        position = -1;
        for j = 1:length(all_channels)
            if(strcmp(selected_channels(i),all_channels(j).labels))
               position = j;
               break;
            end
        end
        
        % Every channels that are in the below the center line of the
        % headset is defined as posterior
        if(position ~= -1 && all_channels(position).X < 0.001)
            posterior_channels = [posterior_channels, selected_channels(i)];
        end
    end
end