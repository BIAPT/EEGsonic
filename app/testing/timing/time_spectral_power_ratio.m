function [time] = time_spectral_power_ratio(information,parameters)
%TIME_SPECTRAL_POWER_RATIO Summary of this function goes here
%   Detailed explanation goes here
    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = get_data_acquisition_size(parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for spr
    tic;
        % Calculate spr
        [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,headset,parameters.spr);
        % Convert and Send to OSC
        send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc);
        eeg_data = [];
    time = toc;
end

