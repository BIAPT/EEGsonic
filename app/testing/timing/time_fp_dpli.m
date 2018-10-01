function [time] = time_fp_dpli(information,parameters)
%TIME_FP_DPLI Summary of this function goes here
%   Detailed explanation goes here

    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.fp_dpli.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    channels_location = headset.channels_location;
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    tic;
        midline_mask = boolean_mask.fp_dpli.midline_channels;
        lateral_mask = boolean_mask.fp_dpli.lateral_channels;                     
        % Calculate fp_dpli
        [avg_dpli_midline,avg_dpli_lateral] = fp_dpli(eeg_data,headset,parameters.fp_dpli,midline_mask,lateral_mask);                   
        % Convert and Send to OSC
        send_fp_dpli(avg_dpli_midline,avg_dpli_lateral,osc);
        eeg_data = [];
    time = toc;
end

