% Reading the values from Figure 9a
map_constellation = [ 7 + 7i
            -7 + 7i
             7 - 7i
            -7 - 7i
             1 + 7i
            -1 + 7i
             1 - 7i
            -1 - 7i
             7 + 1i
            -7 + 1i
             7 - 1i
            -7 - 1i
             1 + 1i
            -1 + 1i
             1 - 1i
            -1 - 1i
             5 + 7i
            -5 + 7i
             5 - 7i
            -5 - 7i
             3 + 7i
            -3 + 7i
             3 - 7i
            -3 - 7i
             5 + 1i
            -5 + 1i
             5 - 1i
            -5 - 1i
             3 + 1i
            -3 + 1i
             3 - 1i
            -3 - 1i
             7 + 5i
            -7 + 5i
             7 - 5i
            -7 - 5i
             1 + 5i
            -1 + 5i
             1 - 5i
            -1 - 5i
             7 + 3i
            -7 + 3i
             7 - 3i
            -7 - 3i
             1 + 3i
            -1 + 3i
             1 - 3i
            -1 - 3i
             5 + 5i
            -5 + 5i
             5 - 5i
            -5 - 5i
             3 + 5i 
            -3 + 5i 
             3 - 5i 
            -3 - 5i 
             5 + 3i
            -5 + 3i
             5 - 3i
            -5 - 3i
             3 + 3i
            -3 + 3i
             3 - 3i
            -3 - 3i ];

% Normalization factor from Section 4.4
map_constellation = map_constellation/sqrt(42);


map_constellation = [ ...
    32   34  42   40   8  10  1   0;...
    33  35  43  41  9  11  3  2;... 
    37  39  47  45  13  15  7  6;... 
     36  38  46  44  12  14  5   4;... 
    52  54  62  60  28  30  22  20;... 
    53  55  63  61  29  31  23  21;... 
    49  51  59  57  25  27  19  17;... 
     48  50  58   56   24  26  18   16 ...
               ];
         
map_constellation = map_constellation(:);