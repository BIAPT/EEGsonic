function [time] = time_fp_wpli(information,parameters)
%TIME_FP_WPLI test how long fp_wpli will take to run in seconds
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
    data_size = parameters.fp_wpli.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    channels_location = headset.channels_location;
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);

    %% Time the critical part of the pipeline for fp_wpli
    tic;
        % Get the right channels mask
        midline_mask = boolean_mask.fp_wpli.midline_channels;
        lateral_mask = boolean_mask.fp_wpli.lateral_channels; 
        
        % Calculate fp_wpli
        [avg_pli_midline,avg_pli_lateral] = fp_wpli(eeg_data,headset,parameters.fp_wpli,midline_mask,lateral_mask);                   
        
        % Convert and send to OSC
        send_fp_wpli(avg_pli_midline,avg_pli_lateral,osc);
        
        % Clear the data
        eeg_data = [];    
    time = toc;
end

