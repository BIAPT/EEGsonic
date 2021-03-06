function [is_replay_directory] = check_replay_directory(path)
%CHECK_REPLAY_DIRECTORY check if the replay directory is well formed
%   path: string that leads to the root of the replay directory

    %% Load app_data.mat
    test_app_data = strcat(path,filesep,'parameters',filesep,'app_data.mat');
    try
        % if successful then it means its well formed
        data_struct = load(test_app_data);
        is_replay_directory = 1;
    catch
        % if it failed it means app_data.mat isn't there
        is_replay_directory = 0;
    end
        
    %% Folder creation testing
    test_parameters_dir = strcat(path,filesep,'parameters');
    test_data_dir = strcat(path,filesep,'data');
    test_features_dir = strcat(path,filesep,'features');
    
    if(~exist(test_parameters_dir, 'dir'))
        is_replay_directory = 0;
    end
    
    if(~exist(test_data_dir, 'dir'))
        is_replay_directory = 0;
    end
    
    if(~exist(test_features_dir, 'dir'))
        is_replay_directory = 0;
    end
end

