function [time] = time_pac(information, parameters)
%TIME_PAC Summary of this function goes here
%   Detailed explanation goes here

    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.pac.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    pac_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [pac_data,eeg_info] = filter_channels(pac_data, eeg_info, non_scalp_channels); % filter the data
    
    %% Create the frontal and posterior mask
    boolean_mask = get_selected_channels(information,parameters);
    % Get the right mask
    frontal_mask = boolean_mask.pac.frontal_channels;
    parietal_mask = boolean_mask.pac.parietal_channels;                    
    
    %% Calculate the time to run pac
    tic;
    phase_amplitude_coupling(pac_data,eeg_info,parameters.pac,frontal_mask,parietal_mask);
    time = toc;
end

