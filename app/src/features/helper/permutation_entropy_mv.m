function [pe, pen]=permutation_entropy_mv(data, m, L)
% permutation entropy for multivariate signals (just a repetition of calculation for multi-channel signals)
% 2018.1.19. Heonsoo Lee

% Input:
%   data: each column must be a time series
%   m: embedding dimension, or pattern size
%   L: time lag
%
% Output:
%   pe: (unnormalized) permutation entropy
%   pen: normalized permutation entropy

%% TODO refactor this to be a bit more readable

numpat=factorial(m); % number of patterns
denom=log2(numpat); % normalization factor
Ddata=delay_reconstruction(data, L, m); % delay reconstruction
for c=1:size(data,2)
    %% real value -> symoblic pattern
    udata=zeros(size(Ddata(:,:,c),1), 1);
    [~, Ddata_sort]=sort(Ddata(:,:,c),2);
    for i=1:m
        udata=udata+Ddata_sort(:,i)*10^(round(m/2)-i)'; % *** double precision: 10^-16
    end
    %% probability
    [u_patterns, ~]=unique(udata); % find unique patterns
    u_len=length(u_patterns); % # of unique patterns
    p=zeros(1, numpat);
    for u=1:u_len
        ind=find(udata==u_patterns(u));
        p(u)=length(ind)/size(udata,1);
    end
    pe(1,c)=-sum(p.*log2(p+eps));clear p;
    pen(1,c)=pe(c)./denom;
end




