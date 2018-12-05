function [features_worker] = launch_replayer(information,parameters)
%LAUNCH_REPLAYER Summary of this function goes here
%   Detailed explanation goes here

    p = gcp(); % get the current parallel pool
    
    parameters.warm_up_wait_time = 10;
    features_worker = parfeval(p,@calculate_features,0,data_directory,features_directory,information,parameters);
    pause(parameters.warm_up_wait_time); % This is used to give some time for the warmup of the feature calculation
    
end

