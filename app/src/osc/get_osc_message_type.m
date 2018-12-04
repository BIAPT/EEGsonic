function [type] = get_osc_message_type(data)
%GET_OSC_MESSAGE_TYPE helper function to output the type of osc message
%   Input:
%       data: data that will be sent
%   Output:
%       type: output type for the message that will become data
        type = "";
        for i = 1:length(data)
            type = strcat(type,"f");
            type = char(type);
        end
end

