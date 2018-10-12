function [time] = time_phase_amplitude_coupling(information,parameters)
%TIME_PHASE_AMPLITUDE_COUPLING test how long pac will take to run in seconds
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
    data_size = parameters.pac.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for pac
    tic;
        % Get the right channels masks
        frontal_mask = boolean_mask.pac.frontal_channels;
        parietal_mask = boolean_mask.pac.parietal_channels;  
        
        % Calculate pac
        [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(eeg_data,headset,parameters.pac,frontal_mask,parietal_mask);
        
        % Convert and send to OSC
        send_phase_amplitude_coupling(rpt_frontal,rpt_parietal,osc);
        
        % Clear the data
        eeg_data = [];
    time = toc; 
end

