

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








