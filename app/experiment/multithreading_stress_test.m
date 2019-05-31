p = parpool(6); % get the current parallel pool



for i = 1:7
   f(i) = parfeval(p,@inf_loop,0,i); 
end




function inf_loop(fake_data)

    index = 1;
    while(index)
        1+1
    end

end