function [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,eeg_info,parameters)
%SPECTRAL POWER RATIO Summary of this function goes here
%   Detailed explanation goes here

%NOTE: Gram mistake in the whole app (bandwith -> need to be bandwidth)
    
    %% Setup Variables
    eeg_data = eeg_data';
    
    %% Create params struct for Chronux function
    params.tapers = [parameters.time_bandwith_product parameters.number_tapers];
    params.Fs = eeg_info.sampling_rate;
    params.trialave = 1;
    window_parameters = [parameters.window_size parameters.step_size];    

    %% Theta
    avg_spectrum_theta = [];
    for i = 1:eeg_info.number_channels
        params.fpass = [parameters.theta.bandwith];
        [spectrum_theta, ~, ~] = mtspecgramc(eeg_data(:,i), window_parameters, params);
        overall_spectrum_theta = mean(spectrum_theta,2);
        avg_spectrum_theta = [avg_spectrum_theta,mean(overall_spectrum_theta)];
    end
    
    %% Beta
    avg_spectrum_beta = [];
    params.fpass = [parameters.beta.bandwith];
    [spectrum_beta, time_beta, frequency_beta] = mtspecgramc(eeg_data, window_parameters,params);
    overall_spectrum_beta = mean(spectrum_beta,2);
    avg_spectrum_beta = mean(overall_spectrum_beta);
    
    %% Alpha
    avg_spectrum_alpha = [];
    params.fpass = [parameters.alpha.bandwith];
    [spectrum_alpha, time_alpha, frequency_alpha] = mtspecgramc(eeg_data, window_parameters,params);
    overall_spectrum_alpha = mean(spectrum_alpha,2)
    avg_spectrum_alpha = mean(overall_spectrum_alpha);
    
    %% Ratio
    ratio_beta_alpha = avg_spectrum_beta/avg_spectrum_alpha;
    ratio_alpha_theta = avg_spectrum_alpha/avg_spectrum_theta;
end

