function [hd_channel_index] = hub_location(eeg_data,eeg_info,parameters)
%HUB_LOCATION Summary of this function goes here
%   Detailed explanation goes here

%% Step 1: Get or calculate wPLI + surrogates
%{
-	Calculate the wPLI values of all combinations of electrodes,
    corrected with 10 iterations of surrogate wPLI. 
%}
    full_wpli = wpli(eeg_data,eeg_info,parameters);

%% Step 2: Thresholding
%{
-	Choose the top 10% of wPLI values (this value will also need to be adjustable).
%}

    sorted_wpli = sort(full_wpli(:));
    treshold_index = floor((1-parameters.top_connection_threshold)*length(sorted_wpli));
    treshold_value = sorted_wpli(threshold_index);
    
    % Here we binarized the wpli
    full_wpli(full_wpli >= threshold_value) = 1;
    full_wpli(full_wpli < threshold_value) = 0;
    
    
%% Step 3: Calculate the Degree of each node
%{
-	Calculate the degree of each electrode.
%}
    channels_degree = degrees_und(full_wpli);

%% Step 4: Find the location of the electrode
%{
-	Find the electrode with the highest degree. 
%}
    [~,hd_channel_index] = max(channels_degree);

end

