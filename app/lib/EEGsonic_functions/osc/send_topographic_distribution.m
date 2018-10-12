function send_topographic_distribution(ratio_front_back,osc)
%SEND_TOPOGRAPHIC_DISTRIBUTION send to the osc receivers the data in string
%format
%   Input:
%       ratio_front_back: singular value representing ratio_front_back
%       osc: osc data structure

    
    osc_base_string = "/topographic_distribution/ratio_front_back ";
    ratio_front_back_osc = osc_base_string + num2str(ratio_front_back);
end

