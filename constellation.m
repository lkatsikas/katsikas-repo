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
    1   17  21   5   4  20  16   0;...
    33  49  53  37  36  52  48  32;... 
    41  57  61  45  44  60  56  40;... 
     9  25  29  13  12  28  24   8;... 
    11  27  31  15  14  30  26  10;... 
    43  59  63  47  46  62  58  42;... 
    35  51  55  39  38  54  50  34;... 
     3  19  23   7   6  22  18   2 ...
               ];
           