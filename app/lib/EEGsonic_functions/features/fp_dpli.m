function [avg_dpli_midline,avg_dpli_lateral] = fp_dpli(eeg_data,eeg_info,parameters,midline_mask,lateral_mask)
%FP_DPLI Calculate frontoparietal dPLI measure (average dPLI for midline
%and lateral electrodes)
%   Input:
%       eeg_data: data to calculate the measures on
%       eeg_info: headset information
%       parameters: variables data as inputed by the user
%       midline_mask: boolean mask for the midline electrodes
%       lateral_mask: boolean mask for the lateral electrode
%   Output:
%       avg_dpli_midline: average dPLI for the midline electrodes
%       avg_dpli_lateral: average dPLI for the lateral electrodes

    %% Use the boolean mask to get relevant data
    midline_eeg = eeg_data(midline_mask == 1,:);
    lateral_eeg = eeg_data(lateral_mask == 1,:);
    
    %% Calculate dPLI
    midline_dpli = dpli(midline_eeg,eeg_info,parameters);
    lateral_dpli = dpli(lateral_eeg,eeg_info,parameters);
    
    %% Calculate the average for the midline and lateral electrodes
    avg_dpli_midline = mean2(midline_dpli);
    avg_dpli_lateral = mean2(lateral_dpli);
end

