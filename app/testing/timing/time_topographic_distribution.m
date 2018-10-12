function [time] = time_topographic_distribution(information,parameters)
%TIME_TOPOGRAPHIC_DISTRIBUTION test how long td will take to run in seconds
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
    data_size = parameters.td.required_size*1000;
    boolean_mask = get_selected_channels(information,parameters);
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for td
    tic;
        % Get the relevant channels masks
        frontal_mask = boolean_mask.td.frontal_channels;
        posterior_mask = boolean_mask.td.posterior_channels;
        
        % Calculate td
        [ratio_front_back] = topographic_distribution(eeg_data,headset,parameters.td,frontal_mask,posterior_mask);
        
        % Convert and send to OSC
        send_topographic_distribution(ratio_front_back,osc);
        
        % clear the data
        eeg_data = [];
    time = toc; 

end

