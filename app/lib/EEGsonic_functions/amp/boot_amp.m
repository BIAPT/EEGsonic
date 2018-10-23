function boot_amp(amp_type,ip)
%BOOT_AMP Summary of this function goes here
%   Detailed explanation goes here

    if(strcmp(amp_type,"egi129"))
       clean_amp("egi129");
       ampinit(ip)
       ampon;
       ampstart;
    end
end

