function [hd_channel_index] = hub_location(eeg_data,eeg_info,parameters)
%HUB_LOCATION choose from the the channels the channel with the highest
%degree
%   Input:
%       eeg_data: data to calculate the measures on
%       eeg_info: headset information
%       parameters: variables data as inputed by the user
%   Output:
%       hd_channel_index: index of the channel with the highest degree

    % Calculate the wPLI for the full eeg
    full_wpli = wpli(eeg_data,eeg_info,parameters);

    % Threshold the wPLI depending on the top connection threshold
    sorted_wpli = sort(full_wpli(:));
    treshold_index = floor((1-parameters.top_connection_threshold)*length(sorted_wpli));
    treshold_value = sorted_wpli(treshold_index);
    
    % Here we binarized the wpli
    full_wpli(full_wpli >= treshold_value) = 1;
    full_wpli(full_wpli < treshold_value) = 0;
     
    %% Caculate the binary degree of the network
    channels_degree = degrees_und(full_wpli);

    %% Find the channel with the highest degree
    [~,hd_channel_index] = max(channels_degree);

end

