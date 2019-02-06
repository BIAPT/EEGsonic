function [information,parameters,state] = load_app_data(path,is_default)
%LOAD_APP_DATA load the app_data given a path
%   path: path to the app data
%   is_default: boolean that says if the app_data is a saved one or the
%   default

    data = load(path);
    if(is_default)
        information = data.information;
        parameters = data.parameters;
        state = data.state;
    elseif(is_default == 2)
        
    else
        information = data.app_data.information;
        parameters = data.app_data.parameters;
        state = -1;
    end
end

