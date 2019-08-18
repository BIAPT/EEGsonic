function calculate_features(information,parameters)
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

    %% Variables Initialization
    index = -1; %%TODO Load the index
    eeg_info = [];
    data_acquisition_size = 5; %By default(in seconds)
    osc = parameters.osc;
    data_directory = information.data_directory;
    features_directory = information.features_directory;
    
    % Create the right directory
    mkdir(features_directory,'spr');
    mkdir(features_directory,'td');
    mkdir(features_directory,'pac');
    mkdir(features_directory,'fp_wpli');
    mkdir(features_directory,'fp_dpli');
    mkdir(features_directory,'hl');
    mkdir(features_directory,'pe');
    
    spr_directory = strcat(features_directory, filesep,'spr');
    td_directory = strcat(features_directory, filesep,'td');
    pac_directory = strcat(features_directory, filesep,'pac');
    fp_wpli_directory = strcat(features_directory, filesep,'fp_wpli');
    fp_dpli_directory = strcat(features_directory, filesep,'fp_dpli');
    hl_directory = strcat(features_directory, filesep,'hl');
    pe_directory = strcat(features_directory, filesep,'pe');
    
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
        sampling_rate = parameters.general.egi129.sampling_rate;
        
        % Convert secs to points
        spr_data_required_size = spr_data_required_size*sampling_rate;
        td_data_required_size = td_data_required_size*sampling_rate;
        pac_data_required_size = pac_data_required_size*sampling_rate;
        fp_wpli_data_required_size = fp_wpli_data_required_size*sampling_rate;
        fp_dpli_data_required_size = fp_dpli_data_required_size*sampling_rate;
        hl_data_required_size = hl_data_required_size*sampling_rate;
        pe_data_required_size = pe_data_required_size*sampling_rate;       
    end
    

    %% Main Loop Calculating the features
    while(1)
        % Get the next index
        replay_data = load(information.replay_path);
        next_index = replay_data.index;
        
        if(index ~= next_index)
            if(next_index < index)
                % Reset all the collected data yet 
                spr_data = [];
                td_data = [];
                pac_data = [];
                fp_wpli_data = [];
                fp_dpli_data = [];
                hl_data = [];
                pe_data = [];
            end
            index = next_index;
            [~,data] = parload(data_directory,index); % try to load the data
