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
    % Use the PAC code you have implemented in EEGapp to construct a phase-amplitude modulgram,
    % assigning each temporal sample to one of n = 18 equally spaced phase bins.  

    %To note: number of bins = 18, as said by slack. May have to make this
    %modular
    number_bins = 18;
    bin_size = (2*pi)/number_bins; 
    number_channels = size(eeg_data,1);
    % ! Speedup can be gained over here, leave that for now  ! %
    sorted_amplitude = zeros(number_bins,2);
    
    % Here we sort amplitude according to the phase
    for channel = 1:number_channels
        channel_phase = low_frequency_phase(channel,:);
        channel_amplitude = high_frequency_amplitude(channel,:);
        
        for point_index = 1:length(channel_phase)
            % Incrementing the amplitude and putting in the right bin
            for bin = 1:number_bins
                if(is_phase_in_range(channel_phase,point_index,bin,bin_size))
                    sorted_amplitude(bin,1) = sorted_amplitude(bin) + channel_amplitude(point_index);
                    sorted_amplitude(bin,2) = sorted_amplitude(bin,2) + 1;
                end
            end
        end
    end
    
    % Calculate the average amplitude
    avg_sorted_amplitude = zeros(number_bins,1);
    for bin = 1:number_bins
            if sorted_amplitude(bin,2) == 0
                avg_sorted_amplitude(bin) = 0;
            else
                avg_sorted_amplitude(bin) = (sorted_amplitude(bin,1)/sorted_amplitude(bin,2));
            end
    end   
    
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

function [is_in_range] = is_phase_in_range(channel_phase,point_index,bin,bin_size)
    is_in_range = channel_phase(point_index) > -pi + (bin-1)*bin_size && channel_phase(point_index) < -pi + (bin)*bin_size;
end

