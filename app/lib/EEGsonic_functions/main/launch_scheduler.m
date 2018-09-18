function [data_worker,features_worker] = launch_scheduler(information,parameters)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   information: contains data pertaining to saving/loading
%   parameters: contains user entered data for features calculation/osc
    p = gcp(); % get the current parallel pool
    
    %% Creating saving folder
    folder_name = information.folder_name + "-" + string(now);
    base_directory = information.saving_directory +"\"+folder_name;
    data_directory = base_directory+"\data";
    features_directory = base_directory+"\features";
    
    % Directory creation
    mkdir(base_directory);
    mkdir(data_directory); 
    mkdir(features_directory); 
    
    %% Launch and return the two workers
    sleep_delay = 0.1; % in seconds
    data_worker = parfeval(p,@acquire_eeg,0,data_directory,information,parameters);
    features_worker = parfeval(p,@calculate_features,0,data_directory,features_directory,sleep_delay,information,parameters);
end

