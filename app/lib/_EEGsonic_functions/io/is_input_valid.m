function [is_valid,reason] = is_input_valid(app,type)
%IS_INPUT_VALID Check if the input entered by the user is valid
%
    is_valid = 1;
    reason = '';
    
    switch type
        case 'osc'
            path = app.PathEditField.Value;
            ip = app.IPAddressEditField.Value;
            port = app.PortEditField.Value;
            [is_valid,reason] = check_osc_receiver(path,ip,port);
        case 'spr'
            
        case 'td'
            
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

