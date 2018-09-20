function [avg_pe_frontal,avg_pe_parietal] = permutation_entropy(eeg_data,eeg_info,parameters,frontal_mask,posterior_mask)
%PERMUTATION_ENTROPY Summary of this function goes here
%   Detailed explanation goes here

%% TODO SEE CODE IN PERMUTATION ENTROPY AND USE IT HERE !

%% STEP N: Average 
%{
    Using a 10-second window of EEG, for frontal (Fp1, Fp2, F3, F4 and Fz) and posterior (P3, P4, Pz, O1, O2 and Oz)
    for both EGI and DSI-24 headset, calculate PE for each channel.  
    Average over all frontal channels and all parietal channels. 
    Output these values to OSC every 10 seconds.  
%}
end

