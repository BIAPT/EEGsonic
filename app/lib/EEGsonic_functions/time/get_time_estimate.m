function [time] = get_time_estimate(type,information,parameters)
%GET_TIME_ESTIMATE Summary of this function goes here
%   Detailed explanation goes here

    %% TODO: Depending on the type of analysis technique we want to do
    % we will fetch the function that best approximate the time required
    % for our analysis technique to finsh and then give our inputs
    % into that function (functions will be stored in time_estimate
    % structure)
    
    if(strcmp(type,"spr"))
        
    elseif(strcmp(type,"td"))
        
    elseif(strcmp(type,"pac"))
        
    elseif(strcmp(type,"fp_wpli"))
        
    elseif(strcmp(type,"fp_dpli"))
        
    elseif(strcmp(type,"hl"))
        
    elseif(strcmp(type,"pe"))
        
    end
end

