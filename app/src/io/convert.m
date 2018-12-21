function convert(output_path,input_path,input_file,type)
%CONVERT Summary of this function goes here
%   Detailed explanation goes here
    %% Static variables
    app_sampling_rate = 5; % in seconds

    data_path = strcat(output_path,filesep,'data');
    [eeg,sampling_frequency] = load_eeg(input_file,input_path,type);
    
    recording_length = floor(length(eeg)/sampling_frequency); %in seconds
    max_index = recording_length/5; % Sampling frequency
    for i = 0:(max_index-1)
       start = i*sampling_frequency*app_sampling_rate + 1;
       stop = (i+1)*sampling_frequency*app_sampling_rate;
       data = eeg(:,start:stop);
       parsave(data_path,i,data);
    end
end

