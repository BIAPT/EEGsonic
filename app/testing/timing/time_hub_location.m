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
    
    if(parameters.general.egi129.is_selected)
        eeg_info = information.headset.egi129;
    elseif(parameters.general.dsi24.is_selected)
        eeg_info = information.headset.dsi24;
    end
        
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);

    %% Time the critical part of the pipeline for hl
    tic;
        % Calculate hl
        [hd_channel_index,hd_graph] = hub_location(eeg_data,eeg_info,parameters.hl);
        
        % Convert and Send to OSC
        send_hub_location(parameters.hl.is_graph,hd_channel_index,hd_graph,osc);
        
        % Clear the data
        eeg_data = [];
    time = toc;
end

