function launch_cleaner(information,parameters)
%LAUNCH_CLEANER cleaner function to finish some amplifier specific task
%before closing
%   Input:
%      information: static data of the app
%      parameters: inputed data by the user
    
    %% Close and clean the amplifiers
    if(parameters.general.egi129.is_selected)
        clean_egi129();
    elseif(parameters.general.dsi24.is_selected)
        clean_dsi24();
    end
end

function clean_egi129()

end

function clean_dsi24()

end

