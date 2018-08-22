function [is_valid,reason] = is_input_valid(app,type)
%IS_INPUT_VALID Check if the input entered by the user is valid
    is_valid = 1;
    reason = '';
    
    switch type
        case 'osc'
            path = app.PathEditField.Value;
            ip = app.IPAddressEditField.Value;
            port = app.PortEditField.Value;
            [is_valid,reason] = check_osc_receiver(path,ip,port);
        case 'spr'
            window_size = app.SPRWindowSizeEditField.Value;
            time_bandwith_product = app.SPRTimeBandwithProductEditField.Value;
            number_tapers = app.SPRNumberTapersEditField.Value;
            theta_bandwith = app.SPRThetaBandwithEditField.Value;
            is_theta = app.SPRThetaBandwithCheckBox.Value;
            alpha_bandwith = app.SPRAlphaBandwithEditField.Value;
            is_alpha = app.SPRAlphaBandwithCheckBox.Value;
            beta_bandwith = app.SPRBetaBandwithEditField.Value;
            is_beta = app.SPRBetaBandwithCheckBox.Value;
            averaging_size = app.SPRAveragingSizeEditField.Value;
            [is_valid,reason] = check_spr(window_size,time_bandwith_product,number_tapers, ...
                                theta_bandwith,is_theta,alpha_bandwith,is_alpha,beta_bandwith,...
                                is_beta,averaging_size);
        case 'td'
           window_size = app.TDWindowSizeEditField.Value;
           frequency = app.TDFrequencyEditField.Value;
           [is_valid,reason] = check_td(window_size,frequency);
        case 'pac'
            window_size = app.PACWindowSizeEditField.Value;
            frontal_channels = app.PACFrontalChannelsListBox.Value;
            parietal_channels = app.PACParietalChannelsListBox.Value;
            extra_low_frequency = app.PACExtraLowFrequencyBandwithEditField.Value;
            high_frequency = app.PACHighFrequencyBandwithEditField.Value;
            [is_valid,reason] = check_pac(window_size,frontal_channels,parietal_channels,...
                                extra_low_frequency,high_frequency);
        case 'fp_wpli'
            
            [is_valid,reason] = check_fp_wpli(window_size,midline_channels,lateral_channels,...
                                number_surrogates,p_value)            
        case 'fp_dpli'
            
        case 'hl'
            
        case 'pe'
    end

end

function [is_valid,reason] = check_osc_receiver(path,ip,port)
    is_valid = 1;
    reason = "";
    %% PATH 
    %(Not sure what to check, empty for now)
    is_empty = path == "";
    if(is_empty)
       is_valid = 0;
       reason = reason + "Path is empty. ";
    end
    %% IP (Must contain numbers and dots)
    
    is_dot = ~isempty(strfind(ip,'.'));
    if(is_dot == 0)
       is_valid = 0; 
       reason = reason + "IP contains no dots. ";
    end
    is_number =  all(ismember(erase(ip,'.'),'0123456789'));
    if(is_number == 0)
        is_valid = 0;
        reason = reason + "IP contains an illegal character. ";
    end
    %% PORT (Must contain only numbers)
    % TODO Could also list the ports and check if right one choosen.
    is_number = all(ismember(port,'0123456789'));
    if(is_number == 0)
       is_valid = 0;
       reason = reason + "Port contains an illegal character. ";
    end
end

function [is_valid,reason] = check_spr(window_size,time_bandwith_product,number_tapers, ...
                             theta_bandwith,is_theta,alpha_bandwith,is_alpha,beta_bandwith,...
                             is_beta,averaging_size)
    is_valid = 1;
    reason = "";
    
    % For most of the variable we don't need to check for ridiculous inputs
    % as the application already take care of that
    
    %% Window Size and Averaging Size
    if(averaging_size < window_size)
       is_valid = 0;
       reason = reason + "Window size is longer than the averaging size. ";
    end
    
    %% Theta Bandwith
    if(is_theta)
        [is_valid,theta_reason] = check_bandwith(is_valid,theta_bandwith,"Theta");
        reason = reason + theta_reason;
    end
    
    %% Alpha Bandwith
    if(is_alpha)
        [is_valid,alpha_reason] = check_bandwith(is_valid,alpha_bandwith,"Alpha"); 
        reason = reason + alpha_reason;
    end
    
    %% Beta Bandwith
    if(is_beta)
        [is_valid,beta_reason] = check_bandwith(is_valid,beta_bandwith,"Beta");  
        reason = reason + beta_reason;
    end
    

end

function [is_valid,reason] = check_td(window_size,frequency)
    is_valid = 1;
    reason = "";
    
    % TODO Add possible error over here (some are already handled by the
    % app GUI.
end

function [is_valid,reason] = check_pac(window_size,frontal_channels,parietal_channels,...
                             extra_low_frequency,high_frequency)
    is_valid = 1;
    reason = "";
    
    %% Frontal Channels
    if(isempty(frontal_channels))
        is_valid = 0;
        reason = reason + "No frontal channels were selected. ";
    end
    %% Parietal Channels
    if(isempty(parietal_channels))
        is_valid = 0;
        reason = reason + "No parietal channels were selected. ";        
    end
    %% Extra Low Frequency
    [is_valid,extra_low_reason] = check_bandwith(is_valid,extra_low_frequency,"Extra Low Frequency");
    reason = reason + extra_low_reason;
    %% High Frequency
    [is_valid,high_reason] = check_bandwith(is_valid,high_frequency,"High Frequency");
    reason = reason + high_reason;
end

function [is_valid,reason] = check_fp_wpli(window_size,midline_channels,lateral_channels,...
                             number_surrogates,p_value)
   is_valid = 1;
   reason = "";
   
   %% Midline Channels
   if(isempty(midline_channels))
      is_valid = 0;
      reason = reason + "No midline channels were selected. ";
   end
   
   %% Lateral Channels
   if(isempty(lateral_channels))
       is_valid = 0;
       reason = reason + "No lateral channels were selected. ";
   end
   %% Number of Surrogates
   max_number = 20; %Need to be setted, but more than 20 is way too much
   if(number_surrogates > max_number)
      is_valid = 0;
      reason = reason + "Number of surrogate exceed a reasonable value: " + num2str(number_surrogates) + " > " + max_number + ". ";
   end
   
end

function [is_valid,reason] = check_bandwith(is_valid,bandwith,type)
    reason = "";
    bandwith = erase(bandwith,'[');
    bandwith = erase(bandwith,']');
    bandwith = str2double(strsplit(bandwith,{',',' '}));
    if(length(bandwith) ~= 2)
       is_valid = 0;
       reason = reason + type + " Bandwith is malformated: require [x,y]. ";
    else
        if(bandwith(1) >= bandwith(2))
           is_valid = 0;
           reason = reason + type+" Bandwith first value is greater than the second. ";
        end
    end
end