function [data_acquisition_size] = get_data_acquisition_size(parameters)
%GET_DATA_ACQUISITION_SIZE return a given data acquisition size in Hz
%   Input: 
%       parameters: variables data as inputed by the user
%   Output:
%       data_acquisition_size: size of the data converted in Hz

    if(parameters.general.egi129.is_selected)
       data_acquisition_size = parameters.general.egi129.data_acquisition_size*1000; 
    elseif(parameters.general.dsi24.is_selected)
        data_acquisition_size = parameters.general.dsi24.data_acquisition_size*1000;
    end
end

