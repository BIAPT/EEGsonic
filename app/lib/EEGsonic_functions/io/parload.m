function [is_ready,data] = parload(path,name)
%PARLOAD Wrapper function to load data from a folder
%   Input:
%       path: folder where to find the data we are trying to load
%       name: name of the file we are trying to load
%   Output:
%       is_ready: boolean to check if the data is ready to be loaded
%       data: matrix containing the data we tried to load

    %% Setting up variables
    name = fix_name(name);
    file_path = strcat(path,filesep,name,".mat");    
    
    %% Try to load the data
    try
        data_struct = load(file_path);
        data = data_struct.data;
        is_ready = 1;
    catch
        is_ready = 0;
        data = [];
    end
end

