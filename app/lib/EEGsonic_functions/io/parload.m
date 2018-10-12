function [is_ready,data] = parload(path,index)
%PARLOAD Summary of this function goes here
%   Detailed explanation goes here
    file_path = strcat(path,filesep,index,".mat");    
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

