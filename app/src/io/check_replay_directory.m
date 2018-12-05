function [is_replay_directory] = check_replay_directory(path)
%CHECK_REPLAY_DIRECTORY Summary of this function goes here
%   Detailed explanation goes here

    % In this function we should go through the 
    test_file = strcat(path,filesep,'parameters',filesep,'app_data.mat');
    try
        data_struct = load(test_file);
        is_replay_directory = 1;
    catch
        is_replay_directory = 0;
    end
            
        
end

