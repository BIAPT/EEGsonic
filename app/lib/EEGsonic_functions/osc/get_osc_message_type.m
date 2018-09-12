function [type] = get_osc_message_type(matrix,conversion_type)
%GET_OSC_MESSAGE_TYPE Summary of this function goes here
%   Detailed explanation goes here

    if(strcmp(conversion_type,"matrix"))
        type = "";
        for i = 1:length(matrix)
            type = strcat(type,"f");
            type = char(type);
        end
    end
end

