function [hd,n] = ideal_lp(wc,N)

a = (N-1) / 2;
m = [0 : 1 : (N-1) ];
n = m - a + eps;                   
                                   
hd = sin(wc*n) ./ (pi*n);
