function [avg_pli_midline,avg_pli_lateral] = fp_wpli(eeg_data,eeg_info,params)
%FP_WPLI Summary of this function goes here
%   Detailed explanation goes here

    %% Note: Filtering? Do we filter from 0.1 50Hz?
    
    %% Calculate wPLI
    wpli = w_PhaseLagIndex(eeg_data);
    surrogates_wpli = [];
    corrected_wpli = [];
    
    %% Calculate surrogates
    for i = 1:params.number_surrogates
        surrogates_wpli = [surrogates_wpli, w_PhaseLagIndex_surrogate(eeg_data)];
    end
    
    %% Threshold with p value     
    for m = 1:length(wpli)
        for n = 1:length(PLI)
            test = surrogates_wpli(:,m,n);
            p = signrank(test, wpli(m,n));       
            if p < params.p_value && wpli(m,n) - median(test) > 0
                corrected_wpli(i,m,n) = PLI(m,n) - median(test);
            else
                corrected_wpli(i,m,n) = 0;
            end          
        end
    end
end

