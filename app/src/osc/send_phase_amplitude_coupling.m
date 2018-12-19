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
    osc_base = '/phase_amplitude_coupling_frontal_and_parietal';
    rpt_frontal_parietal = [rpt_frontal,rpt_parietal];
    osc_type = get_osc_message_type(rpt_frontal_parietal);
    
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
        
        %% Sending rpt frontal and parietal
        oscsend(u,osc_base,osc_type,rpt_frontal_parietal);    
        
        fclose(u);
    end    
end

