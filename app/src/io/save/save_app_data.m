function save_app_data(information,parameters,path)
%SAVE_APP_DATA save the information and parameters into app_data
%   information: static data in the app
%   parameters: variable data in the app as given by the user
%   path: path to where we should save the app_data

    app_data = struct();
    app_data.parameters = parameters;
    app_data.information = information;
    save(path,'app_data');
end

