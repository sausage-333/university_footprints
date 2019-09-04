% hw5_prob5_20150651.m
disp('----------------');
disp('HW5 Problem 5');
disp('----------------');

format long

u_1 = @(t, u1, u2) u1/9 - (2*u2)/3 - (t.^2)/9 + 2/3; % System of u1
u_1_iv = -3;                                         % and its initial value
u_2 = @(t, u1, u2) u2 + 3*t - 4;                     % System of u2
u_2_iv = 5;                                          % and its initial value

actual_u_1 = @(t) (-3*exp(t) + t.^2);
actual_u_2 = @(t) (4*exp(t) - 3*t + 1);

a = 0;          % Start point
b = 2;          % End point
h = 0.2;        % Space btween two points
N = (b-a)/h;    % Number of points

t = a;
w_1 = u_1_iv;
w_2 = u_2_iv;

result = zeros(6, N+1);                         % Matrix for Results
result(1, 1) = w_1;                             % First row contains approx sol of u_1
result(2, 1) = actual_u_1(t);                   % Second row contains actual sol of u_1
result(3, 1) = abs(result(1, 1) - result(2, 1));% Third row contains error btw approx & actual of u_1
result(4, 1) = w_2;                             % Fourth row contains approx sol of u_2
result(5, 1) = actual_u_2(t);                   % Fifth row contains actual sol of u_2
result(6, 1) = abs(result(4, 1) - result(5, 1));% Sixth row contains error btw approx & actual of u_2

% Runge-Kutta method of order four
for i = 1:N
   
    k_1_1 = h * u_1(t, w_1, w_2);
    k_1_2 = h * u_2(t, w_1, w_2);
    
    k_2_1 = h * u_1(t + h/2, w_1 + k_1_1/2, w_2 + k_1_2/2);
    k_2_2 = h * u_2(t + h/2, w_1 + k_1_1/2, w_2 + k_1_2/2);
    
    k_3_1 = h * u_1(t + h/2, w_1 + k_2_1/2, w_2 + k_2_2/2);
    k_3_2 = h * u_2(t + h/2, w_1 + k_2_1/2, w_2 + k_2_2/2);
    
    k_4_1 = h * u_1(t + h, w_1 + k_3_1, w_2 + k_3_2);
    k_4_2 = h * u_2(t + h, w_1 + k_3_1, w_2 + k_3_2);
    
    w_1 = w_1 + (k_1_1 + 2*k_2_1 + 2*k_3_1 + k_4_1)/6;
    w_2 = w_2 + (k_1_2 + 2*k_2_2 + 2*k_3_2 + k_4_2)/6;
    
    t = a + i*h;
    
    result(1, i + 1) = w_1;
    result(2, i + 1) = actual_u_1(t);                   
    result(3, i + 1) = result(1, i + 1) - result(2, i + 1);
    
    result(4, i + 1) = w_2;
    result(5, i + 1) = actual_u_2(t);                   
    result(6, i + 1) = result(4, i + 1) - result(5, i + 1);
    
end

result