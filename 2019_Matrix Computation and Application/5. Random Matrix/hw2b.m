% Matlab HW 5
m = 128; 

nom = zeros(100:1);
sup_eigv = zeros(100:1);
diff = zeros(100:1);

for i = 1:100
    
    A = randn(m,m)/sqrt(m);
    
    % Default is 2 norm
    % <norm> array contains every 100 norms of A.
    nom(i) =  norm(A);
    
    % Spectral Radius is the biggest eigenvalue
    % <sup_eigv> array contains every 100 spectral radius of A.
    sup_eigv(i) = max(abs(eig(A)));
    
    % Difference between norm and spectral radius
    diff(i) = nom(i) - sup_eigv(i);
    
end

figure(1);
histfit(nom);
title("Norm Distribution of 128x128 Matrix");

hold off;

figure(2);
plot(sup_eigv);
hold on

plot(nom);

title("Norm and Spectral Radius of 128x128 Matrix");
legend('Spectral Radius', 'Norm');

% Analyze the norm of the matrix
% in average, standard deviation, maximumm and minimum
average_norm = mean(nom)
maximum_norm = max(nom)
minimum_norm = min(nom)
standard_norm = std(nom)
diff = norm(diff)