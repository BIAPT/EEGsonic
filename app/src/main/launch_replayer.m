function [features_worker] = launch_replayer(information,parameters)
%LAUNCH_REPLAYER Summary of this function goes here
%   Detailed explanation goes here

    p = gcp(); % get the current parallel pool
    
    parameters.warm_up_wait_time = 10;
    index = -1; % Here we start at -1 to pause the feature calculator and make it wait
    save(information.replay_path,'index');
    features_worker = parfeval(p,@calculate_features,0,information,parameters);
end

