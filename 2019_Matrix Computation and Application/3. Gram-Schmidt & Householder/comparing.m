function main

    format long;

    [U, X] = qr(randn(100));
    [V, X] = qr(randn(100));
    S = diag(2.^(-1:-1:-100));
     
    A = U*S*V';

    [QC, RC] = cgs(A);
    
    [QM, RM] = mgs(A);
    
    [QH, RH] = householding(A);
    
    figure(1);
   
    x = 1:100;
    y = diag(RC);
    semilogy(x, y(x), 'k');
    hold on;
    
    x = 1:100;
    y = abs(diag(RH));
    semilogy(x, y(x), 'b');
    hold on;
    
    x = 1:100;
    y = diag(RM);
    semilogy(x, y(x), 'r');

end


function [Q, R] = cgs(A)
% Computes a reduced QR factorization A = Q_hat * R_hat
% using Classical Gram-Schmidt orthogonalization
%
%  Input: Matrix A having EQUAL or MORE ROWS than columns (m x n)
% Output: Decomposed matrix Q having orthornormal column vectors (m x n)
%         Decomposed triangular matrix R (n x n)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m n] = size(A);
    
    V = zeros(m, n);
    Q = zeros(m, n);
    R = zeros(n, n);
    
    V(:, 1) = A(:, 1);
    R(1, 1) = norm(V(:, 1));
    Q(:, 1) = V(:, 1) / R(1, 1);
    
    for j = 2:n
        V(:, j) = A(:, j);
        for i = 1:(j-1)
            R(i, j) = Q(:, i)' * A(:, j);
            V(:, j) = V(:, j) - R(i, j) * Q(:, i);
        end
    R(j, j) = norm(V(:, j));
    Q(:, j) = V(:, j) / R(j, j);
    end
end

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