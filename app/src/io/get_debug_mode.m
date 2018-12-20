function string_debug_mode = get_debug_mode(debug_mode)
%GET_DEBUG_MODE Summary of this function goes here
%   Detailed explanation goes here
    if(debug_mode)
        string_debug_mode = 'On';
    else
        string_debug_mode = 'Off';
    end
end

