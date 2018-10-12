function [time] = time_permutation_entropy(information,parameters)
%TIME_PERMUTATION_ENTROPY test how long pe will take to run in seconds
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
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for pe
    tic;
        % Get the right channels mask
        frontal_mask = boolean_mask.pe.frontal_channels;
        posterior_mask = boolean_mask.pe.posterior_channels;  
        
        % Calculate pe
        [avg_pe_frontal,avg_pe_posterior] = permutation_entropy(eeg_data,headset,parameters.pe,frontal_mask,posterior_mask);
        
        % Convert and send to OSC
        send_permutation_entropy(avg_pe_frontal,avg_pe_posterior,osc);
        
        % Clear the data
        eeg_data = [];    
    time = toc;
end

