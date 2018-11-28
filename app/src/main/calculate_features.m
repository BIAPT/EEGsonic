function calculate_features(data_directory,features_directory,information,parameters)
%CALCULATE_FEATURES Main pipeline to calculate the features based on data
%recorder from the data_thread
%   Input:
%       data_directory: directory where to find the collected data
%       features_directory: directory where to save the features
%       information: static data in the app
%       parameters: variable data in the app as given by the user
    
    %% Warm up 
    %  This function will call each analysis technique once to not have a
    %  slow down during the first pass of the pipeline
    warm_up(information,parameters);

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
        channels_location = information.headset.egi129.channels_location;
        sleep_delay = data_acquisition_size/10;
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
        sleep_delay = data_acquizition_size/10;
        channels_location = information.headset.dsi24.channels_location;        
        % TODO add acquisition size once we get it;
    end
    

    %% Main Loop Calculating the features
    while(1)
        [is_ready,data] = parload(data_directory,index); % try to load the data
        if(is_ready)
            disp("Analyzing: " + num2str(index));
            
            % Spectral Power Ratio
            if(parameters.spr.is_selected)
                spr_data = [spr_data, data]; 
                if(length(spr_data) == spr_data_required_size)
                    % Calculate spr
                    [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(spr_data,eeg_info,parameters.spr);
                    % Convert and Send to OSC
                    send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"ratio_beta_alpha_"+num2str(index),ratio_beta_alpha);
                        parsave(features_directory,"ratio_alpha_theta_"+num2str(index),ratio_alpha_theta);
                    end
                    spr_data = [];
                end
            end
            
            % Topographic Distribution
            if(parameters.td.is_selected)
                td_data = [td_data,data];
                if(length(td_data) == td_data_required_size)
                    % Get the right mask 
                    frontal_mask = boolean_mask.td.frontal_channels;
                    posterior_mask = boolean_mask.td.posterior_channels;
                    % Calculate td
                    [ratio_front_back] = topographic_distribution(td_data,eeg_info,parameters.td,frontal_mask,posterior_mask);
                    % Convert and Send to OSC
                    send_topographic_distribution(ratio_front_back,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"ratio_front_back_"+num2str(index),ratio_front_back);
                    end
                    td_data = [];
                end
            end
            
            % Phase Amplitude Coupling
            if(parameters.pac.is_selected)
                pac_data = [pac_data,data];
                if(length(pac_data) == pac_data_required_size)
                    % Get the right mask
                    frontal_mask = boolean_mask.pac.frontal_channels;
                    parietal_mask = boolean_mask.pac.parietal_channels;                    
                    % Calculate pac
                    [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(pac_data,eeg_info,parameters.pac,frontal_mask,parietal_mask);
                    % Convert and Send to OSC
                    send_phase_amplitude_coupling(rpt_frontal,rpt_parietal,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"rpt_frontal_"+num2str(index),rpt_frontal);
                        parsave(features_directory,"rpt_parietal_"+num2str(index),rpt_parietal);
                    end
                    pac_data = [];
                end
            end
            
            % Fronto-parietal weighted Phase Lag Index
            if(parameters.fp_wpli.is_selected)
                fp_wpli_data = [fp_wpli_data,data];
                if(length(fp_wpli_data) == fp_wpli_data_required_size)
                    % Get the right mask
                    midline_mask = boolean_mask.fp_wpli.midline_channels;
                    lateral_mask = boolean_mask.fp_wpli.lateral_channels; 
                    % Calculate fp_wpli
                    [avg_pli_midline,avg_pli_lateral] = fp_wpli(fp_wpli_data,eeg_info,parameters.fp_wpli,midline_mask,lateral_mask);                   
                    % Convert and Send to OSC
                    send_fp_wpli(avg_pli_midline,avg_pli_lateral,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"avg_pli_midline_"+num2str(index),avg_pli_midline);
                        parsave(features_directory,"avg_pli_lateral_"+num2str(index),avg_pli_lateral);
                    end
                    fp_wpli_data = [];
                end
            end
            
            % Fronto-Parietal directed Phase Lag Index
            if(parameters.fp_dpli.is_selected)
                fp_dpli_data = [fp_dpli_data,data];
                if(length(fp_dpli_data) == fp_dpli_data_required_size)
                    % Get the right mask
                    midline_mask = boolean_mask.fp_dpli.midline_channels;
                    lateral_mask = boolean_mask.fp_dpli.lateral_channels;                     
                    % Calculate fp_dpli
                    [avg_dpli_midline,avg_dpli_lateral] = fp_dpli(fp_dpli_data,eeg_info,parameters.fp_dpli,midline_mask,lateral_mask);                   
                    % Convert and Send to OSC
                    send_fp_dpli(avg_dpli_midline,avg_dpli_lateral,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"avg_dpli_midline_"+num2str(index),avg_dpli_midline);
                        parsave(features_directory,"avg_dpli_lateral"+num2str(index),avg_dpli_lateral);
                    end
                    fp_dpli_data = [];
                end
            end
            
            % Hub Location
            if(parameters.hl.is_selected)
                hl_data = [hl_data,data];
                if(length(hl_data) == hl_data_required_size)
                    % Calculate hl
                    [hd_channel_index] = hub_location(hl_data,eeg_info,parameters.hl);
                    % Convert and Send to OSC
                    send_hub_location(parameters.hl.output_type,hd_channel_index,channels_location,osc);                    
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"hd_channel_index_"+num2str(index),hd_channel_index);
                    end
                    hl_data = [];
                end
                
            end
            
            % Permutation Entropy
            if(parameters.pe.is_selected)
               pe_data = [pe_data,data];
               if(length(pe_data) == pe_data_required_size)
                    % Get the right mask
                    frontal_mask = boolean_mask.pe.frontal_channels;
                    posterior_mask = boolean_mask.pe.posterior_channels;  
                    % Calculate pe
                    [avg_pe_frontal,avg_pe_posterior] = permutation_entropy(pe_data,eeg_info,parameters.pe,frontal_mask,posterior_mask);
                    % Convert and Send to OSC
                    send_permutation_entropy(avg_pe_frontal,avg_pe_posterior,osc);
                    % Saving
                    if(information.is_save_features)
                        parsave(features_directory,"avg_pe_frontal_"+num2str(index),avg_pe_frontal);
                        parsave(features_directory,"avg_pe_posterior_"+num2str(index),avg_pe_posterior);
                    end
                    pe_data = [];
               end
            end
            index = index+1; 
        else
            disp("Waiting " + num2str(sleep_delay) + " sec for " + num2str(index)); 
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end
