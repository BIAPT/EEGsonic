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
    osc_base_string = "/permutation_entropy/";
    avg_pe_frontal_osc = osc_base_string + "avg_pe_frontal " + num2str(avg_pe_frontal);
    avg_pe_parietal_osc = osc_base_string + "avg_pe_parietal " + num2str(avg_pe_parietal);
    
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
        
        %% Sending avg_pe_frontal
        for string_index = 1:length(avg_pe_frontal_osc)
            current_osc_message = strsplit(avg_pe_frontal_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        %% Sending avg_pe_parietal
        for string_index = 1:length(avg_pe_parietal_osc)
            current_osc_message = strsplit(avg_pe_parietal_osc(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            value_osc_message = str2double(current_osc_message(2));
            oscsend(u,base_osc_message,'f',value_osc_message);    
        end
        
        fclose(u);
    end    
end

