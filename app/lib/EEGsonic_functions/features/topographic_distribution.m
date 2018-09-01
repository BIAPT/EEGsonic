function [ratio_front_back] = topographic_distribution(eeg_data,eeg_info,td)
%TOPOGRAPHIC_DISTRIBUTION Summary of this function goes here
%   Detailed explanation goes here

    % TODO add td.front_channels and td.back_channels will be easier to
    % work with
    
    %% Formating
    eeg_data = eeg_data';
    
    %% Spectral topographic map
    [eegspecdB,freqs,~,~,~] = spectopo(eeg_data,length(eeg_data),...,
                              eeg_info.sampling_rate,'chanlocs',...,
                              eeg_info.channels_info,'freqfac',2,...,
                              'freq',td.frequency,'plot','off');
    
    %% Normalization
    %Note: Should we normalize the eegspecdB?
    
    %% Frontal Averaging
    
    %% Posterior Averaging
    
    %% Ratio Front and Posterior
end

