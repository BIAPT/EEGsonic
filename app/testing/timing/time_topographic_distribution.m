function [time] = time_topographic_distribution(information,parameters)
%TIME_ Summary of this function goes here
%   Detailed explanation goes here

    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.td.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for td
    tic;
        frontal_mask = boolean_mask.td.frontal_channels;
        posterior_mask = boolean_mask.td.posterior_channels;
        % Calculate td
        [ratio_front_back] = topographic_distribution(eeg_data,headset,parameters.td,frontal_mask,posterior_mask);
        % Convert and Send to OSC
        send_topographic_distribution(ratio_front_back,osc);
        eeg_data = [];
    time = toc; 

end

