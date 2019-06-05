function save_app_data(information,parameters,path)
%SAVE_APP_DATA save the information and parameters into app_data
%   information: static data in the app
%   parameters: variable data in the app as given by the user
%   path: path to where we should save the app_data


    % We save the app data to the parameters folder
    % This means that path should be the root folder directory
    app_data_path = strcat(path,filesep,"parameters",filesep,"app_data.mat");
    app_data = struct();
    app_data.parameters = parameters;
    app_data.information = information;
    save(app_data_path,'app_data');
    
    % But we also save the recording_info to the src folder.
    recording_info_path = strcat(path, filesep, "recording_info.mat");
    recording_info = get_headset(information,parameters);
    save(recording_info_path,'recording_info');
    
    % Log the app data into a text file
    log_parameters_to_file(path,"information.txt",parameters)
end

