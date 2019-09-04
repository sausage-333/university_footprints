file = "female_o.wav";
auto_correl = short_time_auto_cor(file);
%plot(auto_correl);
pow_spec = power_spectrum(auto_correl);
plot(pow_spec)
title("FFT of male_o.wav");

function glot_trn = glottal_train(freq)

    


end;

function pow_spec = power_spectrum(acy)

    % Return power spectrum of given autocorrelation function
    % In this function, FFT will be executed
    
    pow_spec = abs(fft(acy));
    
    % Power spectrum is symmetric
    szz = size(pow_spec);
    
    % Observe fft up to 8kHz
    pow_spec = pow_spec(1:round(szz(1) / 6));
    
end


function acy = short_time_auto_cor(filename)

    % Return the autocorrelation of given filenmae with short time analysis
    % By plotting it, you can easily check Fundamental Frequency

    [y, fs] = audioread(filename);
    
    sz = size(y);
    
    % 30ms is the considerable duration of the stationary signal
    k = floor(log2(0.03 * fs));
    % This is the rectangular window length
    % To calculate easily, I set the length power of 2
    sample_per_frame = 2^k;
    
    % Just probe the middle of signal
    y = y(round(sz(1) / 2) : round(sz(1) / 2) + sample_per_frame - 1);
    % Autocorrelate it
    acy = xcorr(y);
    
    szz = size(acy);
    
    % Autocorrelate function is symmetric
    acy = acy(round(szz(1) / 2):szz(1));
    
end