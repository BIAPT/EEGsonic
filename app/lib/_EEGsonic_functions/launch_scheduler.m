function launch_scheduler(app,information,parameters)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   information: contains data pertaining to saving/loading
%   parameters: contains user entered data for features calculation/osc
    

    %Need at least 2 CPUs to do run this properly
    parfor cpu = 1:2
        is_running = evalin('base','is_running');
        if(cpu == 1)
           while(is_running)
              % Get the data and save it here
              a = 1+1
              is_running = evalin('base','is_running');
           end
        else
            while(is_running)
               % Calculate features here
               b = 1+2
               is_running = evalin('base','is_running');
            end
        end
    end
end

