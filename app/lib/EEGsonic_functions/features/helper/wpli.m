function [z_score_wpli] = wpli(eeg_data,eeg_info,parameters)
%WPLI Summary of this function goes here
%   Detailed explanation goes here

    

    %% Note: do we calculate segments of data like before and then average?
    %% TODO: Make this a standalone function by adding the w_PhaseLagIndex + surrogate 
    %        into this
    
    %% Calculate wPLI
    uncorrected_wpli = w_PhaseLagIndex(eeg_data);
    surrogates_wpli = [];
    corrected_wpli = [];
    
    length_wpli = length(uncorrected_wpli);
    
    %% Calculate surrogates
    for i = 1:parameters.number_surrogates
        surrogates_wpli = [surrogates_wpli, w_PhaseLagIndex_surrogate(eeg_data)];
    end
    
    %% Threshold with p value     
    for m = 1:length_wpli
        for n = 1:length_wpli
            test = surrogates_wpli(:,m,n);
            p = signrank(test, uncorrected_wpli(m,n));       
            if p < parameters.p_value && uncorrected_wpli(m,n) - median(test) > 0
                corrected_wpli(i,m,n) = uncorrected_wpli(m,n) - median(test);
            else
                corrected_wpli(i,m,n) = 0;
            end          
        end
    end
    
    %% Take the Z score across all segments        
    z_score_wpli = mean(corrected_wpli,3); %average across the right dimension (FIND WHAT IT IS)

end

