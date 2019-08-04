% ampstart.m:
% This function starts the amp, and must be called before
% trying to collect data.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampstart

ampsrvinit;

success = ampsrv(ampacqstart);

return
