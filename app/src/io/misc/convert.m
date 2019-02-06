function [sampling_rate,number_channels,channels_location,channels_info] = convert(output_path,input_path,input_file,type)
%CONVERT will load the EEG data and segment it into chunks
%   output_path: String of where to save the sliced data (root lvl folder)
%   input_path: String of where the data is currently located
%   input_file: String of the name of the file we are converting
%   type: the type of data we are trying to convert

    %% Static variables
    app_sampling_rate = 5; % in seconds
    
    %% Variables
    data_path = strcat(output_path,filesep,'data');
    
    %% Loading EEG
    [eeg,sampling_rate,number_channels,channels_location,channels_info] = load_eeg(input_file,input_path,type);
    recording_length = floor(length(eeg)/sampling_rate); %in seconds
    max_index = recording_length/5; % Sampling frequency
    
    %% Slicing EEG into data chunks
    for i = 0:(max_index-1)
       start = i*sampling_rate*app_sampling_rate + 1;
       stop = (i+1)*sampling_rate*app_sampling_rate;
       data = eeg(:,start:stop);
       % Saving the data at the right place
       parsave(data_path,i,data);
    end
end

