function [fixed_name] = fix_name(name)
    fixed_name = name;
    if(isnumeric(name))
       fixed_name = num2str(name); 
    end

end