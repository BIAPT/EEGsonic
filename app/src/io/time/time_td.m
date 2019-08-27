function [time] = time_td(information, parameters)
%TIME_TD Summary of this function goes here
%   Detailed explanation goes here
    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.td.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    td_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [td_data,eeg_info] = filter_channels(td_data, eeg_info, non_scalp_channels); % filter the data
    
    %% Create the frontal and posterior mask
    boolean_mask = get_selected_channels(information,parameters);
    % Get the right mask 
    frontal_mask = boolean_mask.td.frontal_channels;
    posterior_mask = boolean_mask.td.posterior_channels;
    
    %% Calculate the time to run td
    tic;
    topographic_distribution(td_data,eeg_info,parameters.td,frontal_mask,posterior_mask);
    time = toc;
    

end

