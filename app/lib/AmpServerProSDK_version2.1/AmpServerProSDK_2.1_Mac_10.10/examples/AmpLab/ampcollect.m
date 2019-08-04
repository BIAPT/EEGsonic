% ampcollect.m:
% This function collects the specified number of samples from the amplifier.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [data] = ampcollect( numsamples )

ampsrvinit;

data = ampsrv( ampacquire, numsamples );

return
