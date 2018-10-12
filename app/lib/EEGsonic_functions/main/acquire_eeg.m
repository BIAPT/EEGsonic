function acquire_eeg(data_directory,information,parameters)
%ACQUIRE_EEG generate (debugmode == 1) or acquire EEG data and save it into
%the data_directory
%   Input:
%       data_directory: directory where the EEG data need to be saved
%       information: static data of the app
%       parameters: inputed data by the user
    
    %% Selecting an headset
    headset = "";
    if(parameters.general.egi129.is_selected)
        headset = "egi129";
    elseif(parameters.general.dsi24.is_selected)
        headset = "dsi24";
    end
    
    pause(parameters.warm_up_wait_time);
    
    %% Acquiring EEG data
    index = 0;    
    while(1) % will never stop, need to be interupted by the maint thread
        % here depending on the eeg system we will acquire eeg in diff ways
        switch headset
            case "egi129"
                data = get_egi_data(information,parameters);
            case "dsi24"
                data = get_dsi_data(information,parameters);
        end
        % save the EEG data acquired into the data directory
        parsave(data_directory,index,data);
        index = index + 1;
    end
end

function [data] = get_egi_data(information,parameters)
    %% Setting Variables
    data_acquisition_size = parameters.general.egi129.data_acquisition_size;
    
    
    if(information.debug_mode == 1)
        %% Random Generation for debugging
        data = rand(128,data_acquisition_size*1000);
        pause(data_acquisition_size);
    end
end

function [data] = get_dsi_data(information,parameters)
    if(information.debug_mode == 1)
        %% Random Generation for debugging
        data = rand(128,5000);
        pause(5000);
    end
end

