function [hd,n] = ideal_lp(wc,N)

a = (N-1) / 2;
m = [0 : 1 : (N-1) ];
n = m - a + eps;                   % O mikroteros arithmos diplis akribeias
                                   % pou yparxei.Einai defined ap to MATLAB
hd = sin(wc*n) ./ (pi*n);

% Stin consola dino [hd,n] = ideal_lp(0.25*pi,21) me syxnotita apokopis
% 0.25*pi k 21 deigmata.Ti sxediazo me stem(n,hd).
