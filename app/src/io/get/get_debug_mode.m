function string_debug_mode = get_debug_mode(debug_mode)
%GET_DEBUG_MODE boolean to string converter of debug mode
%   debug_mode: boolean, true if in debug mode, false otherwise

    if(debug_mode)
        string_debug_mode = 'On';
    else
        string_debug_mode = 'Off';
    end
end

