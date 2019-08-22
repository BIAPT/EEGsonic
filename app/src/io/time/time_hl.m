function [time] = time_hl(information, parameters)
%TIME_HL Summary of this function goes here
%   Detailed explanation goes here

    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.hl.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;
    
    %% Generating the data
    hl_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [hl_data,eeg_info] = filter_channels(hl_data, eeg_info, non_scalp_channels); % filter the data

    %% Calculate the time hl takes to run
    tic;
    hub_location(hl_data,eeg_info,parameters.hl);
    time = toc;
end

