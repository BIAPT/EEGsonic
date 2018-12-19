function send_permutation_entropy(avg_pe_frontal,avg_pe_parietal,osc)
%SEND_PERMUTATION_ENTROPY send to the osc receivers the data in string
%format
%   Input:
%       avg_pe_frontal: singular value representing the average pe for the
%       frontal region
%       avg_pe_parietal: singular value representing the average pe for the
%       parietal region
%       osc: osc data structure

   %% Create the OSC String
    osc_base = '/permutation_entropy_frontal_and_parietal';
    pe_frontal_parietal = [avg_pe_frontal,avg_pe_parietal];
    osc_type = get_osc_message_type(pe_frontal_parietal);
    
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
        
        %% Sending PE frontal parietal
        oscsend(u,osc_base,osc_type,pe_frontal_parietal);  
        
        fclose(u);
    end    
end

