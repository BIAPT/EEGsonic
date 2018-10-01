function [time] = time_permutation_entropy(information,parameters)
%TIME_PERMUTATION_ENTROPY Summary of this function goes here
%   Detailed explanation goes here

%   % Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.td.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    tic;
        frontal_mask = boolean_mask.pe.frontal_channels;
        posterior_mask = boolean_mask.pe.posterior_channels;  
        % Calculate pe
        [avg_pe_frontal,avg_pe_posterior] = permutation_entropy(eeg_data,eeg_info,parameters.pe,frontal_mask,posterior_mask);
        % Convert and Send to OSC
        send_permutation_entropy(avg_pe_frontal,avg_pe_posterior,osc);
        eeg_data = [];    
    time = toc;
end

