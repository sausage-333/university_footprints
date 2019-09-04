% hw1_prob5_2_20150651.m
clear all;
disp('----------------');
disp('HW1 Problem 5(2)');
disp('----------------');

f = @(x) 2*x.^2 + cos(2*x) - 4*x.*cos(x) + 1; % function value
g = @(x) 4*x + 4*x.*sin(x) - 2*sin(2*x) - 4*cos(x); % derivatie
h = @(x) 4*x.*cos(x) - 4*cos(2*x) + 8*sin(x) + 4; % second derivative

p0 = 2; % initial approximation
p1 = 1; % another initial approximation for Secant method

disp(sprintf('Initial approximation : %0.5e', p0));
MaxIter = 30; % maximum number of iterations
disp(sprintf('Maximum number of iterations : %d', MaxIter));
disp('----------------');

pp_s = secant(p0, p1, f, MaxIter);
pp_n = newton(p0, f, g, MaxIter);
pp_m = modified_newton(p0, f, g, h, MaxIter);

disp(sprintf('Secant method after %d iterations: %0.5e', ...
MaxIter, pp_s(MaxIter+2)));
disp(sprintf('Newton method after %d iterations: %0.5e', ...
MaxIter, pp_n(MaxIter+1)));
disp(sprintf('Modified Newton method after %d iterations: %0.5e', ...
MaxIter, pp_m(MaxIter+1)));

% plot
figure(1);
semilogy(0:MaxIter+1, abs(f(pp_s)), 'k-', ...
0:MaxIter, abs(f(pp_n)), 'b-', ...
0:MaxIter, abs(f(pp_m)), 'r-');
xlabel('Iteration (n)');
ylabel('f(p_n)');
legend('Secant', 'Newton', 'Modified Newton');

% Secant method
function pp = secant(p0, p1, f, MaxIter)
% Add 2 more entries for initial values
pp = zeros(MaxIter+2,1);
pp(1) = p0;
pp(2) = p1;
tol = 1.00000 * 10^-6; % tolerance

i = 1;
q0 = f(p0);
q1 = f(p1);

while i <= MaxIter
    % ith iteration
    pp(i+2) = pp(i+1) - q1 * (pp(i+1) - pp(i)) / (q1 - q0);
    
    if abs(pp(i+2) - pp(i+1)) / abs(pp(i+2)) < tol
        disp(i);
        disp(pp(i+2));
        break
    end
    q0 = q1;
    q1 = f(pp(i+2));
    i = i + 1;
end
end

% Newton method
function pp = newton(p0, f, g, MaxIter)
% Array for results of Newton's method
pp = zeros(MaxIter+1,1);
pp(1) = p0;
tol = 10^-6; % tolerance

i = 1;

while i <=  MaxIter
    % ith iteration
    pp(i+1) = pp(i) - f(pp(i)) / g(pp(i));
    
    if abs(pp(i+1) - pp(i)) / abs(pp(i+1)) < tol
        disp(i);
        disp(pp(i+1));
        break
    end
    
    i = i + 1;
end
end

% Modified Newton method
function pp = modified_newton(p0, f, g, h, MaxIter)
pp = zeros(MaxIter+1,1);
pp(1) = p0;
tol = 10^-6; % tolerance

i = 1;

while i <= MaxIter
    % ith iteration
    pp(i+1) = pp(i) - f(pp(i)) * g(pp(i)) / (g(pp(i)).^2 - f(pp(i)) * h(pp(i)));
    
    if abs(pp(i+1) - pp(i)) / abs(pp(i+1)) < tol
        disp(i);
        disp(pp(i+1));
        break
    end
    
    i = i + 1;
end
end