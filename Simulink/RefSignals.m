
%%---------------------------------------------------------------------------

  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Global declarations
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  %% section 4.4: OFDM frame structure (pp. 24)
  DVBT_SETTINGS.ofdm_mode = 2048;
  DVBT_SETTINGS.payload_carriers = 1512;  
  DVBT_SETTINGS.used_carriers = 1705;
  DVBT_SETTINGS.symbols_per_frame = 68;
  DVBT_SETTINGS.frames_per_superframe = 4; 
  
  DVBT_SETTINGS.ofdm.carrier_count = DVBT_SETTINGS.used_carriers;
  
  
  %% Part 8: Reference Signals
  %% See ETSI EN 300 744, section 4.5, pp. 26
  DVBT_SETTINGS.refsig = {};
  %% Normalization factor for data symbols (Table 6, p. 26)
  DVBT_SETTINGS.refsig.alpha = 1/sqrt(10);
  %% section 4.5.2: PRBS as reference sequence (pp.26)
  DVBT_SETTINGS.refsig.w = zeros(1,DVBT_SETTINGS.used_carriers);
  reg = ones(1,11);
  for k = 1:DVBT_SETTINGS.used_carriers
    DVBT_SETTINGS.refsig.w(k) = reg(11);
    %disp(DVBT_SETTINGS.refsig.w(k));
    new_bit = xor (reg(9), reg(11));
    reg = [ new_bit reg(1:10) ];
  end
  %% section 4.5.3: scattered pilot cells (p. 27)
  DVBT_SETTINGS.refsig.scattered_pilots_period = 4;
  %% section 4.5.4: continual pilot cells (Table 7, p. 28)
  DVBT_SETTINGS.refsig.continual_pilots = ...
      [ 0 48 54 87 141 156 192 201 255 279 282 333 432 450 ...
       483 525 531 618 636 714 759 765 780 804 873 888 918 ...
       939 942 969 984 1050 1101 1107 1110 1137 1140 1146 ...
       1206 1269 1323 1377 1491 1683 1704];
  %% section 4.6: transmission parameter signaling (TPS)
  %% (Table 8, p. 29)
  DVBT_SETTINGS.refsig.tps = ...
      [34 50 209 346 413 569 595 688 790 901 ...
       1073 1219 1262 1286 1469 1594 1687];
  

  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Abbreviations
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  n = 1512; %DVBT_SETTINGS.symbol_length.payload;

  l=l+1;
  if l >= 68
        disp('68 packets sent...');
        l=0;
  end
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Perform actions
  data_out = zeros(DVBT_SETTINGS.ofdm.carrier_count, 1);

  % create a set of pilots
  Kmin=0;
  Kmax=DVBT_SETTINGS.ofdm.carrier_count;
  pilot_set = union (DVBT_SETTINGS.refsig.continual_pilots, ...
                     Kmin + 3*rem(l,4) + ...
		     12*(0:(DVBT_SETTINGS.ofdm.carrier_count-12)/12));

  % Insert TPS symbols
  tps_set=DVBT_SETTINGS.refsig.tps;

  % merge data and pilots
  v=1; % current input payload carrier index
  pilot=1; % current pilot index in pilot_set
  tps=1; % current tps index in tps_set
  for u = 1:DVBT_SETTINGS.ofdm.carrier_count % for all output carriers
    p = 1+pilot_set(pilot); % get next pilot
    if tps <= length(tps_set) % get next tps
      t = 1+tps_set(tps); 
    else
      t = 0;
    end
    
    if u == p % it's a pilot signal
      data_out(u) = 4/3 * 2 * (0.5 - DVBT_SETTINGS.refsig.w(p));
      pilot = pilot + 1;
    elseif u == t; % it's a TPS signal
      data_out(u) = 2 * (0.5 - DVBT_SETTINGS.refsig.w(p));
      tps = tps + 1;
    else % it's a payload carrier
      data_out(u) = DVBT_SETTINGS.refsig.alpha * data_in(v);
      v = v + 1;
    end
  end
  assert (v == DVBT_SETTINGS.payload_carriers+1, 'insert_reference_signals', ...
	  sprintf ('payload carriers: %d expected, %d found', ...
		   DVBT_SETTINGS.payload_carriers, v-1));
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


