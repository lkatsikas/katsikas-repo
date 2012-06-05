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
fprintf('---------------------------------\n');
fprintf('Useful frequency information... |\n');
fprintf('---------------------------------\n');

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
    wavwrite(x1,fs1,n1,'Oversampled_File1.wav');% Create the sampled file.
    [x1,fs1,n1] = wavread('Oversampled_File1.wav');              
    %sound(x1,fs1);                             % Listen to the .wav file.
end

t1 = [0:length(x1)-1] * (1/fs1);                % Time axis.

figure(i);
i = i + 1;
subplot(2,2,1);
plot(t1,x1);
title('Voice Signal 1 - Time Domain. ');
xlabel('Time (sec)');
ylabel('Amplitude');


% Signal 2
if f2 < fs2
    wavwrite(x2,fs2,n2,'Oversampled_File2.wav');% Create the sampled file.
    [x2,fs2,n2] = wavread('Oversampled_File2.wav');              
    %sound(x2,fs2);                             % Listen to the .wav file.
end

t2 = [0:length(x2)-1] * (1/fs2);                % Time axis.

subplot(2,2,2);
plot(t2,x2);
title('Voice Signal 2 - Time Domain. ');
xlabel('Time (sec)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% ---> Step 4 - Calculate FFT for each signal.                         <--- 
% Signal 1
l1 = length(x1); 
NFFT1 = 2^nextpow2(l1);                          % Next power of 2 in order 
X1 = fft(x1,NFFT1)/l1;                           % speed up calculations.
ff1 = fs1/2*linspace(0,1,NFFT1/2+1);

subplot(2,2,3);
plot(ff1,2*abs(X1(1:NFFT1/2+1))) 
title('Voice Signal 1 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

% Signal 2
l2 = length(x2); 
NFFT2 = 2^nextpow2(l2);                          % Next power of 2 in order 
X2 = fft(x2,NFFT2)/l2;                           % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

subplot(2,2,4);
plot(ff2,2*abs(X2(1:NFFT2/2+1))) 
title('Voice Signal 1 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
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
l1 = length(s1); 
NFFT1 = 2^nextpow2(l1);                          % Next power of 2 in order 
X1 = fft(s1,NFFT1)/l1;                           % speed up calculations.
ff1 = fs1/2*linspace(0,1,NFFT1/2+1);

figure(i);
i = i + 1;
subplot(2,2,1:2);
plot(ff1,2*abs(X1(1:NFFT1/2+1))) 
title('AM Modulated Signal 1');
xlabel('Frequency (KHz)');
ylabel('Amplitude');


% Signal 2
l2 = length(s2); 
NFFT2 = 2^nextpow2(l2);                          % Next power of 2 in order 
X2 = fft(s2,NFFT2)/l2;                           % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

subplot(2,2,3:4);
plot(ff2,2*abs(X2(1:NFFT2/2+1))) 
title('AM Modulated Signal 2');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% ---> Step 8 - Multiplex the modulated signals.                       <---
if ( l1 > l2 )                                  % Equalize the length 
    s2(l1) = 0;                                 % of the signals.
end
if ( l2 > l1 )
    s1(l2) = 0;
end

m = s1 + s2;                                    % Multiplexed signal.
l2 = length(m); 
NFFT2 = 2^nextpow2(l2);                         % Next power of 2 in order 
X1 = fft(m,NFFT2)/l2;                           % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

figure(i);
i = i + 1;
subplot(2,2,1:2);
plot(ff2,2*abs(X1(1:NFFT2/2+1))) 
title('Multiplexed signal');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% ---> Step 9 - Add Gaussian noise.                                    <---
% Channel.
SNR = 5;

% Add white Gaussian noise 
variance = 1/SNR;
noise = sqrt(variance);
m(length(noise)) = 0;
r = m.* noise;                                  % Signal with noise.
                                    
l2 = length(r); 
NFFT2 = 2^nextpow2(l2);                         % Next power of 2 in order 
X2 = fft(r,NFFT2)/l2;                           % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

subplot(2,2,3:4);
plot(ff2,2*abs(X1(1:NFFT2/2+1)),ff2,2*abs(X2(1:NFFT2/2+1))) 
xlabel('Frequency (KHz)');
ylabel('Amplitude');
legend('Multiplexed signal','Multiplexed Signal with AWGN');
% -------------------------------------------------------------------------

                                            

% ----> Step 10 - Bandpass Filter Design.                              <---
wc1 = 0.45*pi;
N1 = 100;
hd1 = ideal_lp(wc1,N1);
w_tet_1 = (hanning(N1))';                   % Hanning window.
h1 = hd1 .* w_tet_1;                        % Find the new limited h(n).
fr1 = 0 : 0.01 : pi;                                       
H1 = freqz(h1,1,fr1);  

wc2 = 0.25*pi;
N2 = 100;
hd2 = ideal_lp(wc2,N2);
w_tet_2 = (hanning(N2))';                   % Hanning window.
h2 = hd2 .* w_tet_2;                     	% Find the new limited h(n).
fr2 = 0 : 0.01 : pi;                                       
H2 = freqz(h2,1,fr2);

hb = h1 - h2;
Hb = H1 - H2;                               % Bandpass filter arises from 
                                          	% the abstraction of two 
                                         	% lowpass filters.
figure(i);
i = i + 1;
title('Bandpass Filter');
subplot(2,2,1);
semilogy(fr1,abs(Hb));         
title('H in log scale');

subplot(2,2,2);
plot(fr1,abs(Hb));
title('H in normal scale');
% -------------------------------------------------------------------------



% ----> Step 11 - Apply Bandpass Filtering...                          <---
hb(length(r)) = 0;                        	% Equalize their length. 

y = filter(hb,1,r);                         % y is the filtered signal.

l2 = length(y); 
NFFT2 = 2^nextpow2(l2);                  	% Next power of 2 in order 
X2 = fft(y,NFFT2)/l2;                       % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

subplot(2,2,3:4);
plot(ff2,2*abs(X2(1:NFFT2/2+1))) 
title('Bandpass Filter - Seperation of signal 1.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% ----> Step 12 - Demodulation of the signal.                          <---
demuxed = s1.*c1';                              % Multiplied with the
                                                % initial carrier signal
% -------------------------------------------------------------------------



% ----> Step 13 - Lowpass Filter Design.                               <---
% Low Pass Filter.
wc = 0.28*pi;
N = 100;
hd = ideal_lp(wc,N);
w_tet = (hanning(N))';                         	% Hanning window.
hl = hd .* w_tet;                               % Find the new limited h(n)
fl = 0 : 0.01 : pi;                                       
Hl = freqz(hl,1,fl);

figure(i);
i = i + 1;
title('Lowpass Filter');
subplot(2,2,1);
semilogy(fl,abs(Hl));         
title('H in log scale');

subplot(2,2,2);
plot(fl,abs(Hl));
title('H in normal scale');
% -------------------------------------------------------------------------



% ----> Step 14 - Apply Lowpass Filtering...                           <---
z = filter(hl,1,demuxed);                       % Lowpass filtering the 
                                                % demuxed signal.
% -------------------------------------------------------------------------



% ----> Step 15 - Plot and sound the initial signal 1.                 <---
sound(z,f1);                                    % Send the signal to the 
                                                % audio card for playback.

% Plot the spectrum of the initial signal 1 - Frequency Domain.                                               
l2 = length(z); 
NFFT2 = 2^nextpow2(l2);                         % Next power of 2 in order 
X2 = fft(z,NFFT2)/l2;                           % speed up calculations.
ff2 = fs2/2*linspace(0,1,NFFT2/2+1);

subplot(2,2,3);
plot(ff2,2*abs(X2(1:NFFT2/2+1))) 
title('Lowpass Filter - Cutoff frequencies.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');

% Plot the time scope of the intial signal 1 - Time Domain.
subplot(2,2,4),plot(t1,x1);
title('Signal 1 - Recovered.');
xlabel('Time (sec)');
ylabel('Amplitude');
% -------------------------------------------------------------------------



% =========================================================================
fprintf('\n\n');
fprintf('=== ----------------------------------------------------  ===\n');
fprintf('=== Date   : 02/06/2012.                                | ===\n');
fprintf('=== Course : Communication Systems Theory (HY330).      | ===\n');
fprintf('=== ----------------------------------------------------  ===\n');

fprintf('=== ----------------------------------------------------  ===\n');
fprintf('=== AM     : 2287.                                      | ===\n');
fprintf('=== Author : Katsikas Lampros.                          | ===\n');
fprintf('=== ----------------------------------------------------  ===\n');
fprintf('\n');
% =========================================================================

