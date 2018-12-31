function is_debug_mode = is_debug(app)
% Will check if debug mode is on or off
    mode = app.DebugModeSwitch.Value;
    if(strcmp(mode,'On'))
        is_debug_mode = 1;
    else
        is_debug_mode = 0;
    end
end