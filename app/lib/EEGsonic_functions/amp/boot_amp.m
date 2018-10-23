function boot_amp(information,parameters)
%BOOT_AMP Summary of this function goes here
%   Detailed explanation goes here

    if(parameters.egi129.is_selected == 1 && information.debug_mode == 0)
       clean_amp("egi129");
       ampinit('10.10.10.51') %TODO this need to be variable
       ampon;
       ampstart;
    end
end

