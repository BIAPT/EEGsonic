function [time] = time_phase_amplitude_coupling(information,parameters)
%TIME_PHASE_AMPLITUDE_COUPLING Summary of this function goes here
%   Detailed explanation goes here

    %% Get variables from information and parameters
    headset = get_headset(information,parameters);
    number_channels = headset.number_channels;
    data_size = parameters.pac.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
        %% Time the critical part of the pipeline for td
    tic;
        frontal_mask = boolean_mask.pac.frontal_channels;
        parietal_mask = boolean_mask.pac.parietal_channels;                    
        % Calculate pac
        [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(eeg_data,headset,parameters.pac,frontal_mask,parietal_mask);
        % Convert and Send to OSC
        send_phase_amplitude_coupling(rpt_frontal,rpt_parietal,osc);
        eeg_data = [];
    time = toc; 
end

