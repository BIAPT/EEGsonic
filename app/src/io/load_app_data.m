function [information,parameters] = load_app_data(path,is_default)
%LOAD_APP_DATA Summary of this function goes here
%   Detailed explanation goes here
    data = load(path);
    if(is_default)
        information = data.information;
        parameters = data.parameters;
    else
        information = data.app_data.information;
        parameters = data.app_data.parameters;
    end
end

