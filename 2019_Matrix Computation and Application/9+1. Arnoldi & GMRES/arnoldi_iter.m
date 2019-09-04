% Matlab HW 10

% Define Matrix A
m = 100;
A = randn(m,m)/sqrt(m);
A(1,1) = 1.5;

eigv = eig(A);
% Plot all eigenvalues of A
plot(real(eigv), imag(eigv), '.');

hold on;

% Define Unit circle 
t = 1024;

dPhi = 2*pi/t;
phi = (-pi:dPhi:pi-dPhi);

z = exp(1j*phi);
C = [ real(z) ; imag(z) ];
% Plot Unit circle
plot(z, 'LineWidth', 2.0)

hold on;

% Define vector b
b = zeros(m, 1);
for i=1:m
    b(i, 1) = 1;
end

n = 1;

% Execute Arnoldi iteration
[Q, H] = arnoldi(A, b, n);

% Characteristic Polynomial of H
polyH = charpoly(H)
% Calculate p^n(A)b
pnA = polyvalm(polyH, A);
% Calculate C
C = norm(pnA * b) / norm(b)
polyH(n+1) = polyH(n+1) - C;
% Calculate roots of characteristic polynomial
r = roots(polyH);
plot(real(r), imag(r), '*');

function [Q, H] = arnoldi(A, b, n)
% Calculate Arnoldi Iteration
% with given matrix A and vector b, iteration times n
% Input: Square matrix A
%        Vector b
%        Iteration times n
% Ouput: Matrix containing n Orthonormal Basis, Q
%        Upper Hessenberg Matrix H
% A and b must have the same row dimension

    [m, m] = size(A);

    Q = zeros(m, n+1);
    q_1 = b / norm(b);
    Q(:, 1) = q_1;
    
    H = zeros(n+1, n);
    
    for i=1:n
        v = A * Q(:, i);
        for j=1:i
            H(j, i) = Q(:, j)' * v;
            v = v - H(j, i) * Q(:, j);
        end
        
        H(i+1, i) = norm(v);
        Q(:, i+1) = v / H(i+1, i);
    end    
    
    H = H(1:n, :);  
end