% Matlab HW 5

sig_min = zeros(100:1);
mean_sig_min = zeros(7:1);

for j = 3:7
    
    for i = 1:100

        A = randn(2^j, 2^j)/sqrt(2^j);

        % Default is 2 norm
        % <sigma> array contains all singular values of every 100 matrices.
        sigma = svd(A);

        % <sig_min> array contains 100 minimum singular values
        sig_min(i) = sigma(2^j);

    end
    
    mean_sig_min(j) = mean(sig_min);
    
end

figure(1);
plot(mean_sig_min);
xlim([3 7]);
title("Mean of min s.v of 100 matrices with size of 2^mx2^m");