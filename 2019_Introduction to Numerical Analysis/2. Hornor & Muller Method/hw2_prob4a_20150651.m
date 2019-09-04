% hw2_prob4a_20150651.m
clear all;
disp('----------------');
disp('HW2 Problem 4(a)');
disp('----------------');

f = @(x) x.^3 - 4*x.^2 + 21/4*x - 5/2; % function value
g = @(x) 3*x.^2 - 8*x + 21/4; % derivative of f

p0 = 1/2; % initial approximation

% Newton method
iter = 1;
tol = 10^-5;

p_n_1 = p0;
p_n = p0 - f(p0) / g(p0);  % 1st iteration

while abs(p_n - p_n_1) / abs(p_n) >= tol
    
    % Update
    p_n_1 = p_n;
    p_n = p_n_1 - f(p_n_1) / g(p_n_1);
    
    iter = iter + 1;
    
end

% Horner Method
a = 1;
b = -4 + a*p_n;
c = 21/4 + b*p_n;

fprintf('Newton method after %d iterations: %d\n', iter, p_n);
fprintf('Reduced polynomial: (%d)*x^2 + (%d)*x + (%d)\n', a, b, c);