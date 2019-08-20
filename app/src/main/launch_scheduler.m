function [data_worker,features_worker] = launch_scheduler(information,parameters,state)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   Input:
%       information: contains data pertaining to saving/loading
%       parameters: contains user entered data for features calculation/osc
%   Output:
%       data_worker: the data worker handle to be able to interact with it
%       features_worker: the features worker handle to be able to interact
%       with it

    p = gcp(); % get the current parallel pool
    
    %% Creating saving folder
    % Folder names creation
    folder_name = information.folder_name + "-" + string(now);
    base_directory = strcat(information.saving_directory,filesep,folder_name);
    data_directory = strcat(base_directory,filesep,"data");
    features_directory = strcat(base_directory,filesep,"features");
    parameters_directory = strcat(base_directory,filesep,"parameters");
    
    % Save the information
    information.data_directory = data_directory;
    information.parameters_directory = parameters_directory;
    information.features_directory = features_directory;
    
    % Directory creation
    mkdir(base_directory);
    mkdir(data_directory); 
    mkdir(features_directory);
    mkdir(parameters_directory);
    
    %% Save parameters and information of the app (app_data)
    app_data_path = strcat(parameters_directory,filesep,"app_data.mat");
    app_data = struct();
    app_data.parameters = parameters;
    app_data.information = information;
    save(app_data_path,'app_data');
    
    % But we also save the recording_info to the src folder.
    recording_info_path = strcat(base_directory, filesep, "recording_info.mat");
    recording_info = get_headset(information,parameters);
    save(recording_info_path,'recording_info');
    
    % Log the app data into a text file
    log_parameters_to_file(base_directory,"information.txt",parameters)
    
    %% Launch and return the two workers
    parameters.warm_up_wait_time = 10;
    index = -1; % Here we start at -1 to significate we haven't statrted collecting yet
    save(information.replay_path,'index');
    data_worker = parfeval(p,@acquire_eeg,0,information,parameters);
    features_worker = parfeval(p,@calculate_features,0,information,parameters);
end


