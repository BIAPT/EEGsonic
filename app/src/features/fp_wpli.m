function [avg_pli_midline,avg_pli_lateral] = fp_wpli(eeg_data,eeg_info,parameters,midline_mask,lateral_mask)
%FP_WPLI Calculate frontoparietal dPLI measure (average dPLI for midline
%and lateral electrodes)
%   Input:
%       eeg_data: data to calculate the measures on
%       eeg_info: headset information
%       parameters: variables data as inputed by the user
%       midline_mask: boolean mask for the midline electrodes
%       lateral_mask: boolean mask for the lateral electrode
%   Output:
%       avg_wpli_midline: average wPLI for the midline electrodes
%       avg_wpli_lateral: average wPLI for the lateral electrodes

    %% Use the boolean mask to get relevant data
    midline_eeg = eeg_data(midline_mask == 1,:);
    lateral_eeg = eeg_data(lateral_mask == 1,:);
    
    %% Calculate the wPLI
    midline_wpli = wpli(midline_eeg,eeg_info,parameters);
    lateral_wpli = wpli(lateral_eeg,eeg_info,parameters);

    %% Calculate the average for the midline and lateral electrodes
    avg_pli_midline = mean2(midline_wpli);
    avg_pli_lateral = mean2(lateral_wpli);
    
end

