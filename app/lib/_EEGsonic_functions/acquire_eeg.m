function acquire_eeg(information,parameters)
%ACQUIRE_EEG Summary of this function goes here
%   Detailed explanation goes here
    index = 0;
    while(1)
        % here depending on the eeg system we will acquire eeg in diff ways
        data = rand(128,10000);
        parsave(information.saving_directory,index,data);
        index = index + 1;
    end
end

