function send_phase_amplitude_coupling(rpt_frontal,rpt_parietal,osc)
%SEND_PHASE_AMPLITUDE_COUPLING send to the osc receivers the data in string
%format
%   Input:
%       rpt_frontal: singular value representing the average ratio peak /
%       through for the frontal region
%       rpt_parietal: singular value representing the average ratio peak /
%       through for the parietal region
%       osc: osc data structure

    %% Create the OSC String
    osc_base_string = "/phase_amplitude_coupling/";
    rpt_frontal_osc = osc_base_string + "rpt_frontal " + num2str(rpt_frontal);
    rpt_parietal_osc = osc_base_string + "rpt_parietal " + num2str(rpt_parietal);
    
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
        
        %% Sending rpt frontal
        for string_index = 1:length(rpt_frontal_osc)
            current_osc_message = strsplit(rpt_frontal_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        %% Sending rpt parietal
        for string_index = 1:length(rpt_parietal_osc)
            current_osc_message = strsplit(rpt_parietal_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        fclose(u);
    end    
end

