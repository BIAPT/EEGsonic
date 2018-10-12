function [is_enough,time_left] = is_enough_time(information,parameters)
%IS_ENOUGH_TIME Summary of this function goes here
%   Detailed explanation goes here
   

    
    max_time = 0;
    if(parameters.general.egi129.is_selected)
        max_time = parameters.general.egi129.data_acquisition_size;
    elseif(parameters.general.dsi24.is_selected)
        max_time = parameters.general.dsi24.data_acquisition_size; 
        % TODO add this in the GUI
    end
    
    warm_up(information,parameters); % first warmup to remove the latency for first pass
    time_left = max_time - warm_up(information,parameters); % second warmup to check for real
    is_enough =  time_left > 0;
        
    
end

