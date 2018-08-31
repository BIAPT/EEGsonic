function [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(eeg_data,eeg_info,spr)
%SPECTRAL POWER RATIO Summary of this function goes here
%   Detailed explanation goes here

%% TODO create the three mtscpectro function

%{
window_size,step_size,time_bandwith_product,number_tapers,theta_bandwith,
is_theta,alpha_bandwith,is_alpha,beta_bandwith,is_beta,averaging_size
%}

%% Create params struct for Chronux function
    params.tapers = [spr.time_bandwidth spr.number_tapers];
    params.Fs = eeg_info.sampling_rate;
    params.trialave = 1;
    window_parameters = [spr.window_size spr.step_size];    

    %% Theta
    params.fpass = [fp];
    [S, t, f] = mtspecgramc(eeg_data, window_parameters,params);

    %% Beta
    
    %% Alpha
    
    %% Ratio
end

