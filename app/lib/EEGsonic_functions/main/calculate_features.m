function calculate_features(data_directory,sleep_delay,information,parameters)
%CALCULATE_FEATURES Summary of this function goes here
%   Detailed explanation goes here
    index = 0;
    while(1)
        [is_ready,data] = parload(data_directory,index);
        if(is_ready)
            % TODO Put the right analysis technique here 
            % And send to OSC when ready!
            if(parameters.spr.is_selected)
                
            end
            
            if(parameters.td.is_selected)
                
            end
            
            if(parameters.pac.is_selected)
                
            end
            
            if(parameters.fp_wpli.is_selected)
                
            end
            
            if(parameters.fp_dpli.is_selected)
                
            end
            
            if(parameters.hl.is_selected)
                
            end
            
            if(parameters.pe.is_selected)
                
            end
            
            
            index = index+1; 
        else
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end
