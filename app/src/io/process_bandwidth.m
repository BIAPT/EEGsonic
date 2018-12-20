function bandwidth = process_bandwidth(bandwidth_string)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    
    bandwidth_string = erase(bandwidth_string,'[');
    bandwidth_string = erase(bandwidth_string,']');
    bandwidth = str2double(strsplit(bandwidth_string,{',',' '}));
end

