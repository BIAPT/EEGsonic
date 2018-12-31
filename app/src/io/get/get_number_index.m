function number_index = get_number_index(data_directory)
% GET_NUMBER_INDEX will find the maximum number of index inside a data
% directory
    file_list = dir(data_directory);
    number_index = 0;
    for i = 1:length(file_list)
        value = split(file_list(i).name,".");
        value = value(1);
        try
            value = str2num(cell2mat(value(1)));
            if(value > number_index)
               number_index = value; 
            end
        catch
            % Do nothing if cannot do str2num
        end
    end
end