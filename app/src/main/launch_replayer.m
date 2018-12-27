function [features_worker] = launch_replayer(information,parameters)
%LAUNCH_REPLAYER will launch the feature worker for the replayer
%   information: static data in the app
%   parameters: variable data in the app as given by the user

    p = gcp(); % get the current parallel pool
    
    %% Setup the starting index
    index = -1; % Here we start at -1 to pause the feature calculator and make it wait
    save(information.replay_path,'index');
    
    %% Start the worker
    parameters.warm_up_wait_time = 10;
    features_worker = parfeval(p,@calculate_features,0,information,parameters);
end

