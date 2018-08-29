function launch_cleaner(parameters)
%LAUNCH_CLEANER Summary of this function goes here
%   Detailed explanation goes here
    
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

