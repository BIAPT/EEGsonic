function bandwidth = process_bandwidth(bandwidth_string)
%PROCESS_BANDWIDTH will process the bandwidth string to load it into matrix
%   bandwidth_string: string representing the bandwidth
    
    bandwidth_string = erase(bandwidth_string,'[');
    bandwidth_string = erase(bandwidth_string,']');
    bandwidth = str2double(strsplit(bandwidth_string,{',',' '}));
end

