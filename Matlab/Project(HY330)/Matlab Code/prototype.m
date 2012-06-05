% ================================ Project ================================


% ----> Step 1 - Read two .WAV files and note their values.
% Read the first
[m1 d1] = wavfinfo('File1.wav');            % A piece of information ...         
[x1,f1,n1] = wavread('File1.wav');          % Use this function to read. 
%sound(x1);                                     % Listen to this .wav file.

% Read the second
[m2 d2] = wavfinfo('File2.wav');            % A piece of information ...
[x2,f2,n2] = wavread('File2.wav');          % Use this function to read. 
%sound(x2);                                     % Listen to this .wav file.

%fprintf('---------- Initialy ----------\n');
fprintf('f1 = %d \n',f1);
fprintf('f2 = %d \n',f2);
fprintf('n1 = %d \n',n1);
fprintf('n2 = %d \n',n2);

% For each signal x1,x2 -> f = 16kHz and n = 16 bits/sample.

% ----> Step 2 - Use the appropriate types.
% Needed relations.

% fm = f/2
fm1 = f1/2;                               % Average frequency of x1 signal.
fm2 = f2/2;                               % Average frequency of x2 signal.

% fc >> fm
fc1 = 8000;                              % Carrier frequency for x1 signal.
fc2 = 16000;                             % Carrier frequency for x2 signal.

% fmax = fc + fm
fmax1 = fc1 + fm1;
fmax2 = fc2 + fm2;

% fs = 2 * fmax
fs1 = 2 * fmax1;                        % Sampling frequency for x1 signal.
fs2 = 2 * fmax2;                        % Sampling frequency for x2 signal.

fprintf('---------- Finally ----------\n');
fprintf('fm1 = %d \n',fm1);
fprintf('fm2 = %d \n',fm2);
fprintf('fc1 = %d \n',fc1);
fprintf('fc2 = %d \n',fc2);
fprintf('fs1 = %d \n',fs1);
fprintf('fs2 = %d \n',fs2);
fprintf('n1 = %d \n',n1);
fprintf('n2 = %d \n',n2);

% ----> Step 3 - Sample the input signals using sampling frequences 
% fs1,fs2.
wavwrite(x1,fs1,n1,'sampled_sound_87');          % Create the sampled file.
[x1,fs1,n1] = wavread('sampled_sound_87');              
%sound(x1);                                     % Listen to this .wav file.

wavwrite(x2,fs2,n2,'sampled_sound_88');          % Create the sampled file.
[x2,fs2,n2] = wavread('sampled_sound_88');              
%sound(x2);                                     % Listen to this .wav file.

t1 = [0:length(x1)-1] * (1/fs1);                   % Signal 1 in time axis.

figure(1);
plot(t1,x1);
title('Signal 1');
xlabel('Time (sec)');
ylabel('Amplitude');

t2 = [0:length(x2)-1] * (1/fs2);                   % Signal 2 in time axis.

figure(2);
plot(t2,x2);
title('Signal 2');
xlabel('Time (sec)');
ylabel('Amplitude');


% --> Step 4 - Calculate FFT for each signal. 
% Sample using Fast Fourier Transform (FFT).
% Signal 1
X1 = fft(x1);                               % Fast Fourier Transform of x1. 

% Convert to analog freaquency
k_x1 = 0 : length(X1)-1;
w_x1 = (2*k_x1*pi) / length(X1);                     % Digital frequencies.

new_length_x1 = round(length(X1)/2);   
                                                           
new_X1 = X1(1 : new_length_x1);
new_k_x1 = 0 : (new_length_x1-1);
new_w_x1 = (2*new_k_x1*pi)/length(X1);

Tx1 = 1/fs2;
W_x1 = new_w_x1/Tx1;                                  % Analog w (rad/sec).
digital_fs1 = W_x1 / (2*pi*1000);                         % Analog f (KHz).
figure(3);
plot(digital_fs1,abs(new_X1));
title('Signal 1');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

% Signal 2
X2 = fft(x2);                               % Fast Fourier Transform of x2. 

% Convert to analog freaquency
k_x2 = 0 : length(X2)-1;
w_x2 = (2*k_x2*pi) / length(X2);                     % Digital frequencies.

new_length_x2 = round(length(X2)/2);   
                                                           
