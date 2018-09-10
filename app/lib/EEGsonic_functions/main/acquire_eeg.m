function acquire_eeg(data_directory,information,parameters)
%ACQUIRE_EEG Summary of this function goes here
%   Detailed explanation goes here
    
    %% Selecting an headset
    headset = "";
    if(parameters.general.egi129.is_selected)
        headset = "egi129";
    elseif(parameters.general.dsi24.is_selected)
        headset = "dsi24";
    end
    
    %% Acquiring EEG data
    index = 0;    
    while(1)
        % here depending on the eeg system we will acquire eeg in diff ways
        switch headset
            case "egi129"
                data = get_egi_data(parameters);
            case "dsi24"
                data = get_dsi_data(parameters);
        end
        %of whatever system we selected to use
        parsave(data_directory,index,data);
        index = index + 1;
    end
end

function [data] = get_egi_data(parameters)
    %% Setting Variables
    acquisition_size = parameters.general.egi129.acquisition_size * 1000;
    
    %% Random Generation (DEBUGGING ONLY!)
    data = rand(128,acquisition_size);
    pause(acquisition_size);
end

function [data] = get_dsi_data(parameters)
    data = rand(128,5000);% TODO change this to the data acquisition
end

