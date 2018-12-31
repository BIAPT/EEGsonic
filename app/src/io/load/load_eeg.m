function [eeg,sampling_frequency] = load_eeg(file_name,path,type)
%LOAD_EEG will load the EEG data
%   file_name: name of the file to load
%   path: path to that file
%   type: type of the file to load (.set, edf)

    % Currently supported format: .set files
    if(strcmp(type,'set'))
        data = pop_loadset(file_name,path);
        eeg = data.data;
        sampling_frequency = data.srate;
    end
end
