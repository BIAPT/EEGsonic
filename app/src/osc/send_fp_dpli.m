function send_fp_dpli(dpli,osc)
%SEND_FP_DPLI send to the osc receivers the data in string format
%   Input:
%       avg_dpli_midline: singular value representing the average pli for
%       the midline channels
%       avg_dpli_lateral: singular value representing the average pli for
%       the lateral channels
%       osc: osc data structure

    %% Create the OSC String
    osc_base_left_midline = '/fp_dpli_left_midline';
    osc_base_left_lateral = '/fp_dpli_left_lateral';
    osc_base_right_midline = '/fp_dpli_right_midline';
    osc_base_right_lateral = '/fp_dpli_right_lateral';

    osc_type_left_midline = get_osc_message_type(dpli.left_midline);
    osc_type_left_lateral = get_osc_message_type(dpli.left_lateral);
    osc_type_right_midline = get_osc_message_type(dpli.right_midline);
    osc_type_right_lateral = get_osc_message_type(dpli.right_lateral);
    
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
        oscsend(u,osc_base_left_midline,osc_type_left_midline,dpli.left_midline);
        oscsend(u,osc_base_left_lateral,osc_type_left_lateral,dpli.left_lateral);
        oscsend(u,osc_base_right_midline,osc_type_right_midline,dpli.right_midline);
        oscsend(u,osc_base_right_lateral,osc_type_right_lateral,dpli.right_lateral);
        
        fclose(u);
    end    
end

