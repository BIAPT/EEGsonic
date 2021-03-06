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
            alpha_bandwith = app.SPRAlphaBandwithEditField.Value;
            beta_bandwith = app.SPRBetaBandwithEditField.Value;
            required_size = app.SPRRequiredSizeEditField.Value;
            [is_valid,reason] = check_spr(window_size,step_size,time_bandwith_product,number_tapers, ...
                                theta_bandwith,alpha_bandwith,beta_bandwith,required_size);
        case 'td'
           required_size = app.TDRequiredSizeEditField.Value;
           frequency = app.TDFrequencyEditField.Value;
           [is_valid,reason] = check_td(required_size,frequency);
        case 'pac'
            required_size = app.PACRequiredSizeEditField.Value;
            channels = app.PACChannelsListBox.Value;
            extra_low_frequency = app.PACExtraLowFrequencyBandwithEditField.Value;
            high_frequency = app.PACHighFrequencyBandwithEditField.Value;
            [is_valid,reason] = check_pac(required_size,channels,extra_low_frequency,high_frequency);
        case 'fp_wpli'
            required_size = app.FPwPLIRequiredSizeEditField.Value;
            channels = app.FPwPLIChannelsListBox.Value;
            number_surrogates = app.FPwPLINumberSurrogatesEditField.Value;
            p_value = app.FPwPLIPValueEditField.Value;
            [is_valid,reason] = check_pli(required_size,channels,number_surrogates,p_value)  ;          
        case 'fp_dpli'
            required_size = app.FPdPLIRequiredSizeEditField.Value;
            channels = app.FPdPLIChannelsListBox.Value;
            number_surrogates = app.FPdPLINumberSurrogatesEditField.Value;
            p_value = app.FPdPLIPValueEditField.Value;
            [is_valid,reason] = check_pli(required_size,channels,number_surrogates,p_value);            
        case 'hl'
            required_size = app.HLRequiredSizeEditField.Value;
            number_surrogates = app.HLNumberSurrogatesEditField.Value;
            p_value = app.HLPValueEditField.Value;
            top_connection_threshold = app.HLTopConnectionThresholdEditField.Value;
            [is_valid,reason] = check_hub_location(required_size,number_surrogates,p_value,...
                                top_connection_threshold);            
        case 'pe'
            required_size = app.PERequiredSizeEditField.Value;
            channels = app.PEChannelsListBox.Value;
            embedding_dimension = app.PEEmbeddingDimensionEditField.Value;
            time_delay = app.PETimeDelayEditField.Value;
            [is_valid,reason] = check_permutation_entropy(required_size,channels,embedding_dimension,time_delay);            
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
                             theta_bandwith,alpha_bandwith,beta_bandwith,averaging_size)
    is_valid = 1;
    reason = "";
        
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
    
    %% Theta Bandwith
    [is_valid,theta_reason] = check_bandwith(is_valid,theta_bandwith,"Theta");
    reason = reason + theta_reason;
        
    %% Alpha Bandwith
    [is_valid,alpha_reason] = check_bandwith(is_valid,alpha_bandwith,"Alpha"); 
    reason = reason + alpha_reason;
    
    %% Beta Bandwith
    [is_valid,beta_reason] = check_bandwith(is_valid,beta_bandwith,"Beta");  
    reason = reason + beta_reason;
    
end

function [is_valid,reason] = check_td(window_size,frequency)
    is_valid = 1;
    reason = "";
end

function [is_valid,reason] = check_pac(window_size,channels,extra_low_frequency,high_frequency)
    is_valid = 1;
    reason = "";
    
    %% Frontal Channels
    if(isempty(channels))
        is_valid = 0;
        reason = reason + "No channels were selected. ";
    end
    
    %% Extra Low Frequency
    [is_valid,extra_low_reason] = check_bandwith(is_valid,extra_low_frequency,"Extra Low Frequency");
    reason = reason + extra_low_reason;
    
    %% High Frequency
    [is_valid,high_reason] = check_bandwith(is_valid,high_frequency,"High Frequency");
    reason = reason + high_reason;
    
end

function [is_valid,reason] = check_pli(window_size,channels,number_surrogates,p_value)
   is_valid = 1;
   reason = "";
   
   %% Channels
   if(isempty(channels))
      is_valid = 0;
      reason = reason + "No channels were selected. ";
   end
end

function [is_valid,reason] = check_hub_location(window_size,number_surrogates,p_value,top_connection_threshold)
    is_valid = 1;
    reason = "";
    
end

function [is_valid,reason] = check_permutation_entropy(window_size,channels,embedding_dimension,time_delay)
    is_valid = 1;
    reason = "";
    
    %% Channels
    if(isempty(channels))
        is_valid = 0;
        reason = reason + "No channels were selected. ";
    end    
end


%% Helper Checkers
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