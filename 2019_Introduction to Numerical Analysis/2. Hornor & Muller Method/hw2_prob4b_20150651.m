% hw2_prob4b_20150651.m
clear all;
disp('----------------');
disp('HW2 Problem 4(b)');
disp('----------------');

f = @(x) x.^2 - 2*x + 5/4; % function value
p0 = 0.5; % initial approximation
p1 = 1;
p2 = 1.5;

disp(sprintf('Initial approximation : %0.5e', p0));
MaxIter = 100; % maximum number of iterations
disp(sprintf('Maximum number of iterations : %d', MaxIter));
epsilon = 10^(-5); % tolerance
disp(sprintf('Tolerance : %d', epsilon));
disp('----------------');
[pp numiter] = muller(p0, p1, p2, f, MaxIter, epsilon);
disp(sprintf('Muller method after %d iterations: %0.5e + %0.5ei', ...
numiter, real(pp(numiter+3)), imag(pp(numiter+3))));


% Muller method
function [pp numiter] = muller(p0, p1, p2, f, MaxIter, epsilon)
pp = zeros(MaxIter+3,1);
pp(1) = p0;
pp(2) = p1;
pp(3) = p2;
for i=1:MaxIter

    h1 = pp(i+1) - pp(i);
    h2 = pp(i+2) - pp(i+1);
    
    d1 = (f(pp(i+1)) - f(pp(i))) / h1;
    d2 = (f(pp(i+2)) - f(pp(i+1))) / h2;
    
    d = (d2 - d1) / (h2 + h1);
    
    b = d2 + h2 * d;
    dtm = sqrt(b^2 - 4 * f(pp(i+2)) * d);
    
    if abs(b - dtm) < abs(b + dtm)
        div = b + dtm;
    else
        div = b - dtm;
    end
    
    h = -2 * f(pp(i+2)) / div;
    pp(i+3) = pp(i+2) + h; % Muller update
    
    if abs(h) < epsilon
        disp(pp(i+1));
        disp(i);
        break
    end
    
end
numiter = i;
end