% ampapplyscalingfactor.m:
% This function sets whether or not to apply the scaling factor appropriate for the amplifer
% prior to delivering data to the MATLAB environment. Typically you will want to do this and as such,
% this is on by default.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampapplyscalingfactor( apply )

ampsrvinit;

success = 0; % No return for this function.
ampsrv( applyscalingfactor, apply );

return
