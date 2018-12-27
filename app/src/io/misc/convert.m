function convert(output_path,input_path,input_file,type)
%CONVERT will load the EEG data and segment it into chunks
%   output_path: String of where to save the sliced data (root lvl folder)
%   input_path: String of where the data is currently located
%   input_file: String of the name of the file we are converting
%   type: the type of data we are trying to convert

    %% Static variables TODO: make this more dynamic
    app_sampling_rate = 5; % in seconds
    sampling_frequency = 1000; % (hard coded 1000 Hz)
    
    %% Variables
    data_path = strcat(output_path,filesep,'data');
    
    %% Loading EEG
    [eeg,~] = load_eeg(input_file,input_path,type);
    recording_length = floor(length(eeg)/sampling_frequency); %in seconds
    max_index = recording_length/5; % Sampling frequency
    
    %% Slicing EEG into data chunks
    for i = 0:(max_index-1)
       start = i*sampling_frequency*app_sampling_rate + 1;
       stop = (i+1)*sampling_frequency*app_sampling_rate;
       data = eeg(:,start:stop);
       % Saving the data at the right place
       parsave(data_path,i,data);
    end
end

