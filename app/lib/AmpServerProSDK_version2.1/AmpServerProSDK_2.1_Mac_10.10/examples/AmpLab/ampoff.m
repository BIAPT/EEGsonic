% ampoff.m:
% This function turns off the amplifier. Note, for an NA400,
% this does not actually turn off the amplifier.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampoff

ampsrvinit;

success = ampsrv(amppoweroff);

return
