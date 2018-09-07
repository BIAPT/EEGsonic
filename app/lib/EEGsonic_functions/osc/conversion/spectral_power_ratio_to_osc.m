function [ratio_beta_alpha_osc,ratio_alpha_theta_osc] = spectral_power_ratio_to_osc(ratio_beta_alpha,ratio_alpha_theta)
%SPR_TO_OSC Summary of this function goes here
%   Detailed explanation goes here

    %% Variable Setup
    ratio_beta_alpha_osc = cell(1,129);
    ratio_alpha_theta_osc = cell(1,129);
    number_channels = length(ratio_beta_alpha);
    
    %% Create Base string
    osc_base_string = cell(1,129);
    for i = 1:number_channels
        osc_base_string(i) = "/sensor_"+num2str(i)+"/SpecPowerRatio/";
    end
    %% Beta/Alpha to OSC
    for i = 1:number_channels
        ratio_beta_alpha_osc(i) = osc_base_string(i) + "BetaAlpha " + num2str(ratio_beta_alpha(i));
    end
    
    %% Alpha/Theta to OSC
    for i = 1:number_channels
        ratio_alpha_theta_osc(i) = osc_base_string(i) + "AlphaTheta " + num2str(ratio_alpha_theta(i));
    end
end

