% ============================ Project HY-330 =============================
% === Date    : 02/06/2012                                              ===
% === Course  : Communication Systems Theory (HY330)                    ===
% === ----------------------------------------------------------------- ===
% === AM      : 2287                                                    ===
% === Author  : Katsikas Lampros                                        ===
% === ----------------------------------------------------------------- ===
% === Purpose : Sender reads two .wav files containing voice signals,   ===
% ===           checks the frequencies of each one and if is needed     ===
% ===           resamples the files to meet the Nyiquist therem.        ===
% ===           Then modulates message signals with DSB-SC and          ===
% ===           transmits them over an AWGN channel.                    ===
% ===           Receiver gets the modulated signals, uses a             ===
% ===           bandpass filter around 2nd carriers frequency           ===
% ===           to get only the second signal.                          ===
% ===           Then demodulates this signal and uses a low pass        ===
% ===           filter in order to get the initial signal back.         ===
% ===           The spectrum of the signal is calculated at each        ===
% ===           step of the procedure to make this process more         ===
% ===           familiar to the reader.                                 ===
% =========================================================================


clc;
close all;
clear all;

fprintf('\n===============================================\n');
fprintf('===== DSB-SC modulation of voice signals. =====\n');
fprintf('===============================================\n\n');

i = 1;
file1 = 'File1.wav';
file2 = 'File2.wav';


% ---> Step 1 - Read the .WAV files and get the information required.  <---
fprintf('-----------------------\n');
fprintf('Reading .WAV files... |\n');
fprintf('-----------------------\n');

% Read the first
[m1 d1] = wavfinfo(file1);                      % A piece of information...         
[x1,f1,n1] = wavread(file1);                    % Use this function to read
%sound(x1,f1);                                  % Listen to this .wav file.

% Read the second
[m2 d2] = wavfinfo(file2);                      % A piece of information...
[x2,f2,n2] = wavread(file2);                    % Use this function to read 
%sound(x2,f2);                                  % Listen to this .wav file.

% Print some info about the .wav files...
fprintf('%s info: \n',file1);
fprintf('\t Bits per sample used: %d \n',n1);
fprintf('\t Initial Sampling Frequency: %d \n\n',f1);

fprintf('%s info: \n',file2);
fprintf('\t Bits per sample used: %d \n',n2);
fprintf('\t Initial Sampling Frequency: %d \n\n\n',f2);
% -------------------------------------------------------------------------



% ---> Step 2 - Use the appropriate types.                             <---
fm1 = f1/2;                     % fm is the spectrum of the initial signal. 
fm2 = f2/2;                     % fs is the initial sampling frequency of 
                                % the file.
                                
fc1 = 8000;                     % Carrier frequency(fc) >> fm to avoid
fc2 = 16000;                    % spectrum overlaping.

fmax1 = fc1 + fm1;              % fmax is the maximum frequency expected.
fmax2 = fc2 + fm2;

fs1 = 2 * fmax1;                % fs is the sampling frequency according to
fs2 = 2 * fmax2;                % the Nyiquist theorem.

% Print some constant values...
fprintf('---------------------------------');
fprintf('Useful frequency information... |\n');
fprintf('---------------------------------');

fprintf('Carrier-1 frequency(fc) = %d \n',fc1);
fprintf('Initial signal-1 frequency(fm) = %d \n',fm1);
fprintf('Nyiquist Sampling Frequency for Signal-1(fs) = %d \n\n',fs1);

fprintf('Carrier-2 frequency(fc) = %d \n',fc2);
fprintf('Initial signal-2 frequency(fm) = %d \n',fm2);
fprintf('Nyiquist Sampling Frequency for Signal-2(fs) = %d \n\n',fs2);
% -------------------------------------------------------------------------



% ---> Step 3 - Sample the input signals using sampling frequences.    <---
% Signal 1
if f1 < fs1
    fprintf('f1 < fs1!!!!!!!!!! - %d -- %d \n',f1,fs1);
    wavwrite(x1,fs1,n1,'Oversampled_File1.wav');% Create the sampled file.
    [x1,fs1,n1] = wavread('Oversampled_File1.wav');              
    %sound(x1,fs1);                             % Listen to the .wav file.
end

t1 = [0:length(x1)-1] * (1/fs1);                % Time axis.
figure(i);
i = i + 1;

subplot(2,1,1);
plot(t1,x1);
title('Voice Signal 1 - Time Domain. ');
xlabel('Time (sec)');
ylabel('Amplitude');


% Signal 2
if f2 < fs2
    fprintf('f2 < fs2!!!!!!!!!! - %d -- %d',f2,fs2);
    wavwrite(x2,fs2,n2,'Oversampled_File2.wav');% Create the sampled file.
    [x2,fs2,n2] = wavread('Oversampled_File2.wav');              
    %sound(x2,fs2);                             % Listen to the .wav file.
end

t2 = [0:length(x2)-1] * (1/fs2);                % Time axis.

