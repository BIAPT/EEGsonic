function send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc)
%SEND_SPECTRAL_POWER_RATIO send to the osc receivers the data in string
%format
%   Input:
%       ratio_beta_alpha: vector for the ratio for each channels
%       ratio_alpha_theta: vector for the ratio for each channels
%       osc: osc data structure

    %% Variable Setup
    ratio_beta_alpha_osc = strings(1,128);
    ratio_alpha_theta_osc = strings(1,128);
    osc_base_string = strings(1,128);
    number_channels = length(ratio_beta_alpha);
    
    %% Create Base string
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

