function [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(eeg_data,eeg_info,parameters,frontal_mask,parietal_mask)
%PHASE_AMPLITUDE_COUPLING Summary of this function goes here
%   Detailed explanation goes here

%% Step 1: Extract Phase and Frequency
%{
    Extract the extra low-frequency (0.1 to 1 Hz) and alpha (8-13 Hz) oscillations. 
    Use a Hilbert transform to calculate instantaneous phase and amplitude within each bandwidth.  
%}

%% Step 2: Calculate the Modulagram
%{
    Use the PAC code you have implemented in EEGapp to construct a phase-amplitude modulgram,
    assigning each temporal sample to one of n = 18 equally spaced phase bins.  
%}

%% Step 3: Find the Through and Peak
%{
    In order to determine if we have �trough-max� or �peak-max� coupling, for each of the 11 electrodes,
    calculate the ratio of the PAC from the trough (-?/2 to ?/2) and from the peak (-2 ? to -3 ?/2 PLUS 3 ?/2 to 2 ?).  
%}

%% Step 4: Average and Take Ratio
%{
Average the peak / trough ratio for all frontal electrodes, and for all parietal electrodes.
%}

end

