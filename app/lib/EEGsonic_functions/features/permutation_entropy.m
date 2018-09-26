function [avg_pe_frontal,avg_pe_posterior] = permutation_entropy(eeg_data,eeg_info,parameters,frontal_mask,posterior_mask)
%PERMUTATION_ENTROPY Summary of this function goes here
%   Detailed explanation goes here

%% TODO SEE CODE IN PERMUTATION ENTROPY AND USE IT HERE !

    frontal_eeg = eeg_data(frontal_mask == 1,:)';
    posterior_eeg = eeg_data(posterior_mask == 1,:)';

    embedding_dimension = parameters.embedding_dimension;
    time_delay = parameters.time_delay;
    
    % Here we use code from our collaborator (in
    % lib/EEGsonic_function/features/helper
    frontal_pe = permutation_entropy_mv(frontal_eeg,embedding_dimension,time_delay); 
    posterior_pe = permutation_entropy_mv(posterior_eeg,embedding_dimension,time_delay);
  
%% STEP N: Average 
%{
    Using a 10-second window of EEG, for frontal (Fp1, Fp2, F3, F4 and Fz) and posterior (P3, P4, Pz, O1, O2 and Oz)
    for both EGI and DSI-24 headset, calculate PE for each channel.  
    Average over all frontal channels and all parietal channels. 
    Output these values to OSC every 10 seconds.  
%}

    avg_pe_frontal = mean(frontal_pe);
    avg_pe_posterior = mean(posterior_pe);
end

