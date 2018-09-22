function [corrected_wpli] = wpli(eeg_data,eeg_info,parameters)
%WPLI Summary of this function goes here
%   Detailed explanation goes here

%% Seting up variables
%% NOTE: Do we need the p_value? Seems like no from the information in the documentation
    number_surrogates = parameters.number_surrogates;
    p_value = parameters.value;
    number_channels = size(eeg_data,1);
    
    uncorrected_wpli = zeros(number_channels,number_channels);
    surrogates_wpli = zeros(number_surrogates,number_channels,number_channels);
    corrected_wpli = zeros(number_channels,number_channels);
    
    %% Calculate wPLI
    uncorrected_wpli = w_PhaseLagIndex(eeg_data); % uncorrected
    for i = 1:number_surrogates
        surrogates_wpli(index,:,:) = w_PhaseLagIndex_surrogate(eeg_data);
    end
    corrected_wpli = uncorrected_wpli - squeeze(mean(surrogates_wpli,1));
    
end

