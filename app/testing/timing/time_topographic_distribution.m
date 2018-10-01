function [time] = time_topographic_distribution(information,parameters)
%TIME_ Summary of this function goes here
%   Detailed explanation goes here

    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = get_data_acquisition_size(parameters);

    eeg_data = rand(number_channels,data_size);
    osc = parameters.osc;
    % Populate structure of selected_channels (Boolean mask)
    boolean_mask = get_selected_channels(information,parameters);
    
    
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

