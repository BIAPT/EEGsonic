function calculate_features(data_directory,sleep_delay,information,parameters)
%CALCULATE_FEATURES Summary of this function goes here
%   Detailed explanation goes here
    index = 0;
    eeg_info = [];
    data_acquisition_size = 5; %By default(in seconds)
    
    % required size variables
    spr_required_data_size = 5;
    
    % Data for each analysis technique 
    spr_data = [];
    td_data = [];
    pac_data = [];
    fp_wpli_data = [];
    fp_dpli_data = [];
    hl_data = [];
    pe_data = [];
    
    if(parameters.general.egi129.is_selected)
        eeg_info = information.headset.egi129;
        data_acquisition_size = parameters.general.egi129.data_acquisition_size;
        sec_to_pts = 1000;
        spr_required_data_size = spr_required_data_size*sec_to_pts;
        
    elseif(parameters.general.dsi24.is_selected)
        eeg_info = information.headset.dsi24;
    end
    

    while(1)
        [is_ready,data] = parload(data_directory,index);
        if(is_ready)
            % TODO Put the right analysis technique here 
            % And send to OSC when ready!
            if(parameters.spr.is_selected)
                spr_current_data_size = spr_current_data_size + data_acquisition_size;
                spr_data = [spr_data, data]; %OPTIMIZATION POSSIBLE HERE
                if(length(spr_data) == spr_required_data_size)
                    [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(spr_data,eeg_info,parameters.spr)
                    % Convert to OSC
                    [ratio_beta_alpha_osc,ratio_alpha_theta_osc] = spectral_power_ratio_to_osc(ratio_beta_alpha,ratio_alpha_theta)
                    % Send to OSC receivers
                    spr_current_data_size = 0;
                    spr_data = [];
                end
            end
            
            if(parameters.td.is_selected)
                
            end
            
            if(parameters.pac.is_selected)
                
            end
            
            if(parameters.fp_wpli.is_selected)
                
            end
            
            if(parameters.fp_dpli.is_selected)
                
            end
            
            if(parameters.hl.is_selected)
                
            end
            
            if(parameters.pe.is_selected)
                
            end
            index = index+1; 
        else
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end

