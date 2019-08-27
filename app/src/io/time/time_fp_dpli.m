function [time] = time_fp_dpli(information, parameters)
%TIME_FP_WPLI Summary of this function goes here
%   Detailed explanation goes here
    %% Variable initialization
    sampling_frequency = 1000;
    number_points = sampling_frequency * parameters.fp_dpli.required_size;
    eeg_info = information.headset.egi129;
    number_channels = eeg_info.number_channels;
    non_scalp_channels = parameters.general.egi129.non_scalp_channels;

    %% Generating the data
    fp_dpli_data = rand(number_channels, number_points); 
    
    %% Filter the data
    [fp_dpli_data,eeg_info] = filter_channels(fp_dpli_data, eeg_info, non_scalp_channels); % filter the data
    
    %% Create all the masks
    boolean_mask = get_selected_channels(information,parameters);
    
    %% Calculate the time it takes for fp_dpli to run
    tic;
    fp_dpli(fp_dpli_data,eeg_info,parameters.fp_dpli,boolean_mask.fp_dpli);                   
    time = toc;             
end

