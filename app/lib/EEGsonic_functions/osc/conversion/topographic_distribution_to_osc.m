function [ratio_front_back_osc] = topographic_distribution_to_osc(ratio_front_back)
%TOPOGRAPHIC_DISTRIBUTION_TO_OSC Summary of this function goes here
%   Detailed explanation goes here
    osc_base_string = "/TopoDistribution/RatioFrontBack ";
    ratio_front_back_osc = osc_base_string + num2str(ratio_front_back);
end

