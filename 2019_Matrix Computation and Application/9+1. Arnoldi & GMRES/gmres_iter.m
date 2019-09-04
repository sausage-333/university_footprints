% Matlab HW 10

% Define Matrix A'
m = 200;
A = 2*eye(m) + 0.5 * randn(m)/sqrt(m);

diag_ent = zeros(m, 1);

for k=0:(m-1)
   
    theta = k * pi / (m-1);
    diag_ent(k+1) = (-2 + 2 * sin(theta)) + 1j * cos(theta);
    
end

D = diag(diag_ent);

A_prime = A + D;

eigv = eig(A_prime);
% Plot all eigenvalues of A
%plot(real(eigv), imag(eigv), '.');

%hold on;

% Define circle origin at z = 2 & radius 0.5
t = 1024;

dPhi = 2*pi/t;
phi = (-pi:dPhi:pi-dPhi);

z = 0.5 * exp(1j*phi) + 2;
C = [ real(z); imag(z) ];
% Plot Unit circle
%plot(z, 'LineWidth', 2.0)

% Define vector b
b = zeros(m, 1);
for i=1:m
    b(i, 1) = 1;
end

rel_vec = zeros(1, 11);

for i=0:10
    
    [x, rel_res] = gmres(A_prime, b, i);
    rel_vec(i+1) = rel_res;
    
end

rel_vec
semilogy(rel_vec, '*');


function [x, rel_r] = gmres(A, b, n)
% Execute GMRES using Arnoldi iteration
% with input matrix A, vector b, iteraion times n
% Input: Square matrix A
%        Vector b
%        Iteration times n
% Output: Result vector x
%         Relative residual norm rel_r
%         which is defined by norm(A*x - b) / norm(b)

    q_1 = b / norm(b);
    [Q, H] = arnoldi(A, b, n);
    
    y = (A * Q(:, 1:n)) \ b;
    x = Q(:, 1:n) * y;
    rel_r = norm(A*x - b) / norm(b);
   
end

function [Q, H] = arnoldi(A, b, n)
% Calculate Arnoldi Iteration
% with given matrix A and vector b, iteration times n
% Input: Square matrix A
%        Vector b
%        Iteration times n
% Ouput: Matrix containing n Orthonormal Basis, Q (m * n+1)
%        Upper Hessenberg Matrix H (n+1 * n)
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
    
end