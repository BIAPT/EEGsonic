function [outputArg1,outputArg2] = launch_scheduler(app,number_of_cpu,information,parameters)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   information: contains data pertaining to saving/loading
%   parameters: contains user entered data for features calculation/osc



    %TODO put this into a function within this function for EGI
    parfor cpu =1:number_of_cpu
        if(cpu == 1)
           while(1)
              % Get the data and save it here
           end
        else
            while(1)
               % Calculate features here
            end
        end
    end
end

