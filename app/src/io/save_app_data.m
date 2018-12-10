function save_app_data(information,parameters,path)
%SAVE_APP_DATA Summary of this function goes here
%   Detailed explanation goes here
    app_data = struct();
    app_data.parameters = parameters;
    app_data.information = information;
    save(path,'app_data');
end

