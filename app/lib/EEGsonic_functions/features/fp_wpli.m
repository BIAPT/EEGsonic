function [avg_pli_midline,avg_pli_lateral] = fp_wpli(eeg_data,eeg_info,parameters,midline_mask,lateral_mask)
%FP_WPLI Summary of this function goes here
%   Detailed explanation goes here

%% Step 1: Calculate wPLI
%{
    calculate the wPLI for all combinations of frontal to parietal electrodes for the midline,
    and all frontal to parietal electrodes for lateral.  
%}

%% Step 2: Calculate surrogates
%{
    We will need to test the next part to see if it is feasible in real-time, but ideally: shuffle the data ~10 times to develop an approximate surrogate wPLI.
    Find the average surrogate wPLI, subtract it from the calculated wPLI.
%}

%% Step 3: Average
%{
    Average surrogate-corrected frontoparietal PLI values for all midline electrodes, and lateral electrodes.
    Output these two values to OSC every 10 seconds.
%}
    
end

