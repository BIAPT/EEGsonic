function [time] = time_spr(eeg_info,parameters)
%TIME_SPR Summary of this function goes here
%   Detailed explanation goes here

    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.spr.window_size;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    spr_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [spr_data,eeg_info] = filter_channels(spr_data, eeg_info, non_scalp_channels); % filter the data
            
    %% Calculating the time to 
    tic;
    spectral_power_ratio(spr_data, eeg_info, parameters.spr);
    time = toc;
end

