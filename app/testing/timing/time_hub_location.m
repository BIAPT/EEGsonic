function [time] = time_hub_location(information,parameters)
%TIME_HUB_LOCATION Summary of this function goes here
%   Detailed explanation goes here

    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.pe.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    channels_location = headset.channels_location;
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);

    tic;
        % Calculate hl
        [hd_channel_index] = hub_location(eeg_data,headset,parameters.hl);
        % Convert and Send to OSC
        send_hub_location(hd_channel_index,channels_location,parameters.hl,osc);                    
        eeg_data = [];
    time = toc;
end

