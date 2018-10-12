function [time] = time_hub_location(information,parameters)
%TIME_HUB_LOCATION test how long hl will take to run in seconds
    %Input:
    %   information: static data of the app
    %   parameters: inputed data by the user
    %
    %Output:
    %   time: time it took to run the analysis and to generate the outputs
    %         in seconds

    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.pe.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    channels_location = headset.channels_location;
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);

    %% Time the critical part of the pipeline for hl
    tic;
        % Calculate hl
        [hd_channel_index] = hub_location(eeg_data,headset,parameters.hl);
        
        % Convert and send to OSC
        send_hub_location(hd_channel_index,channels_location,parameters.hl,osc); 
        
        % Clear the data
        eeg_data = [];
    time = toc;
end

