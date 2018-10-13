function [is_valid,reason] = is_input_valid(app,type)
%IS_INPUT_VALID Check if the inputs entered by the user in the GUI are valid
%   Input:
%       app: data structure containing the whole app data
%       type: type of analysis technique to check
%   Output:
%       is_valid: boolean, true means valid and false means input non valid
%       reason: reason for not being valid ("" if valid)

    %% Setting up variables
    is_valid = 1;
    reason = '';
    
    %% Decide which analysis technique to check
    switch type
        % All the case work the same: they extract the data out of the app
        % and give them to a function that will check the given
        case 'osc'
            path = app.PathEditField.Value;
            ip = app.IPAddressEditField.Value;
            port = app.PortEditField.Value;
            [is_valid,reason] = check_osc_receiver(path,ip,port);
        case 'spr'
            window_size = app.SPRWindowSizeEditField.Value;
            step_size = app.SPRStepSizeEditField.Value;
            time_bandwith_product = app.SPRTimeBandwithProductEditField.Value;
            number_tapers = app.SPRNumberTapersEditField.Value;
            theta_bandwith = app.SPRThetaBandwithEditField.Value;
            is_theta = app.SPRThetaBandwithCheckBox.Value;
            alpha_bandwith = app.SPRAlphaBandwithEditField.Value;
            is_alpha = app.SPRAlphaBandwithCheckBox.Value;
            beta_bandwith = app.SPRBetaBandwithEditField.Value;
            is_beta = app.SPRBetaBandwithCheckBox.Value;
            required_size = app.SPRRequiredSizeEditField.Value;
            [is_valid,reason] = check_spr(window_size,step_size,time_bandwith_product,number_tapers, ...
                                theta_bandwith,is_theta,alpha_bandwith,is_alpha,beta_bandwith,...
                                is_beta,required_size);
        case 'td'
           required_size = app.TDRequiredSizeEditField.Value;
           frequency = app.TDFrequencyEditField.Value;
           [is_valid,reason] = check_td(required_size,frequency);
        case 'pac'
            required_size = app.PACRequiredSizeEditField.Value;
            frontal_channels = app.PACFrontalChannelsListBox.Value;
            parietal_channels = app.PACParietalChannelsListBox.Value;
            extra_low_frequency = app.PACExtraLowFrequencyBandwithEditField.Value;
            high_frequency = app.PACHighFrequencyBandwithEditField.Value;
            [is_valid,reason] = check_pac(required_size,frontal_channels,parietal_channels,...
                                extra_low_frequency,high_frequency);
        case 'fp_wpli'
            required_size = app.FPwPLIRequiredSizeEditField.Value;
            midline_channels = app.FPwPLIMidlineChannelsListBox.Value;
            lateral_channels = app.FPwPLILateralChannelsListBox.Value;
            number_surrogates = app.FPwPLINumberSurrogatesEditField.Value;
            p_value = app.FPwPLIPValueEditField.Value;
            [is_valid,reason] = check_pli(required_size,midline_channels,lateral_channels,...
                                number_surrogates,p_value)  ;          
        case 'fp_dpli'
            required_size = app.FPdPLIRequiredSizeEditField.Value;
            midline_channels = app.FPdPLIMidlineChannelsListBox.Value;
            lateral_channels = app.FPdPLILateralChannelsListBox.Value;
            number_surrogates = app.FPdPLINumberSurrogatesEditField.Value;
            p_value = app.FPdPLIPValueEditField.Value;
            [is_valid,reason] = check_pli(required_size,midline_channels,lateral_channels,...
                                number_surrogates,p_value);            
        case 'hl'
            required_size = app.HLRequiredSizeEditField.Value;
            number_surrogates = app.HLNumberSurrogatesEditField.Value;
            p_value = app.HLPValueEditField.Value;
            top_connection_threshold = app.HLTopConnectionThresholdEditField.Value;
            [is_valid,reason] = check_hub_location(required_size,number_surrogates,p_value,...
                                top_connection_threshold);            
        case 'pe'
            required_size = app.PERequiredSizeEditField.Value;
            frontal_channels = app.PEFrontalChannelsListBox.Value;
            posterior_channels = app.PEPosteriorChannelsListBox.Value;
            embedding_dimension = app.PEEmbeddingDimensionEditField.Value;
            time_delay = app.PETimeDelayEditField.Value;
            [is_valid,reason] = check_permutation_entropy(required_size,frontal_channels,...
                                posterior_channels,embedding_dimension,time_delay);            
    end

end

%% Checker function
%  All checker function work the same way: receive input from the main
%  function and return is_valid and the reason for not being valid.
%  The functions contains a series of check and if something doesn't work
%  then it will concatenate the reason to the reason variables
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

function [is_valid,reason] = check_spr(window_size,step_size,time_bandwith_product,number_tapers, ...
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
    
    %% Step Size
    if(step_size >= window_size)
       is_valid = 0;
       reason = reason + "Step size is longer than the window size. ";
    end
    
    %% Bandpass
    if(~is_theta || ~is_alpha || ~is_beta)
       is_valid = 0;
       reason = reason + "Theta, alpha or beta bandpass isn't selected. ";
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

function [is_valid,reason] = check_pli(window_size,midline_channels,lateral_channels,...
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
   
end

function [is_valid,reason] = check_hub_location(window_size,number_surrogates,p_value,...
                             top_connection_threshold)
    is_valid = 1;
    reason = "";
    
    % TODO Add possible error over here (some are already handled by the
    % app GUI.

end

function [is_valid,reason] = check_permutation_entropy(window_size,frontal_channels,...
                             posterior_channels,embedding_dimension,time_delay)
    is_valid = 1;
    reason = "";
    
    %% Frontal Channels
    if(isempty(frontal_channels))
        is_valid = 0;
        reason = reason + "No frontal channels were selected. ";
    end    
    %% Posterior Channels
    if(isempty(posterior_channels))
        is_valid = 0;
        reason = reason + "No posterior channels were selected. ";
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