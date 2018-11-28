function clean_amp(amp_type)
%CLEAN Summary of this function goes here
%   Detailed explanation goes here
    if(strcmp(amp_type,"egi129"))
        close all;
        ampdeinit;
        clear ampsrv;
        clear mex;
        clear KbCheck 
    end
end

