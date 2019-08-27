function [features_worker_1, features_worker_2, features_worker_3] = launch_replayer(information,parameters)
%LAUNCH_REPLAYER will launch the feature worker for the replayer
%   information: static data in the app
%   parameters: variable data in the app as given by the user

    p = gcp(); % get the current parallel pool
    
    %% Setup the starting index
    index = -1; % Here we start at -1 to pause the feature calculator and make it wait
    save(information.replay_path,'index');
    
    %% Start the worker
    parameters.warm_up_wait_time = 10;
        %% Launch all worker for all analysis techniques
    % To do so we will turn off any analysis technique that is not part of
    % the core
    original_parameters = parameters;
    
    % First core = SPR, TD, PAC
    parameters.fp_wpli.is_selected = 0;
    parameters.fp_dpli.is_selected = 0;
    parameters.hl.is_selected = 0;
    parameters.pe.is_selected = 0;
    features_worker_1 = parfeval(p,@calculate_features,0,information,parameters);
    
    % Second core = FP wPLI + FP dPLI + PE
    parameters = original_parameters;
    parameters.spr.is_selected = 0;
    parameters.td.is_selected = 0;
    parameters.pac.is_selected = 0;
    parameters.hl.is_selected = 0;
    features_worker_2 = parfeval(p,@calculate_features,0,information,parameters);
    
    % Third core = HL
    parameters = original_parameters;
    parameters.spr.is_selected = 0;
    parameters.td.is_selected = 0;
    parameters.pac.is_selected = 0;
    parameters.fp_wpli.is_selected = 0;
    parameters.fp_dpli.is_selected = 0;
    parameters.pe.is_selected = 0;
    features_worker_3 = parfeval(p,@calculate_features,0,information,parameters); 
end