%            [data,eeg_info] = filter_channels(data,eeg_info); % filter the data
% TODO: Fix problem with filter channels
            disp("Analyzing: " + num2str(index));
            
            % Spectral Power Ratio
            if(parameters.spr.is_selected)
                spr_data = [spr_data, data]; 
                if(length(spr_data) >= spr_data_required_size)
                    % Calculate spr
                    [ratio_beta_alpha,ratio_alpha_theta] = spectral_power_ratio(spr_data,eeg_info,parameters.spr);
                    % Convert and Send to OSC
                    send_spectral_power_ratio(ratio_beta_alpha,ratio_alpha_theta,osc);
                    % Saving
                    parsave(spr_directory,"ratio_beta_alpha_"+num2str(index),ratio_beta_alpha);
                    parsave(spr_directory,"ratio_alpha_theta_"+num2str(index),ratio_alpha_theta);
                    spr_data = [];
                end
            end
            
            % Topographic Distribution
            if(parameters.td.is_selected)
                td_data = [td_data,data];
                if(length(td_data) >= td_data_required_size)
                    % Get the right mask 
                    frontal_mask = boolean_mask.td.frontal_channels;
                    posterior_mask = boolean_mask.td.posterior_channels;
                    % Calculate td
                    [ratio_front_back] = topographic_distribution(td_data,eeg_info,parameters.td,frontal_mask,posterior_mask);
                    % Convert and Send to OSC
                    send_topographic_distribution(ratio_front_back,osc);
                    % Saving
                    parsave(td_directory,"ratio_front_back_"+num2str(index),ratio_front_back);
                    td_data = [];
                end
            end
            
            % Phase Amplitude Coupling
            if(parameters.pac.is_selected)
                pac_data = [pac_data,data];
                if(length(pac_data) >= pac_data_required_size)
                    % Get the right mask
                    frontal_mask = boolean_mask.pac.frontal_channels;
                    parietal_mask = boolean_mask.pac.parietal_channels;                    
                    % Calculate pac
                    [rpt_frontal,rpt_parietal] = phase_amplitude_coupling(pac_data,eeg_info,parameters.pac,frontal_mask,parietal_mask);
                    % Convert and Send to OSC
                    send_phase_amplitude_coupling(rpt_frontal,rpt_parietal,osc);
                    % Saving
                    parsave(pac_directory,"rpt_frontal_"+num2str(index),rpt_frontal);
                    parsave(pac_directory,"rpt_parietal_"+num2str(index),rpt_parietal);
                    pac_data = [];
                end
            end
            
            % Fronto-parietal weighted Phase Lag Index
            if(parameters.fp_wpli.is_selected)
                fp_wpli_data = [fp_wpli_data,data];
                if(length(fp_wpli_data) >= fp_wpli_data_required_size)
                    % Calculate fp_wpli
                    wpli = fp_wpli(fp_wpli_data,eeg_info,parameters.fp_wpli,boolean_mask.fp_wpli);                   
                    
                    % Convert and Send to OSC
                    send_fp_wpli(wpli,osc);
                    % Saving
                    parsave(fp_wpli_directory,"avg_wpli_left_midline_"+num2str(index),wpli.left_midline);
                    parsave(fp_wpli_directory,"avg_wpli_left_lateral_"+num2str(index),wpli.left_lateral);
                    parsave(fp_wpli_directory,"avg_wpli_right_midline_"+num2str(index),wpli.right_midline);
                    parsave(fp_wpli_directory,"avg_wpli_right_lateral_"+num2str(index),wpli.right_lateral);
                    fp_wpli_data = [];
                end
            end
            
            % Fronto-Parietal directed Phase Lag Index
            if(parameters.fp_dpli.is_selected)
                fp_dpli_data = [fp_dpli_data,data];
                if(length(fp_dpli_data) >= fp_dpli_data_required_size)
                                        
                    % Calculate fp_dpli
                    dpli = fp_dpli(fp_dpli_data,eeg_info,parameters.fp_dpli,boolean_mask.fp_dpli);                   
                    
                    % Convert and Send to OSC
                    send_fp_dpli(dpli,osc);
                    % Saving
                    parsave(fp_dpli_directory,"avg_dpli_left_midline_"+num2str(index),dpli.left_midline);
                    parsave(fp_dpli_directory,"avg_dpli_left_lateral_"+num2str(index),dpli.left_lateral);
                    parsave(fp_dpli_directory,"avg_dpli_right_midline_"+num2str(index),dpli.right_midline);
                    parsave(fp_dpli_directory,"avg_dpli_right_lateral_"+num2str(index),dpli.right_lateral);
                    fp_dpli_data = [];
                end
            end
            
            % Hub Location
            if(parameters.hl.is_selected)
                hl_data = [hl_data,data];
                if(length(hl_data) >= hl_data_required_size)
                    % Calculate hl
                    [hd_channel_index,hd_graph] = hub_location(hl_data,eeg_info,parameters.hl);
                    % Convert and Send to OSC
                    send_hub_location(parameters.hl.is_graph,hd_channel_index,hd_graph,osc);                    
                    % Saving
                    parsave(hl_directory,"hd_channel_index_"+num2str(index),hd_channel_index);
                    hl_data = [];
                end
                
            end
            
            % Permutation Entropy
            if(parameters.pe.is_selected)
               pe_data = [pe_data,data];
               if(length(pe_data) >= pe_data_required_size)
                    % Get the right mask
                    frontal_mask = boolean_mask.pe.frontal_channels;
                    posterior_mask = boolean_mask.pe.posterior_channels;  
                    % Calculate pe
                    [avg_pe_frontal,avg_pe_posterior] = permutation_entropy(pe_data,eeg_info,parameters.pe,frontal_mask,posterior_mask);
                    % Convert and Send to OSC
                    send_permutation_entropy(avg_pe_frontal,avg_pe_posterior,osc);
                    % Saving
                    parsave(pe_directory,"avg_pe_frontal_"+num2str(index),avg_pe_frontal);
                    parsave(pe_directory,"avg_pe_posterior_"+num2str(index),avg_pe_posterior);
                    pe_data = [];
               end
            end
        else
            disp("Waiting " + num2str(sleep_delay) + " sec for " + num2str(index)); 
            pause(sleep_delay); % wait for a bit that the data is available
        end
    end
end
