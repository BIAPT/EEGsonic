% ampinit.m:
% This function initializes the TCP/IP connection to the amplifer. It must
% be run first before sending other commands.
%
% Copyright (c) 2015, Electrical Geodesics, Inc.

function [success] = ampinit(ipaddress)

ampsrvinit;

success = ampsrv(ampconnect,ipaddress);

return
