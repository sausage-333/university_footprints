%%% EE432 Digital Signal Processing Matlab Project %%%
%%% 20150651 Jang Kang-wook %%%

%% (a) - 2 Digital Type 2 Chebyshev LPF with Bilinear Transformation Method %%

%% Stopband / Passband setting
w_p = 0.2 * pi;
w_s = 0.3 * pi;

%% Attenuation setting in dB
att_p = 0.3;
att_s = 30;

%% Set T_d as 1, it doens't matter
T_d = 1;

%% Get Chebyshev 2 filter's order and cutoff frequency
[n, cut_freq] = cheb2ord(w_p, w_s, att_p, att_s, 's');

%% Obtain filter coefficients
[b, a] = cheby2(n, att_s, cut_freq, 's');

%% Apply bilinear transformation and obtain digital filter coefficient
tf2sos(b, a)
[b_z, a_z] = bilinear(b, a, 1/T_d);

%% Obtain frequency response & angular frequency with N tabs
N = 1024;
[H, w] = freqz(b_z, a_z, N);

%% Plot magnitude in dB - (1)
subplot(2,2,1);
plot(w/pi, 20 * log10(abs(H)));
axis([0 1 -50 20]);
title("Log Scale Magnitude");
xlabel('Normalized Freq (#^-1 * pi^-1)')
ylabel('dB')

%% Plot magnitude in linear scale - (2)
subplot(2,2,2)
plot(w/pi, abs(H));
xlabel('Normalized Freq (#^-1 * pi^-1)')
title("Linear Scale Magnitude");

%% Plot group delay - (3)
subplot(2,2,3);
grpdelay(b_z, a_z, N);
title("Group Delay");

%% Plot pole-zero diagram - (4)
subplot(2,2,4);
zplane(b_z, a_z);
title("Pole-zero Diagram");