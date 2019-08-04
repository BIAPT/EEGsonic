% ampon.m:
% This function powers up the selected amplifier, and must be called before
% starting the amplifer.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampon

ampsrvinit;

success = ampsrv(amppoweron);

return
