function calculate_features(data_directory,features_directory,sleep_delay,information,parameters)
%CALCULATE_FEATURES Summary of this function goes here
%   Detailed explanation goes here
    
    %% Variables Initialization
    index = 0;
    eeg_info = [];
    data_acquisition_size = 5; %By default(in seconds)
    osc = parameters.osc;
    
    % Required size variables 
    spr_data_required_size = parameters.spr.required_size;
    td_data_required_size = parameters.td.required_size;
    pac_data_required_size = parameters.pac.required_size;
    fp_wpli_data_required_size = parameters.fp_wpli.required_size;
    fp_dpli_data_required_size = parameters.fp_dpli.required_size; 
    hl_data_required_size = parameters.hl.required_size;
    pe_data_required_size = parameters.pe.required_size;
    
    % Data for each analysis technique 
    spr_data = [];
    td_data = [];
    pac_data = [];
    fp_wpli_data = [];
    fp_dpli_data = [];
    hl_data = [];
    pe_data = [];
    
    % Populate structure of selected_channels (Boolean mask)
    boolean_mask = get_selected_channels(information,parameters);
    
    %% Transforming the Variable depending on headset
    if(parameters.general.egi129.is_selected)
        eeg_info = information.headset.egi129;
        data_acquisition_size = parameters.general.egi129.data_acquisition_size;
        sec_to_pts = 1000;
        % Convert secs to points
        spr_data_required_size = spr_data_required_size*sec_to_pts;
        td_data_required_size = td_data_required_size*sec_to_pts;
        pac_data_required_size = pac_data_required_size*sec_to_pts;
        fp_wpli_data_required_size = fp_wpli_data_required_size*sec_to_pts;
        fp_dpli_data_required_size = fp_dpli_data_required_size*sec_to_pts;
        hl_data_required_size = hl_data_required_size*sec_to_pts;
        pe_data_required_size = pe_data_required_size*sec_to_pts;
        
        
    elseif(parameters.general.dsi24.is_selected)
        eeg_info = information.headset.dsi24;
        % TODO add acquisition size once we get it;
    end
    

    %% Main Loop Calculating the features
    while(1)
        [is_ready,data] = parload(data_directory,index);
        disp("Looking for index: " + num2str(index)); 
        if(is_ready)
            if(parameters.spr.is_selected)
                spr_data = [spr_data, data]; %OPTIMIZATION POSSIBLE HERE
                if(length(spr_data) == spr_data_required_size)
                    [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(spr_data,eeg_info,parameters.spr);
                    % Convert to OSC
                    [ratio_beta_alpha_osc,ratio_alpha_theta_osc] = spectral_power_ratio_to_osc(ratio_beta_alpha,ratio_alpha_theta);
                    % Send to OSC receivers
                    send_feature(ratio_beta_alpha_osc,"f",osc);
                    send_feature(ratio_alpha_theta_osc,"f",osc);
                    % Save the features
                    spr_saved_data = struct();
                    spr_saved_data.ratio_beta_alpha = ratio_beta_alpha;
                    spr_saved_data.ratio_alpha_theta = ratio_alpha_theta;
                    parsave(features_directory,num2str(index)+"_spr",spr_saved_data);
                    spr_data = [];
                end
            end
            
            if(parameters.td.is_selected)
                td_data = [td_data,data];
                if(length(td_data) == td_data_required_size)
                    frontal_mask = boolean_mask.td.frontal_channels;
                    posterior_mask = boolean_mask.td.posterior_channels;
                    [ratio_front_back] = topographic_distribution(td_data,eeg_info,parameters.td,frontal_mask,posterior_mask);
                    % Convert to OSC
                    [ratio_front_back_osc] = topographic_distribution_to_osc(ratio_front_back);
                    % Send to OSC Receivers
                    send_feature(ratio_front_back_osc,"f",osc);
                    td_data = [];
                end
            end
            
            if(parameters.pac.is_selected)
                pac_data = [pac_data,data];
                if(length(pac_data) == pac_data_required_size)
                
                    pac_data = [];
                end
            end
            
            if(parameters.fp_wpli.is_selected)
                fp_wpli_data = [fp_wpli_data,data];
                if(length(fp_wpli_data) == fp_wpli_data_required_size)
                   
                    fp_wpli_data = [];
                end
            end
            
            if(parameters.fp_dpli.is_selected)
                fp_dpli_data = [fp_dpli_data,data];
                if(length(fp_dpli_data) == fp_dpli_data_required_size)
                   
                    fp_dpli_data = [];
                end
            end
            
            if(parameters.hl.is_selected)
                hl_data = [hl_data,data];
                if(length(hl_data) == hl_data_required_size)
                   
                    hl_data = [];
                end
                
            end
            
            if(parameters.pe.is_selected)
               pe_data = [pe_data,data];
               if(length(pe_data) == pe_data_required_size)
                  
                   pe_data = [];
               end
            end
            index = index+1; 
        else
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end
