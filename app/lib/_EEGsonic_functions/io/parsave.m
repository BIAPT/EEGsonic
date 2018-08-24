function parsave(path,index,data)
%PARSAVE Wrapper function to save in the paralelle workers
    file_path = path + index + ".mat";
    save(file_path,'data');
end