new_X2 = X2(1 : new_length_x2);
new_k_x2 = 0 : (new_length_x2-1);
new_w_x2 = (2*new_k_x2*pi)/length(X2);

Tx2 = 1/fs2;
W_x2 = new_w_x2/Tx2;                                  % Analog w (rad/sec).
digital_fs2 = W_x2 / (2*pi*1000);                         % Analog f (KHz).
figure(4);
plot(digital_fs2,abs(new_X2));
title('Signal 2');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

x1 = ifft(new_X1);
x2 = ifft(new_X2);

% ----> Step 5 - Create one carrier signal for each modulating one.
% Carrier Signal 1.
c1 = cos(2*pi*fc1*n1);

% Carrier Signal 2.
c2 = cos(2*pi*fc2*n2);

% ----> Step 6 - Create one AM Modulated signal for each modulating one.
% AM Modulated Signal 1.
s1 = x1 .* c1;

% AM Modulated Signal 2.
s2 = x2 .* c2;

% ----> Step 7 - Calculate FFTs for the AM Modulated signals.
% AM Modulated Signal 1.
S1 = fft(s1);

% Convert to analog freaquency
k_s1 = 0 : length(S1)-1;
w_s1 = (2*k_s1*pi) / length(S1);                     % Digital frequencies.

new_length_s1 = round(length(S1)/2);   
                                                           
new_S1 = S1(1 : new_length_s1);
new_k_s1 = 0 : (new_length_s1-1);
new_w_s1 = (2*new_k_s1*pi)/length(S1);

Ts1 = 1/(fs2);
W_s1 = new_w_s1/Ts1;                                  % Analog w (rad/sec).
fmd1 = W_s1 / (2*pi*1000);                                % Analog f (KHz).
figure(5);
plot(fmd1,abs(new_S1));
title('AM Modulated Signal 1');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

% AM Modulated Signal 2.
S2 = fft(s2);

% Convert to analog freaquency
k_s2 = 0 : length(S2)-1;
w_s2 = (2*k_s2*pi) / length(S2);                     % Digital frequencies.

new_length_s2 = round(length(S2)/2);   
                                                           
new_S2 = S2(1 : new_length_s2);
new_k_s2 = 0 : (new_length_s2-1);
new_w_s2 = (2*new_k_s2*pi)/length(S2);

Ts2 = 1/(fs2);
W_s2 = new_w_s2/Ts2;                                  % Analog w (rad/sec).
fmd2 = W_s2 / (2*pi*1000);                                % Analog f (KHz).
figure(6);
plot(fmd2,abs(new_S2));
title('AM Modulated Signal 2');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

s1 = ifft(new_S1);
s2 = ifft(new_S2);

% ----> Step 8 - Multiplex the modulated signals.
% Equalize the length of the signals.
if ( length(s1) > length(s2) )
    s2(length(s1)) = 0;
end
if ( length(s2) > length(s1) )
    s1(length(s2)) = 0;
end

m = s1 + s2;                                          % Multiplexed signal.
M = fft(m);

k_m = 0 : length(M)-1;
w_m = (2*k_m*pi) / length(M);                        % Digital frequencies.

new_length_m = round(length(M)/2);   
                                                           
new_M = M(1 : new_length_m);
new_k_m = 0 : (new_length_m-1);
new_w_m = (2*new_k_m*pi)/length(M);

