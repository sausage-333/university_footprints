% Matlab HW 5

clear;

m = 128; 

sup_eigv = zeros(100:1);

for i = 1:100
    
    A = randn(m,m)/sqrt(m);
    eigv = eig(A);
    plot(real(eigv), imag(eigv), '*');
    
    % Spectral Radius is the biggest eigenvalue
    % <sup_eigv> array contains every 100 spectral radius of A.
    sup_eigv(i) = max(abs(eigv));
    title("128x128 Matrix")
    hold on;
    
end

% Analyze the spectral radius
% in average, standard deviation, maximumm and minimum
average_radius = mean(sup_eigv)
maximum_radius = max(sup_eigv)
minimum_radius = min(sup_eigv)
standard_deviation = std(sup_eigv)