subplot(2,1,2);
plot(t2,x2);
title('Voice Signal 2 - Time Domain. ');
xlabel('Time (sec)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% ---> Step 4 - Calculate FFT for each signal.                         <--- 
% Signal 1
X1 = fft(x1);                               % Fast Fourier Transform of x1. 

% Plot the Frequency Domain
k_x1 = 0 : length(X1)-1;
w_x1 = (2*k_x1*pi) / length(X1);            % Digital frequencies.

new_length_x1 = round(length(X1)/2);                                                              
new_X1 = X1(1 : new_length_x1);
new_k_x1 = 0 : (new_length_x1-1);
new_w_x1 = (2*new_k_x1*pi)/length(X1);

Tx1 = 1/fs1;
W_x1 = new_w_x1/Tx1;                        % Analog w (rad/sec).
digital_fs1 = W_x1 / (2*pi*1000);           % Analog f (KHz).
figure(i);
i = i + 1;

subplot(2,1,1);
plot(digital_fs1,abs(new_X1));
title('Voice Signal 1 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
xx1 = ifft(new_X1);


% Signal 2
X2 = fft(x2);                               % Fast Fourier Transform of x2. 

% Plot the Frequency Domain
k_x2 = 0 : length(X2)-1;
w_x2 = (2*k_x2*pi) / length(X2);            % Digital frequencies.

new_length_x2 = round(length(X2)/2);                                                             
new_X2 = X2(1 : new_length_x2);
new_k_x2 = 0 : (new_length_x2-1);
new_w_x2 = (2*new_k_x2*pi)/length(X2);

Tx2 = 1/fs2;
W_x2 = new_w_x2/Tx2;                       	% Analog w (rad/sec).
digital_fs2 = W_x2 / (2*pi*1000);           % Analog f (KHz).

subplot(2,1,2);
plot(digital_fs2,abs(new_X2));
title('Voice Signal 2 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
xx2 = ifft(new_X2);
% -------------------------------------------------------------------------



% ---> Step 5 - Create the carrier signal for the modulating one.      <---
% Carrier Signal 1.

c1 = cos(2*pi*fc1*t1);

% Carrier Signal 2.

c2 = cos(2*pi*fc2*t2);
% -------------------------------------------------------------------------



% ---> Step 6 - Create the AM Modulated signal for the modulating one. <--- 
% AM Modulated Signal 1.
s1 = x1 .* c1';

% AM Modulated Signal 2.
s2 = x2 .* c2';
% -------------------------------------------------------------------------



% ---> Step 7 - Calculate FFTs for the AM Modulated signal.            <---
% AM Modulated Signal 1.
S1 = fft(s1);

% Convert to analog freaquency
k_s1 = 0 : length(S1)-1;
w_s1 = (2*k_s1*pi) / length(S1);                    % Digital frequencies.

new_length_s1 = round(length(S1)/2);   
                                                           
new_S1 = S1(1 : new_length_s1);
new_k_s1 = 0 : (new_length_s1-1);
new_w_s1 = (2*new_k_s1*pi)/length(S1);

Ts1 = 1/(fs2);
W_s1 = new_w_s1/Ts1;                                % Analog w (rad/sec).
fmd1 = W_s1 / (2*pi*1000);                          % Analog f (KHz).
figure(i);
i = i + 1;
plot(fmd1,abs(new_S1));
title('AM Modulated Signal 1');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
s1 = ifft(new_S1);


% AM Modulated Signal 2.
S2 = fft(s2);

% Convert to analog freaquency
k_s2 = 0 : length(S2)-1;
w_s2 = (2*k_s2*pi) / length(S2);                    % Digital frequencies.

new_length_s2 = round(length(S2)/2);   
                                                           
new_S2 = S2(1 : new_length_s2);
new_k_s2 = 0 : (new_length_s2-1);
new_w_s2 = (2*new_k_s2*pi)/length(S2);

Ts2 = 1/(fs2);
W_s2 = new_w_s2/Ts2;                                % Analog w (rad/sec).
fmd2 = W_s2 / (2*pi*1000);                          % Analog f (KHz).
figure(i);
i = i + 1;
plot(fmd2,abs(new_S2));
title('AM Modulated Signal 2');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
s2 = ifft(new_S2);
% -------------------------------------------------------------------------



% ---> Step 8 - Multiplex the modulated signals.                      <---
if ( length(s1) > length(s2) )                      % Equalize the length 
    s2(length(s1)) = 0;                             % of the signals.
end
if ( length(s2) > length(s1) )
    s1(length(s2)) = 0;
end

m = s1 + s2;                                        % Multiplexed signal.
M = fft(m);

k_m = 0 : length(M)-1;
w_m = (2*k_m*pi) / length(M);                       % Digital frequencies.

new_length_m = round(length(M)/2);   
                                                           
new_M = M(1 : new_length_m);
new_k_m = 0 : (new_length_m-1);
new_w_m = (2*new_k_m*pi)/length(M);

Tm = 1/(fs2);
W_m = new_w_m/Tm;                                   % Analog w (rad/sec).
fm = W_m / (2*pi*1000);                             % Analog f (KHz).
figure(i);
i = i + 1;
plot(fm,abs(new_M));
title('Multiplexed signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

m = ifft(new_M);
% -------------------------------------------------------------------------


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
figure(i);
i = i + 1;
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

figure(i);
i = i + 1;
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
figure(i);
i = i + 1;
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

figure(i);
i = i + 1;
title('Lowpass Filter');
subplot(1,2,1);
semilogy(fl,abs(Hl));         
title('H in log scale');

subplot(1,2,2);
plot(fl,abs(Hl));
title('H in normal scale');

% ----> Step 14 - Final filtering
%hl(length(demuxed)) = 0;                          % Equalize their length.
z = filter(hl,1,demuxed);  
sound(demuxed);

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
figure(i);
i = i + 1;
plot(fz,abs(new_Z));
title('Lowpass Filtered signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');


% ----> Step 15 - Result
% The result is the initial signal 2