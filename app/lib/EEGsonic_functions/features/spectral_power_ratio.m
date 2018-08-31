function [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,eeg_info,spr)
%SPECTRAL POWER RATIO Summary of this function goes here
%   Detailed explanation goes here

%% TODO create the three mtscpectro function

%{
window_size,step_size,time_bandwith_product,number_tapers,theta_bandwith,
alpha_bandwith,beta_bandwith,averaging_size
%}

%% Create params struct for Chronux function
    params.tapers = [spr.time_bandwidth spr.number_tapers];
    params.Fs = eeg_info.sampling_rate;
    params.trialave = 1;
    window_parameters = [spr.window_size spr.step_size];    

    %% Theta
    params.fpass = [spr.theta_bandwith];
    [spectrum_theta, time_theta, frequency_theta] = mtspecgramc(eeg_data, window_parameters,params);
    avg_spectrum_theta = mean(spectrum_theta);
    
    %% Beta
    params.fpass = [spr.beta_bandwith];
    [spectrum_beta, time_beta, frequency_beta] = mtspecgramc(eeg_data, window_parameters,params);
    avg_spectrum_beta = mean(spectrum_beta);
    
    %% Alpha
    params.fpass = [spr.alpha_bandwith];
    [spectrum_alpha, time_alpha, frequency_alpha] = mtspecgramc(eeg_data, window_parameters,params);
    avg_spectrum_alpha = mean(spectrum_alpha)
    
    %% Ratio
    ratio_beta_alpha = avg_spectrum_beta/avg_spectrum_alpha;
    ratio_alpha_theta = avg_spectrum_alpha/avg_spectrum_theta;
end

