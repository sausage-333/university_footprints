% Matlab HW 5
m = 128; 

sig_min = zeros(100:1);

for i = 1:100
    
    A = randn(m,m)/sqrt(m);
    
    % Default is 2 norm
    % <sigma> array contains all singular values of every 100 matrices.
    sigma =  svd(A);
    
    % <sig_min> array contains 100 minimum singular values
    sig_min(i) = sigma(m);
    
end

prob = zeros(10:1);

for i = 1:10
    
    cmp = sig_min < 2.^-i;
    
    prob(i) = sum(cmp);
    
end

figure(1);
plot(prob);
title("Number of matrix that min s.v < 1/2^x. Size 128x128");