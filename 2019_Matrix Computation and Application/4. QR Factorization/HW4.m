% MATLAB 11.3

format long

m = 50;
n = 12;
t = linspace(0, 1, m)';

A = fliplr(vander(t));
A = A(:, 1:n);   % A is 50 * 12 Matrix
b = cos(4*t);

% A\b outputs the solution of Ax = b

% (a) Formation and Solution of the normal equations
x_a = (A' * A)\(A' * b);

% (b) QR Factorization computed by Modified Gram-Schmidt Algorithm
[Q_m, R_m] = mgs(A);
x_b = (R_m)\(Q_m' * b);

% (c) QR Factorization computed by Householder Algorithm
% Notice this algorithm is Full QR Factorization
[Q_h, R_h] = householding(A);
Q_h = Q_h(:, 1:n);
x_c = (R_h)\(Q_h' * b);

% (d) QR Factorization computed by MATLAB
[Q R] = qr(A);
x_d = R\(Q' * b);

% (e) x = A\b in MATLAB
x_e = A\b;

% (f) Computed by MATLAB's SVD
[U, S, V] = svd(A);
x_f = V * (S\(U' * b));

x = [x_a, x_b, x_c, x_d, x_e, x_f]


function [Q, R] = mgs(A)
% Computes a reduced QR factorization A = Q_hat * R_hat
% using Modified Gram-Schmidt orthogonalization
%
%  Input: Matrix A having EQUAL or MORE ROWS than columns (m x n)
% Output: Decomposed matrix Q having orthornormal column vectors (m x n)
%         Decomposed triangular matrix R (n x n)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m n] = size(A);
    
    V = A;
    Q = zeros(m, n);
    R = zeros(n, n);
    
    for i = 1:n
        R(i, i) = norm(V(:, i));
        Q(:, i) = V(:, i) / R(i, i);
        
        for j = (i+1):n
            R(i, j) = Q(:, i)' * V(:, j);
            disp(R);
            V(:, j) = V(:, j) - R(i, j) * Q(:,i);
        end
    end
end

function [Q, R] = householding(A)

    [W, R] = house(A);
    Q = formQ(W);
    
end


function [W, R] = house(A)
% Computes a full QR factorization A = Q * R
% using Householder reflections
%
%  Input: Matrix A having EQUAL or MORE ROWS than columns (m x n)
% Output: Decomposed lower triangular matrix W (m x n)
%         Column of W defines the successive Householder reflections 
%         Decomposed triangular matrix R (n x n)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m n] = size(A);
    
    V = A;
    W = zeros(m, n);
    R = zeros(n, n);
    
    for k = 1:n
        x = V(k:m, k);    % x is (m-k+1)x1 vector
        
        if (x(1)>=0)
            sign = 1;
        else
            sign = -1;
        end
        
        % eye(m-k+1, 1) is (m-k+1)x1 matrix with only top entry is 1
        W(k:m, k) = sign * norm(x) * eye(m-k+1, 1) + x;
        W(k:m, k) = W(k:m, k) / norm(W(:, k));
        
        V(k:m, k:n) = V(k:m, k:n) - 2 * W(k:m, k) * mtimes(W(k:m, k)', V(k:m, k:n));
    end
    
    R = V(1:n, :);
end

function Q = formQ(W)
% Makes mxm orthogonal matrix Q with W
% Produce dummy orthogonal basis vector by reflection 
%
%  Input: Matrix W produced by house method
% Output: Orthogonal mxm matrix Q

     [m n] = size(W);
     
     Q = eye(m, m);
     
     for k = 1:m
         for j = n:-1:1
             Q(j:m, k) = Q(j:m, k) - 2 * W(j:m, j) * (W(j:m, j)' * Q(j:m, k));
         end
     end
end