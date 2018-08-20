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
                                is_beta,averaging_size)
        case 'td'
           window_size = app.TDWindowSizeEditField.Value;
           frequency = app.TDFrequencyEditField.Value;
           [is_valid,reason] = check_td(window_size,frequency);
        case 'pac'
            
        case 'fp_wpli'
            
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
        [is_valid,reason] = check_bandwith(is_valid,theta_bandwith,"Theta");
    end
    
    %% Alpha Bandwith
    if(is_alpha)
        [is_valid,reason] = check_bandwith(is_valid,alpha_bandwith,"Alpha");        
    end
    
    %% Beta Bandwith
    if(is_beta)
        [is_valid,reason] = check_bandwith(is_valid,beta_bandwith,"Beta");        
    end
    

end

function [is_valid,reason] = check_td(window_size,frequency)
    is_valid = 1;
    reason = "";
    
    % TODO Add possible error over here (some are already handled by the
    % app GUI.
end

function [is_valid,reason] = check_bandwith(is_valid,bandwith,type)
    reason = "";
    bandwith = erase(bandwith,'[');
    bandwith = erase(bandwith,']');
    bandwith = str2double(strsplit(bandwith,{',',' '}));
    if(length(bandwith) ~= 2)
       is_valid = 0;
       reason = reason + type + " Bandwith is malformated: require [x,y]. "
    else
        if(bandwith(1) >= bandwith(2))
           is_valid = 0;
           reason = reason + type+" Bandwith first value is greater than the second. ";
        end
    end
end