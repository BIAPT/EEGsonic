function [ratio_front_back] = topographic_distribution(eeg_data,eeg_info,parameters,frontal_mask,posterior_mask)
%TOPOGRAPHIC_DISTRIBUTION Summary of this function goes here
%   Detailed explanation goes here

    % Relevant channels = frontal_channels and posterior_channels
    %% Spectral topographic map
    [eegspecdB,freqs,~,~,~] = spectopo(eeg_data,length(eeg_data),...,
                              eeg_info.sampling_rate,'chanlocs',...,
                              eeg_info.channels_location,'freqfac',1,...,
                              'freq',parameters.frequency,'plot','off');
    
    %% Normalization
    %Note: Should we normalize the eegspecdB?
    
    %% Frontal Averaging
    frontal_avg = mean(eegspecdB(frontal_mask==1),2); % TODO
    %% Posterior Averaging
    posterior_avg = mean(eegspecdB(posterior_mask==1),2); % TODO
    %% Ratio Front and Posterior
    ratio_front_back = frontal_avg/posterior_avg;
end

