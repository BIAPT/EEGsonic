function send_fp_wpli(avg_pli_midline,avg_pli_lateral,osc)
%SEND_FP_WPLI send to the osc receivers the data in string format
%   Input:
%       avg_pli_midline: singular value representing the average pli for
%       the midline channels
%       avg_pli_lateral: singular value representing the average pli for
%       the lateral channels
%       osc: osc data structure

    %% Create the OSC String
    osc_base_string = "/fp_wpli_midline_lateral";
    avg_pli_midline_osc = osc_base_string + "avg_pli_midline " + num2str(avg_pli_midline);
    avg_pli_lateral_osc = osc_base_string + "avg_pli_lateral " + num2str(avg_pli_lateral);
    
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
        
        %% Sending avg pli midline
        for string_index = 1:length(avg_pli_midline_osc)
            current_osc_message = strsplit(avg_pli_midline_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        %% Sending avg pli lateral 
        for string_index = 1:length(avg_pli_lateral_osc)
            current_osc_message = strsplit(avg_pli_lateral_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        fclose(u);
    end    
end
