function [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(eeg_data,eeg_info,parameters,frontal_mask,parietal_mask)
%PHASE_AMPLITUDE_COUPLING Summary of this function goes here
%   Detailed explanation goes here

%% NOTES:
%   We can have some speedup if we setup the analysis techniques as to
%   remove the eeg channels that we don't need.

%% TODO
% THIS WILL REQUIRE SOME REFACTORING AND SOME COMMENTING

%%  Setting the variables
    number_bins = 18;
    sampling_rate = eeg_info.sampling_rate;
    low_frequency_bandwith = parameters.extra_low_frequency.bandwith;
    high_frequency_bandwith = parameters.high_frequency.bandwith;
    
%% Calculate Modulogram (Frontal)
    frontal_eeg = eeg_data(frontal_mask == 1,:);
    number_channels_frontal = size(frontal_eeg,1)
    [lfo_phase_frontal,hfo_amplitude_frontal] = extract_lfo_hfo(frontal_eeg,sampling_rate,...,
                                                low_frequency_bandwith,high_frequency_bandwith);
    [modulogram_frontal] = calculate_modulogram(number_bins,lfo_phase_frontal,hfo_amplitude_frontal,...,
                                                number_channels_frontal);
                                    
%% Calculate Modulogram (Parietal)
    parietal_eeg = eeg_data(parietal_mask == 1,:);
    number_channels_parietal = size(parietal_eeg,1);
    [lfo_phase_parietal,hfo_amplitude_parietal] = extract_lfo_hfo(parietal_eeg,sampling_rate,...,
                                                  low_frequency_bandwith,high_frequency_bandwith);
    [modulogram_parietal] = calculate_modulogram(number_bins,lfo_phase_parietal,hfo_amplitude_parietal,...,
                                                 number_channels_parietal);
    
%% Step 3: Find the Through and Peak
%{
    In order to determine if we have “trough-max” or “peak-max” coupling, for each of the 11 electrodes,
    calculate the ratio of the PAC from the trough (-?/2 to ?/2) and from the peak (-2 ? to -3 ?/2 PLUS 3 ?/2 to 2 ?).  
%}

% The peak region = -pi/2 to pi/2 , sor from 1/4 of the modulogram to 3/4
% of the modulogram.
    start_index_peak = floor(number_bins/4);
    stop_index_peak = floor(3*number_bins/4);
    
    start_index_through = [1,stop_index_peak+1];
    stop_index_through = [start_index_peak-1,number_bins];

    peak_frontal = mean(modulogram_frontal(start_index_peak:stop_index_peak));
    through_frontal = mean([modulogram_frontal(start_index_through(1):stop_index_through(1));
                       modulogram_frontal(start_index_through(2):stop_index_through(2))]);
    
    peak_parietal = mean(modulogram_parietal(start_index_peak:stop_index_peak));
    through_parietal = mean([modulogram_parietal(start_index_through(1):stop_index_through(1));
                        modulogram_parietal(start_index_through(2):stop_index_through(2))]);
    
    rpt_frontal = peak_frontal/through_frontal;
    rpt_parietal = peak_parietal/through_parietal;

end

function [low_frequency_phase,high_frequency_amplitude] = extract_lfo_hfo(eeg_data,sampling_rate,low_frequency_bandwith,high_frequency_bandwith)
    %LFO filtering
    eeg_low_frequency = bpfilter(low_frequency_bandwith(1),low_frequency_bandwith(2),sampling_rate,double(eeg_data'));
    eeg_low_frequency = eeg_low_frequency';
    
    %HFO filtering
    eeg_high_frequency = bpfilter(high_frequency_bandwith(1),high_frequency_bandwith(2),sampling_rate,double(eeg_data'));
    eeg_high_frequency = eeg_high_frequency';
    
    % Calculate the LFO phase and HFO amplitude 
    low_frequency_phase = angle(hilbert(eeg_low_frequency)); %Take the angle of the Hilbert to get the phase
    high_frequency_amplitude = abs(hilbert(eeg_high_frequency)); %calculating the amplitude by taking absolute value of hilber

end

function [modulogram] = calculate_modulogram(number_bins,low_frequency_phase,...,
                                            high_frequency_amplitude,number_channels)
    bin_size = (2*pi)/number_bins; 
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
    avg_amplitude = mean(avg_sorted_amplitude);
    
    % For each bins set the value at that position
    modulogram = zeros(number_bins,1);
    for bin = 1:number_bins
        modulogram(bin) = ((avg_sorted_amplitude(bin)-avg_amplitude)/avg_amplitude) + 1;
    end   
    
    % Filter the modulogram
    modulogram = modulogram - 1;            % Do this because median filter assumes 0 on each side
    modulogram = medfilt1(modulogram, 2);   % January 16, 2014
    modulogram = modulogram + 1;
end

function [is_in_range] = is_phase_in_range(channel_phase,point_index,bin,bin_size)
    is_in_range = channel_phase(point_index) > -pi + (bin-1)*bin_size && channel_phase(point_index) < -pi + (bin)*bin_size;
end

