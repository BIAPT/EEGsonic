function launch_cleaner(app)
%LAUNCH_CLEANER Summary of this function goes here
%   Detailed explanation goes here

    %% Close the workers
    cancel(app.information.data_worker);
    cancel(app.information.features_worker);
    app.information.data_worker = [];
    app.information.features_worker = [];
    
    %% Close and clean the amplifiers
    if(app.parameters.general.egi129.is_selected)
        clean_egi129();
    elseif(app.parameters.general.dsi24.is_selected)
        clean_dsi24();
    end
end

function clean_egi129()

end

function clean_dsi24()

end

