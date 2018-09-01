function [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,eeg_info,parameters)
%SPECTRAL POWER RATIO Summary of this function goes here
%   Detailed explanation goes here

%% Create params struct for Chronux function
    params.tapers = [parameters.time_bandwidth parameters.number_tapers];
    params.Fs = eeg_info.sampling_rate;
    params.trialave = 1;
    window_parameters = [parameters.window_size parameters.step_size];    

    %% Theta
    params.fpass = [parameters.theta_bandwith];
    [spectrum_theta, time_theta, frequency_theta] = mtspecgramc(eeg_data, window_parameters, params);
    overall_spectrum_theta = mean(spectrum_theta,2);
    avg_spectrum_theta = mean(overall_spectrum_theta);
    
    %% Beta
    params.fpass = [parameters.beta_bandwith];
    [spectrum_beta, time_beta, frequency_beta] = mtspecgramc(eeg_data, window_parameters,params);
    overall_spectrum_beta = mean(spectrum_beta,2);
    avg_spectrum_beta = mean(overall_spectrum_beta);
    
    %% Alpha
    params.fpass = [parameters.alpha_bandwith];
    [spectrum_alpha, time_alpha, frequency_alpha] = mtspecgramc(eeg_data, window_parameters,params);
    overall_spectrum_alpha = mean(spectrum_alpha,2)
    avg_spectrum_alpha = mean(overall_spectrum_alpha);
    
    %% Ratio
    ratio_beta_alpha = avg_spectrum_beta/avg_spectrum_alpha;
    ratio_alpha_theta = avg_spectrum_alpha/avg_spectrum_theta;
end

