
% Bit Interleaver array according to DVB-T standard
v = 6;
i1 = 1;
i2 = 0;
i3 = 0;
i4 = 0;
i5 = 0;
i6 = 0;

for i=1:756
    if(mod(i,v) == 1)
        out1(i1,1) = i;
        i1 = i1 +1;
    end
    if(mod(i,v) == 2)
        out3(mod(i2+(126-105),126)+1,1) = i;
        i2 = i2 +1;
    end
    if(mod(i,v) == 3)
        out5(mod(i3+(126-21),126)+1,1) = i;
        i3 = i3 +1;
    end
    if(mod(i,v) == 4)
        out2(mod(i4+(126-63),126)+1,1) = i;
        i4 = i4 +1;
    end
    if(mod(i,v) == 5)  
        out4(mod(i5+(126-42),126)+1,1) = i;
        i5 = i5 +1;
    end
    if(mod(i,v) == 0)
        out6(mod(i6+(126-84),126)+1,1) = i;
        i6 = i6 +1;
    end
end

j=1;
for i=1:6:756
    BitInterleaverTable(i,1) = out1(j);
    BitInterleaverTable(i+1,1) = out2(j);
    BitInterleaverTable(i+2,1) = out3(j);
    BitInterleaverTable(i+3,1) = out4(j);
    BitInterleaverTable(i+4,1) = out5(j);
    BitInterleaverTable(i+5,1) = out6(j);
    j=j+1;
end

clear j i1 i2 i3 i4 i5 i6 out1 out2 out3 out4 out5 out6 v;



% Symbol interleaver array according to DVB-T Standard
q = 1;
Mr = zeros(1,2048);
Nr = zeros(1,10);

for i=0:2047
    if i == 2,
      Nr(1) = 1;
    end
    Nsum = Nr(1)*2^4 + Nr(2)*2^3 + Nr(3)*2^9 + Nr(4)*2^6 + Nr(5)*2^2 +...
            Nr(6)*2^8 + Nr(7)*2^1 + Nr(8)*2^5 + Nr(9)*2^7 + Nr(10)*2^0;
    Mr(q) = rem(i,2)*2^10 + Nsum;
    if( Mr(q) < 1512 )
        q = q + 1;
    end
    Nr = [Nr(2:10) xor(Nr(1),Nr(4))];
end

SymbolInterleaverTable = Mr(1:1512)+1;

% Expand table to accommodate 6-bit words
SymbolInterleaverTable = [SymbolInterleaverTable*6-5; 
	                 SymbolInterleaverTable*6-4;
					 SymbolInterleaverTable*6-3;
					 SymbolInterleaverTable*6-2;
					 SymbolInterleaverTable*6-1; 
					 SymbolInterleaverTable*6];

% Flatten matrix into lookup table
SymbolInterleaverTable = SymbolInterleaverTable(:);

clear i q Mr Nr Nsum;









