function parsave(path,name,data)
%PARSAVE Wrapper function to save in the paralelle workers
%   Input: 
%       path: where to save the data
%       name: name of the file to be created
%       data: data to be saved in the specified folder
    
    name = fix_name(name);
    file_path = strcat(path,filesep,name,".mat");
    save(file_path,'data');
end