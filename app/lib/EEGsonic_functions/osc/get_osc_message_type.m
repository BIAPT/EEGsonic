function [type] = get_osc_message_type(data,conversion_type)
%GET_OSC_MESSAGE_TYPE helper function to output the type of osc message
%   Input:
%       data: data that will be sent
%       conversion_type: type of conversion we want for the data
%   Output:
%       type: output type for the message that will become data

    if(strcmp(conversion_type,"matrix"))
        type = "";
        for i = 1:length(data)
            type = strcat(type,"f");
            type = char(type);
        end
    end
end

