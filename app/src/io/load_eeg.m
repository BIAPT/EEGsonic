function [eeg,sampling_frequency] = load_eeg(file_name,path,type)
%LOAD_EEG Summary of this function goes here
%   Detailed explanation goes here

    % Currently supported format: .set files
    if(strcmp(type,'set'))
        data = pop_loadset(file_name,path);
        eeg = data.data;
        sampling_frequency = data.srate;
    end
end

