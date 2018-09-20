function [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(eeg_data,eeg_info,parameters,frontal_mask,parietal_mask)
%PHASE_AMPLITUDE_COUPLING Summary of this function goes here
%   Detailed explanation goes here

%% NOTES:
%   We can have some speedup if we setup the analysis techniques as to
%   remove the eeg channels that we don't need.

%%  Setting the variables
    sampling_rate = eeg_info.headset.egi129.sampling_rate
    low_frequency_bandwith = parameters.extra_low_frequency.bandwith;
    high_frequency_bandwith = parameters.high_frequency.bandwith;

%% Step 0: Filter the Signal
    %LFO filtering
    eeg_low_frequency = bpfilter(low_frequency_bandwith(1),low_frequency_bandwith(2),sampling_rate,double(eeg_data'));
    eeg_low_frequency = eeg_low_frequency';
    
    %HFO filtering
    eeg_high_frequency = bpfilter(high_frequency_bandwith(1),high_frequency_bandwith(2),sampling_rate,double(eeg_data'));
    eeg_high_frequency = eeg_high_frequency';

%% Step 1: Extract Phase and Frequency
    % Extract the extra low-frequency (0.1 to 1 Hz) and alpha (8-13 Hz) oscillations. 
    % Use a Hilbert transform to calculate instantaneous phase and amplitude within each bandwidth.  

    low_frequency_phase = angle(hilbert(eeg_low_frequency)); %Take the angle of the Hilbert to get the phase
    high_frequency_amplitude = abs(hilbert(eeg_high_frequency)); %calculating the amplitude by taking absolute value of hilber

%% Step 2: Calculate the Modulagram
%{
    Use the PAC code you have implemented in EEGapp to construct a phase-amplitude modulgram,
    assigning each temporal sample to one of n = 18 equally spaced phase bins.  
%}

    %To note: number of bins = 18, as said by slack. May have to make this
    %modular
    number_bins = 18;
    bin_size = (2*pi)/number_bins; 
    number_channels = size(eeg_data,1);
    % ! Speedup can be gained over here, leave that for now  ! %
    sorted_amplitude = zeros(number_bins,2);
    for channel = 1:number_channels
        channel_phase = low_frequency_phase(channel,:);
        channel_amplitude = high_frequency_amplitude(channel,:);
        for i = 1:length(channel_phase)
            if channel_phase(i) > -pi && channel_phase(i) < -pi + bin_size
                sorted_amplitude(1,1) = sorted_amplitude(1) + channel_amplitude(i);
                sorted_amplitude(1,2) = sorted_amplitude(1,2) + 1;
            elseif channel_phase(i) > -pi + bin_size && channel_phase(i) < -pi + 2*bin_size
                sorted_amplitude(2,1) = sorted_amplitude(2) + channel_amplitude(i);
                sorted_amplitude(2,2) = sorted_amplitude(2,2) + 1;
            elseif channel_phase(i) > -pi + 2*bin_size && channel_phase(i) < -pi + 3*bin_size
                sorted_amplitude(3) = sorted_amplitude(3) + channel_amplitude(i);
                sorted_amplitude(3,2) = sorted_amplitude(3,2) + 1;
            elseif channel_phase(i) > -pi + 3*bin_size && channel_phase(i) < -pi + 4*bin_size
                sorted_amplitude(4) = sorted_amplitude(4) + channel_amplitude(i);
                sorted_amplitude(4,2) = sorted_amplitude(4,2) + 1;
            elseif channel_phase(i) > -pi + 4*bin_size && channel_phase(i) < -pi + 5*bin_size
                sorted_amplitude(5) = sorted_amplitude(5) + channel_amplitude(i);
                sorted_amplitude(5,2) = sorted_amplitude(5,2) + 1;
            elseif channel_phase(i) > -pi + 5*bin_size && channel_phase(i) < -pi + 6*bin_size
                sorted_amplitude(6) = sorted_amplitude(6) + channel_amplitude(i);
                sorted_amplitude(6,2) = sorted_amplitude(6,2) + 1;
            elseif channel_phase(i) > -pi + 6*bin_size && channel_phase(i) < -pi + 7*bin_size
                sorted_amplitude(7) = sorted_amplitude(7) + channel_amplitude(i);
                sorted_amplitude(7,2) = sorted_amplitude(7,2) + 1;
            elseif channel_phase(i) > -pi + 7*bin_size && channel_phase(i) < -pi + 8*bin_size
                sorted_amplitude(8) = sorted_amplitude(8) + channel_amplitude(i);
                sorted_amplitude(8,2) = sorted_amplitude(8,2) + 1;
            elseif channel_phase(i) > -pi + 8*bin_size && channel_phase(i) < -pi + 9*bin_size
                sorted_amplitude(9) = sorted_amplitude(9) + channel_amplitude(i);
                sorted_amplitude(9,2) = sorted_amplitude(9,2) + 1;
            elseif channel_phase(i) > -pi + 9*bin_size && channel_phase(i) < -pi + 10*bin_size
                sorted_amplitude(10) = sorted_amplitude(10) + channel_amplitude(i);
                sorted_amplitude(10,2) = sorted_amplitude(10,2) + 1;
            elseif channel_phase(i) > -pi + 10*bin_size && channel_phase(i) < -pi + 11*bin_size
                sorted_amplitude(11) = sorted_amplitude(11) + channel_amplitude(i);
                sorted_amplitude(11,2) = sorted_amplitude(11,2) + 1;
            elseif channel_phase(i) > -pi + 11*bin_size && channel_phase(i) < -pi + 12*bin_size
                sorted_amplitude(12) = sorted_amplitude(12) + channel_amplitude(i);
                sorted_amplitude(12,2) = sorted_amplitude(12,2) + 1;
            elseif channel_phase(i) > -pi + 12*bin_size && channel_phase(i) < -pi + 13*bin_size
                sorted_amplitude(13) = sorted_amplitude(13) + channel_amplitude(i);
                sorted_amplitude(13,2) = sorted_amplitude(13,2) + 1;
            elseif channel_phase(i) > -pi + 13*bin_size && channel_phase(i) < -pi + 14*bin_size
                sorted_amplitude(14) = sorted_amplitude(14) + channel_amplitude(i);
                sorted_amplitude(14,2) = sorted_amplitude(14,2) + 1;
            elseif channel_phase(i) > -pi + 14*bin_size && channel_phase(i) < -pi + 15*bin_size
                sorted_amplitude(15) = sorted_amplitude(15) + channel_amplitude(i);
                sorted_amplitude(15,2) = sorted_amplitude(15,2) + 1;
            elseif channel_phase(i) > -pi + 15*bin_size && channel_phase(i) < -pi + 16*bin_size
                sorted_amplitude(16) = sorted_amplitude(16) + channel_amplitude(i);
                sorted_amplitude(16,2) = sorted_amplitude(16,2) + 1;
            elseif channel_phase(i) > -pi + 16*bin_size && channel_phase(i) < -pi + 17*bin_size
                sorted_amplitude(17) = sorted_amplitude(17) + channel_amplitude(i);
                sorted_amplitude(17,2) = sorted_amplitude(17,2) + 1;
            elseif channel_phase(i) > -pi + 17*bin_size && channel_phase(i) < -pi + 18*bin_size
                sorted_amplitude(18) = sorted_amplitude(18) + channel_amplitude(i);
                sorted_amplitude(18,2) = sorted_amplitude(18,2) + 1;
            end
        end
    end
%% Step 3: Find the Through and Peak
%{
    In order to determine if we have “trough-max” or “peak-max” coupling, for each of the 11 electrodes,
    calculate the ratio of the PAC from the trough (-?/2 to ?/2) and from the peak (-2 ? to -3 ?/2 PLUS 3 ?/2 to 2 ?).  
%}

%% Step 4: Average and Take Ratio
%{
Average the peak / trough ratio for all frontal electrodes, and for all parietal electrodes.
%}

end

