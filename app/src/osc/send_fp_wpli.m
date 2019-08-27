function send_fp_wpli(wpli,osc)
%SEND_FP_WPLI send to the osc receivers the data in string format
%   Input:
%       avg_pli_midline: singular value representing the average pli for
%       the midline channels
%       avg_pli_lateral: singular value representing the average pli for
%       the lateral channels
%       osc: osc data structure

    %% Create the OSC String
    osc_base_left_midline = '/fp_wpli_left_midline';
    osc_base_left_lateral = '/fp_wpli_left_lateral';
    osc_base_right_midline = '/fp_wpli_right_midline';
    osc_base_right_lateral = '/fp_wpli_right_lateral';
    
    osc_type_left_midline = get_osc_message_type(wpli.left_midline);
    osc_type_left_lateral = get_osc_message_type(wpli.left_lateral);
    osc_type_right_midline = get_osc_message_type(wpli.right_midline);
    osc_type_right_lateral = get_osc_message_type(wpli.right_lateral);
    
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
        
        %% Sending PLI midline and lateral
        oscsend(u,osc_base_left_midline,osc_type_left_midline,wpli.left_midline);
        oscsend(u,osc_base_left_lateral,osc_type_left_lateral,wpli.left_lateral);
        oscsend(u,osc_base_right_midline,osc_type_right_midline,wpli.right_midline);
        oscsend(u,osc_base_right_lateral,osc_type_right_lateral,wpli.right_lateral);
        
        fclose(u);
    end    
end

