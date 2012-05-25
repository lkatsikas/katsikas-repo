
  Tsample = 9;
  VAR = {};
  used_carriers = 1705;

  %% Part 8: Reference Signals
  %% See ETSI EN 300 744, section 4.5, pp. 26
  
  %% section 4.5.2: PRBS as reference sequence (pp.26)
  VAR.w = zeros(1,used_carriers);
  reg = ones(1,11);
  for k = 1:used_carriers
    VAR.w(k) = reg(11);
    %disp(w(k));
    new_bit = xor (reg(9), reg(11));
    reg = [ new_bit reg(1:10) ];
  end
  %% section 4.5.3: scattered pilot cells (p. 27)
  %% section 4.5.4: continual pilot cells (Table 7, p. 28)
  VAR.continual_pilots = ...
      [ 0 48 54 87 141 156 192 201 255 279 282 333 432 450 ...
       483 525 531 618 636 714 759 765 780 804 873 888 918 ...
       939 942 969 984 1050 1101 1107 1110 1137 1140 1146 ...
       1206 1269 1323 1377 1491 1683 1704];
  %% section 4.6: transmission parameter signaling (TPS)
  %% (Table 8, p. 29)
  VAR.tps_signals = ...
      [34 50 209 346 413 569 595 688 790 901 ...
       1073 1219 1262 1286 1469 1594 1687];
   
   for l=0:67
    Kmin = 0;
    VAR.scattered_set = Kmin + 3*rem(l,4) + 12*(0:(used_carriers-12)/12);
    VAR.pilot_set(:,l+1) = union(VAR.continual_pilots,VAR.scattered_set);
   end
   
   %% Adding 1/4 cyclic prefix for Transmitter
   VAR.CyclicPrefixTX = [2048-[(2048/4)-1:-1:0] 1:2048];
   
   %% Adding 1/4 cyclic prefix for Receiver
   VAR.CyclicPrefixRX = [(2048/4)+1:(2048+512)];
   