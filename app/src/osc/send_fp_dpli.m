function send_fp_dpli(dpli,osc)
%SEND_FP_DPLI send to the osc receivers the data in string format
%   Input:
%       avg_dpli_midline: singular value representing the average pli for
%       the midline channels
%       avg_dpli_lateral: singular value representing the average pli for
%       the lateral channels
%       osc: osc data structure

    %% Create the OSC String
    osc_base = '/fp_dpli';
    dpli_midline_lateral = [dpli.left_midline, dpli.left_lateral, dpli.right_midline, dpli.right_lateral];
    osc_type = get_osc_message_type(dpli_midline_lateral);
    
    %% Sending OSC
    % Send osc data one osc receiver at a time
    number_osc_receivers = length(osc.path);
    for osc_index = 1:number_osc_receivers
        % Create a connection to the OSC receivers
        u = udp(osc.ip{osc_index},str2num(osc.port{osc_index}));
        %increase the buffer size (input and output)
        u.InputBufferSize = 3200;
        u.OutputBufferSize = 3200;
        
        % Sending the messages to the OSC receivers
        fopen(u);
        
        %% Sending dpli midline lateral
        oscsend(u,osc_base,osc_type,dpli_midline_lateral);    
        
        fclose(u);
    end    
end

