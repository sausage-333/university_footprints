%%% EE432 Digital Signal Processing Matlab Project %%%
%%% 20150651 Jang Kang-wook %%%

%% (c) - 1 Linear-phase FIR LPF with Hamming Window %%

%% Stopband / Passband setting
w_p = 0.2 * pi;
w_s = 0.3 * pi;

%% Attenuation setting in dB
att_p = 0.3;
att_s = 30;

%% Center Frequency & Window Size(Order) & Number of Tabs Setting
w_c = (w_s + w_p) / 2;
ord = 128;
tab_n = 512;

%% Frequency Resolution Setting & Rectangular Window
dw = pi / tab_n;
window = hamming(ord + 1)';
b = fir1(ord, w_c / pi, 'low', window);

%% Frequency Response of Rectangular Window
H = freqz(b, 1, -pi:dw:pi);

%% Plot magnitude in dB - (1)
subplot(2,3,1);
plot(-1:dw/pi:1, 20 * log10(abs(H)));
axis([0 1 -70 10]);
title("Log Scale Magnitude");
xlabel('Normalized Freq (#^-1 * pi^-1)')
ylabel('dB')

%% Plot magnitude in linear scale - (2)
subplot(2,3,2)
plot(-1:dw/pi:1, abs(H));
axis([0 1 0 1.5]);
xlabel('Normalized Freq (#^-1 * pi^-1)')
title("Linear Scale Magnitude");

%% Plot group delay - (3)
subplot(2,3,3);
grpdelay(window);
title("Group Delay");

%% Plot pole-zero diagram - (4)
subplot(2,3,4);
zplane(window);
title("Pole-zero Diagram");

%% Plot impulse response coefficients - (5)
subplot(2,3,5);
plot(b);
title("Filter Coefficients");