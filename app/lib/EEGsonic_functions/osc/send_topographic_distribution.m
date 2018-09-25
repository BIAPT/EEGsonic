function send_topographic_distribution(ratio_front_back,osc)
%TOPOGRAPHIC_DISTRIBUTION_TO_OSC Summary of this function goes here
%   Detailed explanation goes here
    osc_base_string = "/topographic_distribution/ratio_front_back ";
    ratio_front_back_osc = osc_base_string + num2str(ratio_front_back);
end

