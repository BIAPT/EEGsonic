function [corrected_dpli] = dpli(eeg_data,eeg_info,parameters)
%DPLI Summary of this function goes here
%   Detailed explanation goes here

%% Seting up variables
%% NOTE: Do we need the p_value? Seems like no from the information in the documentation
    number_surrogates = parameters.number_surrogates;
    p_value = parameters.p_value;
    number_channels = size(eeg_data,1);
   
    surrogates_dpli = zeros(number_surrogates,number_channels,number_channels);
    eeg_data = eeg_data';
    %% Calculate wPLI
    uncorrected_dpli = w_PhaseLagIndex(eeg_data); % uncorrected
    for index = 1:number_surrogates
        surrogates_dpli(index,:,:) = w_PhaseLagIndex_surrogate(eeg_data);
    end
    corrected_dpli = uncorrected_dpli - squeeze(mean(surrogates_dpli,1));

end

