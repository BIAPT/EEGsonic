function calculate_features(data_directory,sleep_delay,information,parameters)
%CALCULATE_FEATURES Summary of this function goes here
%   Detailed explanation goes here
    index = 0;
    while(1)
        [is_ready,data] = parload(data_directory,index);
        if(is_ready)
            % Check analysis techniques and run each of them one by one
            
            index = index+1; 
        else
            pause(sleep_delay);
        end
    end
end

