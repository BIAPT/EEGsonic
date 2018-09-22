function [avg_dpli_midline,avg_dpli_lateral] = fp_dpli(eeg_data,eeg_info,parameters,midline_mask,lateral_mask)
%FP_DPLI Summary of this function goes here
%   Detailed explanation goes here

    midline_eeg = eeg_data(midline_mask == 1,:);
    lateral_eeg = eeg_data(lateral_mask == 1,:);
    
    midline_dpli = dpli(midline_eeg,eeg_info,parameters);
    lateral_dpli = dpli(lateral_eeg,eeg_info,parameters);
    
    avg_dpli_midline = mean2(midline_wpli);
    avg_dpli_lateral = mean2(lateral_wpli);
end

