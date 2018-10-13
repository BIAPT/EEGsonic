function [fixed_name] = fix_name(name)
% FIX NAME will fix a name to be a string
%   Input:
%       name: could be any type of names (int,double,string)
%   Output:
%       fixed_name: string of name

    %% Setting up variables
    fixed_name = name;
    % if the name is numeric then we convert to a string
    if(isnumeric(name))
       fixed_name = num2str(name); 
    end

end