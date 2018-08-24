function acquire_eeg(information,parameters)
%ACQUIRE_EEG Summary of this function goes here
%   Detailed explanation goes here
    index = 0;
    folder_name = information.folder_name + "-" + string(now);
    data_directory = information.saving_directory +"\"+folder_name; 
    mkdir(data_directory);
    while(1)
        % here depending on the eeg system we will acquire eeg in diff ways
        data = rand(128,10000);% TODO change this to the data acquisition
        %of whatever system we selected to use
        parsave(data_directory,index,data);
        index = index + 1;
    end
end

