function boot_amp(information,parameters)
%BOOT_AMP will boot up the selected amplifier
%       information: static data in the app
%       parameters: variable data in the app as given by the user

    %% EGI129 booting routine
    if(parameters.egi129.is_selected == 1 && information.debug_mode == 0)
       clean_amp("egi129");
       ampinit('10.10.10.51')
       ampon;
       ampstart;
    end
    %% TODO add DSI-24 booting routine if needed
end

