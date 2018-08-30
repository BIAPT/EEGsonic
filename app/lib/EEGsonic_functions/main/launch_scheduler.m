function [data_worker,features_worker] = launch_scheduler(information,parameters)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   information: contains data pertaining to saving/loading
%   parameters: contains user entered data for features calculation/osc
    p = gcp(); % get the current parallel pool
    
    %% Creating saving folder
    folder_name = information.folder_name + "-" + string(now);
    data_directory = information.saving_directory +"\"+folder_name; 
    mkdir(data_directory); %dir will always be unique
    
    %% Launch and return the two workers
    sleep_delay = 1; % in seconds
    data_worker = parfeval(p,@acquire_eeg,0,data_directory,information,parameters);
    features_worker = parfeval(p,@calculate_features,0,data_directory,sleep_delay,information,parameters);
end
