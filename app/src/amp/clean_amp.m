function clean_amp(amp_type)
%CLEAN_AMP will clean and remove the setup for the amplifier
%   amp_type: String that says which amplifier was started

    %% EGI129 amplifier shut down routine
    if(strcmp(amp_type,"egi129"))
        close all;
        ampdeinit;
        clear ampsrv;
        clear mex;
        clear KbCheck 
    end
    %% TODO add DSI24 shut down routine
end

