function [time] = time_spr(information,parameters)
%TIME_SPR Summary of this function goes here
%   Detailed explanation goes here

    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.spr.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    spr_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [spr_data,eeg_info] = filter_channels(spr_data, eeg_info, non_scalp_channels); % filter the data
            
    %% Calculating the time to run spr
    tic;
    spectral_power_ratio(spr_data, eeg_info, parameters.spr);
    time = toc;
end

