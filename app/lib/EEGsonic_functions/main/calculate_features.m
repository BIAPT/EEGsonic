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
        if(is_ready)
            if(parameters.spr.is_selected)
                spr_data = [spr_data, data]; 
                if(length(spr_data) == spr_data_required_size)
                    % Calculate spr
                    [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(spr_data,eeg_info,parameters.spr);
                    % Convert to OSC
                    [ratio_beta_alpha_osc,ratio_alpha_theta_osc] = spectral_power_ratio_to_osc(ratio_beta_alpha,ratio_alpha_theta);
                    % Send to OSC receivers
                    send_feature(ratio_beta_alpha_osc,"f",osc);
                    send_feature(ratio_alpha_theta_osc,"f",osc);
                    spr_data = [];
                end
            end
            
            if(parameters.td.is_selected)
                td_data = [td_data,data];
                if(length(td_data) == td_data_required_size)
                    frontal_mask = boolean_mask.td.frontal_channels;
                    posterior_mask = boolean_mask.td.posterior_channels;
                    % Calculate td
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
                    frontal_mask = boolean_mask.pac.frontal_channels;
                    parietal_mask = boolean_mask.pac.parietal_channels;                    
                    % Calculate pac
                    [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(pac_data,eeg_info,parameters.pac,frontal_mask,parietal_mask);
                    % Convert to osc
                    [rpt_frontal_osc,rpt_parietal_osc] = phase_amplitude_coupling_to_osc(rpt_frontal,rpt_parietal);
                    % Send to OSC receivers
                    send_feature(rpt_frontal_osc,"f",osc);
                    send_feature(rpt_parietal_osc,"f",osc);
                    pac_data = [];
                end
            end
            
            if(parameters.fp_wpli.is_selected)
                fp_wpli_data = [fp_wpli_data,data];
                if(length(fp_wpli_data) == fp_wpli_data_required_size)
                    midline_mask = boolean_mask.fp_wpli.midline_channels;
                    lateral_mask = boolean_mask.fp_wpli.lateral_channels; 
                    % Calculate fp_wpli
                    [avg_pli_midline,avg_pli_lateral] = fp_wpli(fp_wpli_data,eeg_info,parameters.fp_wpli,midline_mask,lateral_mask);                   
                    % Convert to OSC
                    [avg_pli_midline_osc,avg_pli_lateral_osc] = fp_wpli_to_osc(avg_pli_midline,avg_pli_lateral);
                    % Send to OSC receivers
                    send_feature(avg_pli_midline_osc,"f",osc);
                    send_feature(avg_pli_lateral_osc,"f",osc);                    
                    fp_wpli_data = [];
                end
            end
            
            if(parameters.fp_dpli.is_selected)
                fp_dpli_data = [fp_dpli_data,data];
                if(length(fp_dpli_data) == fp_dpli_data_required_size)
                    midline_mask = boolean_mask.fp_dpli.midline_channels;
                    lateral_mask = boolean_mask.fp_dpli.lateral_channels;                     
                    % Calculate fp_dpli
                    [avg_dpli_midline,avg_dpli_lateral] = fp_dpli(fp_dpli_data,eeg_info,parameters.fp_dpli,midline_mask,lateral_mask);                   
                    % Convert to OSC
                    [avg_dpli_midline_osc,avg_dpli_lateral_osc] = fp_dpli_to_osc(avg_dpli_midline,avg_dpli_lateral);
                    % Send to OSC receivers
                    send_feature(avg_dpli_midline_osc,"f",osc);
                    send_feature(avg_dpli_lateral_osc,"f",osc);                     
                    fp_dpli_data = [];
                end
            end
            
            if(parameters.hl.is_selected)
                hl_data = [hl_data,data];
                if(length(hl_data) == hl_data_required_size)
                    % Calculate hl
                    [avg_location_hd_node] = hub_location(eeg_data,eeg_info,parameters.hl);
                    % Convert to OSC
                    [avg_location_hd_node_osc] = hub_location_to_osc(avg_location_hd_node);
                    % Send to OSC receivers
                    send_feature(avg_location_hd_node_osc,"f",osc);                    
                    hl_data = [];
                end
                
            end
            
            if(parameters.pe.is_selected)
               pe_data = [pe_data,data];
               if(length(pe_data) == pe_data_required_size)
                    frontal_mask = boolean_mask.pe.frontal_channels;
                    posterior_mask = boolean_mask.pe.posterior_channels;  
                    % Calculate pe
                    [avg_pe_frontal,avg_pe_parietal] = permutation_entropy(eeg_data,eeg_info,parameters.pe,frontal_mask,posterior_mask);
                    % Convert to OSC
                    [avg_pe_frontal_osc,avg_pe_parietal_osc] = permutation_entropy_to_osc(avg_pe_frontal,avg_pe_parietal);
                    % Send to OSC receivers
                    send_feature(avg_pe_frontal_osc,"f",osc);
                    send_feature(avg_pe_parietal_osc,"f",osc);
                    pe_data = [];
               end
            end
            index = index+1; 
        else
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end
