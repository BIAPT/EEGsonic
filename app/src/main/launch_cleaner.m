function launch_cleaner(information,parameters)
%LAUNCH_CLEANER cleaner function to finish some amplifier specific task
%before closing
%   Input:
%      information: static data of the app
%      parameters: inputed data by the user

    %% Check if in demo mode
    if(information.debug_mode)
        % if we are we simply exit;
       return; 
    end
    
    %% Close and clean the amplifiers
    if(parameters.general.egi129.is_selected)
        clean_egi129();
    elseif(parameters.general.dsi24.is_selected)
        clean_dsi24();
    end
end

% Cleaner for EGI129
function clean_egi129()
    disp("Shutting down EGI 129 amplifier");
    clean_amp("egi129");
end

% Cleaner for DSI24
function clean_dsi24()

end

