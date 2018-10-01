function [time] = time_topographic_distribution(information,parameters)
%TIME_ Summary of this function goes here
%   Detailed explanation goes here

    headset = get_headset(information,parameters);
    if(parameters.general.egi129.is_selected)
        number_channels = information.headset.egi129.number_channels;
        data_size = parameters.general.egi129.data_acquisition_size*1000;
        eeg_info = information.headset.egi129;
    elseif(parameters.general.dsi24.is_selected)
        number_channels = information.headset.dsi24.number_channels;
        data_size = parameters.general.dsi24.data_acquisition_size*1000;
        eeg_info = information.headset.dsi24;
    end
    eeg_data = rand(number_channels,data_size);
    osc = parameters.osc;
    % Populate structure of selected_channels (Boolean mask)
    boolean_mask = get_selected_channels(information,parameters);
    
    
    tic;
        frontal_mask = boolean_mask.td.frontal_channels;
        posterior_mask = boolean_mask.td.posterior_channels;
        % Calculate td
        [ratio_front_back] = topographic_distribution(eeg_data,eeg_info,parameters.td,frontal_mask,posterior_mask);
        % Convert and Send to OSC
        send_topographic_distribution(ratio_front_back,osc);
        eeg_data = [];
    time = toc; 

end

