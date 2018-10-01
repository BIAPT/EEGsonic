function [data_acquisition_size] = get_data_acquisition_size(parameters)
%GET_DATA_ACQUISITION_SIZE Summary of this function goes here
%   Detailed explanation goes here

    if(parameters.general.egi129.is_selected)
       data_acquisition_size = parameters.general.egi129.data_acquisition_size*1000; 
    elseif(parameters.general.dsi24.is_selected)
        data_acquisition_size = parameters.general.dsi24.data_acquisition_size*1000;
    end
end

