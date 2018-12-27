function y=delayRecons(data, L, m)
% INPUT
% data: 2-d matrix (time by channel)
% L: delay time
% m: embedding dimension
%
% OUTPUT: 3-d matrix (time by EMB vector by channel)
% y(1,:,1) = [data(1) data(1+L) data(1+2L) ... data(1+(m-1)L)]
%
% Heonsoo Lee 2011.11.17

%% TODO refactor this to be a bit more readable

[Len,ch]=size(data);

y=zeros(Len-L*(m-1),m,ch);
for c=1:ch
    for j=1:m
        y(:, j, c)=data(1+(j-1)*L:end-(m-j)*L, c);
    end
end

