% ============================ Project HY-330 =============================
% === Date    : 02/06/2012                                              ===
% === Course  : Communication Systems theory (HY330)                    ===
% === ----------------------------------------------------------------- ===
% === AM      : 2287                                                    ===
% === Author  : Katsikas Lampros                                        ===
% === ----------------------------------------------------------------- ===
% === Purpose : Sender reads two .wav files containing voice signals,   ===
% ===           checks the frequencies of each one and if is needed     ===
% ===           resamples the files to meet the Nyiquist therem.        ===
% ===           then modulates message signals with DSB-SC and          ===
% ===           transmits them over an AWGN channel.                    ===
% ===           Receiver gets the modulated signals, uses a             ===
% ===           bandpass filter around 2nd carriers frequency           ===
% ===           to get only the second signal.                          ===
% ===           then demodulates this signal and uses a low pass        ===
% ===           filter in order to get the initial signal back.         ===
% ===           the spectrum of the signal is calculated at each        ===
% ===           step of the procedure to make this process more         ===
% ===           familiar to the reader.                                 ===
% =========================================================================


clc;
clear all;
close all;

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

t1 = [0:length(x1)-1] * (1/fs1);                % time axis.
figure(i);
i = i + 1;

subplot(2,2,3);
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

t2 = [0:length(x2)-1] * (1/fs2);                % time axis.

subplot(2,2,4);
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

subplot(2,2,1);
plot(digital_fs1,abs(new_X1));
title('Voice Signal 1 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
x1 = ifft(new_X1);


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

subplot(2,2,2);
plot(digital_fs2,abs(new_X2));
title('Voice Signal 2 - Frequency Domain.');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
x2 = ifft(new_X2);
% -------------------------------------------------------------------------



% ---> Step 5 - Create the carrier signal for the modulating one.      <---
% Carrier Signal 1.
t1 = t1';
c1 = cos(2*pi*fc1*n1);

% Carrier Signal 2.
t2 = t2';
c2 = cos(2*pi*fc2*n2);
% -------------------------------------------------------------------------



% ---> Step 6 - Create the AM Modulated signal for the modulating one. <--- 
% Modulated Signal 1.
z1 = x1 .* c1;

% Modulated Signal 2.
z2 = x2 .* c2;

figure(i);
i = i + 1;
subplot(2,2,1);
plot(t1,z1);
title('DSB-SC Signal 1 - Time Domain');
xlabel('time (sec)');
ylabel('Amplitude');

subplot(2,2,2);
plot(t2,z2);
title('DSB-SC Signal 2 - Time Domain');
xlabel('Time (sec)');
ylabel('Amplitude');

% -------------------------------------------------------------------------



% ---> Step 7 - Calculate FFTs for the AM Modulated signal.            <---
% AM Modulated Signal 1.
S1 = fft(z1);

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
subplot(2,2,1),plot(fmd1,abs(new_S1));
title('AM Modulated Signal 1');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
s1 = ifft(new_S1);


% AM Modulated Signal 2.
S2 = fft(z2);

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

subplot(2,2,2),plot(fmd2,abs(new_S2));
title('AM Modulated Signal 2');
xlabel('Frequency (KHz)');
ylabel('Amplitude');
s2 = ifft(new_S2);
% -------------------------------------------------------------------------





% task 3.2
l1=length(z1);
f=linspace(-fs1/2,fs1/2,l1);
Z1=fftshift(fft(z1,l1)/l1);
figure(i);
i = i + 1;
subplot(2,1,2),plot(f,abs(Z1));
title('DSB SC MODULAtION IN FREQUENCY DOMAIN');
xlabel('frequency(hz)');
ylabel('amplitude');
axis([-200000 200000 0 0.3]);
% task 3.3 demodulation
d1=z1.*c1;
S1=fftshift(fft(d1,length(d1))/length(d1));
figure(i);
i = i + 1;
plot(f,abs(S1));
title(' demodulated signal IN FREQUENCY DOMAIN before filtring');
xlabel('frequency(hz)');
ylabel('amplitude');
axis([-200000 200000 0 0.3]);
hold on
Hlp=1./sqrt(1+(f./fc1).^(2*100));
plot(f,Hlp,'g');
title(' frequency response of low pass filter');
xlabel('frequency(hz)');
ylabel('amplitude');
axis([-200000 200000 0 2]);
% task 3.4

Hlp = Hlp';

E1=Hlp.*S1;
figure(i)
i = i + 1;
subplot(2,1,1),plot(f,E1);
title(' Recover signal IN FREQUENCY DOMAIN after filtring');
xlabel('frequency(hz)');
ylabel('amplitude');
axis([-200000 200000 0 0.3]);
e1=ifft(ifftshift(E1))*length(E1);
subplot(2,1,2),plot(t1,(1/0.5)*e1);
title(' Recover signal IN time DOMAIN after filtring');
xlabel('time(sec)');
ylabel('amplitude');

