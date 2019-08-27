function [filtered_labels, filtered_eeg_info] = filter_channels_labels(all_labels, eeg_info, non_scalp_channels)
%FILTER_CHANNELS Summary of this function goes here
%   Detailed explanation goes here

    % Here we will be using the non_scalp_channels from eeg_info
    number_channels = eeg_info.number_channels;
    
    % Create a mask of the index we want to keep in the data
    mask = [];
    for i = 1:number_channels
       is_scalp = 1;
       for j = 1:length(non_scalp_channels)
           if(strcmp(non_scalp_channels{j}, eeg_info.channels_location(i).labels))
               is_scalp = 0;
               non_scalp_channels(j) = [];
               break;
           end
       end
       mask = [mask;is_scalp];
    end
    
    
    % Filter the data using the mask
    % Note: It's useless to filter the eeg_info over and over again. Fix
    % this is it becomes a bootleneck (optimization possible)
    mask = mask == 1;
    filtered_labels = all_labels(mask);
    eeg_info.channels_location = eeg_info.channels_location(mask);
    eeg_info.number_channels = nnz(mask); % Number of non zero element
    filtered_eeg_info = eeg_info;
end
