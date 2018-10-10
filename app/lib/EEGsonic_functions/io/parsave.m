function parsave(path,name,data)
%PARSAVE Wrapper function to save in the paralelle workers
    file_path = strcat(path,filesep,name,".mat");
    save(file_path,'data');
end

