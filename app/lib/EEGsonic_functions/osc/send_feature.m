function [success] = send_feature(osc_string_list,type,osc)
%SEND_DATA_OSC Summary of this function goes here
%   Detailed explanation goes here

%% NOTE:
% We have to convert from string to character array for the oscsend function
% to work, might have to do with how the authors handled string in their
% code. Everywhere you see char(something) is when I convert to character
% array.

%% TODO:
% If we want to send arrays we need to send them by giving the type as
% 'ffffffffffffff...'
% Then we send our matrix or whatever. Which means that if we want to send
% a matrix we don't need to transform it into a string
    %% Variable Setup
    success = 1;
    number_osc_receivers = length(osc.path);
    type = char(type);
    
    %% Sending OSC
    % Send osc data one osc receiver at a time
    for osc_index = 1:number_osc_receivers
        u = udp(osc.ip{osc_index},str2num(osc.port{osc_index}));
        % Make the buffers bigger than 512 bytes (TODO CHECK IF NEED TO BE
        % CHANGED BASED ON THE INPUT, most likely not)
        u.InputBufferSize = 3200;
        u.OutputBufferSize = 3200;
        %
        fopen(u);
        for string_index = 1:length(osc_string_list)
            current_osc_message = strsplit(osc_string_list(string_index)," ");
            base_osc_message = char(current_osc_message(1));
            if(strcmp(type,'f'))
                value_osc_message = char(str2double(current_osc_message(2)));
            end
            oscsend(u,base_osc_message,type,value_osc_message);    
        end
        fclose(u);
    end
    
    
end


