function parsave(path,name,data)
%PARSAVE Wrapper function to save in the paralelle workers
    
    name = fix_name(name);
    file_path = strcat(path,filesep,name,".mat");
    save(file_path,'data');
end