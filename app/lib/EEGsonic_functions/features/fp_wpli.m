function [avg_pli_midline,avg_pli_lateral] = fp_wpli(eeg_data,eeg_info,parameters,midline_mask,lateral_mask)
%FP_WPLI Summary of this function goes here
%   Detailed explanation goes here

%% Step 1: Calculate wPLI
%{
    calculate the wPLI for all combinations of frontal to parietal electrodes for the midline,
    and all frontal to parietal electrodes for lateral.  
%}

    midline_eeg = eeg_data(midline_mask == 1,:);
    lateral_eeg = eeg_data(lateral_mask == 1,:);
    
    midline_wpli = wpli(midline_eeg,eeg_info,parameters);
    lateral_wpli = wpli(lateral_eeg,eeg_info,parameters);
% Meaning calculate wPLI for midline and wPLI for lateral channels

%% Step 3: Average
%{
    Average surrogate-corrected frontoparietal PLI values for all midline electrodes, and lateral electrodes.
    Output these two values to OSC every 10 seconds.
%}
   avg_pli_midline = mean2(midline_wpli);
   avg_pli_lateral = mean2(lateral_wpli);
    
end

