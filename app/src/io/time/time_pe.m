function [time] = time_pe(information, parameters)
%TIME_PE Summary of this function goes here
%   Detailed explanation goes here

%% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.pe.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    pe_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [pe_data,eeg_info] = filter_channels(pe_data, eeg_info, non_scalp_channels); % filter the data
    
    %% Create the frontal and posterior mask
    boolean_mask = get_selected_channels(information,parameters);
    % Get the right mask
    frontal_mask = boolean_mask.pe.frontal_channels;
    posterior_mask = boolean_mask.pe.posterior_channels;   
    
    %% Calculate the time it takes to run pe
    % Calculate pe
    tic;
    permutation_entropy(pe_data,eeg_info,parameters.pe,frontal_mask,posterior_mask);
    time = toc;             
end

