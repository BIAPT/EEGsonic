function [text] = load_text_file(file_name)
%LOAD_TEXT_FILE will read a text file and load its content
%   Input:
%       file_name: The name of the file that we need to load the text from
%   Output:
%       text: content of the file in string format

    %% Opening the file and setting up the variables 
    file_id = fopen(file_name,'r');
    current_line = fgets(file_id);
    text = "";
    
    %% Reading the file and put inside the text
    while(current_line ~= -1)
        text = text + current_line;
        current_line = fgets(file_id);
    end
   
    %% Close the file
    fclose(file_id);
end


