function [time] = time_spectral_power_ratio(information,parameters)
%TIME_SPECTRAL_POWER_RATIO test how long spr will take to run in seconds
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
    data_size = parameters.spr.required_size*1000;
    osc = parameters.osc;
    
    %% Generate the EEG data
    eeg_data = rand(number_channels,data_size);
    
    %% Time the critical part of the pipeline for spr
    tic;
        % Calculate spr
        [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,headset,parameters.spr);
        
        % Convert and send to OSC
        send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc);
        
        % Clear the data
        eeg_data = [];
    time = toc;
end

