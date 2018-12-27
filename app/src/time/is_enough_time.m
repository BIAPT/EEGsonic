function [is_enough,time_left] = is_enough_time(information,parameters)
%IS_ENOUGH_TIME will check if there is enough time to do everything that
%was selected
%   information: static data of the app
%   parameters: inputed data by the user
   

    
    max_time = 0;
    if(parameters.general.egi129.is_selected)
        max_time = parameters.general.egi129.data_acquisition_size;
    elseif(parameters.general.dsi24.is_selected)
        max_time = parameters.general.dsi24.data_acquisition_size; 
        % TODO add this in the GUI
    end
    
    time_left = max_time - warm_up(information,parameters); % second warmup to check for real
    is_enough =  time_left > 0;
        
    
end

