% ampstop.m:
% This function stops the amp.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampstop

ampsrvinit;

success = ampsrv(ampacqstop);

return
