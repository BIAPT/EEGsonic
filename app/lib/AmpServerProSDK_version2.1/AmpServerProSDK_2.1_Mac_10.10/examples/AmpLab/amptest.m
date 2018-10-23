% ampinit.m:
% This function is simply a test showing how to add to the MATLAB layer.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = amptest(longarg)

ampsrvinit;

success = 0; % no error code for power on
ampsrv(test,longarg);

return