Tm = 1/(fs2);
W_m = new_w_m/Tm;                                     % Analog w (rad/sec).
fm = W_m / (2*pi*1000);                                   % Analog f (KHz).
figure(7);
plot(fm,abs(new_M));
title('Multiplexed signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

m = ifft(new_M);

% ----> Step 9 - Add Gaussian noise.
% Channel.
SNR = 5;

% Received signal.
% Add white Gaussian noise with 2 methods

% Method 1 - Use a standard MatLab function.
% To activate this method make SNR = 20 for better results.
% SNR = 20;
% r = awgn(m,SNR);


% Method 2 - Using Mathematics.
% 10*log(P_signal/variance) = SNR => 
%                        _
% Psignal/variance = SNR  |
% Psignal = 1 (standard)  |  =>
%                        -
variance = 1/SNR;
noise = sqrt(variance);
m(length(noise)) = 0;
r = m .* noise;

R = fft(r);

k_r = 0 : length(R)-1;
w_r = (2*k_r*pi) / length(R);                        % Digital frequencies.

new_length_r = round(length(R)/2);   
                                                           
new_R = R(1 : new_length_r);
new_k_r = 0 : (new_length_r-1);
new_w_r = (2*new_k_r*pi)/length(R);

Tr = 1/(fs2);
W_r = new_w_r/Tr;                                     % Analog w (rad/sec).
fr = W_r / (2*pi*1000);                                    % Analog f (Hz).
figure(8);
plot(fm,abs(new_M),fr,abs(new_R));                     % Plot both signals.
xlabel('Frequency (KHz)');
ylabel('Amplitude');
legend('Multiplexed signal','Multiplexed Signal with AWGN');

r = ifft(new_R);

% ----> Step 10 - Bandpass Filter Design.
wc1 = 0.45*pi;
N1 = 100;
hd1 = ideal_lp(wc1,N1);
w_tet_1 = (hanning(N1))';                                 % Hanning window.
h1 = hd1 .* w_tet_1;                           % Find the new limited h(n).
fr1 = 0 : 0.01 : pi;                                       
H1 = freqz(h1,1,fr1);  

wc2 = 0.25*pi;
N2 = 100;
hd2 = ideal_lp(wc2,N2);
w_tet_2 = (hanning(N2))';                                 % Hanning window.
h2 = hd2 .* w_tet_2;                           % Find the new limited h(n).
fr2 = 0 : 0.01 : pi;                                       
H2 = freqz(h2,1,fr2);

hb = h1 - h2;
Hb = H1 - H2;                                 % Bandpass filter arises from 
                                                   % the abstraction of two 
                                                         % lowpass filters.

figure(9);
title('Bandpass Filter');
subplot(1,2,1);
semilogy(fr1,abs(Hb));         
title('H in log scale');

subplot(1,2,2);
plot(fr1,abs(Hb));
title('H in normal scale');

% ----> Step 11 - Bandpass filtering...
hb(length(r)) = 0;                                 % Equalize their length. 

y = filter(hb,1,r);                             % y is the filtered signal.
Y = fft(y);

k_y = 0 : length(Y)-1;
w_y = (2*k_y*pi) / length(Y);                        % Digital frequencies.

new_length_y = round(length(Y)/2);   
                                                           
new_Y = Y(1 : new_length_y);
new_k_y = 0 : (new_length_y-1);
new_w_y = (2*new_k_y*pi)/length(Y);

Ty = 1/(fs2);
W_y = new_w_y/Ty;                                     % Analog w (rad/sec).
fy = W_y / (2*pi*1000);                                   % Analog f (KHz).
figure(10);
plot(fy,abs(new_Y));
title('Bandpass Filtered signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

y = ifft(new_Y);

% ----> Step 12 - Mix the filtered signal with the initial carrier signal. 
demuxed = y .* c2; 

% ----> Step 13 - Lowpass Filter Design.
% Low Pass Filter.
wc = 0.28*pi;
N = 100;
hd = ideal_lp(wc,N);
w_tet = (hanning(N))';                                    % Hanning window.
hl = hd .* w_tet;                              % Find the new limited h(n).
fl = 0 : 0.01 : pi;                                       
Hl = freqz(hl,1,fl);

figure(11);
title('Lowpass Filter');
subplot(1,2,1);
semilogy(fl,abs(Hl));         
title('H in log scale');

subplot(1,2,2);
plot(fl,abs(Hl));
title('H in normal scale');

% ----> Step 14 - Final filtering
%hl(length(demuxed)) = 0;                           % Equalize their length.
z = filter(hl,1,demuxed);  

Z = fft(z);

k_z = 0 : length(Z)-1;
w_z = (2*k_z*pi) / length(Z);                        % Digital frequencies.

new_length_z = round(length(Z)/2);   
                                                           
new_Z = Z(1 : new_length_z);
new_k_z = 0 : (new_length_z-1);
new_w_z = (2*new_k_z*pi)/length(Z);

Tz = 1/(fs2);
W_z = new_w_z/Tz;                                     % Analog w (rad/sec).
fz = W_z / (2*pi*1000);                                   % Analog f (KHz).
figure(12);
plot(fz,abs(new_Z));
title('Lowpass Filtered signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');


% ----> Step 15 - Result
% The result is the initial signal 2