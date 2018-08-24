function [data_worker,features_worker] = launch_scheduler(information,parameters)
%LAUNCH_scheduler Will take care of getting eeg data and calculating
%features
%   information: contains data pertaining to saving/loading
%   parameters: contains user entered data for features calculation/osc
    p = gcp(); % get the current parallel pool
    data_worker = parfeval(p,@acquire_eeg,0,information,parameters);
    features_worker = parfeval(p,@calculate_features,0,information,parameters);
end

function acquire_eeg(information,parameters)
    while(1)
        disp('data');
    end
end

function calculate_features(information,parameters)
    while(1)
        disp('features');
    end
end

