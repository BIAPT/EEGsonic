function create_dir_structure(output_path,app_data)
%CREATE_DIR_STRUCTURE create the directory structure to save the data into
%   output_path: String of where to save the data
%   app_data: data to be saved

    %% Variable creation
    data_path = strcat(output_path,filesep,'data');
    parameters_path = strcat(output_path,filesep,'parameters');
    features_path = strcat(output_path,filesep,'features');

    %% Folder initialization
    mkdir(output_path);
    mkdir(data_path);
    mkdir(parameters_path);
    mkdir(features_path);

    %% Create information.txt
    file_name = strcat(output_path,filesep,'information.txt');
    file_id = fopen(file_name,'w');
    
    %% Write the conten into the file
    fprintf(file_id,"Information EEG session converted on the - " + (date) + "\n");
    fprintf(file_id,"\n");
    fclose(file_id);
    
    %% Create app_data.mat
    app_data_path = strcat(parameters_path,filesep,'app_data.mat');
    save(app_data_path,'app_data');
end

