function [avg_location_hd_node] = hub_location(eeg_data,eeg_info,parameters)
%HUB_LOCATION Summary of this function goes here
%   Detailed explanation goes here

%% Step 1: Get or calculate wPLI + surrogates
%{
-	Calculate the wPLI values of all combinations of electrodes,
    corrected with 10 iterations of surrogate wPLI. 
%}

%% Step 2: Thresholding
%{
-	Choose the top 10% of wPLI values (this value will also need to be adjustable).
%}

%% Step 3: Calculate the Degree of each node
%{
-	Calculate the degree of each electrode.
%}

%% Step 4: Find the location of the electrode
%{
-	Find the electrode with the highest degree. 
%}

end

